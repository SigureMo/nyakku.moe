VERSION 5.00
Object = "{6B7E6392-850A-101B-AFC0-4210102A8DA7}#1.3#0"; "COMCTL32.OCX"
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.2#0"; "COMDLG32.OCX"
Begin VB.Form Main 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "温度场后处理程序"
   ClientHeight    =   9555
   ClientLeft      =   1875
   ClientTop       =   3120
   ClientWidth     =   13260
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   9555
   ScaleWidth      =   13260
   Begin VB.Frame Options_Frame 
      Caption         =   "计算动态演示及选项"
      Height          =   2535
      Left            =   10440
      TabIndex        =   5
      Top             =   3600
      Width           =   2415
      Begin VB.CheckBox Only_Phase_CheckBox 
         Caption         =   "仅显示相态"
         Height          =   375
         Left            =   360
         TabIndex        =   8
         Top             =   1680
         Width           =   1335
      End
      Begin VB.CheckBox Dynamic_View_CheckBox 
         Caption         =   "动态过程演示"
         Height          =   495
         Left            =   360
         TabIndex        =   7
         Top             =   1080
         Value           =   1  'Checked
         Width           =   1695
      End
      Begin VB.CheckBox Hidden_Sand_CheckBox 
         Caption         =   "仅显示铸件"
         Height          =   495
         Left            =   360
         TabIndex        =   6
         Top             =   480
         Value           =   1  'Checked
         Width           =   1575
      End
   End
   Begin VB.CommandButton Show_T_Profile_Button 
      Caption         =   "显示温度曲线"
      Height          =   735
      Left            =   10440
      TabIndex        =   4
      Top             =   2160
      Width           =   2295
   End
   Begin VB.CommandButton Compute_Button 
      Caption         =   "开始计算"
      Height          =   735
      Left            =   10440
      TabIndex        =   3
      Top             =   840
      Width           =   2295
   End
   Begin MSComDlg.CommonDialog CommonDialog 
      Left            =   240
      Top             =   240
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   393216
   End
   Begin ComctlLib.StatusBar StatusBar 
      Align           =   2  'Align Bottom
      Height          =   375
      Left            =   0
      TabIndex        =   2
      Top             =   9180
      Width           =   13260
      _ExtentX        =   23389
      _ExtentY        =   661
      SimpleText      =   ""
      _Version        =   327682
      BeginProperty Panels {0713E89E-850A-101B-AFC0-4210102A8DA7} 
         NumPanels       =   4
         BeginProperty Panel1 {0713E89F-850A-101B-AFC0-4210102A8DA7} 
            Key             =   ""
            Object.Tag             =   ""
         EndProperty
         BeginProperty Panel2 {0713E89F-850A-101B-AFC0-4210102A8DA7} 
            Key             =   ""
            Object.Tag             =   ""
         EndProperty
         BeginProperty Panel3 {0713E89F-850A-101B-AFC0-4210102A8DA7} 
            Object.Width           =   3528
            MinWidth        =   3528
            Key             =   ""
            Object.Tag             =   ""
         EndProperty
         BeginProperty Panel4 {0713E89F-850A-101B-AFC0-4210102A8DA7} 
            Object.Width           =   5292
            MinWidth        =   5292
            Key             =   ""
            Object.Tag             =   ""
         EndProperty
      EndProperty
   End
   Begin ComctlLib.ProgressBar ProgressBar 
      Height          =   375
      Left            =   120
      TabIndex        =   1
      Top             =   8640
      Width           =   9735
      _ExtentX        =   17171
      _ExtentY        =   661
      _Version        =   327682
      Appearance      =   1
   End
   Begin VB.PictureBox Grid 
      AutoRedraw      =   -1  'True
      Height          =   8000
      Left            =   240
      ScaleHeight     =   7935
      ScaleWidth      =   9540
      TabIndex        =   0
      Top             =   240
      Width           =   9600
   End
   Begin VB.Menu File 
      Caption         =   "文件"
      Begin VB.Menu Data_Import 
         Caption         =   "导入数据"
         Shortcut        =   ^O
      End
      Begin VB.Menu Graph_Export 
         Caption         =   "导出云图"
         Shortcut        =   ^P
      End
   End
   Begin VB.Menu Setting 
      Caption         =   "设置"
      Begin VB.Menu Params_Settings 
         Caption         =   "参数设置"
         Shortcut        =   ^Q
      End
      Begin VB.Menu Probe_Settings 
         Caption         =   "温度探针"
         Shortcut        =   ^W
      End
   End
