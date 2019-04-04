VERSION 5.00
Begin VB.Form Calculator 
   Caption         =   "Calc"
   ClientHeight    =   7560
   ClientLeft      =   120
   ClientTop       =   465
   ClientWidth     =   13680
   KeyPreview      =   -1  'True
   LinkTopic       =   "Form1"
   ScaleHeight     =   7560
   ScaleWidth      =   13680
   StartUpPosition =   3  '窗口缺省
   Begin VB.CommandButton Key_MMinus 
      Caption         =   "M-"
      Height          =   375
      Left            =   7920
      TabIndex        =   45
      Top             =   1560
      Width           =   735
   End
   Begin VB.CommandButton Key_MPlus 
      Caption         =   "M+"
      Height          =   375
      Left            =   6960
      TabIndex        =   44
      Top             =   1560
      Width           =   735
   End
   Begin VB.CommandButton Key_MR 
      Caption         =   "MR"
      Height          =   495
      Left            =   6120
      TabIndex        =   43
      Top             =   1440
      Width           =   615
   End
   Begin VB.CommandButton Key_MC 
      Caption         =   "MC"
      Height          =   375
      Left            =   5160
      TabIndex        =   42
      Top             =   1440
      Width           =   615
   End
   Begin VB.CommandButton Key_MS 
      Caption         =   "MS"
      Height          =   375
      Left            =   8760
      TabIndex        =   41
      Top             =   1560
      Width           =   735
   End
   Begin VB.TextBox Memory 
      Height          =   735
      Left            =   7440
      Locked          =   -1  'True
      TabIndex        =   39
      Top             =   600
      Width           =   1095
   End
   Begin VB.CommandButton Clear_History_Button 
      Caption         =   "Clear"
      Height          =   495
      Left            =   11880
      TabIndex        =   37
      Top             =   6360
      Width           =   975
   End
   Begin VB.ListBox History 
      Height          =   6000
      ItemData        =   "calc.frx":0000
      Left            =   9720
      List            =   "calc.frx":0002
      TabIndex        =   36
      Top             =   960
      Width           =   3375
   End
   Begin VB.CommandButton Key_Power 
      Caption         =   "x^y"
      Height          =   615
      Left            =   840
      Style           =   1  'Graphical
      TabIndex        =   35
      Top             =   2400
      Width           =   615
   End
   Begin VB.CommandButton Key_Exp 
      Caption         =   "e"
      Height          =   495
      Left            =   840
      Style           =   1  'Graphical
      TabIndex        =   34
      Top             =   5040
      Width           =   615
   End
   Begin VB.CommandButton Key_PI 
      Caption         =   "π"
      Height          =   615
      Left            =   960
      Style           =   1  'Graphical
      TabIndex        =   33
      Top             =   6000
      Width           =   615
   End
   Begin VB.CommandButton Key_Mod 
      Caption         =   "Mod"
      Height          =   615
      Left            =   3840
      Style           =   1  'Graphical
      TabIndex        =   32
      Top             =   3960
      Width           =   615
   End
   Begin VB.CommandButton Key_Ln 
      Caption         =   "ln"
      Height          =   615
      Left            =   1680
      Style           =   1  'Graphical
      TabIndex        =   31
      Top             =   4920
      Width           =   855
   End
   Begin VB.CommandButton Key_Log 
      Caption         =   "log"
      Height          =   615
      Left            =   1680
      Style           =   1  'Graphical
      TabIndex        =   30
      Top             =   4080
      Width           =   735
   End
   Begin VB.CommandButton Key_ArcTan 
      Caption         =   "arctan"
      Height          =   495
      Left            =   3600
      Style           =   1  'Graphical
      TabIndex        =   29
      Top             =   3240
      Width           =   855
   End
   Begin VB.CommandButton Key_ArcCos 
      Caption         =   "arccos"
      Height          =   735
      Left            =   2880
      Style           =   1  'Graphical
      TabIndex        =   28
      Top             =   3120
      Width           =   615
   End
   Begin VB.CommandButton Key_ArcSin 
      Caption         =   "arcsin"
      Height          =   735
      Left            =   1680
      Style           =   1  'Graphical
      TabIndex        =   27
      Top             =   3120
      Width           =   975
   End
   Begin VB.CommandButton Key_Tan 
      Caption         =   "tan"
      Height          =   615
      Left            =   3840
      Style           =   1  'Graphical
      TabIndex        =   26
      Top             =   2400
      Width           =   495
   End
   Begin VB.CommandButton Key_Cos 
      Caption         =   "cos"
      Height          =   615
      Left            =   2880
      Style           =   1  'Graphical
      TabIndex        =   25
      Top             =   2400
      Width           =   615
   End
   Begin VB.CommandButton Key_Sin 
      Caption         =   "sin"
      Height          =   615
      Left            =   1680
      Style           =   1  'Graphical
      TabIndex        =   24
      Top             =   2400
      Width           =   975
   End
   Begin VB.CommandButton Key_RightBracket 
      Caption         =   ")"
      Height          =   855
      Left            =   3600
      Style           =   1  'Graphical
      TabIndex        =   23
      Top             =   5880
      Width           =   855
   End
   Begin VB.CommandButton Key_LeftBracket 
      Caption         =   "("
      Height          =   735
      Left            =   2640
      Style           =   1  'Graphical
      TabIndex        =   22
      Top             =   6000
      Width           =   855
   End
   Begin VB.TextBox Result 
      Height          =   855
      Left            =   600
      Locked          =   -1  'True
      TabIndex        =   21
      Top             =   1200
      Width           =   4335
   End
   Begin VB.TextBox Expression_Box 
      Height          =   855
      Left            =   600
      Locked          =   -1  'True
      TabIndex        =   20
      Top             =   120
      Width           =   4335
   End
   Begin VB.CommandButton Key_Divide 
      Caption         =   "÷"
      Height          =   615
      Left            =   8160
      Style           =   1  'Graphical
      TabIndex        =   19
      Top             =   2040
      Width           =   855
   End
   Begin VB.CommandButton Key_Multiply 
      Caption         =   "×"
      Height          =   855
      Left            =   8280
      Style           =   1  'Graphical
      TabIndex        =   18
      Top             =   2880
      Width           =   735
   End
   Begin VB.CommandButton Key_Minus 
      Caption         =   "-"
      Height          =   615
      Left            =   8160
      Style           =   1  'Graphical
      TabIndex        =   17
      Top             =   3840
      Width           =   975
   End
   Begin VB.CommandButton Key_Plus 
      Caption         =   "+"
      Height          =   735
      Left            =   8160
      Style           =   1  'Graphical
      TabIndex        =   16
      Top             =   4800
      Width           =   975
   End
   Begin VB.CommandButton Key_Equal 
      Caption         =   "="
      Height          =   975
      Left            =   8160
      Style           =   1  'Graphical
      TabIndex        =   15
      Top             =   5880
      Width           =   855
   End
   Begin VB.CommandButton Key_Back 
      Caption         =   "←"
      Height          =   800
      Left            =   6960
      Style           =   1  'Graphical
      TabIndex        =   14
      Top             =   2040
      Width           =   800
   End
   Begin VB.CommandButton Key_C 
      Caption         =   "C"
      Height          =   800
      Left            =   5880
      Style           =   1  'Graphical
      TabIndex        =   13
      Top             =   2040
      Width           =   800
   End
   Begin VB.CommandButton Key_CE 
      Caption         =   "CE"
      Height          =   800
      Left            =   4680
      Style           =   1  'Graphical
      TabIndex        =   12
      Top             =   2040
      Width           =   800
   End
   Begin VB.CommandButton Key_Dot 
      Caption         =   "."
      Height          =   800
      Left            =   7080
      Style           =   1  'Graphical
      TabIndex        =   11
      Top             =   5880
      Width           =   800
   End
   Begin VB.CommandButton Key_0 
      Caption         =   "0"
      Height          =   800
      Left            =   5760
      Style           =   1  'Graphical
      TabIndex        =   10
      Top             =   6000
      Width           =   800
   End
   Begin VB.CommandButton Key_Negative 
      Caption         =   "±"
      Height          =   800
      Left            =   4680
      Style           =   1  'Graphical
      TabIndex        =   9
      Top             =   5880
      Width           =   800
   End
   Begin VB.CommandButton Key_9 
      Caption         =   "9"
      Height          =   800
      Left            =   6960
      Style           =   1  'Graphical
      TabIndex        =   8
      Top             =   2880
      Width           =   800
   End
   Begin VB.CommandButton Key_8 
      Caption         =   "8"
      Height          =   800
      Left            =   5880
      Style           =   1  'Graphical
      TabIndex        =   7
      Top             =   2880
      Width           =   800
   End
   Begin VB.CommandButton Key_7 
      Caption         =   "7"
      Height          =   800
      Left            =   4680
      Style           =   1  'Graphical
      TabIndex        =   6
      Top             =   3000
      Width           =   800
   End
   Begin VB.CommandButton Key_6 
      Caption         =   "6"
      Height          =   855
      Left            =   6840
      Style           =   1  'Graphical
      TabIndex        =   5
      Top             =   3720
      Width           =   800
   End
   Begin VB.CommandButton Key_5 
      Caption         =   "5"
      Height          =   800
      Left            =   5880
      Style           =   1  'Graphical
      TabIndex        =   4
      Top             =   3720
      Width           =   800
   End
   Begin VB.CommandButton Key_4 
      Caption         =   "4"
      Height          =   800
      Left            =   4680
      Style           =   1  'Graphical
      TabIndex        =   3
      Top             =   3720
      Width           =   800
   End
   Begin VB.CommandButton Key_3 
      Caption         =   "3"
      Height          =   800
      Left            =   6840
      Style           =   1  'Graphical
      TabIndex        =   2
      Top             =   4800
      Width           =   800
   End
   Begin VB.CommandButton Key_2 
      Caption         =   "2"
      Height          =   800
      Left            =   5760
      Style           =   1  'Graphical
      TabIndex        =   1
      Top             =   4800
      Width           =   800
   End
   Begin VB.CommandButton Key_1 
      Caption         =   "1"
      Height          =   800
      Left            =   4680
      Style           =   1  'Graphical
      TabIndex        =   0
      Top             =   4800
      Width           =   800
   End
   Begin VB.Label Memory_Label 
      Caption         =   "Memory"
      Height          =   255
      Left            =   7560
      TabIndex        =   40
      Top             =   240
      Width           =   855
   End
   Begin VB.Label History_Label 
      Caption         =   "History"
      Height          =   375
      Left            =   9840
      TabIndex        =   38
      Top             =   360
      Width           =   1335
   End
