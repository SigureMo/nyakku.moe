VERSION 5.00
Begin VB.Form Calculator 
   Caption         =   "Calc"
   ClientHeight    =   8535
   ClientLeft      =   225
   ClientTop       =   870
   ClientWidth     =   17190
   KeyPreview      =   -1  'True
   LinkTopic       =   "Form1"
   ScaleHeight     =   8535
   ScaleWidth      =   17190
   StartUpPosition =   3  '窗口缺省
   Begin VB.Frame Key_Frame 
      Height          =   5000
      Left            =   500
      TabIndex        =   24
      Top             =   2500
      Width           =   9000
      Begin VB.CommandButton Key_Plot 
         Caption         =   "Plot"
         Height          =   800
         Left            =   8100
         Style           =   1  'Graphical
         TabIndex        =   70
         Top             =   4100
         Width           =   800
      End
      Begin VB.CommandButton Key_Equal 
         Caption         =   "="
         Height          =   800
         Left            =   8100
         Style           =   1  'Graphical
         TabIndex        =   69
         Top             =   4100
         Width           =   800
      End
      Begin VB.CommandButton Key_Plus 
         Caption         =   "+"
         Height          =   800
         Left            =   8100
         Style           =   1  'Graphical
         TabIndex        =   68
         Top             =   3100
         Width           =   800
      End
      Begin VB.CommandButton Key_Minus 
         Caption         =   "-"
         Height          =   800
         Left            =   8100
         Style           =   1  'Graphical
         TabIndex        =   67
         Top             =   2100
         Width           =   800
      End
      Begin VB.CommandButton Key_1 
         Caption         =   "1"
         Height          =   800
         Left            =   5100
         Style           =   1  'Graphical
         TabIndex        =   66
         Top             =   3100
         Width           =   800
      End
      Begin VB.CommandButton Key_2 
         Caption         =   "2"
         Height          =   800
         Left            =   6100
         Style           =   1  'Graphical
         TabIndex        =   65
         Top             =   3100
         Width           =   800
      End
      Begin VB.CommandButton Key_3 
         Caption         =   "3"
         Height          =   800
         Left            =   7100
         Style           =   1  'Graphical
         TabIndex        =   64
         Top             =   3100
         Width           =   800
      End
      Begin VB.CommandButton Key_4 
         Caption         =   "4"
         Height          =   800
         Left            =   5100
         Style           =   1  'Graphical
         TabIndex        =   63
         Top             =   2100
         Width           =   800
      End
      Begin VB.CommandButton Key_5 
         Caption         =   "5"
         Height          =   800
         Left            =   6100
         Style           =   1  'Graphical
         TabIndex        =   62
         Top             =   2100
         Width           =   800
      End
      Begin VB.CommandButton Key_6 
         Caption         =   "6"
         Height          =   800
         Left            =   7100
         Style           =   1  'Graphical
         TabIndex        =   61
         Top             =   2100
         Width           =   800
      End
      Begin VB.CommandButton Key_Negative 
         Caption         =   "±"
         Height          =   800
         Left            =   5100
         Style           =   1  'Graphical
         TabIndex        =   60
         Top             =   4100
         Width           =   800
      End
      Begin VB.CommandButton Key_0 
         Caption         =   "0"
         Height          =   800
         Left            =   6100
         Style           =   1  'Graphical
         TabIndex        =   59
         Top             =   4100
         Width           =   800
      End
      Begin VB.CommandButton Key_Dot 
         Caption         =   "."
         Height          =   800
         Left            =   7100
         Style           =   1  'Graphical
         TabIndex        =   58
         Top             =   4100
         Width           =   800
      End
      Begin VB.CommandButton Key_LeftBracket 
         Caption         =   "("
         Height          =   800
         Left            =   3100
         Style           =   1  'Graphical
         TabIndex        =   57
         Top             =   4100
         Width           =   800
      End
      Begin VB.CommandButton Key_RightBracket 
         Caption         =   ")"
         Height          =   800
         Left            =   4100
         Style           =   1  'Graphical
         TabIndex        =   56
         Top             =   4100
         Width           =   800
      End
      Begin VB.CommandButton Key_Log 
         Caption         =   "log"
         Height          =   800
         Left            =   2100
         Style           =   1  'Graphical
         TabIndex        =   55
         Top             =   3100
         Width           =   800
      End
      Begin VB.CommandButton Key_PI 
         Caption         =   "π"
         Height          =   800
         Left            =   1100
         Style           =   1  'Graphical
         TabIndex        =   54
         Top             =   4100
         Width           =   800
      End
      Begin VB.CommandButton Key_Exp 
         Caption         =   "e"
         Height          =   800
         Left            =   1100
         Style           =   1  'Graphical
         TabIndex        =   53
         Top             =   3100
         Width           =   800
      End
      Begin VB.CommandButton Key_Factorial 
         Caption         =   "n!"
         Height          =   800
         Left            =   2100
         Style           =   1  'Graphical
         TabIndex        =   52
         Top             =   4100
         Width           =   800
      End
      Begin VB.CommandButton Key_Reciprocal 
         Caption         =   "1/x"
         Enabled         =   0   'False
         Height          =   800
         Left            =   100
         Style           =   1  'Graphical
         TabIndex        =   51
         Top             =   3100
         Width           =   800
      End
      Begin VB.CommandButton Key_Dms 
         Caption         =   "dms"
         Enabled         =   0   'False
         Height          =   800
         Left            =   3100
         Style           =   1  'Graphical
         TabIndex        =   50
         Top             =   3100
         Width           =   800
      End
      Begin VB.CommandButton Key_Deg 
         Caption         =   "deg"
         Enabled         =   0   'False
         Height          =   800
         Left            =   4100
         Style           =   1  'Graphical
         TabIndex        =   49
         Top             =   3100
         Width           =   800
      End
      Begin VB.CommandButton Key_Up 
         Caption         =   "↑"
         Enabled         =   0   'False
         Height          =   800
         Left            =   100
         Style           =   1  'Graphical
         TabIndex        =   48
         Top             =   4100
         Width           =   800
      End
      Begin VB.CommandButton Key_Mod 
         Caption         =   "Mod"
         Height          =   800
         Left            =   4100
         Style           =   1  'Graphical
         TabIndex        =   47
         Top             =   2100
         Width           =   800
      End
      Begin VB.CommandButton Key_E 
         Caption         =   "Exp"
         Height          =   800
         Left            =   3100
         Style           =   1  'Graphical
         TabIndex        =   46
         Top             =   2100
         Width           =   800
      End
      Begin VB.CommandButton Key_Ln 
         Caption         =   "ln"
         Height          =   800
         Left            =   2100
         Style           =   1  'Graphical
         TabIndex        =   45
         Top             =   2100
         Width           =   800
      End
      Begin VB.CommandButton Key_Power_By_10 
         Caption         =   "10^x"
         Height          =   800
         Left            =   1100
         TabIndex        =   44
         Top             =   2100
         Width           =   800
      End
      Begin VB.CommandButton Key_Sqrt 
         Caption         =   "√"
         Height          =   800
         Left            =   100
         Style           =   1  'Graphical
         TabIndex        =   43
         Top             =   2100
         Width           =   800
      End
      Begin VB.CommandButton Key_Multiply 
         Caption         =   "×"
         Height          =   800
         Left            =   8100
         Style           =   1  'Graphical
         TabIndex        =   42
         Top             =   1100
         Width           =   800
      End
      Begin VB.CommandButton Key_9 
         Caption         =   "9"
         Height          =   800
         Left            =   7100
         Style           =   1  'Graphical
         TabIndex        =   41
         Top             =   1100
         Width           =   800
      End
      Begin VB.CommandButton Key_8 
         Caption         =   "8"
         Height          =   800
         Left            =   6100
         Style           =   1  'Graphical
         TabIndex        =   40
         Top             =   1100
         Width           =   800
      End
      Begin VB.CommandButton Key_7 
         Caption         =   "7"
         Height          =   800
         Left            =   5100
         Style           =   1  'Graphical
         TabIndex        =   39
         Top             =   1100
         Width           =   800
      End
      Begin VB.CommandButton Key_ArcTan 
         Caption         =   "arctan"
         Height          =   800
         Left            =   4100
         Style           =   1  'Graphical
         TabIndex        =   38
         Top             =   1100
         Width           =   800
      End
      Begin VB.CommandButton Key_ArcCos 
         Caption         =   "arccos"
         Height          =   800
         Left            =   3100
         Style           =   1  'Graphical
         TabIndex        =   37
         Top             =   1100
         Width           =   800
      End
      Begin VB.CommandButton Key_ArcSin 
         Caption         =   "arcsin"
         Height          =   800
         Left            =   2100
         Style           =   1  'Graphical
         TabIndex        =   36
         Top             =   1100
         Width           =   800
      End
      Begin VB.CommandButton Key_YRoot 
         Caption         =   "y√x"
         Height          =   800
         Left            =   1100
         Style           =   1  'Graphical
         TabIndex        =   35
         Top             =   1100
         Width           =   800
      End
      Begin VB.CommandButton Key_Cube 
         Caption         =   "x^3"
         Height          =   800
         Left            =   100
         Style           =   1  'Graphical
         TabIndex        =   34
         Top             =   1100
         Width           =   800
      End
      Begin VB.CommandButton Key_Divide 
         Caption         =   "÷"
         Height          =   800
         Left            =   8100
         Style           =   1  'Graphical
         TabIndex        =   33
         Top             =   100
         Width           =   800
      End
      Begin VB.CommandButton Key_Back 
         Caption         =   "←"
         Height          =   800
         Left            =   7100
         Style           =   1  'Graphical
         TabIndex        =   32
         Top             =   100
         Width           =   800
      End
      Begin VB.CommandButton Key_C 
         Caption         =   "C"
         Height          =   800
         Left            =   6100
         Style           =   1  'Graphical
         TabIndex        =   31
         Top             =   100
         Width           =   800
      End
      Begin VB.CommandButton Key_CE 
         Caption         =   "CE"
         Height          =   800
         Left            =   5100
         Style           =   1  'Graphical
         TabIndex        =   30
         Top             =   100
         Width           =   800
      End
      Begin VB.CommandButton Key_Tan 
         Caption         =   "tan"
         Height          =   800
         Left            =   4100
         Style           =   1  'Graphical
         TabIndex        =   29
         Top             =   100
         Width           =   800
      End
      Begin VB.CommandButton Key_Cos 
         Caption         =   "cos"
         Height          =   800
         Left            =   3100
         Style           =   1  'Graphical
         TabIndex        =   28
         Top             =   100
         Width           =   800
      End
      Begin VB.CommandButton Key_Sin 
         Caption         =   "sin"
         Height          =   800
         Left            =   2100
         Style           =   1  'Graphical
         TabIndex        =   27
         Top             =   100
         Width           =   800
      End
      Begin VB.CommandButton Key_Power 
         Caption         =   "x^y"
         Height          =   800
         Left            =   1100
         Style           =   1  'Graphical
         TabIndex        =   26
         Top             =   100
         Width           =   800
      End
      Begin VB.CommandButton Key_Square 
         Caption         =   "x^2"
         Height          =   800
         Left            =   100
         Style           =   1  'Graphical
         TabIndex        =   25
         Top             =   100
         Width           =   800
      End
   End
   Begin VB.Frame Settings_Frame 
      Caption         =   "Settings"
      Height          =   2000
      Left            =   5000
      TabIndex        =   14
      Top             =   250
      Width           =   5100
      Begin VB.CommandButton Key_X 
         Caption         =   "x"
         Height          =   400
         Left            =   3800
         TabIndex        =   23
         Top             =   1500
         Width           =   800
      End
      Begin VB.TextBox Y_Max_Box 
         Height          =   400
         Left            =   3000
         TabIndex        =   19
         Text            =   "1"
         Top             =   1000
         Width           =   1000
      End
      Begin VB.TextBox Y_Min_Box 
         Height          =   400
         Left            =   1200
         TabIndex        =   18
         Text            =   "-1"
         Top             =   1000
         Width           =   1000
      End
      Begin VB.TextBox X_Max_Box 
         Height          =   400
         Left            =   3000
         TabIndex        =   17
         Text            =   "1"
         Top             =   400
         Width           =   1000
      End
      Begin VB.TextBox X_Min_Box 
         Height          =   400
         Left            =   1200
         TabIndex        =   15
         Text            =   "-1"
         Top             =   400
         Width           =   1000
      End
      Begin VB.Label Range_Y_Step_Label 
         AutoSize        =   -1  'True
         Caption         =   "-"
         Height          =   180
         Left            =   2500
         TabIndex        =   22
         Top             =   1000
         Width           =   90
      End
      Begin VB.Label Range_Y_Label 
         AutoSize        =   -1  'True
         Caption         =   "Range_y"
         Height          =   180
         Left            =   240
         TabIndex        =   21
         Top             =   1000
         Width           =   630
      End
      Begin VB.Label Range_X_Step_Label 
         AutoSize        =   -1  'True
         Caption         =   "-"
         Height          =   180
         Left            =   2500
         TabIndex        =   20
         Top             =   400
         Width           =   90
      End
      Begin VB.Label Range_X_Label 
         AutoSize        =   -1  'True
         Caption         =   "Range_x"
         Height          =   180
         Left            =   240
         TabIndex        =   16
         Top             =   400
         Width           =   630
      End
   End
   Begin VB.Frame History_Frame 
      Caption         =   "History"
      Height          =   8000
      Left            =   11000
      TabIndex        =   10
      Top             =   240
      Width           =   4000
      Begin VB.CommandButton Clear_History_Button 
         Caption         =   "Clear"
         Height          =   500
         Left            =   2520
         TabIndex        =   12
         Top             =   7200
         Width           =   1000
      End
      Begin VB.ListBox History 
         Height          =   6000
         ItemData        =   "calc.frx":0000
         Left            =   300
         List            =   "calc.frx":0002
         TabIndex        =   11
         Top             =   600
         Width           =   3500
      End
   End
   Begin VB.Frame Memory_Frame 
      Caption         =   "Memory"
      Height          =   2000
      Left            =   5000
      TabIndex        =   3
      Top             =   250
      Width           =   5100
      Begin VB.TextBox Memory 
         Height          =   800
         Left            =   300
         Locked          =   -1  'True
         TabIndex        =   9
         Top             =   300
         Width           =   2000
      End
      Begin VB.CommandButton Key_MS 
         Caption         =   "MS"
         Height          =   400
         Left            =   4200
         TabIndex        =   8
         Top             =   1300
         Width           =   800
      End
      Begin VB.CommandButton Key_MMinus 
         Caption         =   "M-"
         Height          =   400
         Left            =   3200
         TabIndex        =   7
         Top             =   1300
         Width           =   800
      End
      Begin VB.CommandButton Key_MPlus 
         Caption         =   "M+"
         Height          =   400
         Left            =   2200
         TabIndex        =   6
         Top             =   1300
         Width           =   800
      End
      Begin VB.CommandButton Key_MR 
         Caption         =   "MR"
         Height          =   400
         Left            =   1200
         TabIndex        =   5
         Top             =   1300
         Width           =   800
      End
      Begin VB.CommandButton Key_MC 
         Caption         =   "MC"
         Height          =   400
         Left            =   200
         TabIndex        =   4
         Top             =   1300
         Width           =   800
      End
   End
   Begin VB.Frame Graph_Frame 
      Caption         =   "Graph"
      Height          =   6000
      Left            =   11000
      TabIndex        =   2
      Top             =   250
      Width           =   6000
      Begin VB.PictureBox Graph 
         AutoRedraw      =   -1  'True
         DrawStyle       =   2  'Dot
         Height          =   5000
         Left            =   500
         ScaleHeight     =   4935
         ScaleWidth      =   4935
         TabIndex        =   13
         Top             =   500
         Width           =   5000
      End
   End
   Begin VB.TextBox Result 
      Height          =   800
      Left            =   500
      Locked          =   -1  'True
      TabIndex        =   1
      Top             =   1250
      Width           =   4000
   End
   Begin VB.TextBox Expression_Box 
      Height          =   800
      Left            =   500
      Locked          =   -1  'True
      TabIndex        =   0
      Top             =   250
      Width           =   4000
   End
   Begin VB.Menu Mode 
      Caption         =   "模式"
      Begin VB.Menu CalculateMode 
         Caption         =   "科学计算器"
      End
      Begin VB.Menu GraphMode 
         Caption         =   "图形绘制器"
      End
   End
