VERSION 5.00
Begin VB.Form Profile 
   Caption         =   "Form1"
   ClientHeight    =   7650
   ClientLeft      =   15945
   ClientTop       =   2895
   ClientWidth     =   12795
   LinkTopic       =   "Form1"
   ScaleHeight     =   7650
   ScaleWidth      =   12795
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
      Height          =   6255
      Left            =   480
      ScaleHeight     =   6195
      ScaleWidth      =   11715
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
Private Sub Form_Load()
    Show_Graph
End Sub

Private Sub Refresh_Button_Click()
    Show_Graph
End Sub

Private Sub Show_Graph()
    Graph.Scale (-0.1 * range_t, 2000)-(1.1 * range_t, -200)
    Graph.Line (0, 0)-(0, 1600)
    Graph.Line (0, 0)-(range_t, 0)
    For i = 0 To range_t
        Graph.PSet (i, Tp(i))
    Next i
End Sub