End
Attribute VB_Name = "Calculator"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Declare Function compute Lib "calc.dll" (ByVal Expression As String) As Single
Dim Expression As String
Dim Operands As String
Dim Operators As String

Private Sub Form_Load()
    'Shell (start & "calc.exe")
    Operands = "1234567890."
    Operators = "+-*/()^"
End Sub

' 判断是操作数还是操作符
Public Function isOperand(c As String) As Boolean
    If InStr(1, Operands, c) Then
        isOperand = True
    Else
        isOperand = False
    End If
End Function

Public Function isOperator(c As String) As Boolean
    If InStr(1, Operators, c) Then
        isOperator = True
    Else
        isOperator = False
    End If
End Function

' 快捷键
Private Sub Form_KeyPress(KeyAscii As Integer)
    Select Case KeyAscii
        Case 8
            Call Key_Back_Click
        Case 13
            Call Key_Equal_Click
        Case 27
            Call Key_C_Click
        Case 37
            Call Key_Mod_Click
        Case 40
            Call Key_LeftBracket_Click
        Case 41
            Call Key_RightBracket_Click
        Case 42
            Call Key_Multiply_Click
        Case 43
            Call Key_Plus_Click
        Case 45
            Call Key_Minus_Click
        Case 46
            Call Key_Dot_Click
        Case 47
            Call Key_Divide_Click
        Case 48
            Call Key_0_Click
        Case 49
            Call Key_1_Click
        Case 50
            Call Key_2_Click
        Case 51
            Call Key_3_Click
        Case 52
            Call Key_4_Click
        Case 53
            Call Key_5_Click
        Case 54
            Call Key_6_Click
        Case 55
            Call Key_7_Click
        Case 56
            Call Key_8_Click
        Case 57
            Call Key_9_Click
        Case 58
            Call Key_0_Click
        Case 61
            Call Key_Equal_Click
        Case 79
            Call Key_ArcCos_Click
        Case 83
            Call Key_ArcSin_Click
        Case 84
            Call Key_ArcTan_Click
        Case 94
            Call Key_Power_Click
        Case 101
            Call Key_Exp_Click
        Case 108
            Call Key_Log_Click
        Case 110
            Call Key_Ln_Click
        Case 111
            Call Key_Cos_Click
        Case 112
            Call Key_PI_Click
        Case 115
            Call Key_Sin_Click
        Case 116
            Call Key_Tan_Click
        Case 127
            Call Key_CE_Click
    End Select
    
    'MsgBox KeyAscii
