---
title: 试试做一个基于 AST 的深度学习前端～
date: 2022-06-11
category: 做点有趣的
tags:
   - TVM
   - Relay
   - Compiler
   - JIT
   - AST
---

::: tip

嘛，众所周知，为了改进神经网络搭建的表达方式，目前有两种主流的解决方案，一种是 AST-Based，一种是 Tracing-Based，前者将代码作为 Python 的一个内部 DSL 出现的，代码本身并不会由 Python 解释器执行，避免了性能及部署上的一些难题。嘛，还是很有趣的嘛，所以我们试试这个吧～

:::

<!-- more -->

## 构想一下做个什么

唔，做一个什么样的东西呢？我是想无论如何至少能够正确运行的，所以需要选一个后端来执行。然后前端的话，就类似 TorchScript 那样，写在 Python 代码里的 DSL，然后加上个装饰器把代码编译一下，之后传给后端执行就好了～

简单设计下，我的想法是至少能实现这样的一个简单的运算：

```python
def foo(a, b, c):
   d = a @ b
   e = d + c
   return e
```

唔，对于深度学习来说，不知道数据的 shape 和 dtype 可是不行的，所以我就想将这个类型信息放在 Type Hints 里，这样还能不浪费类型注解。虽说 Python 运行时会忽略它，但……反正我们又不在 Python 解释器执行运算，我们只需要能够拿到 AST 就好了，只要 AST 里有这个类型信息就好了嘛～那么加上类型信息的语法会像这样：

```python
def foo(
   a: Tensor[(2, 3), f32],
   b: Tensor[(3, 4), f32],
   c: Tensor[(2, 4), f32],
):
   d = a @ b
   e = d + c
   return e
```

嘛，很简单嘛，看起来实现并不难～

## 让我们把 AST 拿出来

拿个 AST 可太简单啦～我们直接用 Python ast 模块就好啦～

```python
from __future__ import annotations

import ast
import inspect


def foo(a, b):
    x = a + b
    return x


foo_ast = ast.parse(inspect.getsource(foo))
print(ast.dump(foo_ast))

# Module(
#     body=[
#         FunctionDef(
#             name="foo",
#             args=arguments(
#                 posonlyargs=[], args=[arg(arg="a"), arg(arg="b")], kwonlyargs=[], kw_defaults=[], defaults=[]
#             ),
#             body=[
#                 Assign(
#                     targets=[Name(id="x", ctx=Store())],
#                     value=BinOp(left=Name(id="a", ctx=Load()), op=Add(), right=Name(id="b", ctx=Load())),
#                 ),
#                 Return(value=Name(id="x", ctx=Load())),
#             ],
#             decorator_list=[],
#         )
#     ],
#     type_ignores=[],
# )
```

喏，这不就拿到了 AST 嘛～

ast 甚至有现成的 ast.NodeVisitor 让我们能够方便地通过访问者模式来遍历 AST ～

我们试试做个简单的 Printer

```python
class LevelManager:
    def __init__(self, printer: Printer):
        self.printer = printer

    def __enter__(self):
        self.printer.level += 1

    def __exit__(self, type, value, traceback):
        self.printer.level -= 1


class Printer(ast.NodeVisitor):
    def __init__(self, indent=2):
        super().__init__()
        self.indent = indent
        self.level = 0

    @property
    def indent_str(self):
        return self.indent * self.level * " "

    def visit_Module(self, node: ast.Module):
        print(f"{self.indent_str}Module(")
        for stmt in node.body:
            with LevelManager(self):
                self.visit(stmt)  # type: ignore
        print(f"{self.indent_str})")

    def visit_FunctionDef(self, node: ast.FunctionDef):
        print(f"{self.indent_str}FunctionDef(")
        with LevelManager(self):
            print(f"{self.indent_str}{node.name}")
        with LevelManager(self):
            self.visit(node.args)
        for stmt in node.body:
            with LevelManager(self):
                self.visit(stmt)  # type: ignore
        print(f"{self.indent_str})")

    def visit_Assign(self, node: ast.Assign):
        print(f"{self.indent_str}Assign(")
        for lhs in node.targets:
            with LevelManager(self):
                self.visit(lhs)
        with LevelManager(self):
            self.visit(node.value)
        print(f"{self.indent_str})")

    def visit_Name(self, node: ast.Name):
        print(f"{self.indent_str}Name(")
        with LevelManager(self):
            print(f"{self.indent_str}{node.id}")
        print(f"{self.indent_str})")

    def visit_BinOp(self, node: ast.BinOp):
        print(f"{self.indent_str}BinOp(")
        with LevelManager(self):
            self.visit(node.left)
            self.visit(node.right)
        print(f"{self.indent_str})")

    def visit_Return(self, node: ast.Return):
        print(f"{self.indent_str}Return(")
        with LevelManager(self):
            self.visit(node.value)  # type: ignore
        print(f"{self.indent_str})")

    def visit_arguments(self, node: ast.arguments):
        print(f"{self.indent_str}arguments(")
        for arg in node.args:
            with LevelManager(self):
                self.visit(arg)
        print(f"{self.indent_str})")

    def visit_arg(self, node: ast.arg):
        print(f"{self.indent_str}arg(")
        with LevelManager(self):
            print(f"{self.indent_str}{node.arg}")
        print(f"{self.indent_str})")


printer = Printer()
printer.visit(foo_ast)
```

