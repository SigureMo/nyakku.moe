VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "Operation"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Public opType As String '操作类型 操作数、操作符、变量
' 运算符专用
Public details As String '详情 比如括号等等
Public text As String '显示文本
Public precedence As Integer '优先级
Public varNum As Integer 'n 元运算符
' 运算数 变量专用
Public value As Integer '常量、变量值
Public dot As Integer ' 小数点位置

Public Function isOperator() As Boolean
    isOperator = (opType = "operator")
End Function

Public Function isOperand() As Boolean
    isOperand = (opType = "operand")
End Function

Public Function isVariable() As Boolean
    isOperand = (opType = "variable")
End Function

' 不加和到运算临时变量

Public Function isDot() As Boolean
    isOperand = (details = "dot")
End Function

' 不入后缀表达式队列部分

Public Function isLeftBracket() As Boolean
    isOperand = (details = "leftBracket")
End Function

Public Function isRightBracket() As Boolean
    isOperand = (details = "rightBracket")
End Function

' 不入运算单位栈部分

Public Function isEqual() As Boolean
    isOperand = (details = "equal")
End Function

Public Function isCE() As Boolean
    isOperand = (details = "CE")
End Function

Public Function isC() As Boolean
    isOperand = (details = "C")
End Function

Public Function isBackSpace() As Boolean
    isOperand = (details = "backspace")
End Function

' 单双目运算符

Public Function isUnaryOperator() As Boolean
    isUnaryOperator = (varNum = 1)
End Function

Public Function isBinaryOperator() As Boolean
    isBinaryOperator = (varNum = 2)
End Function

' 整型 or 实型

Public Function isInt() As Boolean
    isInt = (dot = 0)
End Function