End Sub

' 按键变色
Private Sub Press_Key(Key)
    ' 记得设置 Key.Style 为 1
    Key.BackColor = &H80000010
    Delay (0.1)
    Key.BackColor = &H8000000F
End Sub

' sleep
Public Sub Delay(PauseTime As Single)
    Dim Start As Single
    Start = Timer
    Do While Timer < Start + PauseTime
        DoEvents
    Loop
End Sub

' 显示表达式
Public Sub Show_Expression()
    Expression_Box.Text = ""
    i = 0
    While i < Len(Expression)
        c = Mid(Expression, i + 1, 1)
        If c = "s" Then
            Expression_Box.Text = Expression_Box.Text & "sin"
        ElseIf c = "o" Then
            Expression_Box.Text = Expression_Box.Text & "cos"
        ElseIf c = "t" Then
            Expression_Box.Text = Expression_Box.Text & "tan"
        ElseIf c = "S" Then
            Expression_Box.Text = Expression_Box.Text & "arcsin"
        ElseIf c = "O" Then
            Expression_Box.Text = Expression_Box.Text & "arccos"
        ElseIf c = "T" Then
            Expression_Box.Text = Expression_Box.Text & "arctan"
        ElseIf c = "l" Then
            Expression_Box.Text = Expression_Box.Text & "log"
        ElseIf c = "n" Then
            Expression_Box.Text = Expression_Box.Text & "ln"
        ElseIf c = "%" Then
            Expression_Box.Text = Expression_Box.Text & "Mod"
        ElseIf c = "p" Then
            Expression_Box.Text = Expression_Box.Text & "π"
        ElseIf c = "e" Then
            Expression_Box.Text = Expression_Box.Text & "e"
        Else
            Expression_Box.Text = Expression_Box.Text & c
        End If
        i = i + 1
    Wend
