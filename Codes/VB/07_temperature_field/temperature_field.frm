VERSION 5.00
Begin VB.Form Form1 
   Caption         =   "Form1"
   ClientHeight    =   8775
   ClientLeft      =   120
   ClientTop       =   465
   ClientWidth     =   11565
   LinkTopic       =   "Form1"
   ScaleHeight     =   8775
   ScaleWidth      =   11565
   StartUpPosition =   3  '窗口缺省
   Begin VB.Frame Frame3 
      Caption         =   "区域快捷操作"
      Height          =   1575
      Left            =   6840
      TabIndex        =   10
      Top             =   3000
      Width           =   4215
      Begin VB.CheckBox InvertSelcet_Check_Box 
         Caption         =   "反选"
         Height          =   255
         Left            =   360
         TabIndex        =   12
         Top             =   840
         Width           =   975
      End
      Begin VB.Label Tips_Label 
         AutoSize        =   -1  'True
         Caption         =   "Tips:支持按住 Shift 进行区域选择哦！"
         Height          =   180
         Left            =   120
         TabIndex        =   11
         Top             =   480
         Width           =   3240
      End
   End
   Begin VB.Frame Frame2 
      Caption         =   "材料设置"
      Height          =   1935
      Left            =   6840
      TabIndex        =   9
      Top             =   5160
      Width           =   4455
   End
   Begin VB.PictureBox Msg_Box 
      Height          =   495
      Left            =   240
      ScaleHeight     =   435
      ScaleWidth      =   5955
      TabIndex        =   8
      Top             =   7560
      Width           =   6015
   End
   Begin VB.Frame Frame1 
      Caption         =   "网格设置"
      Height          =   2175
      Left            =   6840
      TabIndex        =   1
      Top             =   480
      Width           =   4575
      Begin VB.CommandButton Grid_Generate_Button 
         Caption         =   "网格生成"
         Height          =   495
         Left            =   2760
         TabIndex        =   7
         Top             =   1560
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
      AutoRedraw      =   -1  'True
      Height          =   6615
      Left            =   240
      ScaleHeight     =   6555
      ScaleWidth      =   6315
      TabIndex        =   0
      Top             =   240
      Width           =   6375
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
Dim Grid_Generated As Boolean
Dim color_arr
Dim SAND%, CASTING%, CHILL%, SEC%

Private Sub Form_Load()
    Grid_Generated = False
    color_arr = Array(vbYellow, vbRed, vbBlue, vbWhite)
    Start_x = -1
    SAND = 0
    CASTING = 1
    CHILL = 2
    SEC = 3
End Sub

Private Sub Redraw_Area(x_start As Integer, x_end As Integer, y_start As Integer, y_end As Integer)
    For i = x_start To x_end
        For j = y_start To y_end
            Grid.Line (i, j)-(i + 1, j + 1), color_arr(grid_matrix(i, j)), BF
        Next j
    Next i
    Generate_Grid
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
    Dim real_x%, real_y%
    If Not Grid_Generated Then
        MsgBox "请先生成网格！"
        Exit Sub
    End If
    If Button = 1 Then
        Clear_Empty_Grid
        real_x = Int(x)
        real_y = Int(y)
        If Shift = 1 Then
            If Start_x = -1 Then
                Start_x = real_x
                Start_y = real_y
                Msg_Box.Cls
                Msg_Box.Print "已选中起始点 (" & real_x & ", " & real_y & ") 请选择终点"
            Else
                Call Set_Area_Values(Start_x, real_x, Start_y, real_y, SEC)
                Call Redraw_Area(0, Val(Delta_X_Box.Text), 0, Val(Delta_Y_Box.Text))
                Msg_Box.Cls
                Msg_Box.Print "已选中区域 (" & Start_x & ", " & Start_y & ")-(" & real_x & ", " & real_y & ")"
                Start_x = -1
            End If
        ElseIf Shift = 2 Then
            MsgBox "暂不支持 Ctrl 连续点选"
        ElseIf Shift = 0 Then
            Start_x = -1
            grid_matrix(real_x, real_y) = SEC
            Msg_Box.Cls
            Msg_Box.Print "已选中点 (" & real_x & ", " & real_y & ")"
            Call Redraw_Area(0, Val(Delta_X_Box.Text), 0, Val(Delta_Y_Box.Text))
        End If
    End If
End Sub

Private Sub Grid_Generate_Button_Click()
    If IsNumeric(Delta_X_Box.Text) And IsNumeric(Delta_Y_Box.Text) Then
        Generate_Grid
    Else
        MsgBox "请在网格参数中输入纯数字！"
    End If
End Sub

Private Sub Same_Grid_Check_Box_Click()
    If Same_Grid_Check_Box.value = 1 Then
        Delta_Y_Box.Text = Delta_X_Box.Text
        Delta_Y_Box.Enabled = False
    Else
        Delta_Y_Box.Enabled = True
    End If
End Sub

Private Sub Set_Area_Values(x_start As Integer, x_end As Integer, y_start As Integer, y_end As Integer, value As Integer)
    If x_start < x_end Then
        x_s = x_start
        x_e = x_end
    Else
        x_e = x_start
        x_s = x_end
    End If
    If y_start < y_end Then
        y_s = y_start
        y_e = y_end
    Else
        y_e = y_start
        y_s = y_end
    End If
    For i = x_s To x_e
        For j = y_s To y_e
            grid_matrix(i, j) = value
        Next j
    Next i
End Sub

Private Sub Clear_Empty_Grid()
    range_x = Val(Delta_X_Box.Text)
    range_y = Val(Delta_Y_Box.Text)
    For i = 0 To range_x
        For j = 0 To range_y
            If grid_matrix(i, j) = SEC Then
                grid_matrix(i, j) = SAND
            End If
        Next j
    Next i
    Call Redraw_Area(0, range_x, 0, range_y)
End Sub

Private Sub Select_Material_Button_Click()
    range_x = Val(Delta_X_Box.Text)
    range_y = Val(Delta_Y_Box.Text)
    For i = 0 To range_x
        For j = 0 To range_y
            If grid_matrix(i, j) = SEC Then
                grid_matrix(i, j) = SAND
            End If
        Next j
    Next i
    Call Redraw_Area(0, range_x, 0, range_y)
End Sub
