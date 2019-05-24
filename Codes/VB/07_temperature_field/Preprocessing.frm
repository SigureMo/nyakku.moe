VERSION 5.00
Object = "{6B7E6392-850A-101B-AFC0-4210102A8DA7}#1.3#0"; "COMCTL32.OCX"
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.2#0"; "COMDLG32.OCX"
Begin VB.Form Preprocessing 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "温度场前处理程序"
   ClientHeight    =   8880
   ClientLeft      =   2880
   ClientTop       =   2520
   ClientWidth     =   13215
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   8880
   ScaleWidth      =   13215
   Begin VB.Frame Mode_Frame 
      Caption         =   "选择模式"
      Height          =   1935
      Left            =   8520
      TabIndex        =   27
      Top             =   2520
      Width           =   4500
      Begin VB.CommandButton Select_Button 
         Caption         =   "选择"
         Height          =   255
         Left            =   3120
         TabIndex        =   45
         Top             =   1440
         Width           =   1095
      End
      Begin VB.TextBox Radius_Text 
         Height          =   270
         Left            =   3480
         TabIndex        =   41
         Top             =   1080
         Width           =   495
      End
      Begin VB.TextBox Center_Y_Text 
         Height          =   270
         Left            =   2760
         TabIndex        =   40
         Top             =   1080
         Width           =   495
      End
      Begin VB.TextBox Center_X_Text 
         Height          =   270
         Left            =   2160
         TabIndex        =   39
         Top             =   1080
         Width           =   495
      End
      Begin VB.TextBox Rect_EY_Text 
         Height          =   270
         Left            =   3720
         TabIndex        =   38
         Top             =   720
         Width           =   375
      End
      Begin VB.TextBox Rect_EX_Text 
         Height          =   270
         Left            =   3240
         TabIndex        =   37
         Top             =   720
         Width           =   375
      End
      Begin VB.TextBox Rect_SY_Text 
         Height          =   270
         Left            =   2640
         TabIndex        =   36
         Top             =   720
         Width           =   375
      End
      Begin VB.TextBox Rect_SX_Text 
         Height          =   270
         Left            =   2160
         TabIndex        =   35
         Top             =   720
         Width           =   375
      End
      Begin VB.TextBox Point_Y_Text 
         Height          =   270
         Left            =   2640
         TabIndex        =   34
         Top             =   360
         Width           =   375
      End
      Begin VB.TextBox Point_X_Text 
         Height          =   270
         Left            =   2160
         TabIndex        =   33
         Top             =   360
         Width           =   375
      End
      Begin VB.CheckBox Shortcuts_Enable_Check 
         Caption         =   "启用快捷键"
         Height          =   255
         Left            =   1680
         TabIndex        =   32
         Top             =   1440
         Value           =   1  'Checked
         Width           =   1455
      End
      Begin VB.CheckBox Ongoing_Select_Check 
         Caption         =   "连续选择"
         Height          =   255
         Left            =   240
         TabIndex        =   31
         Top             =   1440
         Value           =   1  'Checked
         Width           =   1455
      End
      Begin VB.OptionButton Circle_Select_Option 
         Caption         =   "圆形区域"
         Height          =   375
         Left            =   240
         TabIndex        =   30
         Top             =   960
         Width           =   1095
      End
      Begin VB.OptionButton Rect_Select_Option 
         Caption         =   "矩形区域"
         Height          =   375
         Left            =   240
         TabIndex        =   29
         Top             =   600
         Width           =   1095
      End
      Begin VB.OptionButton Single_Select_Option 
         Caption         =   "点选"
         Height          =   375
         Left            =   240
         TabIndex        =   28
         Top             =   240
         Width           =   1095
      End
      Begin VB.Label MM_Label 
         Caption         =   "(mm)"
         Height          =   255
         Left            =   4080
         TabIndex        =   44
         Top             =   1080
         Width           =   375
      End
      Begin VB.Label Alt_Label 
         AutoSize        =   -1  'True
         Caption         =   "(Alt)"
         Height          =   180
         Left            =   1320
         TabIndex        =   43
         Top             =   1080
         Width           =   450
      End
      Begin VB.Label Shift_Label 
         AutoSize        =   -1  'True
         Caption         =   "(Shift)"
         Height          =   180
         Left            =   1320
         TabIndex        =   42
         Top             =   720
         Width           =   630
      End
   End
   Begin MSComDlg.CommonDialog CommonDialog 
      Left            =   360
      Top             =   240
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   393216
   End
   Begin ComctlLib.StatusBar StatusBar 
      Align           =   2  'Align Bottom
      Height          =   375
      Left            =   0
      TabIndex        =   25
      Top             =   8505
      Width           =   13215
      _ExtentX        =   23310
      _ExtentY        =   661
      SimpleText      =   ""
      _Version        =   327682
      BeginProperty Panels {0713E89E-850A-101B-AFC0-4210102A8DA7} 
         NumPanels       =   3
         BeginProperty Panel1 {0713E89F-850A-101B-AFC0-4210102A8DA7} 
            Object.Width           =   3528
            MinWidth        =   3528
            Key             =   ""
            Object.Tag             =   ""
         EndProperty
         BeginProperty Panel2 {0713E89F-850A-101B-AFC0-4210102A8DA7} 
            Object.Width           =   5292
            MinWidth        =   5292
            Key             =   ""
            Object.Tag             =   ""
         EndProperty
         BeginProperty Panel3 {0713E89F-850A-101B-AFC0-4210102A8DA7} 
            Object.Width           =   9701
            MinWidth        =   9701
            Key             =   ""
            Object.Tag             =   ""
         EndProperty
      EndProperty
   End
   Begin VB.Frame Fill_Option_Frame 
      Caption         =   "填充选项"
      Height          =   915
      Left            =   8520
      TabIndex        =   9
      Top             =   4560
      Width           =   4500
      Begin VB.ComboBox Material_Combo 
         Height          =   300
         ItemData        =   "Preprocessing.frx":0000
         Left            =   1320
         List            =   "Preprocessing.frx":000D
         Style           =   2  'Dropdown List
         TabIndex        =   12
         Top             =   360
         Width           =   1455
      End
      Begin VB.CommandButton Select_Material_Button 
         Caption         =   "指定材料"
         Height          =   495
         Left            =   2880
         TabIndex        =   11
         Top             =   240
         Width           =   1455
      End
      Begin VB.CheckBox InvertSelect_Check_Box 
         Caption         =   "反向填充"
         Height          =   255
         Left            =   240
         TabIndex        =   10
         Top             =   360
         Width           =   1215
      End
   End
   Begin VB.Frame Frame2 
      Caption         =   "材料设置"
      Height          =   2745
      Left            =   8520
      TabIndex        =   8
      Top             =   5640
      Width           =   4500
      Begin VB.PictureBox Chill_Color 
         BackColor       =   &H00FF0000&
         BorderStyle     =   0  'None
         Height          =   255
         Left            =   1680
         ScaleHeight     =   255
         ScaleWidth      =   615
         TabIndex        =   24
         Top             =   2040
         Width           =   615
      End
      Begin VB.PictureBox Casting_Color 
         BackColor       =   &H000000FF&
         BorderStyle     =   0  'None
         Height          =   255
         Left            =   1680
         ScaleHeight     =   255
         ScaleWidth      =   615
         TabIndex        =   23
         Top             =   1440
         Width           =   615
      End
      Begin VB.PictureBox Sand_Color 
         BackColor       =   &H0000FFFF&
         BorderStyle     =   0  'None
         Height          =   255
         Left            =   1680
         ScaleHeight     =   255
         ScaleWidth      =   615
         TabIndex        =   22
         Top             =   840
         Width           =   615
      End
      Begin VB.ComboBox Chill_Combo 
         Height          =   300
         Left            =   3000
         Style           =   2  'Dropdown List
         TabIndex        =   18
         Top             =   2040
         Width           =   1095
      End
      Begin VB.ComboBox Casting_Combo 
         Height          =   300
         Left            =   3000
         Style           =   2  'Dropdown List
         TabIndex        =   17
         Top             =   1440
         Width           =   1095
      End
      Begin VB.ComboBox Sand_Combo 
         Height          =   300
         ItemData        =   "Preprocessing.frx":0023
         Left            =   3000
         List            =   "Preprocessing.frx":0025
         Style           =   2  'Dropdown List
         TabIndex        =   16
         Top             =   840
         Width           =   1095
      End
      Begin VB.Label Chill_Label 
         AutoSize        =   -1  'True
         Caption         =   "冷铁"
         Height          =   180
         Left            =   480
         TabIndex        =   21
         Top             =   2040
         Width           =   360
      End
      Begin VB.Label Casting_Label 
         AutoSize        =   -1  'True
         Caption         =   "铸件"
         Height          =   180
         Left            =   480
         TabIndex        =   20
         Top             =   1440
         Width           =   360
      End
      Begin VB.Label Sand_Label 
         AutoSize        =   -1  'True
         Caption         =   "铸型"
         Height          =   180
         Left            =   480
         TabIndex        =   19
         Top             =   840
         Width           =   360
      End
      Begin VB.Line Line2 
         X1              =   2640
         X2              =   2640
         Y1              =   840
         Y2              =   2280
      End
      Begin VB.Line Line1 
         X1              =   1320
         X2              =   1320
         Y1              =   840
         Y2              =   2280
      End
      Begin VB.Label Materals_Select_Label 
         AutoSize        =   -1  'True
         Caption         =   "材料选择"
         Height          =   180
         Left            =   3120
         TabIndex        =   15
         Top             =   360
         Width           =   720
      End
      Begin VB.Label Color_Label 
         AutoSize        =   -1  'True
         Caption         =   "颜色"
         Height          =   180
         Left            =   1800
         TabIndex        =   14
         Top             =   360
         Width           =   360
      End
      Begin VB.Label Material_Type_Label 
         AutoSize        =   -1  'True
         Caption         =   "材料类型"
         Height          =   180
         Left            =   360
         TabIndex        =   13
         Top             =   360
         Width           =   720
      End
   End
   Begin VB.Frame Frame1 
      Caption         =   "网格设置"
      Height          =   2220
      Left            =   8520
      TabIndex        =   1
      Top             =   240
      Width           =   4500
      Begin VB.CommandButton Micro_Mesh_Button 
         Caption         =   "细致划分"
         Height          =   495
         Left            =   2640
         TabIndex        =   26
         Top             =   1560
         Width           =   1455
      End
      Begin VB.CommandButton Mesh_Button 
         Caption         =   "生成网格"
         Height          =   500
         Left            =   480
         TabIndex        =   7
         Top             =   1560
         Width           =   1455
      End
      Begin VB.TextBox Delta_Y_Box 
         Height          =   375
         Left            =   3120
         TabIndex        =   6
         Text            =   "25"
         Top             =   1000
         Width           =   1000
      End
      Begin VB.TextBox Delta_X_Box 
         Height          =   375
         Left            =   960
         TabIndex        =   4
         Text            =   "25"
         Top             =   1000
         Width           =   1000
      End
      Begin VB.CheckBox Same_Grid_Check_Box 
         Caption         =   "等网格"
         Height          =   255
         Left            =   600
         TabIndex        =   2
         Top             =   480
         Width           =   1095
      End
      Begin VB.Label Delta_Y_Label 
         AutoSize        =   -1  'True
         Caption         =   "Δy"
         Height          =   180
         Left            =   2280
         TabIndex        =   5
         Top             =   1080
         Width           =   270
      End
      Begin VB.Label Delta_X_Label 
         AutoSize        =   -1  'True
         Caption         =   "Δx"
         Height          =   180
         Left            =   300
         TabIndex        =   3
         Top             =   1080
         Width           =   270
      End
   End
   Begin VB.PictureBox Grid 
      AutoRedraw      =   -1  'True
      Height          =   8000
      Left            =   240
      ScaleHeight     =   7935
      ScaleWidth      =   7935
      TabIndex        =   0
      Top             =   200
      Width           =   8000
   End
   Begin VB.Menu File 
      Caption         =   "文件"
      Begin VB.Menu Data_Import 
         Caption         =   "导入数据"
         Shortcut        =   ^O
      End
      Begin VB.Menu Data_Export 
         Caption         =   "导出数据"
         Shortcut        =   ^S
      End
      Begin VB.Menu Graph_Export 
         Caption         =   "导出云图"
         Shortcut        =   ^P
      End
   End