emmm，很好写哒～就针对各个 Node 分别处理就好啦，虽然打印的不太好看，但总归是能用～

不过为了简单，这里没实现所有 Node 的 visit 函数，毕竟我们也不是做一个完整的 Python 语法解释器～事实上我们只是实现个 Python 语法子集就好啦～

虽说这样写已经足够简单了，但在处理一些实际问题时还是会有点麻烦，之后我们在实际遍历语法树时候会用另外一个库，不过用法基本一致啦～

## 了解下 TVM Relay

TVM 应该算是目前使用最广泛的深度学习编译器了吧，TVM 是一个完整的端到端的深度学习编译器，也就是说，我们只需要给他一个给定深度学习框架的模型，它就能对该模型进行编译到目标机器后端。

![](../img/lets-make-an-ast-based-deeplearning-frontend/tvm-dyn-workflow.svg)

TVM 的编译栈如上图所示，总的来说，它分为三级，首先是各种前端转换为统一的 Relay IR（Graph 级），之后可以递降到 TIR（Tensor 级），最后编译到目标机器代码，在 TVM runtime 上可执行。

后面的我们都不需要关心，我们只关心通过前端可以编译到的统一表示 Relay IR 就好啦～

这要如何实现呢？

就以刚刚这个例子来说

```python
def foo(
   a: Tensor[(2, 3), f32],
   b: Tensor[(3, 4), f32],
   c: Tensor[(2, 4), f32],
):
   d = a @ b
   e = d + c
   return e
```

我们只需要这样～

```python
import tvm
from tvm import relay
import numpy as np
from tvm.contrib import graph_executor

target = "llvm"
dtype = "float32"
ret_shape = (2, 4)

a_var = relay.var("a", shape=(2, 3), dtype=dtype)
b_var = relay.var("b", shape=(3, 4), dtype=dtype)
c_var = relay.var("c", shape=(2, 4), dtype=dtype)
d_var = relay.nn.matmul(a_var, b_var)
e_var = relay.add(d_var, c_var)


foo = relay.Function([a_var, b_var, c_var], e_var, ret_type=relay.TensorType(ret_shape, dtype))
mod = tvm.IRModule.from_expr(foo)

print(mod)
# def @main(%a: Tensor[(2, 3), float32], %b: Tensor[(3, 4), float32], %c: Tensor[(2, 4), float32]) -> Tensor[(2, 4), float32] {
#   %0 = nn.matmul(%a, %b, units=None);
#   add(%0, %c)
# }
```

输出的是 Relay IR 的文本形式～

Relay 提供了一系列比较常见的算子 API，比如 relay.add、relay.sub 啦～神经网络相关的大多在 relay.nn 下，所以搭建模型就非常简单啦～不过要注意的是，由于 Relay 的算子本身大多比较精简，功能较为单一，所以可能一个算子需要多个 Relay 算子组合实现，比如 Relay 的卷积算子是不带 bias 的，因此需要额外组合 bias_add 算子来实现完整的卷积操作～

我们进一步编译并传入些数据，让它 run 起来～

```python
with tvm.transform.PassContext(opt_level=3):
    lib = relay.build(mod, target)

dev = tvm.device(str(target), 0)
module = graph_executor.GraphModule(lib["default"](dev))

dtype = "float32"
a = np.random.rand(2, 3).astype(dtype)
b = np.random.rand(3, 4).astype(dtype)
c = np.random.rand(2, 4).astype(dtype)
module.set_input("a", a)
module.set_input("b", b)
module.set_input("c", c)
module.run()

tvm_output = module.get_output(0, tvm.nd.empty(ret_shape)).numpy()
print("TVM output:")
print(tvm_output)
# TVM output:
# [[0.27161965 1.1484863  0.7768694  0.26964152]
#  [0.48174655 2.10517    1.8035419  1.4846797 ]]
```

唔，我们和 numpy 的对比下～

```python
def foo_np(a, b, c):
    return a @ b + c


np_output = foo_np(a, b, c)
print("Numpy output:")
print(np_output)

assert np.allclose(tvm_output, np_output)
# Numpy output:
# [[0.27161965 1.1484863  0.7768694  0.26964152]
#  [0.48174655 2.10517    1.8035419  1.4846797 ]]
```

嘿嘿，当然是一～模～一～样～啦～

## 循着 AST 逐步转换

很好，我们已经能够成功对 AST 进行遍历，也能够根据一段代码描述来编译成可运行的 Relay IR 并且执行，那么剩下的就是将两者组合在一起啦，也就是主要的编译工作～

具体如何实现，当然就是对 AST 进行遍历，遍历过程中利用 Relay API 构建 Relay IR 就好啦～

