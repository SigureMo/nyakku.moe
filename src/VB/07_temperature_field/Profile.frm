VERSION 5.00
Object = "{6B7E6392-850A-101B-AFC0-4210102A8DA7}#1.3#0"; "COMCTL32.OCX"
Begin VB.Form Profile 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "温度曲线"
   ClientHeight    =   7725
   ClientLeft      =   15870
   ClientTop       =   2820
   ClientWidth     =   12795
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   7725
   ScaleWidth      =   12795
   Begin ComctlLib.StatusBar StatusBar 
      Align           =   2  'Align Bottom
      Height          =   375
      Left            =   0
      TabIndex        =   4
      Top             =   7350
      Width           =   12795
      _ExtentX        =   22569
      _ExtentY        =   661
      SimpleText      =   ""
      _Version        =   327682
      BeginProperty Panels {0713E89E-850A-101B-AFC0-4210102A8DA7} 
         NumPanels       =   3
         BeginProperty Panel1 {0713E89F-850A-101B-AFC0-4210102A8DA7} 
            Object.Tag             =   ""
         EndProperty
         BeginProperty Panel2 {0713E89F-850A-101B-AFC0-4210102A8DA7} 
            Object.Tag             =   ""
         EndProperty
         BeginProperty Panel3 {0713E89F-850A-101B-AFC0-4210102A8DA7} 
            Object.Tag             =   ""
         EndProperty
      EndProperty
   End
   Begin VB.CommandButton Confirm_Button 
      Caption         =   "确定"
      Height          =   495
      Left            =   10200
      TabIndex        =   3
      Top             =   6720
      Width           =   2055
   End
   Begin VB.CommandButton Refresh_Button 
      Caption         =   "刷新显示"
      Height          =   495
      Left            =   7800
      TabIndex        =   2
      Top             =   6720
      Width           =   2055
   End
   Begin VB.CommandButton Graph_Export_Button 
      Caption         =   "导出图像"
      Height          =   495
      Left            =   5280
      TabIndex        =   1
      Top             =   6720
      Width           =   2175
   End
   Begin VB.PictureBox Graph 
      AutoRedraw      =   -1  'True
      BorderStyle     =   0  'None
      Height          =   6000
      Left            =   360
      ScaleHeight     =   6000
      ScaleWidth      =   12000
      TabIndex        =   0
      Top             =   240
      Width           =   12000
   End
End
Attribute VB_Name = "Profile"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Dim Tmax%, TPrintStep%, TimePrintNum%, TimePrintStep%

Private Sub Form_Load()
    Tmax = 1600
    TPrintStep = 300
    TimePrintNum = 10
    TimePrintStep = Int(range_t / TimePrintNum)
    If TimePrintStep Mod 100 <> 0 Then
        TimePrintStep = Int(TimePrintStep / 100) * 100
        TimePrintNum = TimePrintNum + 1
    End If
    Show_Graph
End Sub

Private Sub Refresh_Button_Click()
    Show_Graph
End Sub

