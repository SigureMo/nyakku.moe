VERSION 5.00
Begin VB.Form Calculator 
   Caption         =   "Calc"
   ClientHeight    =   7560
   ClientLeft      =   120
   ClientTop       =   465
   ClientWidth     =   9315
   KeyPreview      =   -1  'True
   LinkTopic       =   "Form1"
   ScaleHeight     =   7560
   ScaleWidth      =   9315
   StartUpPosition =   3  '窗口缺省
   Begin VB.TextBox Text1 
      Height          =   855
      Left            =   720
      TabIndex        =   20
      Text            =   "Text1"
      Top             =   360
      Width           =   2415
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
End
Attribute VB_Name = "Calculator"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Dim operationUnitStack As Stack '运算单位栈
Dim operatorStack As Stack '运算符栈
Dim operandTmp As Integer '运算数临时变量 默认 integer ，当出现小数点 Redim 为 single
Dim postfixExpressionQueue As Queue '后缀表达式队列
Dim runtimeStack As Stack '运算时栈 用于对后缀表达式进行计算

Private Sub Form_Load()
    'Shell (start & "calc.exe")
    Set operationUnitStack = New Stack
    Set operatorStack = New Stack
    operandTmp = 0
    Set postfixExpressionQueue = New Queue
    Set runtimeStack = New Stack
End Sub

Private Sub Form_KeyPress(KeyAscii As Integer)
    Select Case KeyAscii
        Case 8
            Call Key_Back_Click
        Case 13
            Call Key_Equal_Click
        Case 27
            Call Key_C_Click
        Case 42
            Call Key_Multiply_Click
        Case 43
            Call Key_Plus_Click
        Case 45
            Call Key_Minus_Click
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
        Case 127
            Call Key_CE_Click
    End Select
    
    'MsgBox KeyAscii
End Sub

Private Sub Press_Key(Key)
    ' 记得设置 Key.Style 为 1
    Key.BackColor = &H80000010
    Delay (0.1)
    Key.BackColor = &H8000000F
End Sub

Public Sub Delay(PauseTime As Single)
    Dim Start As Single
    Start = Timer
    Do While Timer < Start + PauseTime
        DoEvents
    Loop
End Sub

Private Sub Key_0_Click()
    Call Press_Key(Key_0)
    Text1.text = Text1.text & 0
End Sub

Private Sub Key_1_Click()
    Call Press_Key(Key_1)
    Text1.text = Text1.text & 1
End Sub

Private Sub Key_2_Click()
    Call Press_Key(Key_2)
    Text1.text = Text1.text & 2
End Sub

Private Sub Key_3_Click()
    Call Press_Key(Key_3)
    Text1.text = Text1.text & 3
End Sub

Private Sub Key_4_Click()
    Call Press_Key(Key_4)
    Text1.text = Text1.text & 4
End Sub

Private Sub Key_5_Click()
    Call Press_Key(Key_5)
    Text1.text = Text1.text & 5
End Sub

Private Sub Key_6_Click()
    Call Press_Key(Key_6)
    Text1.text = Text1.text & 6
End Sub

Private Sub Key_7_Click()
    Call Press_Key(Key_7)
    Text1.text = Text1.text & 7
End Sub

Private Sub Key_8_Click()
    Call Press_Key(Key_8)
    Text1.text = Text1.text & 8
End Sub

Private Sub Key_9_Click()
    Call Press_Key(Key_9)
    Text1.text = Text1.text & 9
End Sub

Private Sub Key_Back_Click()
    Call Press_Key(Key_Back)
    Text1.text = Text1.text & "←"
End Sub

Private Sub Key_C_Click()
    Call Press_Key(Key_C)
    Text1.text = Text1.text & "C"
End Sub

Private Sub Key_CE_Click()
    Call Press_Key(Key_CE)
    Text1.text = Text1.text & "CE"
End Sub

Private Sub Key_Divide_Click()
    Call Press_Key(Key_Divide)
    Text1.text = Text1.text & "/"
End Sub

Private Sub Key_Dot_Click()
    Call Press_Key(Key_Dot)
End Sub

Private Sub Key_Equal_Click()
    Call Press_Key(Key_Equal)
    Text1.text = Text1.text & "="
End Sub

Private Sub Key_Minus_Click()
    Call Press_Key(Key_Minus)
    Text1.text = Text1.text & "-"
End Sub

Private Sub Key_Multiply_Click()
    Call Press_Key(Key_Multiply)
    Text1.text = Text1.text & "x"
End Sub

Private Sub Key_Negative_Click()
    Call Press_Key(Key_Negative)
End Sub

Private Sub Key_Plus_Click()
    Call Press_Key(Key_Plus)
    Text1.text = Text1.text & "+"
End Sub
