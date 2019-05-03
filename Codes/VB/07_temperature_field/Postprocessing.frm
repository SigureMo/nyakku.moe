VERSION 5.00
Object = "{6B7E6392-850A-101B-AFC0-4210102A8DA7}#1.3#0"; "COMCTL32.OCX"
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.2#0"; "COMDLG32.OCX"
Begin VB.Form Form1 
   Caption         =   "Form1"
   ClientHeight    =   7410
   ClientLeft      =   120
   ClientTop       =   465
   ClientWidth     =   11955
   LinkTopic       =   "Form1"
   ScaleHeight     =   7410
   ScaleWidth      =   11955
   StartUpPosition =   3  '窗口缺省
   Begin VB.CheckBox Dynamic_View_CheackBox 
      Caption         =   "观看动态过程"
      Height          =   495
      Left            =   9720
      TabIndex        =   7
      Top             =   3600
      Value           =   1  'Checked
      Width           =   1695
   End
   Begin VB.CheckBox Hidden_Sand_CheckBox 
      Caption         =   "仅显示铸件"
      Height          =   495
      Left            =   9720
      TabIndex        =   6
      Top             =   2760
      Value           =   1  'Checked
      Width           =   1575
   End
   Begin MSComDlg.CommonDialog CommonDialog 
      Left            =   9840
      Top             =   720
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   393216
   End
   Begin ComctlLib.StatusBar StatusBar 
      Align           =   2  'Align Bottom
      Height          =   375
      Left            =   0
      TabIndex        =   5
      Top             =   7035
      Width           =   11955
      _ExtentX        =   21087
      _ExtentY        =   661
      SimpleText      =   ""
      _Version        =   327682
      BeginProperty Panels {0713E89E-850A-101B-AFC0-4210102A8DA7} 
         NumPanels       =   2
         BeginProperty Panel1 {0713E89F-850A-101B-AFC0-4210102A8DA7} 
            TextSave        =   ""
            Object.Tag             =   ""
         EndProperty
         BeginProperty Panel2 {0713E89F-850A-101B-AFC0-4210102A8DA7} 
            TextSave        =   ""
            Object.Tag             =   ""
         EndProperty
      EndProperty
   End
   Begin VB.CommandButton Settings_Button 
      Caption         =   "参数设置"
      Height          =   615
      Left            =   10680
      TabIndex        =   4
      Top             =   1320
      Width           =   975
   End
   Begin VB.CommandButton Data_Import_Button 
      Caption         =   "导入数据"
      Height          =   615
      Left            =   10560
      TabIndex        =   3
      Top             =   600
      Width           =   1095
   End
   Begin VB.PictureBox ShadeGuide 
      AutoRedraw      =   -1  'True
      Height          =   6255
      Left            =   7080
      ScaleHeight     =   6195
      ScaleWidth      =   1035
      TabIndex        =   2
      Top             =   240
      Width           =   1095
   End
   Begin ComctlLib.ProgressBar ProgressBar1 
      Height          =   375
      Left            =   120
      TabIndex        =   1
      Top             =   6600
      Width           =   6855
      _ExtentX        =   12091
      _ExtentY        =   661
      _Version        =   327682
      Appearance      =   1
   End
   Begin VB.PictureBox Grid 
      AutoRedraw      =   -1  'True
      Height          =   6135
      Left            =   120
      ScaleHeight     =   6075
      ScaleWidth      =   6675
      TabIndex        =   0
      Top             =   240
      Width           =   6735
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Dim PI!
Dim Material_Matrix()
Dim Temperature_Matrix()
Dim Tmp_Matrix()
Dim Loaded As Boolean
Dim Materials(2) As Material
Dim range_x%, range_y%

Private Sub Form_Load()
    Dim i As Integer
    PI = 3.1415926
    Loaded = False
    Init_ShadeGuide
End Sub

' 导入数据
Private Sub Data_Import_Button_Click()
    'On Error GoTo ErrHandler
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
                        Case 1
                            Materials(line) = StringToMaterial(s)
                        Case 2
                            range_x = Val(Split(s, ",")(0))
                            range_y = Val(Split(s, ",")(1))
                            ReDim Material_Matrix(range_x - 1, range_y - 1)
                            ReDim Temperature_Matrix(range_x - 1, range_y - 1)
                            ReDim Tmp_Matrix(range_x - 1, range_y - 1)
                            Grid.Scale (0, 0)-(range_x, range_y)
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
ErrHandler:
    Exit Sub
End Sub

' 初始化色标
Private Sub Init_ShadeGuide()
    ShadeGuide.BackColor = vbBlack
    ShadeGuide.Scale (0, 18)-(8, 0)
    ShadeGuide.ForeColor = vbWhite
    delta = PI / 16
    For i = 0 To 15
        ShadeGuide.Line (2, i + 1)-(4, i + 2), Get_Color(i * 100), BF
        ShadeGuide.CurrentX = 4: ShadeGuide.CurrentY = i + 1: ShadeGuide.Print i * 100
    Next i
    ShadeGuide.CurrentX = 5: ShadeGuide.CurrentY = 17: ShadeGuide.Print "色标"
End Sub

'' 色温对照函数
Private Function Get_Color(t As Integer) As Variant
    Dim i%
    Dim w!
    w = 2.5
    i = t / 100
    Get_Color = HSV2RGB(250 - sigmoid_variant(i / 16, w) * 250, 1, 1)
    ' 由于直接均匀分色在中间的绿色区域区分并不明显，使用 sigmoid 函数（两侧缓慢，中间比较快）对其进行调整, w 越大，效果越明显
End Function

'' Sigmoid 自定义变体，用于调节颜色变化速率
Private Function sigmoid_variant(X As Single, w As Single) As Single
    ' x (0, 1) w(0, INF) output (0, 1)
    X = w * 2 * (X - 0.5) ' x (-w, w) y (1-sigmoid(w), sigmoid(w))
    h = 2 * (sigmoid(w) - 0.5)
    sigmoid_variant = (sigmoid(X) - 0.5) / h + 0.5
End Function

'' Sigmoid
Private Function sigmoid(X As Single) As Single
    sigmoid = 1 / (1 + Exp(-X))
End Function

'' HSV 色值转化为 RGB 色值
Private Function HSV2RGB(h As Integer, s As Single, v As Single) As Variant
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
    HSV2RGB = RGB(r * 255, g * 255, b * 255)
End Function

' 参数设置
Private Sub Settings_Button_Click()
    Settings.Show
End Sub

' 网格相关
'' 移动回调
Private Sub Grid_MouseMove(Button As Integer, Shift As Integer, X As Single, Y As Single)
    If Loaded Then
        StatusBar.Panels(1).Text = "(" & Int(X) & ", " & Int(Y) & ")"
    End If
End Sub

