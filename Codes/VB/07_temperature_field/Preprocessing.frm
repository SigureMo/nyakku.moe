VERSION 5.00
Begin VB.Form Form1 
   Caption         =   "Form1"
   ClientHeight    =   8775
   ClientLeft      =   2955
   ClientTop       =   2295
   ClientWidth     =   11565
   LinkTopic       =   "Form1"
   ScaleHeight     =   8775
   ScaleWidth      =   11565
   Begin VB.CommandButton Data_Export_Button 
      Caption         =   "导出数据"
      Height          =   615
      Left            =   9240
      TabIndex        =   15
      Top             =   7680
      Width           =   1455
   End
   Begin VB.Frame Frame3 
      Caption         =   "点选设置"
      Height          =   1575
      Left            =   6960
      TabIndex        =   10
      Top             =   3000
      Width           =   4215
      Begin VB.ComboBox Material_Combo 
         Height          =   300
         ItemData        =   "Preprocessing.frx":0000
         Left            =   480
         List            =   "Preprocessing.frx":000D
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
      Begin VB.CheckBox InvertSelect_Check_Box 
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
      Height          =   2295
      Left            =   6840
      TabIndex        =   9
      Top             =   5160
      Width           =   4455
      Begin VB.PictureBox Chill_Color 
         BackColor       =   &H00FF0000&
         Height          =   255
         Left            =   1680
         ScaleHeight     =   195
         ScaleWidth      =   555
         TabIndex        =   27
         Top             =   1560
         Width           =   615
      End
      Begin VB.PictureBox Casting_Color 
         BackColor       =   &H000000FF&
         Height          =   255
         Left            =   1680
         ScaleHeight     =   195
         ScaleWidth      =   555
         TabIndex        =   26
         Top             =   1200
         Width           =   615
      End
      Begin VB.PictureBox Sand_Color 
         BackColor       =   &H0000FFFF&
         Height          =   255
         Left            =   1680
         ScaleHeight     =   195
         ScaleWidth      =   555
         TabIndex        =   25
         Top             =   720
         Width           =   615
      End
      Begin VB.ComboBox Chill_Combo 
         Height          =   300
         Left            =   3000
         Style           =   2  'Dropdown List
         TabIndex        =   21
         Top             =   1680
         Width           =   1095
      End
      Begin VB.ComboBox Casting_Combo 
         Height          =   300
         Left            =   3000
         Style           =   2  'Dropdown List
         TabIndex        =   20
         Top             =   1200
         Width           =   1095
      End
      Begin VB.ComboBox Sand_Combo 
         Height          =   300
         ItemData        =   "Preprocessing.frx":0023
         Left            =   3000
         List            =   "Preprocessing.frx":0025
         Style           =   2  'Dropdown List
         TabIndex        =   19
         Top             =   720
         Width           =   975
      End
      Begin VB.Label Chill_Label 
         AutoSize        =   -1  'True
         Caption         =   "冷铁"
         Height          =   180
         Left            =   480
         TabIndex        =   24
         Top             =   1440
         Width           =   360
      End
      Begin VB.Label Casting_Label 
         AutoSize        =   -1  'True
         Caption         =   "铸件"
         Height          =   180
         Left            =   480
         TabIndex        =   23
         Top             =   1080
         Width           =   360
      End
      Begin VB.Label Sand_Label 
         AutoSize        =   -1  'True
         Caption         =   "铸型"
         Height          =   180
         Left            =   480
         TabIndex        =   22
         Top             =   720
         Width           =   360
      End
      Begin VB.Line Line2 
         X1              =   2640
         X2              =   2640
         Y1              =   480
         Y2              =   1800
      End
      Begin VB.Line Line1 
         X1              =   1320
         X2              =   1320
         Y1              =   480
         Y2              =   1680
      End
      Begin VB.Label Materals_Select_Label 
         AutoSize        =   -1  'True
         Caption         =   "材料选择"
         Height          =   180
         Left            =   3120
         TabIndex        =   18
         Top             =   240
         Width           =   720
      End
      Begin VB.Label Color_Label 
         AutoSize        =   -1  'True
         Caption         =   "颜色"
         Height          =   180
         Left            =   1800
         TabIndex        =   17
         Top             =   360
         Width           =   360
      End
      Begin VB.Label Material_Type_Label 
         AutoSize        =   -1  'True
         Caption         =   "材料类型"
         Height          =   180
         Left            =   360
         TabIndex        =   16
         Top             =   360
         Width           =   720
      End
   End
   Begin VB.PictureBox Msg_Box 
      Height          =   495
      Left            =   240
      ScaleHeight     =   435
      ScaleWidth      =   5955
      TabIndex        =   8
      Top             =   7920
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
      Height          =   540
      Left            =   360
      TabIndex        =   12
      Top             =   7200
      Width           =   4410
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
Dim grid_w%, grid_l%
Dim Start_x%, Start_y%
Dim Meshed As Boolean
Dim color_arr
Dim Tips_arr
Dim click_cnt%
Dim SAND%, CASTING%, CHILL%, SEC%
Dim Materials(2) As Material
Dim Material_List() As Material