End Sub

' 按键回调

' Operands
Private Sub Key_0_Click()
    Call Press_Key(Key_0)
    Expression = Expression & 0
    Call Show_Expression
End Sub

Private Sub Key_1_Click()
    Call Press_Key(Key_1)
    Expression = Expression & 1
    Call Show_Expression
End Sub

Private Sub Key_2_Click()
    Call Press_Key(Key_2)
    Expression = Expression & 2
    Call Show_Expression
End Sub

Private Sub Key_3_Click()
    Call Press_Key(Key_3)
    Expression = Expression & 3
    Call Show_Expression
End Sub

Private Sub Key_4_Click()
    Call Press_Key(Key_4)
    Expression = Expression & 4
    Call Show_Expression
End Sub

Private Sub Key_5_Click()
    Call Press_Key(Key_5)
    Expression = Expression & 5
    Call Show_Expression
End Sub

Private Sub Key_6_Click()
    Call Press_Key(Key_6)
    Expression = Expression & 6
    Call Show_Expression
End Sub

Private Sub Key_7_Click()
    Call Press_Key(Key_7)
    Expression = Expression & 7
    Call Show_Expression
End Sub

Private Sub Key_8_Click()
    Call Press_Key(Key_8)
    Expression = Expression & 8
    Call Show_Expression
End Sub

Private Sub Key_9_Click()
    Call Press_Key(Key_9)
    Expression = Expression & 9
    Call Show_Expression
End Sub

Private Sub Key_Dot_Click()
    Call Press_Key(Key_Dot)
    Expression = Expression & "."
    Call Show_Expression
End Sub



' Operators

Private Sub Key_Plus_Click()
    Call Press_Key(Key_Plus)
    Expression = Expression & "+"
    Call Show_Expression
End Sub

Private Sub Key_Minus_Click()
    Call Press_Key(Key_Minus)
    Expression = Expression & "-"
    Call Show_Expression
End Sub

Private Sub Key_Multiply_Click()
    Call Press_Key(Key_Multiply)
    Expression = Expression & "*"
    Call Show_Expression