End
Attribute VB_Name = "Calculator"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Declare Function compute Lib "calc.dll" (ByVal Expression As String) As Double
Dim Expression As String
Dim Operands As String
Dim Operators As String


Private Sub Form_Load()
    Shell (Start & "calc.exe")
    Operands = "1234567890.x"
    Operators = "+-*/()^"
    Call CalculateMode_Click
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
    If Not ((Calculator.ActiveControl Is X_Min_Box) Or (Calculator.ActiveControl Is Y_Min_Box) Or (Calculator.ActiveControl Is X_Max_Box) Or (Calculator.ActiveControl Is Y_Max_Box)) Then
        Select Case KeyAscii
            Case 8
                Call Key_Back_Click
            Case 13
                Call Key_Equal_Click
            Case 27
                Call Key_C_Click
            Case 33
                Call Key_Factorial_Click
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
            Case 64
                Call Key_Sqrt_Click
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
            Case 113
                Call Key_Square_Click
            Case 115
                Call Key_Sin_Click
            Case 116
                Call Key_Tan_Click
            Case 120
                Call Key_X_Click
            Case 127
                Call Key_CE_Click
        End Select
    End If
    
    'MsgBox KeyAscii
End Sub

' 括号回调
Private Sub ShowLeftBracket()
    LeftBracketNum = 0
    i = 1
    While i <= Len(Expression)
        c = Mid(Expression, i, 1)
        If c = "(" Then
            LeftBracketNum = LeftBracketNum + 1
        ElseIf c = ")" Then
            LeftBracketNum = LeftBracketNum - 1
        End If
        i = i + 1
    Wend
    If LeftBracketNum Then
        Key_LeftBracket.Caption = "(_" & LeftBracketNum
    Else
        Key_LeftBracket.Caption = "("
    End If
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
        ElseIf c = "@" Then
            Expression_Box.Text = Expression_Box.Text & "√"
        Else
            Expression_Box.Text = Expression_Box.Text & c
        End If
        i = i + 1
    Wend