Private Sub Show_Graph()
    Dim color, Tl!, m As Material, k!
    k = Graph.Height / Graph.Width ' 高宽比，保证某些小组件在宽高上一致
    m = Materials(CASTING)
    Tl = m.Tl
    Graph.BackColor = vbWhite
    Graph.Scale (-0.1 * range_t, Tmax * 1.25)-(1.1 * range_t, -Tmax * 0.125)
    
    ' 坐标轴
    Graph.DrawWidth = 2
    Graph.Line (0, 0)-(0, Tmax * 1.05), vbBlack
    Graph.Line (0, 0)-(range_t * 1.05, 0), vbBlack
    '' 指针
    Dim arrowSize!
    arrowSize = 0.01
    Graph.Line (range_t * arrowSize, Tmax * (1.05 - arrowSize * 3 ^ 0.5 / k))-(0, Tmax * 1.05), vbBlack
    Graph.Line (-range_t * arrowSize, Tmax * (1.05 - arrowSize * 3 ^ 0.5 / k))-(0, Tmax * 1.05), vbBlack
    Graph.Line (range_t * (1.05 - arrowSize * 3 ^ 0.5), Tmax * 0.01 / k)-(range_t * 1.05, 0), vbBlack
    Graph.Line (range_t * (1.05 - arrowSize * 3 ^ 0.5), -Tmax * 0.01 / k)-(range_t * 1.05, 0), vbBlack
    
    ' 辅助坐标网格及标注坐标值
    Graph.FontSize = 8
    For i = 1 To 5
        Graph.DrawWidth = 1
        Graph.Line (0, i * TPrintStep)-(range_t, i * TPrintStep), RGB(160, 160, 160)
        Graph.DrawWidth = 2
        Graph.Line (0, i * TPrintStep)-(range_t * 0.01, i * TPrintStep), vbBlack
        Graph.CurrentX = -0.05 * range_t: Graph.CurrentY = i * TPrintStep + Tmax * 0.01: Graph.Print i * TPrintStep
    Next i
    
    For i = 1 To TimePrintNum
        Graph.DrawWidth = 1
        Graph.Line (i * TimePrintStep, 0)-(i * TimePrintStep, Tmax), RGB(160, 160, 160)
        Graph.DrawWidth = 2
        Graph.Line (i * TimePrintStep, 0)-(i * TimePrintStep, Tmax * 0.01 / k), vbBlack
        Graph.CurrentX = i * TimePrintStep - range_t * 0.02: Graph.CurrentY = -0.05 * Tmax: Graph.Print i * TimePrintStep
    Next i
    
    ' 绘制标题、坐标轴单位、0
    Graph.FontSize = 8
    Graph.CurrentX = -0.05 * range_t: Graph.CurrentY = -0.05 * Tmax: Graph.Print 0
    Graph.FontBold = True
    Graph.FontSize = 18
    Graph.CurrentX = range_t / 3: Graph.CurrentY = Tmax * 1.07: Graph.Print "点(" & Main.px + 1 & ", " & Main.py + 1 & ")温度变化曲线"
    Graph.FontSize = 10
    Graph.CurrentX = -0.1 * range_t: Graph.CurrentY = 1.07 * Tmax: Graph.Print "温度/℃"
    Graph.CurrentX = 1.03 * range_t: Graph.CurrentY = -0.05 * Tmax: Graph.Print "时间步"
    Graph.FontBold = False
    
    ' 液相线（熔点）辅助线
    Graph.DrawWidth = 1
    Graph.Line (0, Tl)-(range_t, Tl), vbRed
    
    ' 坐标系
    Graph.DrawWidth = 2
    For i = 0 To range_t
        If Tp(i) - Tl > 0.1 Then
            color = vbRed
        ElseIf Tl - Tp(i) > 0.1 Then
            color = vbBlue
        Else
            color = vbYellow
        End If
        If Tp(i) > 0.01 Then
            Graph.PSet (i, Tp(i)), color
        End If
    Next i
End Sub

' 移动回调
Private Sub Graph_MouseMove(Button As Integer, Shift As Integer, X As Single, Y As Single)
    Dim i%, t!
    i = Int(X)
    If i >= 0 And i < range_t And Y >= 0 And Y < Tmax Then
        t = Tp(i)
        If t > 0 Then
            Show_Graph
            Graph.DrawWidth = 1
            Graph.Line (0, t)-(range_t, t), RGB(200, 200, 200)
            Graph.Line (i, 0)-(i, Tmax), RGB(200, 200, 200)
            StatusBar.Panels(1).Text = "时间步：" & i
            StatusBar.Panels(2).Text = Round(i * delta_t, 3) & "s"
            StatusBar.Panels(3).Text = Round(t, 3) & "℃"
        End If
    End If
    Graph.Refresh
End Sub

' 导出图像
Private Sub Graph_Export_Button_Click()
    Call Export_Picture(Graph, Main.CommonDialog, "温度曲线.bmp")
End Sub

' 关闭窗口
Private Sub Confirm_Button_Click()
    Unload Me
End Sub