End Sub

Private Sub Key_Divide_Click()
    Call Press_Key(Key_Divide)
    Expression = Expression & "/"
    Call Show_Expression
End Sub

Private Sub Key_Negative_Click()
    Call Press_Key(Key_Negative)
    Expression = Expression & "-"
    Call Show_Expression
End Sub

Private Sub Key_Power_Click()
    Call Press_Key(Key_Power)
    Expression = Expression & "^"
    Call Show_Expression
End Sub

Private Sub Key_LeftBracket_Click()
    Call Press_Key(Key_LeftBracket)
    Expression = Expression & "("
    Call Show_Expression
End Sub

Private Sub Key_RightBracket_Click()
    Call Press_Key(Key_RightBracket)
    Expression = Expression & ")"
    Call Show_Expression
End Sub

Private Sub Key_Sin_Click()
    Call Press_Key(Key_Sin)
    Expression = Expression & "s"
    Call Show_Expression
End Sub

Private Sub Key_Cos_Click()
    Call Press_Key(Key_Cos)
    Expression = Expression & "o"
    Call Show_Expression
End Sub

Private Sub Key_Tan_Click()
    Call Press_Key(Key_Tan)
    Expression = Expression & "t"
    Call Show_Expression
End Sub

Private Sub Key_ArcSin_Click()
    Call Press_Key(Key_ArcSin)
    Expression = Expression & "S"
    Call Show_Expression
End Sub

Private Sub Key_ArcCos_Click()
    Call Press_Key(Key_ArcCos)
    Expression = Expression & "O"
    Call Show_Expression
End Sub

Private Sub Key_ArcTan_Click()
    Call Press_Key(Key_ArcSin)
    Expression = Expression & "T"
    Call Show_Expression
End Sub

Private Sub Key_Log_Click()
    Call Press_Key(Key_Log)
    Expression = Expression & "l"
    Call Show_Expression
End Sub

Private Sub Key_Ln_Click()
    Call Press_Key(Key_Ln)
    Expression = Expression & "n"
    Call Show_Expression
End Sub

Private Sub Key_Mod_Click()
    Call Press_Key(Key_Mod)
    Expression = Expression & "%"
    Call Show_Expression
End Sub

Private Sub Key_PI_Click()
    Call Press_Key(Key_PI)
    Expression = Expression & "p"
    Call Show_Expression
End Sub

Private Sub Key_Exp_Click()
    Call Press_Key(Key_Exp)
    Expression = Expression & "e"
    Call Show_Expression
End Sub

' 特殊操作符
Private Sub Key_Back_Click()
    Call Press_Key(Key_Back)
    If Not Expression = "" Then
        Expression = Mid(Expression, 1, Len(Expression) - 1)
    End If
    Call Show_Expression
End Sub

Private Sub Key_C_Click()
    Call Press_Key(Key_C)
    Expression = ""
    Call Show_Expression
End Sub

Private Sub Key_CE_Click()
    Call Press_Key(Key_CE)
    For i = Len(Expression) To 1 Step -1
        If isOperand(Mid(Expression, Len(Expression), 1)) Then
            Expression = Mid(Expression, 1, Len(Expression) - 1)
        Else
            Exit For
        End If
    Next i
    Call Show_Expression
End Sub

Private Sub Key_Equal_Click()
    Call Press_Key(Key_Equal)
    Expression = Expression & "="
    Result.Text = compute(Expression)
    Expression = ""
    History.AddItem (Expression_Box.Text & "=" & Result.Text)
End Sub

' Clear History
Private Sub Clear_History_Button_Click()
    Call History.Clear
End Sub

' About Memory （只针对 Result， 不针对 Expression）
Private Sub Key_MS_Click()
    If IsNumeric(Result.Text) Then
        Memory.Text = Result.Text
    End If
End Sub

Private Sub Key_MC_Click()
    Memory.Text = ""
End Sub

Private Sub Key_MR_Click()
    Expression = Expression & Memory.Text
    Call Show_Expression
End Sub

Private Sub Key_MPlus_Click()
    Memory.Text = Val(Memory.Text) + Val(Result.Text)
End Sub

Private Sub Key_MMinus_Click()
    Memory.Text = Val(Memory.Text) - Val(Result.Text)
End Sub
