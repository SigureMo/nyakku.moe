VERSION 5.00
Begin VB.Form Form1 
   Caption         =   "Form1"
   ClientHeight    =   7470
   ClientLeft      =   120
   ClientTop       =   465
   ClientWidth     =   11565
   LinkTopic       =   "Form1"
   ScaleHeight     =   7470
   ScaleWidth      =   11565
   StartUpPosition =   3  '窗口缺省
   Begin VB.PictureBox Msg_Box 
      Height          =   375
      Left            =   480
      ScaleHeight     =   315
      ScaleWidth      =   2955
      TabIndex        =   9
      Top             =   6840
      Width           =   3015
   End
   Begin VB.Frame Frame1 
      Caption         =   "网格设置"
      Height          =   2175
      Left            =   6840
      TabIndex        =   1
      Top             =   480
      Width           =   4575
      Begin VB.CommandButton Select_Material_Button 
         Caption         =   "材料指定"
         Height          =   375
         Left            =   2640
         TabIndex        =   8
         Top             =   1560
         Width           =   1455
      End
      Begin VB.CommandButton Grid_Generate_Button 
         Caption         =   "网格生成"
         Height          =   495
         Left            =   360
         TabIndex        =   7
         Top             =   1440
         Width           =   1455
      End
      Begin VB.TextBox Delta_Y_Box 
         Height          =   495
         Left            =   3240
         TabIndex        =   6
         Text            =   "25"
         Top             =   840
         Width           =   975
      End
      Begin VB.TextBox Delta_X_Box 
         Height          =   375
         Left            =   840
         TabIndex        =   4
         Text            =   "25"
         Top             =   960
         Width           =   1095
      End
      Begin VB.CheckBox Same_Grid_Check_Box 
         Caption         =   "等网格"
         Height          =   255
         Left            =   240
         TabIndex        =   2
         Top             =   360
         Width           =   1095
      End
      Begin VB.Label Delta_Y_Label 
         Caption         =   "Δy"
         Height          =   255
         Left            =   2640
         TabIndex        =   5
         Top             =   960
         Width           =   495
      End
      Begin VB.Label Delta_X_Label 
         Caption         =   "Δx"
         Height          =   375
         Left            =   360
         TabIndex        =   3
         Top             =   960
         Width           =   495
      End
   End
   Begin VB.PictureBox Grid 
      Height          =   5895
      Left            =   240
      ScaleHeight     =   5835
      ScaleWidth      =   5835
      TabIndex        =   0
      Top             =   240
      Width           =   5895
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Dim grid_matrix(1000, 1000) As Integer
Dim range_x%, range_y%
Dim Start_x%, Start_y%
Dim Start As Boolean
Dim Grid_Generated As Boolean
Dim color_arr

Private Sub Show_Grid()
    For i = 0 To range_x
        For j = 0 To range_y
            Grid.Line (i, j)-(i + 1, j + 1), color_arr(grid_matrix(i, j)), BF
        Next j
    Next i
    Generate_Grid
End Sub


Private Sub Form_Load()
    Grid_Generated = False
    color_arr = Array(vbYellow, vbBlue, vbRed, vbGreen, vbWhite)
End Sub

Private Sub Generate_Grid()
    range_x = Val(Delta_X_Box.Text)
    range_y = Val(Delta_Y_Box.Text)
    Grid.Scale (0, 0)-(range_x, range_y)
    For i = 0 To range_x
        Grid.Line (i, 0)-(i, range_y)
    Next i
    For i = 0 To range_y
        Grid.Line (0, i)-(range_x, i)
    Next i
    Grid_Generated = True
End Sub

Private Sub Grid_MouseDown(Button As Integer, Shift As Integer, x As Single, y As Single)
    If Not Grid_Generated Then
        MsgBox "请先生成网格！"
        Exit Sub
    End If
    If Button = 1 Then
        real_x = Int(x)
        real_y = Int(y)
        grid_matrix(real_x, real_y) = 4
        Msg_Box.Cls
        Msg_Box.Print "x:" & real_x & " y:" & real_y & " shift:" & Shift
        Show_Grid
    End If
End Sub

Private Sub Grid_Generate_Button_Click()
    Grid.Cls
    If IsNumeric(Delta_X_Box.Text) And IsNumeric(Delta_Y_Box.Text) Then
        Generate_Grid
    Else
        MsgBox "请在网格参数中输入纯数字！"
    End If
End Sub

Private Sub Same_Grid_Check_Box_Click()
    If Same_Grid_Check_Box.Value = 1 Then
        Delta_Y_Box.Text = Delta_X_Box.Text
        Delta_Y_Box.Enabled = False
    Else
        Delta_Y_Box.Enabled = True
    End If
End Sub