End
Attribute VB_Name = "Preprocessing"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Dim Material_Matrix(1000, 1000) As Integer
Dim Select_Matrix(1000, 1000) As Boolean
Dim grid_w%, grid_l%
Dim start_x%, start_y%
Dim Center_x!, Center_y!
Dim Meshed As Boolean
Dim Tips_arr
Dim click_cnt%
Dim Material_List() As Material

Private Sub Form_Load()
    Init_Material_Params
    Meshed = False
    grid_w = 500
    grid_l = 500
    start_x = -1
    Center_x = -1
    Tips_arr = Array("Alt 为选中圆形区域， Shift 选中矩形区域", _
                     "支持按住 Ctrl 连续点选哦！", _
                     "既想要区域选又想要连续选怎么办？试试按键组合！", _
                     "右键一下选择区域就都清空了呢~", _
                     "适当使用反向填充会有奇效哦！", _
                     "单击滑轮就可以快速填充材料！", _
                     "本程序以 mm 为单位哦，整体长度为 " & grid_w & "，整体宽度为 " & grid_l)
    click_cnt = 0
    Call Load_Params(Material_List)
    For i = 0 To UBound(Material_List)
        If Material_List(i).type = SAND Then
            Sand_Combo.AddItem (i & "," & Material_List(i).name)
        ElseIf Material_List(i).type = CASTING Then
            Casting_Combo.AddItem (i & "," & Material_List(i).name)
        ElseIf Material_List(i).type = CHILL Then
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
    Grid.Scale (0, range_y)-(range_x, 0)
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
Private Sub Grid_MouseDown(Button As Integer, Shift As Integer, X As Single, Y As Single)
    click_cnt = click_cnt + 1
    StatusBar.Panels(3).Text = "Tips:" & Tips_arr(click_cnt Mod (UBound(Tips_arr) - LBound(Tips_arr) + 1))
    Dim real_x%, real_y%, Mode%, Ongoing As Boolean
    Dim x_mm!, y_mm!, radius!
    Dim delta_x%, delta_y%
    If Not Meshed Then
        MsgBox "请先生成网格"
        Exit Sub
    End If
    delta_x = 500 / range_x
    delta_y = 500 / range_y
    If Button = 1 Then
        Call Get_Mode(Shift, Mode, Ongoing)
        real_x = Int(X)
        real_y = Int(Y)
        x_mm = (real_x + 0.5) * delta_x
        y_mm = (real_y + 0.5) * delta_y
        StatusBar.Panels(2).Text = "已选择点 (" & real_x + 1 & ", " & real_y + 1 & ")"
        If Not Ongoing Then
            Clear_Select_Matrix
        End If
        If Mode = 0 Then
            Point_X_Text.Text = real_x + 1
            Point_Y_Text.Text = real_y + 1
            Select_Matrix(real_x, real_y) = True
            start_x = real_x
            start_y = real_y
            Center_x = x_mm
            Center_y = y_mm
        ElseIf Mode = 1 Then
            If Not start_x = -1 Then
                Call Mark_Area(start_x, real_x, start_y, real_y)
                Rect_EX_Text.Text = real_x + 1
                Rect_EY_Text.Text = real_y + 1
                start_x = -1
            Else
                start_x = real_x
                start_y = real_y
                Rect_SX_Text = real_x + 1
                Rect_SY_Text = real_y + 1
            End If
        ElseIf Mode = 2 Then
            If Center_x >= 0 Then
                radius = Sqr((Center_x - x_mm) ^ 2 + (Center_y - y_mm) ^ 2) + 1
                Call Mark_Circle(Center_x, Center_y, radius)
                Radius_Text.Text = radius
                Center_x = -1
            Else
                Center_x = x_mm
                Center_y = y_mm
                Center_X_Text.Text = x_mm
                Center_Y_Text.Text = y_mm
            End If
        End If
    ElseIf Button = 2 Then
        Clear_Select_Matrix
    ElseIf Button = 4 Then
        Select_Material_Button_Click
    End If
    Call Redraw_Area(0, range_x, 0, range_y)
    Call Redraw_Sec_Area(0, range_x, 0, range_y)