End Sub


' Mode Change
Private Sub GraphMode_Click()
    Result.Visible = False
    Memory_Frame.Visible = False
    History_Frame.Visible = False
    Graph_Frame.Visible = True
    Settings_Frame.Visible = True
    Key_Equal.Visible = False
    Key_Plot.Visible = True
End Sub

Private Sub CalculateMode_Click()
    Result.Visible = True
    Memory_Frame.Visible = True
    History_Frame.Visible = True
    Graph_Frame.Visible = False
    Settings_Frame.Visible = False
    Key_Equal.Visible = True
    Key_Plot.Visible = False
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
'' Basic
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
    Call ShowLeftBracket
End Sub

Private Sub Key_RightBracket_Click()
    Call Press_Key(Key_RightBracket)
    Expression = Expression & ")"
    Call Show_Expression
    Call ShowLeftBracket
End Sub

Private Sub Key_Root_Click()

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

Private Sub Key_Factorial_Click()
    Call Press_Key(Key_Factorial)
    Expression = Expression & "!"
    Call Show_Expression
End Sub

Private Sub Key_Sqrt_Click()
    Call Press_Key(Key_Sqrt)
    Expression = Expression & "@"
    Call Show_Expression
End Sub

'' 组合
Private Sub Key_Power_By_10_Click()
    Call Press_Key(Key_Power_By_10)
    Expression = Expression & "10^"
    Call Show_Expression