End
Attribute VB_Name = "Main"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Dim PI!
Dim Material_Matrix() As Integer
Dim Temperature_Matrix() As Single
Dim Tmp_Matrix() As Single
Dim L_Matrix() As Single
Dim Loaded As Boolean
Dim paused As Boolean
Dim pause_index%
Public px%, py%, popen As Boolean, Show_Probe%
Public delta_x As Single, delta_y As Single
Public SX_Matrix, SY_Matrix, WX_Matrix, WY_Matrix, DX_Matrix, DY_Matrix

Private Sub Form_Load()
    PI = 3.1415926
    Loaded = False
    paused = True
    pause_index = 1
    Show_Probe = 1
    px = -1
    Init_Material_Params
    Init_ShadeGuide
    Params_Settings.Enabled = False
    Probe_Settings.Enabled = False
    Compute_Button.Enabled = False
    Show_T_Profile_Button.Enabled = False
    Graph_Export.Enabled = False
End Sub

Private Sub Form_QueryUnload(Cancel As Integer, UnloadMode As Integer)
    If Not paused Then
        If MsgBox("程序正在计算中，真的要退出吗？", vbYesNo + vbDefaultButton1, "退出") = vbNo Then
            Cancel = True
            Exit Sub
        End If
        paused = True
    End If
    Unload Settings
    Unload Set_Probe
    Unload Profile
End Sub

' 初始化相关
'' 创建各种矩阵
Private Sub Redim_Matrixes()
    ReDim Material_Matrix(range_x - 1, range_y - 1)
    ReDim Temperature_Matrix(range_x - 1, range_y - 1)
    ReDim Tmp_Matrix(range_x - 1, range_y - 1)
    ReDim L_Matrix(range_x - 1, range_y - 1)
    ReDim SX_Matrix(range_x - 1, range_y - 1): ReDim SY_Matrix(range_x - 1, range_y - 1)
    ReDim WX_Matrix(range_x - 1, range_y - 1): ReDim WY_Matrix(range_x - 1, range_y - 1)
    ReDim DX_Matrix(range_x - 1, range_y - 1): ReDim DY_Matrix(range_x - 1, range_y - 1)
    ReDim Tp(1)
End Sub

'' 初始化各种矩阵
Private Sub Init_Matrixes()
    Dim dx!, dy!
    Dim i%, j%
    For i = 0 To range_x - 1
        For j = 0 To range_y - 1
            ' 温度矩阵
            Temperature_Matrix(i, j) = T0(Material_Matrix(i, j))
            
            ' 潜热矩阵
            If Material_Matrix(i, j) = CASTING Then
                L_Matrix(i, j) = Materials(CASTING).L
            End If
            
            ' SWD 矩阵
            dx = delta_x
            dy = delta_y
            If i = 0 Or i = range_x - 1 Then ' 左右边界
                dx = dx / 2
            End If
            If j = 0 Or j = range_y - 1 Then ' 上下边界
                dy = dy / 2
            End If
            ' 水平相邻
            DX_Matrix(i, j) = delta_x
            SX_Matrix(i, j) = dy
            WX_Matrix(i, j) = dx
            ' 竖直相邻
            DY_Matrix(i, j) = delta_y
            SY_Matrix(i, j) = dx
            WY_Matrix(i, j) = dy
        Next j
    Next i
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
    Dim cnt%, line%, i%, j%, c
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
                        Case 1
                            Materials(line) = StringToMaterial(s)
                        Case 2
                            range_x = Val(Split(s, ",")(0))
                            range_y = Val(Split(s, ",")(1))
                            delta_x = 0.5 / range_x
                            delta_y = 0.5 / range_y
                            
                            Redim_Matrixes
                            
                            Grid.Scale (0, range_y)-(range_x * 1.2, 0)
                            Params_Settings.Enabled = True
                            Probe_Settings.Enabled = True
                            Graph_Export.Enabled = True
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
    Loaded = True
    Init_Matrixes
    Redraw_Graph
    Compute_Button.Caption = "开始计算"
    pause_index = 1
