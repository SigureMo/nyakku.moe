VERSION 5.00
Begin VB.Form Set_Probe 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "温度探针设置"
   ClientHeight    =   3630
   ClientLeft      =   15870
   ClientTop       =   5460
   ClientWidth     =   5010
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   3630
   ScaleWidth      =   5010
   Begin VB.CommandButton Delete_Button 
      Caption         =   "删除探针"
      Height          =   615
      Left            =   3480
      TabIndex        =   8
      Top             =   1800
      Width           =   1215
   End
   Begin VB.CommandButton Cancel_Button 
      Caption         =   "取消"
      Height          =   615
      Left            =   3480
      TabIndex        =   7
      Top             =   2880
      Width           =   1215
   End
   Begin VB.CommandButton Apply_Button 
      Caption         =   "应用"
      Height          =   615
      Left            =   1920
      TabIndex        =   6
      Top             =   2880
      Width           =   1215
   End
   Begin VB.CommandButton Confirm_Button 
      Caption         =   "确定"
      Height          =   615
      Left            =   360
      TabIndex        =   5
      Top             =   2880
      Width           =   1215
   End
   Begin VB.CheckBox Show_Probe_Check 
      Caption         =   "显示探针"
      Height          =   255
      Left            =   720
      TabIndex        =   4
      Top             =   1920
      Value           =   1  'Checked
      Width           =   1335
   End
   Begin VB.TextBox Py_Box 
      Height          =   375
      Left            =   3360
      TabIndex        =   1
      Text            =   "0"
      Top             =   840
      Width           =   1095
   End
   Begin VB.TextBox Px_Box 
      Height          =   375
      Left            =   840
      TabIndex        =   0
      Text            =   "0"
      Top             =   840
      Width           =   1095
   End
   Begin VB.Label Py_Label 
      AutoSize        =   -1  'True
      Caption         =   "y:"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   12
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   240
      Left            =   2640
      TabIndex        =   3
      Top             =   840
      Width           =   270
   End
   Begin VB.Label Px_Label 
      AutoSize        =   -1  'True
      Caption         =   "x:"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   12
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   240
      Left            =   360
      TabIndex        =   2
      Top             =   840
      Width           =   270
   End
End
Attribute VB_Name = "Set_Probe"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub Form_Load()
    Main.popen = True
    Px_Box.Text = Main.px + 1
    Py_Box.Text = Main.py + 1
    Show_Probe_Check.Value = Main.Show_Probe
End Sub

Private Sub Confirm_Button_Click()
    Set_Params
    Unload Me
    Main.popen = False
End Sub

Private Sub Apply_Button_Click()
    Set_Params
End Sub

Private Sub Cancel_Button_Click()
    Unload Me
    Main.popen = False
End Sub

Private Sub Set_Params()
    If Val(Px_Box.Text) <= 0 Or Val(Py_Box.Text) <= 0 Or Val(Px_Box.Text) > range_x Or Val(Py_Box.Text) > range_y Then
        MsgBox "该点不存在"
        Exit Sub
    End If
    Main.px = Val(Px_Box.Text) - 1
    Main.py = Val(Py_Box.Text) - 1
    Main.Show_Probe = Show_Probe_Check.Value
    Main.Redraw_Graph
    ReDim Tp(1)
End Sub

Private Sub Delete_Button_Click()
    Main.px = -1
    Main.Redraw_Graph
End Sub