End Sub

Private Sub Key_E_Click()
    Call Press_Key(Key_E)
    Expression = Expression & "*10^"
    Call Show_Expression
End Sub

Private Sub Key_YRoot_Click()
    Call Press_Key(Key_YRoot)
    Expression = Expression & "^(1/"
    Call Show_Expression
    Call ShowLeftBracket
End Sub

Private Sub Key_Square_Click()
    Call Press_Key(Key_Square)
    Expression = Expression & "^2"
    Call Show_Expression
End Sub

Private Sub Key_Cube_Click()
    Call Press_Key(Key_Cube)
    Expression = Expression & "^3"
    Call Show_Expression
End Sub


'' 特殊操作符
Private Sub Key_Back_Click()
    Call Press_Key(Key_Back)
    If Not Expression = "" Then
        Expression = Mid(Expression, 1, Len(Expression) - 1)
    End If
    Call Show_Expression
    Call ShowLeftBracket
End Sub

Private Sub Key_C_Click()
    Call Press_Key(Key_C)
    Expression = ""
    Call Show_Expression
    Call ShowLeftBracket
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
    Call ShowLeftBracket
End Sub

Private Sub Key_Equal_Click()
    Call Press_Key(Key_Equal)
    If Expression <> "" Then
        Expression = Expression & "="
        Result.Text = compute(Expression)
        Expression = ""
        History.AddItem (Expression_Box.Text & "=" & Result.Text)
    End If
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