Private Sub Form_Load()
    Meshed = False
    grid_w = 500
    grid_l = 500
    color_arr = Array(vbYellow, vbRed, vbBlue)
    Start_x = -1
    SAND = 0
    CASTING = 1
    CHILL = 2
    Tips_arr = Array("支持按住 Shift 进行区域选择哦！", "支持按住 Ctrl 连续点选哦！", "Shift Ctrl 同时按住也是支持的哦", "适当使用反向填充会有奇效哦！", "本程序以 mm 为单位哦，整体长度为" & grid_w & "，整体宽度为" & grid_l)
    click_cnt = 0
    Call Load_Params(Material_List)
    For i = 0 To UBound(Material_List)
        If Material_List(i).type_ = SAND Then
            Sand_Combo.AddItem (i & "," & Material_List(i).name)
        ElseIf Material_List(i).type_ = CASTING Then
            Casting_Combo.AddItem (i & "," & Material_List(i).name)
        ElseIf Material_List(i).type_ = CHILL Then
            Chill_Combo.AddItem (i & "," & Material_List(i).name)
        End If
    Next i
    Sand_Combo.Text = Sand_Combo.List(0)
    Casting_Combo.Text = Casting_Combo.List(0)
    Chill_Combo.Text = Chill_Combo.List(0)
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

'' 绘制外圈边界
Private Sub Redraw_Border()
    Grid.Line (0, 0)-(range_x, 1 / 2), vbBlack, BF
    Grid.Line (0, range_y - 1 / 2)-(range_x, range_y), vbBlack, BF
    Grid.Line (0, 0)-(1 / 2, range_y), vbBlack, BF
    Grid.Line (range_x - 1 / 2, 0)-(range_x, range_y), vbBlack, BF
End Sub

'' 绘制网格
Private Sub Mesh()
    Grid.Scale (0, 0)-(range_x, range_y)
    For i = 0 To range_x
        Grid.Line (i, 0)-(i, range_y)
    Next i
    For i = 0 To range_y
        Grid.Line (0, i)-(range_x, i)
    Next i
    Redraw_Border
    Meshed = True
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
        Msg_Box.Cls
        Msg_Box.Print "已选择点 (" & real_x & ", " & real_y & ")"
        If Shift = 1 Or Shift = 3 Then
            If Shift = 1 Then
                Clear_Select_Matrix
            End If
            If Not Start_x = -1 Then
                Call Mark_Area(Start_x, real_x, Start_y, real_y)
                Msg_Box.Cls
                Msg_Box.Print "已选择区域 (" & Start_x & ", " & Start_y & ")-(" & real_x & ", " & real_y & ")"
                Start_x = -1
            Else
                Start_x = real_x
                Start_y = real_y
            End If
        ElseIf Shift = 0 Or Shift = 2 Then
            Start_x = real_x
            Start_y = real_y
            If Shift = 0 Then
                Clear_Select_Matrix
            End If
            Select_Matrix(real_x, real_y) = True
        End If
        Call Redraw_Area(0, range_x, 0, range_y)
        Call Redraw_Sec_Area(0, range_x, 0, range_y)
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

