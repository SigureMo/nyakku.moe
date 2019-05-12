VERSION 5.00
Object = "{6B7E6392-850A-101B-AFC0-4210102A8DA7}#1.3#0"; "COMCTL32.OCX"
Begin VB.Form Profile 
   Caption         =   "Form1"
   ClientHeight    =   8235
   ClientLeft      =   15945
   ClientTop       =   2895
   ClientWidth     =   12795
   LinkTopic       =   "Form1"
   ScaleHeight     =   8235
   ScaleWidth      =   12795
   Begin ComctlLib.StatusBar StatusBar 
      Align           =   2  'Align Bottom
      Height          =   375
      Left            =   0
      TabIndex        =   4
      Top             =   7860
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
      Height          =   375
      Left            =   11160
      TabIndex        =   3
      Top             =   7080
      Width           =   1335
   End
   Begin VB.CommandButton Refresh_Button 
      Caption         =   "刷新显示"
      Height          =   495
      Left            =   9120
      TabIndex        =   2
      Top             =   7080
      Width           =   1695
   End
   Begin VB.CommandButton Export_Graph_Button 
      Caption         =   "导出图像"
      Height          =   495
      Left            =   6840
      TabIndex        =   1
      Top             =   7080
      Width           =   2175
   End
   Begin VB.PictureBox Graph 
      AutoRedraw      =   -1  'True
      BorderStyle     =   0  'None
      Height          =   6255
      Left            =   480
      ScaleHeight     =   6255
      ScaleWidth      =   11775
      TabIndex        =   0
      Top             =   360
      Width           =   11775
   End
End
Attribute VB_Name = "Profile"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Dim Tmax%, TPrintStep%

Private Sub Form_Load()
    Tmax = 1600
    TPrintStep = 300
    Show_Graph
End Sub

Private Sub Refresh_Button_Click()
    Show_Graph
End Sub

Private Sub Show_Graph()
    Dim color, Tl!, m As Material
    m = Materials(CASTING)
    Tl = m.Tl
    Graph.BackColor = vbWhite
    Graph.Scale (-0.1 * range_t, Tmax * 1.25)-(1.1 * range_t, -Tmax * 0.125)
    
    ' 坐标轴
    Graph.DrawWidth = 2
    Graph.Line (0, 0)-(0, Tmax * 1.05), vbBlack
    Graph.Line (0, 0)-(range_t * 1.05, 0), vbBlack
    
    ' 辅助坐标网格
    Graph.DrawWidth = 1
    For i = 1 To 5
        Graph.Line (0, i * TPrintStep)-(range_t, i * TPrintStep), RGB(160, 160, 160)
    Next i
    
    For i = 1 To range_t
        If i Mod 200 = 0 Then
            Graph.Line (i, 0)-(i, Tmax), RGB(160, 160, 160)
        End If
    Next i
    
    ' 液相线（熔点）辅助线
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
End Sub
