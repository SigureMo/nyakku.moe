VERSION 5.00
Begin VB.Form Form1 
   Caption         =   "Form1"
   ClientHeight    =   10365
   ClientLeft      =   120
   ClientTop       =   465
   ClientWidth     =   12405
   FillStyle       =   0  'Solid
   LinkTopic       =   "Form1"
   ScaleHeight     =   10365
   ScaleWidth      =   12405
   StartUpPosition =   3  '窗口缺省
   Begin VB.PictureBox CheckerBoard 
      AutoRedraw      =   -1  'True
      FillStyle       =   2  'Horizontal Line
      Height          =   10000
      Left            =   100
      ScaleHeight     =   9945
      ScaleWidth      =   9945
      TabIndex        =   0
      Top             =   100
      Width           =   10000
   End
   Begin VB.Label White_Score_Label 
      AutoSize        =   -1  'True
      Caption         =   "White:0"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   15
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   300
      Left            =   10320
      TabIndex        =   3
      Top             =   1680
      Width           =   1155
   End
   Begin VB.Label Black_Score_Label 
      AutoSize        =   -1  'True
      Caption         =   "Black:0"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   15
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   300
      Left            =   10320
      TabIndex        =   2
      Top             =   1080
      Width           =   1155
   End
   Begin VB.Label Next_Label 
      AutoSize        =   -1  'True
      Caption         =   "Next:Black"
      BeginProperty Font 
         Name            =   "新宋体"
         Size            =   18
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   360
      Left            =   10320
      TabIndex        =   1
      Top             =   360
      Width           =   1950
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Dim chess_matrix(18, 18) As Integer
Dim next_color As Integer ' 1 black, 2 white
Dim black_score As Integer
Dim white_score As Integer


Private Sub Init_CheckerBoard()
    w = CheckerBoard.Width
    CheckerBoard.Height = w
    check_size = w / 20
    CheckerBoard.Scale (-1, -1)-(19, 19)
    For i = 0 To 18
        CheckerBoard.Line (i, 0)-(i, 18)
        CheckerBoard.Line (0, i)-(18, i)
    Next i
    CheckerBoard.FillStyle = vbFSSolid
    CheckerBoard.FillColor = vbBlack
    CheckerBoard.Circle (3, 3), 0.15
    CheckerBoard.Circle (3, 9), 0.15
    CheckerBoard.Circle (3, 15), 0.15
    CheckerBoard.Circle (9, 3), 0.15
    CheckerBoard.Circle (9, 9), 0.15
    CheckerBoard.Circle (9, 15), 0.15
    CheckerBoard.Circle (15, 3), 0.15
    CheckerBoard.Circle (15, 9), 0.15
    CheckerBoard.Circle (15, 15), 0.15
End Sub

Private Sub Form_Load()
    next_color = 1
    black_score = 0
    white_score = 0
    Init_CheckerBoard
End Sub

Private Sub change_color()
    If next_color = 1 Then
        next_color = 2
    Else
        next_color = 1
    End If
End Sub

Private Sub Draw_chess()
    For i = 0 To 18
        For j = 0 To 18
            If chess_matrix(i, j) = 1 Then
                CheckerBoard.FillColor = vbBlack
                CheckerBoard.Circle (i, j), 0.3, vbBlack
            ElseIf chess_matrix(i, j) = 2 Then
                CheckerBoard.FillColor = vbWhite
                CheckerBoard.Circle (i, j), 0.3, vbWhite
            End If
        Next j
    Next i
End Sub

Private Sub Redraw()
    CheckerBoard.Cls
    Init_CheckerBoard
    Draw_chess
    If next_color = 1 Then
        Next_Label.Caption = "Next:Black"
    Else
        Next_Label.Caption = "Next:White"
    End If
    Black_Score_Label.Caption = "Black:" & black_score
    White_Score_Label.Caption = "White:" & white_score
    
End Sub

Private Sub Clear_CheckerBoard()
    For i = 0 To 18
        For j = 0 To 18
            chess_matrix(i, j) = 0
        Next j
    Next i
    next_color = 1
End Sub


Private Sub CheckerBoard_MouseDown(Button As Integer, Shift As Integer, x As Single, y As Single)
    If Button = 1 Then
        If Round(x) <= 18 And Round(x) >= 0 And Round(y) >= 0 And Round(y) <= 18 Then
            If chess_matrix(Round(x), Round(y)) = 0 Then
                chess_matrix(Round(x), Round(y)) = next_color
                change_color
            End If
            Redraw
            winner = Check_Winner(Round(x), Round(y))
            If winner = 1 Then
                black_score = black_score + 1
                MsgBox "黑棋胜！"
                Clear_CheckerBoard
            ElseIf winner = 2 Then
                white_score = white_score + 1
                MsgBox "白棋胜！"
                Clear_CheckerBoard
            ElseIf winner = 3 Then
                MsgBox "平局！"
                Clear_CheckerBoard
            End If
            Redraw
        End If
    End If
End Sub

Private Function Check_Winner(x As Integer, y As Integer) As Integer
    chess_color = chess_matrix(x, y)
    num = 0
    win = False
    full = True
    
    win = have_five(x, y, 1, 0) Or have_five(x, y, 0, 1) Or have_five(x, y, 1, 1) Or have_five(x, y, 1, -1)
    
    ' full?
    For i = 0 To 18
        For j = 0 To 18
            If chess_matrix(i, j) = 0 Then
                full = False
            End If
        Next j
    Next i
            
    If win Then
        Check_Winner = chess_color
    ElseIf full Then
        Check_Winner = 3
    Else
        Check_Winner = 0
    End If
End Function

Private Function have_five(x As Integer, y As Integer, axis_x As Integer, axis_y As Integer) As Boolean
    chess_color = chess_matrix(x, y)
    num = 0
    For i = -4 To 4
        target_x = x + i * axis_x
        target_y = y + i * axis_y
        If target_x >= 0 And target_x <= 18 And target_y >= 0 And target_y <= 18 Then
            If chess_matrix(target_x, target_y) = chess_color Then
                num = num + 1
                If num >= 5 Then
                    have_five = True
                    Exit Function
                End If
            Else
                num = 0
            End If
        End If
    Next i
    have_five = False
End Function
