VERSION 5.00
Object = "{6B7E6392-850A-101B-AFC0-4210102A8DA7}#1.3#0"; "COMCTL32.OCX"
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.2#0"; "COMDLG32.OCX"
Begin VB.Form 温度场前处理程序 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "Form1"
   ClientHeight    =   8775
   ClientLeft      =   2880
   ClientTop       =   2520
   ClientWidth     =   13305
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   8775
   ScaleWidth      =   13305
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
      Top             =   8400
      Width           =   13305
      _ExtentX        =   23469
      _ExtentY        =   661
      SimpleText      =   ""
      _Version        =   327682
      BeginProperty Panels {0713E89E-850A-101B-AFC0-4210102A8DA7} 
         NumPanels       =   3
         BeginProperty Panel1 {0713E89F-850A-101B-AFC0-4210102A8DA7} 
            Object.Width           =   3528
            MinWidth        =   3528
            TextSave        =   ""
            Key             =   ""
            Object.Tag             =   ""
         EndProperty
         BeginProperty Panel2 {0713E89F-850A-101B-AFC0-4210102A8DA7} 
            Object.Width           =   4410
            MinWidth        =   4410
            TextSave        =   ""
            Key             =   ""
            Object.Tag             =   ""
         EndProperty
         BeginProperty Panel3 {0713E89F-850A-101B-AFC0-4210102A8DA7} 
            Object.Width           =   8819
            MinWidth        =   8819
            TextSave        =   ""
            Key             =   ""
            Object.Tag             =   ""
         EndProperty
      EndProperty
   End
   Begin VB.Frame Frame3 
      Caption         =   "点选设置"
      Height          =   1755
      Left            =   8500
      TabIndex        =   9
      Top             =   2880
      Width           =   4500
      Begin VB.ComboBox Material_Combo 
         Height          =   300
         ItemData        =   "Preprocessing.frx":0000
         Left            =   600
         List            =   "Preprocessing.frx":000D
         Style           =   2  'Dropdown List
         TabIndex        =   12
         Top             =   1080
         Width           =   1455
      End
      Begin VB.CommandButton Select_Material_Button 
         Caption         =   "指定材料"
         Height          =   495
         Left            =   2640
         TabIndex        =   11
         Top             =   960
         Width           =   1455
      End
      Begin VB.CheckBox InvertSelect_Check_Box 
         Caption         =   "反向填充"
         Height          =   255
         Left            =   600
         TabIndex        =   10
         Top             =   480
         Width           =   1215
      End
   End
   Begin VB.Frame Frame2 
      Caption         =   "材料设置"
      Height          =   2745
      Left            =   8520
      TabIndex        =   8
      Top             =   5160
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
      Left            =   8500
      TabIndex        =   1
      Top             =   200
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
Attribute VB_Name = "温度场前处理程序"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Dim Material_Matrix(1000, 1000) As Integer
Dim Select_Matrix(1000, 1000) As Boolean
Dim grid_w%, grid_l%
Dim Start_x%, Start_y%
Dim Meshed As Boolean
Dim Tips_arr
Dim click_cnt%
Dim Material_List() As Material

Private Sub Form_Load()
    Init_Material_Params
    Meshed = False
    grid_w = 500
    grid_l = 500
    Start_x = -1
    Tips_arr = Array("支持按住 Shift 进行区域选择哦！", "支持按住 Ctrl 连续点选哦！", "Shift Ctrl 同时按住也是支持的哦", "适当使用反向填充会有奇效哦！", "本程序以 mm 为单位哦，整体长度为" & grid_w & "，整体宽度为" & grid_l)
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
    Dim real_x%, real_y%
    If Not Meshed Then
        MsgBox "请先生成网格"
        Exit Sub
    End If
    If Button = 1 Then
        real_x = Int(X)
        real_y = Int(Y)
        StatusBar.Panels(2).Text = "已选择点 (" & real_x + 1 & ", " & real_y + 1 & ")"
        If Shift = 1 Or Shift = 3 Then
            If Shift = 1 Then
                Clear_Select_Matrix
            End If
            If Not Start_x = -1 Then
                Call Mark_Area(Start_x, real_x, Start_y, real_y)
                StatusBar.Panels(2).Text = "已选择区域 (" & Start_x + 1 & ", " & Start_y + 1 & ")-(" & real_x + 1 & ", " & real_y + 1 & ")"
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

'' 鼠标移动回调
Private Sub Grid_MouseMove(Button As Integer, Shift As Integer, X As Single, Y As Single)
    If Meshed Then
        StatusBar.Panels(1).Text = "当前位置为(" & Int(X) + 1 & ", " & Int(Y) + 1 & ")"
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
    yc = delta_y / Val(Delta_X_Box)
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
End Sub

Private Sub Casting_Color_Click()
    Set_Color (CASTING)
End Sub

Private Sub Chill_Color_Click()
    Set_Color (CHILL)
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
                            delta_x = 0.5 / range_x
                            delta_y = 0.5 / range_y
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