ErrHandler:
    Exit Sub
End Sub

'' 初始化色标
Private Sub Init_ShadeGuide()
    Dim delta!, i!
    Grid.AutoRedraw = True
    Grid.BackColor = vbBlack
    Grid.Scale (-40, 18)-(8, 0)
    Grid.ForeColor = vbWhite
    If Only_Phase_CheckBox.Value Then
        Grid.Line (1, 7)-(3, 8), vbBlue, BF
        Grid.CurrentX = 4: Grid.CurrentY = 7.5: Grid.Print "固相"
        Grid.Line (1, 9)-(3, 10), vbYellow, BF
        Grid.CurrentX = 4: Grid.CurrentY = 9.5: Grid.Print "凝固中"
        Grid.Line (1, 11)-(3, 12), vbRed, BF
        Grid.CurrentX = 4: Grid.CurrentY = 11.5: Grid.Print "液相"
    Else
        delta = PI / 16
        For i = 0 To 15
            Grid.Line (2, i + 1)-(4, i + 2), Get_Color(i * 100), BF
            Grid.CurrentX = 4: Grid.CurrentY = i + 1: Grid.Print i * 100
        Next i
        Grid.CurrentX = 5: Grid.CurrentY = 17: Grid.Print "色标"
    End If
End Sub

''' 色温对照函数
Private Function Get_Color(t As Single) As Variant
    Dim i%
    Dim w!
    w = 4
    i = Int(t / 100)
    If i > 16 Then
        i = 16
    ElseIf i < 0 Then
        i = 0
    End If
    Get_Color = HSV(250 - sigmoid_variant(i / 16, w) * 250, 1, 1)
    ' 由于直接均匀分色在中间的绿色区域区分并不明显，使用 sigmoid 函数（两侧缓慢，中间比较快）对其进行调整
    ' w 越大，上述效果越明显，由于本问题色标主要集中在中间区域（800-1000），故设较大的权值（4），如非本情况可适当减小（如 2.5）
End Function

''' Sigmoid 自定义变体，用于调节颜色变化速率
Private Function sigmoid_variant(X As Single, w As Single) As Single
    ' x (0, 1) w(0, INF) output (0, 1)
    Dim h!
    X = w * 2 * (X - 0.5) ' x (-w, w) y (1-sigmoid(w), sigmoid(w))
    h = 2 * (sigmoid(w) - 0.5)
    sigmoid_variant = (sigmoid(X) - 0.5) / h + 0.5
End Function

''' Sigmoid
Private Function sigmoid(X As Single) As Single
    sigmoid = 1 / (1 + Exp(-X))
End Function

''' 根据 HSV 色值生成 RGB 颜色
Private Function HSV(h As Integer, s As Single, v As Single) As Variant
   ' h(0, 360) s(0, 1.0) v(0, 1.0)
    Dim r As Single, g As Single, b As Single
    Dim i As Integer, f As Single, p As Single, q As Single, t As Single
    i = Int(h / 60) Mod 6
    f = h / 60 - i
    p = v * (1 - s)
    q = v * (1 - f * s)
    t = v * (1 - (1 - f) * s)
    
    Select Case i
        Case 0
            r = v
            g = t
            b = p
        Case 1
            r = q
            g = v
            b = p
        Case 2
            r = p
            g = v
            b = t
        Case 3
            r = p
            g = q
            b = v
        Case 4
            r = t
            g = p
            b = v
        Case 5
            r = v
            g = p
            b = q
    End Select
    HSV = RGB(r * 255, g * 255, b * 255)
End Function

' 按键回调
'' 参数设置
Private Sub Params_Settings_Click()
    Settings.Show
End Sub

'' 设置探针
Private Sub Probe_Settings_Click()
    Set_Probe.Show
End Sub

