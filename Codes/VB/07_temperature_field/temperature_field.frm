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
      Caption         =   "点选设置"
      Height          =   1575
      Left            =   6960
      TabIndex        =   10
      Top             =   3000
      Width           =   4215
      Begin VB.ComboBox Material_Combo1 
         Height          =   300
         ItemData        =   "temperature_field.frx":0000
         Left            =   480
         List            =   "temperature_field.frx":000D
         Style           =   2  'Dropdown List
         TabIndex        =   14
         Top             =   840
         Width           =   1335
      End
      Begin VB.CommandButton Select_Material_Button 
         Caption         =   "指定材料"
         Height          =   375
         Left            =   2280
         TabIndex        =   13
         Top             =   840
         Width           =   1575
      End
      Begin VB.CheckBox InvertSelcet_Check_Box 
         Caption         =   "反向填充"
         Height          =   255
         Left            =   240
         TabIndex        =   11
         Top             =   360
         Width           =   1215
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
      Begin VB.CommandButton Mesh_Button 
         Caption         =   "生成网格"
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
   Begin VB.Label Tips_Label 
      AutoSize        =   -1  'True
      Height          =   180
      Left            =   7320
      TabIndex        =   12
      Top             =   7920
      Width           =   90
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Dim Material_Matrix(1000, 1000) As Integer
Dim Select_Matrix(1000, 1000) As Boolean
Dim range_x%, range_y%
Dim Start_x%, Start_y%
Dim Meshed As Boolean
Dim color_arr
Dim Tips_arr
Dim click_cnt%
Dim SAND%, CASTING%, CHILL%, SEC%


Private Sub Form_Load()
    Meshed = False
    color_arr = Array(vbYellow, vbRed, vbBlue)
    Start_x = -1
    SAND = 0
    CASTING = 1
    CHILL = 2
    Tips_arr = Array("支持按住 Shift 进行区域选择哦！", "支持按住 Ctrl 连续点选哦！", "Shift Ctrl 同时按住也是支持的哦", "适当使用反向填充会有奇效哦！")
    click_cnt = 0
    Load_Params
End Sub

' 绘制相关

'' 绘制底色
Private Sub Redraw_Area(x_start As Integer, x_end As Integer, y_start As Integer, y_end As Integer)
    For i = x_start To x_end
        For j = y_start To y_end
            Grid.Line (i, j)-(i + 1, j + 1), color_arr(Material_Matrix(i, j)), BF
        Next j
    Next i
    Mesh
End Sub

'' 绘制选择矩阵
Private Sub Redraw_Sec_Area(x_start As Integer, x_end As Integer, y_start As Integer, y_end As Integer)
    For i = x_start To x_end
        For j = y_start To y_end
            If Select_Matrix(i, j) Then
                Grid.Line (i, j)-(i + 1, j + 1), vbWhite, BF
            End If
        Next j
    Next i
    Mesh
End Sub

'' 绘制网格
Private Sub Mesh()
    range_x = Val(Delta_X_Box.Text)
    range_y = Val(Delta_Y_Box.Text)
    Grid.Scale (0, 0)-(range_x, range_y)
    For i = 0 To range_x
        Grid.Line (i, 0)-(i, range_y)
    Next i
    For i = 0 To range_y
        Grid.Line (0, i)-(range_x, i)
    Next i
    Meshed = True
End Sub

Private Sub Grid_Generate_Button_Click()

End Sub

' 点选相关

'' 点选回调
Private Sub Grid_MouseDown(Button As Integer, Shift As Integer, x As Single, y As Single)
    click_cnt = click_cnt + 1
    Tips_Label.Caption = "Tips:" & Tips_arr(click_cnt Mod (UBound(Tips_arr) - LBound(Tips_arr) + 1))
    Dim real_x%, real_y%
    If Not Meshed Then
        MsgBox "请先生成网格"
        Exit Sub
    End If
    If Button = 1 Then
        real_x = Int(x)
        real_y = Int(y)
        If Shift = 1 Or Shift = 3 Then
            If Not Shift = 3 Then
                Clear_Select_Matrix
            End If
            If Start_x = -1 Then
                Start_x = real_x
                Start_y = real_y
                Msg_Box.Cls
                Msg_Box.Print "已选择起始点 (" & real_x & ", " & real_y & ") 请继续选择终点"
            Else
                Call Mark_Area(Start_x, real_x, Start_y, real_y)
                Msg_Box.Cls
                Msg_Box.Print "已选择区域 (" & Start_x & ", " & Start_y & ")-(" & real_x & ", " & real_y & ")"
                Start_x = -1
            End If
        ElseIf Shift = 0 Or Shift = 2 Then
            If Shift = 0 Then
                Clear_Select_Matrix
            End If
            Start_x = -1
            Select_Matrix(real_x, real_y) = True
            Msg_Box.Cls
            Msg_Box.Print "已选择点 (" & real_x & ", " & real_y & ")"
        End If
        Call Redraw_Area(0, Val(Delta_X_Box.Text), 0, Val(Delta_Y_Box.Text))
        Call Redraw_Sec_Area(0, Val(Delta_X_Box.Text), 0, Val(Delta_Y_Box.Text))
    End If