唔，为了更加方便地对类型提示信息进行转换，这里使用了 Relay 在使用的 [synr](https://synr.readthedocs.io/en/latest/) 作为内建 ast 模块的替代。

用法和 ast 模块基本一致啦

```python
from __future__ import annotations

import synr


def foo(a, b):
    x = a + b
    return x


foo_ast = synr.to_ast(foo, synr.PrinterDiagnosticContext())
print(foo_ast)
```

如果想要修改解析过程中的行为，只需要 `synr.to_ast(foo, synr.PrinterDiagnosticContext(), parser)` 即可，parser 是一个继承了 `synr.Transformer` 的类实例～

如果你发现你的 synr 不支持 `@` 或者其他的运算符，可以参考 [synr 的 PR24](https://github.com/octoml/synr/pull/24) 自己加一下～

唔，因为一个 `Transformer` 写起来蛮长的，且我写的还不够优雅，整体也可以参考 [relay parser](https://github.com/apache/tvm/blob/main/python/tvm/script/parser.py) 的实现，所以就不展示了，不过整体的思路就是把代码编译成利用 Relay API 构建的形式啦，很简单的。比如参数表里的变量都用 relay.var 构造下，当整个函数编译完就用 relay.Function 构造整个函数就好啦～

当然，因为我们是在编译，符号表的管理是不可或缺的，但这已经是非常基础的内容了，没啥说的必要。不过值得一提的是，由于所有算子都以函数形式呈现（如 `conv2d(input, weights, bias, kernel_size, strides)`），所以这要求在编译之前把所有算子注册在符号表之中～当然，注册时候就已经要把算子转换逻辑写好～

## 加个装饰器，整个 JIT

嘛，等我们把 AST 编译成 Relay IR 后，就可以运行什么的啦～

但现在的代码看起来可能像这样

```python
def foo(
   a: Tensor[(2, 3), f32],
   b: Tensor[(3, 4), f32],
   c: Tensor[(2, 4), f32],
):
   d = a @ b
   e = d + c
   return e

foo_transformed = synr.to_ast(foo, synr.PrinterDiagnosticContext(), parser)

with tvm.transform.PassContext(opt_level=3):
    lib = relay.build(foo_transformed, target)

dev = tvm.device(str(target), 0)
module = graph_executor.GraphModule(lib["default"](dev))

dtype = "float32"
a = np.random.rand(2, 3).astype(dtype)
b = np.random.rand(3, 4).astype(dtype)
c = np.random.rand(2, 4).astype(dtype)
module.set_input("a", a)
module.set_input("b", b)
module.set_input("c", c)
module.run()

tvm_output = module.get_output(0, tvm.nd.empty(ret_shape)).numpy()
```

如果我们能实现直接 `foo(a, b, c)` 就能直接得到结果就好了嘛～这也好说，我们加个装饰器就好了嘛～

我们的目标是

```python
@function
def foo(
   a: Tensor[(2, 3), f32],
   b: Tensor[(3, 4), f32],
   c: Tensor[(2, 4), f32],
):
   d = a @ b
   e = d + c
   return e

tvm_output = foo(a, b, c)
```

这很简单的～把 TVM 那些逻辑放到装饰器里，就好了嘛，下面实现下这个装饰器～

```python
class function:
    def __init__(self, dsl_func: Callable) -> None:
        parser = TinyNnParser()
        relay_func = synr.to_ast(dsl_func, synr.PrinterDiagnosticContext(), parser)
        target = "llvm"
        mod = tvm.IRModule.from_expr(relay_func)

        with tvm.transform.PassContext(opt_level=3):
            lib = relay.build(mod, target)

        dev = tvm.device(str(target), 0)
        self.module = graph_executor.GraphModule(lib["default"](dev))

        self.params = relay_func.params
        self.dtype = relay_func.ret_type.dtype
        self.shape = relay_func.ret_type.shape
        self.ret_type = relay_func.ret_type

        self.__name__ = dsl_func.__name__
        self.__qualname__ = dsl_func.__qualname__
        self.__dsl_code__ = inspect.getsource(dsl_func)
        self.__relay_code__ = relay_func

    def __call__(self, *args):
        assert len(args) == len(self.params)
        for arg, param in zip(args, self.params):
            self.module.set_input(param.name_hint, arg)
        self.module.run()
        return self.module.get_output(0, tvm.nd.empty(self.shape)).numpy()
```

嘿嘿，现在稍微像点样子了，结果就不对比了，和之前应该是一样的～

emmmm，不过要说这有什么用呢……<span title="比如说水个毕设啥的">比如说……</span>，啊，好像确实没啥用……不过只是一个尝试啦，不要考虑什么实用性啥的啦～

唔，完整的代码这次也不放出来了，因为实在写的不咋样 ( •̥́ ˍ •̀ू )

## References

1. [针对神经网络的编译器和传统编译器的区别和联系是什么？](https://www.zhihu.com/question/396105855/answer/1868408680)
2. [ast — Abstract Syntax Trees](https://docs.python.org/3/library/ast.html)
3. [TVM Python API - tvm.relay](https://tvm.apache.org/docs/reference/api/python/relay/index.html)
4. [Synr: A stable AST for python](https://synr.readthedocs.io/en/latest/)
5. [TVM Relay parser 源码](https://github.com/apache/tvm/blob/main/python/tvm/script/parser.py)