End Sub

''' 检查模式
Private Sub Get_Mode(Shift As Integer, ByRef Mode%, ByRef Ongoing As Boolean)
    Dim ShiftDown As Boolean, AltDown As Boolean, CtrlDown As Boolean
    ShiftDown = (Shift And vbShiftMask) > 0
    CtrlDown = (Shift And vbCtrlMask) > 0
    AltDown = (Shift And vbAltMask) > 0
    Ongoing = False
    If Shortcuts_Enable_Check.value Then
        If ShiftDown Then
            Mode = 1
        ElseIf AltDown Then
            Mode = 2
        Else
            Mode = 0
        End If
        If CtrlDown Then
            Ongoing = True
        End If
    Else
        If Single_Select_Option.value Then
            Mode = 0
        ElseIf Rect_Select_Option.value Then
            Mode = 1
        ElseIf Circle_Select_Option.value Then
            Mode = 2
        End If
        If Ongoing_Select_Check.value Then
            Ongoing = True
        End If
    End If
End Sub

'' 鼠标移动回调
Private Sub Grid_MouseMove(Button As Integer, Shift As Integer, X As Single, Y As Single)
    If Meshed Then
        StatusBar.Panels(1).Text = "当前位置为(" & Int(X) + 1 & ", " & Int(Y) + 1 & ")"
    End If
End Sub

'' Shift 区域选择
Private Sub Mark_Area(x_start As Integer, x_end As Integer, y_start As Integer, y_end As Integer)
    Dim x_step, y_step
    x_step = 1
    y_step = 1
    If x_start > x_end Then
        x_step = -1
    End If
    If y_start > y_end Then
        y_step = -1
    End If
    For i = x_start To x_end Step x_step
        For j = y_start To y_end Step y_step
            Select_Matrix(i, j) = True
        Next j
    Next i
    StatusBar.Panels(2).Text = "已选择矩形区域 (" & x_start + 1 & ", " & y_start + 1 & ")-(" & x_end + 1 & ", " & y_end + 1 & ")"
End Sub

'' 圆形区域选择
Private Sub Mark_Circle(Center_x!, Center_y!, radius!)
    Dim delta_x%, delta_y%
    Dim start_x%, start_y%, end_x%, end_y%
    Dim x_mm!, y_mm!
    delta_x = 500 / range_x
    delta_y = 500 / range_y
    start_x = Int((Center_x - radius) / delta_x) - 1
    start_y = Int((Center_y - radius) / delta_y) - 1
    end_x = Int((Center_x + radius) / delta_x) + 1
    end_y = Int((Center_y + radius) / delta_y) + 1
    For i = start_x To end_x
        For j = start_y To end_y
            If i >= 0 And i < range_x And j >= 0 And j < range_y Then
                x_mm = (i + 0.5) * delta_x
                y_mm = (j + 0.5) * delta_y
                If Sqr((Center_x - x_mm) ^ 2 + (Center_y - y_mm) ^ 2) <= radius Then
                    Select_Matrix(i, j) = True
                End If
            End If
        Next j
    Next i
    StatusBar.Panels(2).Text = "已选择圆形区域 (" & Center_x & ", " & Center_y & ")" & " 半径" & radius & " mm"
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
    Dim delta_x%, delta_y%
    If Not IsNumeric(Delta_X_Box.Text) Or Not IsNumeric(Delta_Y_Box.Text) Then
        MsgBox "请确定空间步长均为数字！"
        Exit Sub
    End If
    
    delta_x = Val(Delta_X_Box.Text)
    delta_y = Val(Delta_Y_Box.Text)
    
    If delta_x < 1 Or delta_y < 1 Then
        MsgBox "空间步长应为正整数"
        Exit Sub
    ElseIf grid_w Mod delta_x Or grid_l Mod delta_y Then
        MsgBox "请确定该区域可被正确划分（可整除）"
        Exit Sub
    End If
    
    range_x_tmp = grid_w / delta_x
    range_y_tmp = grid_l / delta_y
    
    If range_x_tmp > 1000 Or range_y_tmp > 1000 Then
        MsgBox "空间步长太小，最多划分为 1000 * 1000 的网格"
        Exit Sub
    ElseIf range_x_tmp * range_y_tmp > 10000 Then
            MsgBox "本程序对于过于精细的划分支持并不好，如有卡顿现象请见谅……"
    End If
    
    range_x = range_x_tmp
    range_y = range_y_tmp
    Grid.Cls
    Mesh
    Clear_Material_Matrix
    Clear_Select_Matrix
    Call Redraw_Area(0, range_x, 0, range_y)
    Mesh_Button.Caption = "重新划分"
End Sub

'' 细致划分回调
Private Sub Micro_Mesh_Button_Click()
    Dim delta_x%, delta_y%
    Dim xc%, yc%
    Dim Tmp_Matrix(1000, 1000)
    delta_x = 500 / range_x
    delta_y = 500 / range_y
    If Not Meshed Then
        MsgBox "请先生成网格"
        Exit Sub
    End If
    If Val(Delta_X_Box) <= 0 Or Val(Delta_X_Box) > delta_x Or Val(Delta_Y_Box) <= 0 Or Val(Delta_Y_Box) > delta_y Then
        MsgBox "请确保当前网格比原网格更精细"
        Exit Sub
    End If
    If delta_x Mod Val(Delta_X_Box) Or delta_y Mod Val(Delta_Y_Box) Then
        MsgBox "请确保当前网格大小能被原网格大小整除"
        Exit Sub
    End If
    xc = delta_x / Val(Delta_X_Box)
    yc = delta_y / Val(Delta_Y_Box)
    new_range_x = 500 / Val(Delta_X_Box)
    new_range_y = 500 / Val(Delta_Y_Box)
    For i = 0 To new_range_x - 1
        For j = 0 To new_range_y - 1
            Tmp_Matrix(i, j) = Material_Matrix(Int(i / xc), Int(j / yc))
        Next j
    Next i
    range_x = new_range_x
    range_y = new_range_y
    For i = 0 To range_x - 1
        For j = 0 To range_y - 1
           Material_Matrix(i, j) = Tmp_Matrix(i, j)
        Next j
    Next i
    Grid.Scale (0, range_y)-(range_x, 0)
    Call Redraw_Area(0, range_x, 0, range_y)
    Mesh
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

' 模式选择相关
'' 启用快捷键回调
Private Sub Shortcuts_Enable_Check_Click()
    If Shortcuts_Enable_Check.value Then
        Shift_Label.Visible = True
        Alt_Label.Visible = True
    Else
        Shift_Label.Visible = False
        Alt_Label.Visible = False
    End If
End Sub

'' 选择参数所示区域
Private Sub Select_Button_Click()
    On Error GoTo ErrorHandler
    If Not Meshed Then
        MsgBox "请先生成网格"
        Exit Sub
    End If
    
    If Not Ongoing_Select_Check.value Then
        Clear_Select_Matrix
    End If
    If Single_Select_Option.value Then
        Select_Matrix(Point_X_Text.Text - 1, Point_Y_Text.Text - 1) = True
    ElseIf Rect_Select_Option.value Then
        Call Mark_Area(Rect_SX_Text.Text - 1, Rect_EX_Text.Text - 1, Rect_SY_Text.Text - 1, Rect_EY_Text.Text - 1)
    ElseIf Circle_Select_Option.value Then
        Call Mark_Circle(Center_X_Text.Text, Center_Y_Text.Text, Radius_Text.Text)
    End If
    Call Redraw_Area(0, range_x, 0, range_y)
    Call Redraw_Sec_Area(0, range_x, 0, range_y)
ErrorHandler:
    MsgBox "请确保输入以及选项正确！"
    Exit Sub
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

' 颜色修改
Private Sub Sand_Color_Click()
    Set_Color (SAND)
    Call Redraw_Area(0, range_x, 0, range_y)
End Sub

Private Sub Casting_Color_Click()
    Set_Color (CASTING)
    Call Redraw_Area(0, range_x, 0, range_y)
End Sub

Private Sub Chill_Color_Click()
    Set_Color (CHILL)
    Call Redraw_Area(0, range_x, 0, range_y)
End Sub

'' 颜色弹窗
Private Sub Set_Color(t As Integer)
    Dim pallets(), color
    pallets = Array(Sand_Color, Casting_Color, Chill_Color)
    On Error GoTo ErrHandler
    CommonDialog.CancelError = True
    CommonDialog.Flags = cdlCCRGBInit
    CommonDialog.ShowColor
    color = CommonDialog.color
    color_arr(t) = color
    pallets(t).BackColor = color
ErrHandler:
    Exit Sub
End Sub

'' 导入数据
Private Sub Data_Import_Click()
    On Error GoTo ErrHandler
    Dim filename As String
    filename = App.Path & "\data\mesh.dat"
    CommonDialog.CancelError = True
    CommonDialog.Flags = cdlOFNHideReadOnly
    CommonDialog.Filter = "All Files (*.*)|*.*|Text Files (*.txt)|*.txt|Binary Files (*.dat)|*.dat"
    CommonDialog.filename = filename
    CommonDialog.FilterIndex = 3
    CommonDialog.ShowOpen
    filename = CommonDialog.filename
    Dim cnt%, line%
    Dim s As String
    i = 0
    line = 0
    Open filename For Input As #1
        Do While Not EOF(1)
            Line Input #1, s
            If Not s = "" Then
                If Mid(s, 1, 3) = "###" Then
                    cnt = cnt + 1
                    line = 0
                Else
                    Select Case cnt
                        Case 2
                            range_x = Val(Split(s, ",")(0))
                            range_y = Val(Split(s, ",")(1))
                            delta_x = 500 / range_x
                            delta_y = 500 / range_y
                            Delta_X_Box.Text = delta_x
                            Delta_Y_Box.Text = delta_y
                            Grid.Scale (0, range_y)-(range_x, 0)
                            Mesh
                        Case 3
                            j = 0
                            For Each c In Split(s, ",")
                                Material_Matrix(line, j) = Val(c)
                                j = j + 1
                            Next c
                    End Select
                    line = line + 1
                End If
            End If
        Loop
    Close #1
    Call Redraw_Area(0, range_x, 0, range_y)
    Mesh
ErrHandler:
    Exit Sub
End Sub

' 导出数据
Private Sub Data_Export_Click()
    If Not Meshed Then
        MsgBox "请先生成网格"
        Exit Sub
    End If
    On Error GoTo ErrHandler
    Dim filename As String
    filename = App.Path & "\data\mesh.dat"
    CommonDialog.CancelError = True
    CommonDialog.Flags = cdlOFNHideReadOnly
    CommonDialog.Filter = "All Files (*.*)|*.*|Text Files (*.txt)|*.txt|Binary Files (*.dat)|*.dat"
    CommonDialog.filename = filename
    CommonDialog.FilterIndex = 3
    CommonDialog.ShowSave
    filename = CommonDialog.filename

    Dim line As String
    Open filename For Output As #1
        Print #1, "### Materials"
        Print #1, MaterialToString(Material_List(Val(Split(Sand_Combo.Text, ",")(0))))
        Print #1, MaterialToString(Material_List(Val(Split(Casting_Combo.Text, ",")(0))))
        Print #1, MaterialToString(Material_List(Val(Split(Chill_Combo.Text, ",")(0))))
        Print #1, ""
        
        Print #1, "### Range"
        Print #1, range_x & "," & range_y
        Print #1, ""
        
        Print #1, "### Matrix"
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
        Print #1, ""
    Close #1
ErrHandler:
    Exit Sub
End Sub

'导出云图
Private Sub Graph_Export_Click()
    If Not Meshed Then
        MsgBox "请先生成网格"
        Exit Sub
    End If
    Call Export_Picture(Grid, CommonDialog, "前处理.bmp")
End Sub

' 加载材料参数文件
Private Sub Load_Params(ByRef Material_List() As Material)
    Dim s As String
    Dim filename As String
    filename = App.Path & "\data\params.dat"
    i = 0
    Open filename For Input As #1
        Do While Not EOF(1)
            Line Input #1, s
            If Not (s = "" Or Mid(s, 1, 1) = "#") Then
                ReDim Preserve Material_List(i)
                Material_List(i) = StringToMaterial(s)
                i = i + 1
            End If
        Loop
    Close #1
End Sub
