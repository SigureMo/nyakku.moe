/*
# Tree Traversals Again
An inorder binary tree traversal can be implemented in a non-recursive way with a stack. For example,
suppose that when a 6-node binary tree (with the keys numbered from 1 to 6) is traversed, the stack
operations are: push(1); push(2); push(3); pop(); pop(); push(4); pop(); pop(); push(5); push(6); pop();
pop(). Then a unique binary tree (shown in Figure 1) can be generated from this sequence of operations.
 Your task is to give the postorder traversal sequence of this tree.
# Specification:
IN:
Each input file contains one test case. For each case, the first line contains a positive integer N (≤30)
 which is the total number of nodes in a tree (and hence the nodes are numbered from 1 to N). Then 2N lines
 follow, each describes a stack operation in the format: "Push X" where X is the index of the node being
 pushed onto the stack; or "Pop" meaning to pop one node from the stack.
OUT:
For each test case, print the postorder traversal sequence of the corresponding tree in one line. A solution
is guaranteed to exist. All the numbers must be separated by exactly one space, and there must be no extra
space at the end of the line.
# Sample:
IN:
6
Push 1
Push 2
Push 3
Pop
Pop
Push 4
Pop
Pop
Push 5
Push 6
Pop
Pop
OUT:
3 4 2 6 5 1

*/

"use strict";

const readline = require("readline");
const rl = readline.createInterface({
  input: process.stdin,
  output: process.stdout
});

var inputs = [];
var lineNum = 0;
var nodeNum;
var stack = [];
var list = [];

function node(num) {
  this.num = num;
  this.left = null;
  this.right = null;
}

rl.on("line", function(line) {
  if (lineNum === 0) {
    nodeNum = parseInt(line);
  } else if (lineNum <= nodeNum * 2) {
    // console.log(inputs);
    inputs.push(line);
    if (lineNum === nodeNum * 2) {
      dispose();
      rl.close();
    }
  }
  lineNum++;
});

rl.on("close", function() {
  process.exit(0);
});

function dispose() {
  var n;
  var flag = 0;
  var root;
  var pointer = null;
  for (var line in inputs) {
    if (inputs[line].split(" ")[0] === "Push") {
      n = new node(inputs[line].split(" ")[1]);
      // console.log(pointer);
      if (!flag) {
        root = n;
      }
      flag = 1;
      if (pointer) {
        if (!pointer.left) {
          pointer.left = n;
        } else {
          pointer.right = n;
        }
      }
      pointer = n;
      stack.push(n);
    } else {
      pointer = stack.pop();
    }
  }
  postOrderTraversal(root);

  console.log(list.join(" "));
}

function postOrderTraversal(tree) {
  if (tree) {
    postOrderTraversal(tree.left);
    postOrderTraversal(tree.right);
    list.push(tree.num);
  }
}