' Graph
' Plot

Private Sub Key_X_Click()
    Call Press_Key(Key_X)
    Expression = Expression & "x"
    Call Show_Expression
End Sub

Private Sub Key_Plot_Click()
    Graph.Cls
    Graph.DrawWidth = 2
    x_min = Val(X_Min_Box.Text)
    x_max = Val(X_Max_Box.Text)
    y_min = Val(Y_Min_Box.Text)
    y_max = Val(Y_Max_Box.Text)
    delta_x = x_max - x_min
    delta_y = y_max - y_min
    Graph.Scale (x_min, y_max)-(x_max, y_min)
    Graph.Line (0, y_min)-(0, y_max)
    Graph.Line (x_min, 0)-(x_max, 0)
    ' Axis x
    For i = x_min To x_max Step delta_x * 0.1
        Graph.Line (i, 0)-(i, delta_y * 0.02)
        Graph.CurrentX = i: Graph.CurrentY = -delta_y * 0.05: Graph.Print Format(i, "0.00")
    Next i
    ' Axis y
    For i = y_min To y_max Step delta_y * 0.1
        Graph.Line (0, i)-(delta_y * 0.01, i)
        Graph.CurrentX = -delta_x * 0.1: Graph.CurrentY = i: Graph.Print Format(i, "0.00")
    Next i
    ' Plot
    If Expression <> "" Then
        Expression = Expression & "="
        For x = x_min To x_max Step 0.001
            tempExpression = ""
            i = 1
            While i < Len(Expression)
                idx = InStr(i, Expression, "x")
                If idx Then
                    tempExpression = tempExpression & Mid(Expression, i, idx - i) & Format(x, "0.000")
                    i = idx + 1
                Else
                    tempExpression = tempExpression & Mid(Expression, i, Len(Expression))
                    i = Len(Expression) + 1
                End If
            Wend
            Graph.PSet (x, compute(tempExpression))
        Next
    End If
    
End Sub
