Attribute VB_Name = "Calc"
Dim operationUnitStack As Stack '运算单位栈
Dim operatorStack As Stack '运算符栈
Dim operandTmp As Operation '运算数临时变量
Dim postfixExpressionQueue As Queue '后缀表达式队列
Dim runtimeStack As Stack '运算时栈 用于对后缀表达式进行计算

Public Sub init()
    'Shell (start & "calc.exe")
    Set operationUnitStack = New Stack
    Set operatorStack = New Stack
    Set operandTmp = New Operation
    operandTmp.value = 0
    operandTmp.dot = 0
    Set postfixExpressionQueue = New Queue
    Set runtimeStack = New Stack
End Sub

Public Sub addUnit(unit As Operation)
    If unit.isBackSpace() Then
        Call operationUnitStack.pop
    ElseIf unit.isC() Then
        Call operationUnitStack.clear
    ElseIf unit.isCE() Then
        While operationUnitStack.peek().isOperand()
            Call operationUnitStack.pop
        Wend
    ElseIf unit.isEqual() Then
        Call compute
    Else
        operationUnitStack.push (unit)
    End If
End Sub

Public Sub compute()
    ' 运行前检验
    If Not operatorStack.isEmpty() Then
        MsgBox "运算符栈运行前非空！"
    End If
    If Not (operandTmp.value = 0) Then
        MsgBox "运算数临时变量运行前非空！"
    End If
    If Not (operandTmp.dot = 0) Then
        MsgBox "小数点位置临时变量运行前非空！"
    End If
    If Not postfixExpressionQueue.isEmpty() Then
        MsgBox "后缀表达式队列运行前非空！"
    End If
    If Not runtimeStack.isEmpty() Then
        MsgBox "运行时栈运行前非空！"
    
    ' 将中缀表达式整理为后缀表达式
    eles = operationUnitStack.getElements()
    For Each ele In eles
        If ele.isVariable() Then
            Set newOperand = New Operation
            newOperand.value = operandTmp.value * ele.value
            newOperand.dot = operandTmp.dot + ele.dot - 1
            postfixExpressionQueue.enqueue (newOperand)
            operandTmp.value = 0
            operandTmp.dot = 0
        ElseIf ele.isOperator() Then
            Set newOperand = New Operation
            newOperand.value = operandTmp.value
            newOperand.dot = operandTmp.dot - 1
            postfixExpressionQueue.enqueue (newOperand) ' 将已经暂存的操作数装载入后缀队列
            operandTmp.value = 0
            operandTmp.dot = 0
            
            If ele.isLeftBracket() Then ' 遇到左括号强制入栈，并降低优先级
                ele.precedence = 0
                operatorStack.push (ele)
            ElseIf ele.isRightBracket() Then ' 遇到右括号操作数出栈，直到遇到左括号或栈空
                While Not (operatorStack.isEmpty() Or operatorStack.peek().isLeftBracket())
                    postfixExpressionQueue.enqueue (operatorStack.pop())
                Wend
                If Not operatorStack.isEmpty() Then
                    Call operatorStack.pop
                End If
            ElseIf operatorStack.isEmpty() Or ele.precedence > operatorStack.peek().precedence Then ' 若优先级高于栈顶运算符，则入栈
                operatorStack.push (ele)
            Else
                While Not operatorStack.isEmpty() And ele.precedence <= operatorStack.peek().precedence ' 若优先级小于等于栈顶运算符，则连续出栈，直到大于栈顶
                    postfixExpressionQueue.enqueue (operatorStack.pop())
                Wend
                opertorStack.push (ele)
            End If
        ElseIf ele.isOperand() Then
            operandTmp.value = operandTmp.value * 10 + ele.value
            If ele.isDot() Then
                operandTmp.dot = 1
            End If
            If Not (operandTmp.dot = 0) Then
                operandTmp.dot = operandTmp.dot + 1
            End If
        End If
    Next ele
    While Not operatorStack.isEmpty() ' 剩余操作符全部出栈
        postfixExpressionQueue.enqueue (operatorStack.pop())
    Wend
    
    ' 对后缀表达式进行计算 实在太麻烦了 卡住了！
    if
End Sub