''' 点击回调
Private Sub Grid_MouseDown(Button As Integer, Shift As Integer, X As Single, Y As Single)
    Dim real_x%, real_y%
    real_x = Int(X)
    real_y = Int(Y)
    If Loaded And popen And real_x < range_x And Y < range_y Then
        px = real_x
        py = real_y
        Set_Probe.Px_Box.Text = px + 1
        Set_Probe.Py_Box.Text = py + 1
    End If
End Sub

'' 切换隐藏/显示铸型
Private Sub Hidden_Sand_CheckBox_Click()
    Redraw_Cloud_Chart (Hidden_Sand_CheckBox.Value)
    Mesh
End Sub

'' 开始计算
Private Sub Compute_Button_Click()
    Dim i%, j%
    Dim PrintStep%
    Dim Solid_Fraction!
    PrintStep = 30
    ReDim Preserve Tp(range_t)
    Probe_Settings.Enabled = False
    If px <> -1 Then
        Show_T_Profile_Button.Enabled = True
    End If
    If paused Then
        Compute_Button.Caption = "暂停计算"
        paused = False
        Grid.AutoRedraw = True
        Data_Import.Enabled = False
        ProgressBar.Min = 1
        ProgressBar.Max = range_t
        For i = pause_index To range_t
            ' 判断是否暂停
            If paused Then
                pause_index = i
                Exit Sub
            End If
            
            ' 计算下一时刻温度
            Next_T
            
            ' 记录探针温度
            If Not px = -1 Then
                Tp(i) = Temperature_Matrix(px, py)
            End If
            
            ' 显示时间
            StatusBar.Panels(4).Text = Round(delta_t * i, 3) & "s"
            
            If i Mod PrintStep = 0 Then
                ' 绘制云图
                If Dynamic_View_CheckBox.Value Then
                    Redraw_Graph
                    Grid.Refresh
                End If
                
                ' 绘制进度条
                ProgressBar.Value = i
                
                ' 获取固相率并显示
                Solid_Fraction = Get_Solid_Fraction()
                StatusBar.Panels(3).Text = "固相率：" & Round(Solid_Fraction * 100, 2) & "%"
                If Solid_Fraction > 0.99 Then ' 终凝阶段降低误差
                    PrintStep = 1
                ElseIf Solid_Fraction > 0.98 Then
                    PrintStep = 5
                End If
                If Solid_Fraction = 1 Then
                    Exit For
                End If
                
                ' 将部分算力交由其他控件，防止卡死
                DoEvents
            End If
        Next i
        Compute_Button.Caption = "开始计算"
        pause_index = 1
        paused = True
        Probe_Settings.Enabled = True
        Data_Import.Enabled = True
    Else
        Compute_Button.Caption = "继续计算"
        paused = True
        Data_Import.Enabled = True
    End If
End Sub

' 显示温度曲线
Private Sub Show_T_Profile_Button_Click()
    Profile.Show
End Sub

' 导出云图
Private Sub Graph_Export_Click()
    Call Export_Picture(Grid, CommonDialog, "后处理.bmp")
End Sub

' 移动回调
Private Sub Grid_MouseMove(Button As Integer, Shift As Integer, X As Single, Y As Single)
    Dim real_x%, real_y%
    real_x = Int(X)
    real_y = Int(Y)
    If Loaded Then
        If real_x < range_x And real_y < range_y Then
            StatusBar.Panels(1).Text = "(" & real_x + 1 & ", " & real_y + 1 & ")"
            StatusBar.Panels(2).Text = Temperature_Matrix(real_x, real_y) & "℃"
        Else
            StatusBar.Panels(1).Text = "Air"
            StatusBar.Panels(2).Text = T0(AIR) & "℃"
        End If
    End If
End Sub

' 仅显示相态回调
Private Sub Only_Phase_CheckBox_Click()
    Init_ShadeGuide
    If Only_Phase_CheckBox.Value Then
        Hidden_Sand_CheckBox.Enabled = False
    Else
        Hidden_Sand_CheckBox.Enabled = True
    End If
    If Loaded Then
        Grid.Scale (0, range_y)-(range_x * 1.2, 0)
        Redraw_Graph
    End If
End Sub

' 是否动态演示切换回调
Private Sub Dynamic_View_CheckBox_Click()
    If Dynamic_View_CheckBox.Value Then
        Hidden_Sand_CheckBox.Enabled = True
        Only_Phase_CheckBox.Enabled = True
    Else
        Hidden_Sand_CheckBox.Enabled = False
        Only_Phase_CheckBox.Enabled = False
    End If
End Sub

' 绘制相关
'' 绘制云图
Private Sub Redraw_Cloud_Chart(Only_Casting As Boolean)
    Dim i%, j%
    For i = 0 To range_x - 1
        For j = 0 To range_y - 1
            If Only_Casting Then
                If Material_Matrix(i, j) = CASTING Then
                    Grid.Line (i, j)-(i + 1, j + 1), Get_Color(Temperature_Matrix(i, j)), BF
                Else
                    Grid.Line (i, j)-(i + 1, j + 1), RGB(77, 77, 77), BF
                End If
            Else
                Grid.Line (i, j)-(i + 1, j + 1), Get_Color(Temperature_Matrix(i, j)), BF
            End If
        Next j
    Next i
End Sub

'' 绘制相态
Private Sub Redraw_Phase_State()
    Dim Tl!
    Dim color
    Dim i%, j%
    Tl = Materials(CASTING).Tl
    For i = 0 To range_x - 1
        For j = 0 To range_y - 1
            If Material_Matrix(i, j) = CASTING Then
                If Temperature_Matrix(i, j) - Tl > 0.001 Then
                    color = vbRed
                ElseIf Tl - Temperature_Matrix(i, j) > 0.001 Then
                    color = vbBlue
                Else
                    color = vbYellow
                End If
                Grid.Line (i, j)-(i + 1, j + 1), color, BF
            Else
                Grid.Line (i, j)-(i + 1, j + 1), RGB(77, 77, 77), BF
            End If
        Next j
    Next i
End Sub

'' 绘制边界
Private Sub Redraw_Border()
    Grid.Line (0, 0)-(range_x, 1 / 2), vbBlack, BF
    Grid.Line (0, range_y - 1 / 2)-(range_x, range_y), vbBlack, BF
    Grid.Line (0, 0)-(1 / 2, range_y), vbBlack, BF
    Grid.Line (range_x - 1 / 2, 0)-(range_x, range_y), vbBlack, BF
End Sub

'' 绘制网格
Private Sub Mesh()
    Dim i%
    For i = 0 To range_x
        Grid.Line (i, 0)-(i, range_y), vbBlack
    Next i
    For i = 0 To range_y
        Grid.Line (0, i)-(range_x, i), vbBlack
    Next i
    Redraw_Border
End Sub

'' 绘制温度探针
Private Sub Redraw_Probe()
    Dim i%
    If Show_Probe = 0 Then
        Exit Sub
    End If
    If px = -1 Then
        Exit Sub
    End If
    Dim color As Variant
    Grid.FillStyle = vbFSSolid
    For i = 4 To 0 Step -1
        If i Mod 2 = 0 Then
            color = vbRed
        Else
            color = vbWhite
        End If
        Grid.FillColor = color
        Grid.Circle (px + 0.5, py + 0.5), (2 * i + 1) / 18, color
    Next i
End Sub

'' 绘制相图、相态、网格、探针
Public Sub Redraw_Graph()
    If Only_Phase_CheckBox.Value Then
        Redraw_Phase_State
    Else
        Redraw_Cloud_Chart (Hidden_Sand_CheckBox.Value)
    End If
    Redraw_Probe
    Mesh
End Sub

' 计算相关
'' 温度矩阵下一时刻
Private Sub Next_T()
    ' 计算下一时刻温度
    Dim s!, w!, d! ' 两结点间接触宽度、结点厚度、两结点温度中心距离
    Dim i%, j%
    Dim t!, m!, heat!, dT!
    Dim Ma As Material
    For i = 0 To range_x - 1
        For j = 0 To range_y - 1
            ' 计算从各方向获得的热量
            heat = 0
            Ma = Materials(Material_Matrix(i, j))
            ' Call Get_SWD(s, w, d, i, j, 0)
            s = SX_Matrix(i, j): w = WX_Matrix(i, j): d = DX_Matrix(i, j)
            heat = heat + Get_Heat(i, j, i - 1, j, s, w, d)
            heat = heat + Get_Heat(i, j, i + 1, j, s, w, d)
            ' Call Get_SWD(s, w, d, i, j, 1)
            s = SY_Matrix(i, j): w = WY_Matrix(i, j): d = DY_Matrix(i, j)
            heat = heat + Get_Heat(i, j, i, j - 1, s, w, d)
            heat = heat + Get_Heat(i, j, i, j + 1, s, w, d)
            m = Ma.rho * s * w ' 单元质量
            dT = heat / (Ma.c * m) ' 临时温度变化值
            t = Temperature_Matrix(i, j)
            
            ' 计算潜热
            If compute_L Then
                If Material_Matrix(i, j) = CASTING And t + dT < Materials(CASTING).Tl And L_Matrix(i, j) > 0.001 Then
                    heat = heat + Ma.c * m * (t - Materials(CASTING).Tl)
                    t = Materials(CASTING).Tl
                    If -heat >= L_Matrix(i, j) * m Then
                        heat = heat + L_Matrix(i, j) * m
                        L_Matrix(i, j) = 0
                        dT = heat / (Ma.c * m)
                    Else
                        L_Matrix(i, j) = L_Matrix(i, j) + heat / m
                        dT = 0
                    End If
                End If
            End If
            
            ' 计算温度
            Tmp_Matrix(i, j) = t + dT
        Next j
    Next i
    
    ' 临时矩阵传回温度矩阵
    For i = 0 To range_x - 1
        For j = 0 To range_y - 1
            Temperature_Matrix(i, j) = Tmp_Matrix(i, j)
        Next j
    Next i
End Sub

'' 计算两结点的接触宽度、厚度、温度中心距离
Private Sub Get_SWD(ByRef s!, ByRef w!, ByRef d!, ByVal X%, ByVal Y%, ByVal direct%)
    Dim dx!, dy!
    dx = delta_x
    dy = delta_y
    If X = 0 Or X = range_x - 1 Then ' 左右边界
        dx = dx / 2
    End If
    If Y = 0 Or Y = range_y - 1 Then ' 上下边界
        dy = dy / 2
    End If
    If direct = 0 Then ' 两结点水平相邻
        d = delta_x
        s = dy
        w = dx
    Else ' 两结点竖直相邻
        d = delta_y
        s = dx
        w = dy
    End If
End Sub


'' 计算源结点到目的结点的交换热量
Private Function Get_Heat(X%, Y%, sx%, sy%, s!, w!, d!)
    Dim h!, k!, k1!, k2!
    If sx < 0 Or sx >= range_x Or sy < 0 Or sy >= range_y Then
        h = TT(Material_Matrix(X, Y), AIR)
        Get_Heat = h * (T0(AIR) - Temperature_Matrix(X, Y)) * s * delta_t
    Else
        If Material_Matrix(X, Y) = Material_Matrix(sx, sy) Then
            k = Materials(Material_Matrix(X, Y)).k
        Else
            k1 = Materials(Material_Matrix(X, Y)).k
            k2 = Materials(Material_Matrix(sx, sy)).k
            k = 2 * k1 * k2 / (k1 + k2)
        End If
        Get_Heat = k * (Temperature_Matrix(sx, sy) - Temperature_Matrix(X, Y)) / d * s * delta_t
    End If
End Function

'' 获取固相率
Private Function Get_Solid_Fraction() As Single
    Dim i%, j%
    Dim cnt%, total%
    cnt = 0
    total = 0
    For i = 0 To range_x - 1
        For j = 0 To range_y - 1
            If Material_Matrix(i, j) = CASTING Then
                If L_Matrix(i, j) < 0.01 Then
                    cnt = cnt + 1
                End If
                total = total + 1
            End If
        Next j
    Next i
    If total = 0 Then
        Get_Solid_Fraction = 0
    Else
        Get_Solid_Fraction = 1# * cnt / total
    End If
End Function