'' 根据选择矩阵设置材料矩阵
Private Sub Set_Values_By_SecMatrix(value As Integer)
    For i = 0 To range_x - 1
        For j = 0 To range_y - 1
            If Select_Matrix(i, j) Then
                Material_Matrix(i, j) = value
            End If
        Next j
    Next i
End Sub

'' 清空选择矩阵
Private Sub Clear_Select_Matrix()
    For i = 0 To range_x - 1
        For j = 0 To range_y - 1
            Select_Matrix(i, j) = False
        Next j
    Next i
End Sub

'' 清空材料矩阵
Private Sub Clear_Material_Matrix()
    For i = 0 To range_x - 1
        For j = 0 To range_y - 1
            Material_Matrix(i, j) = 0
        Next j
    Next i
End Sub


' 网格设置

'' 网格生成回调
Private Sub Mesh_Button_Click()
    If IsNumeric(Delta_X_Box.Text) And IsNumeric(Delta_Y_Box.Text) Then
        delta_x = Val(Delta_X_Box.Text)
        delta_y = Val(Delta_Y_Box.Text)
        
        If delta_x < 1 Or delta_y < 1 Then
            MsgBox "空间步长应为正整数"
        ElseIf grid_w Mod delta_x And grid_l Mod delta_y Then
            MsgBox "请确定该区域可被正确划分（可整除）"
        Else
            range_x_tmp = grid_w / delta_x
            range_y_tmp = grid_l / delta_y
            If range_x_tmp > 1000 Or range_y_tmp > 1000 Then
                MsgBox "空间步长太小，最多划分为 1000 * 1000 的网格"
            Else
                If range_x_tmp * range_y_tmp > 10000 Then
                    MsgBox "本程序对于过于精细的划分支持并不好，如有卡顿现象请见谅……"
                End If
                range_x = range_x_tmp
                range_y = range_y_tmp
                Grid.Cls
                Mesh
            End If
        End If
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
    If Not Meshed Then
        MsgBox "请先生成网格"
        Exit Sub
    End If
    Select Case Material_Combo.Text
        Case "铸型"
            t = 0
        Case "铸件"
            t = 1
        Case "冷铁"
            t = 2
    End Select
    For i = 0 To range_x - 1
        For j = 0 To range_y - 1
            If (Select_Matrix(i, j) And InvertSelect_Check_Box.value = 0) Or (Not Select_Matrix(i, j) And InvertSelect_Check_Box.value = 1) Then
                Material_Matrix(i, j) = t
            End If
        Next j
    Next i
    Call Redraw_Area(0, range_x, 0, range_y)
    Clear_Select_Matrix
End Sub


' 导出数据

Private Sub Data_Export_Button_Click()
    Materials(0) = Material_List(Val(Split(Sand_Combo.Text, ",")(0)))
    Materials(1) = Material_List(Val(Split(Casting_Combo.Text, ",")(0)))
    Materials(2) = Material_List(Val(Split(Chill_Combo.Text, ",")(0)))
    Call Save_Materials(Materials)
    Dim line As String
    Open "data/mesh.dat" For Append As #1
    Print #1, "RANGE" & ":" & range_x & "," & range_y
    For i = 0 To range_x - 1
        line = ""
        For j = 0 To range_y - 1
            If Not j = 0 Then
                line = line & ","
            End If
            line = line & Material_Matrix(i, j)
        Next j
        Print #1, line
    Next i
    Close #1
End Sub