End Sub

'' Shift 区域选择
Private Sub Mark_Area(x_start As Integer, x_end As Integer, y_start As Integer, y_end As Integer)
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
            Select_Matrix(i, j) = True
        Next j
    Next i
End Sub

'' 根据选择矩阵设置选择矩阵
Private Sub Set_Values_By_SecMatrix(value As Integer)
    range_x = Val(Delta_X_Box.Text)
    range_y = Val(Delta_Y_Box.Text)
    For i = 0 To range_x
        For j = 0 To range_y
            If Select_Matrix(i, j) Then
                Material_Matrix(i, j) = value
            End If
        Next j
    Next i
End Sub

'' 清空选择矩阵
Private Sub Clear_Select_Matrix()
    range_x = Val(Delta_X_Box.Text)
    range_y = Val(Delta_Y_Box.Text)
    For i = 0 To range_x
        For j = 0 To range_y
            Select_Matrix(i, j) = False
        Next j
    Next i
End Sub

'' 清空材料矩阵
Private Sub Clear_Material_Matrix()
    range_x = Val(Delta_X_Box.Text)
    range_y = Val(Delta_Y_Box.Text)
    For i = 0 To range_x
        For j = 0 To range_y
            Material_Matrix(i, j) = 0
        Next j
    Next i
End Sub


' 网格设置

'' 网格生成回调
Private Sub Mesh_Button_Click()
    If IsNumeric(Delta_X_Box.Text) And IsNumeric(Delta_Y_Box.Text) Then
        Grid.Cls
        Mesh
    Else
        MsgBox "请确定空间步长均为数字！"
    End If
    Clear_Material_Matrix
    Clear_Select_Matrix
End Sub

'' 等网格回调
Private Sub Same_Grid_Check_Box_Click()
    If Same_Grid_Check_Box.value = 1 Then
        Delta_Y_Box.Text = Delta_X_Box.Text
        Delta_Y_Box.Enabled = False
    Else
        Delta_Y_Box.Enabled = True
    End If
End Sub

'' 等网格跟随
Private Sub Delta_X_Box_Change()
    If Same_Grid_Check_Box.value = 1 Then
        Delta_Y_Box.Text = Delta_X_Box.Text
    End If
End Sub


' 材料指定
Private Sub Select_Material_Button_Click()
    Select Case Material_Combo1.Text
        Case "铸型"
            t = 0
        Case "铸件"
            t = 1
        Case "冷铁"
            t = 2
    End Select
    range_x = Val(Delta_X_Box.Text)
    range_y = Val(Delta_Y_Box.Text)
    For i = 0 To range_x
        For j = 0 To range_y
            If (Select_Matrix(i, j) And InvertSelcet_Check_Box.value = 0) Or (Not Select_Matrix(i, j) And InvertSelcet_Check_Box.value = 1) Then
                Material_Matrix(i, j) = t
            End If
        Next j
    Next i
    Call Redraw_Area(0, range_x, 0, range_y)
    Clear_Select_Matrix
End Sub

' 加载参数

Private Sub Load_Params()
    Dim s() As String
    Dim filename As String
    filename = "data/params.dat"
    i = 0
    Open filename For Input As #1
    Do While Not EOF(1)
        i = i + 1
        ReDim Preserve s(i)
        Line Input #1, s(i)
    Loop
    Close #1
    For Each i In s
        If (Not i = "") And (Not Mid(i, 1, 1) = "#") Then
            MsgBox i
        End If
    Next i
End Sub
