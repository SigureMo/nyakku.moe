VERSION 5.00
Begin VB.Form Set_Probe 
   Caption         =   "Form1"
   ClientHeight    =   3630
   ClientLeft      =   15945
   ClientTop       =   5535
   ClientWidth     =   4560
   LinkTopic       =   "Form1"
   ScaleHeight     =   3630
   ScaleWidth      =   4560
   Begin VB.CommandButton Delete_Button 
      Caption         =   "删除探针"
      Height          =   615
      Left            =   3120
      TabIndex        =   8
      Top             =   1800
      Width           =   1215
   End
   Begin VB.CommandButton Cancel_Button 
      Caption         =   "取消"
      Height          =   615
      Left            =   3360
      TabIndex        =   7
      Top             =   2880
      Width           =   1095
   End
   Begin VB.CommandButton Apply_Button 
      Caption         =   "应用"
      Height          =   615
      Left            =   1800
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
      Width           =   1095
   End
   Begin VB.CheckBox Show_Probe_Check 
      Caption         =   "显示探针"
      Height          =   255
      Left            =   960
      TabIndex        =   4
      Top             =   1920
      Value           =   1  'Checked
      Width           =   2055
   End
   Begin VB.TextBox Py_Box 
      Height          =   375
      Left            =   3360
      TabIndex        =   1
      Text            =   "0"
      Top             =   840
      Width           =   975
   End
   Begin VB.TextBox Px_Box 
      Height          =   375
      Left            =   960
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
    Px_Box.Text = Main.px
    Py_Box.Text = Main.py
    Show_Probe_Check.Value = Main.Show_Probe
    ReDim Tp(1)
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
    Main.px = Val(Px_Box.Text)
    Main.py = Val(Py_Box.Text)
    Main.Show_Probe = Show_Probe_Check.Value
    Main.Redraw_Cloud_Chart (Main.Hidden_Sand_CheckBox.Value)
    Main.Mesh
    Main.Redraw_Probe
End Sub

Private Sub Delete_Button_Click()
    Main.px = -1
    Main.Redraw_Cloud_Chart (Main.Hidden_Sand_CheckBox.Value)
    Main.Mesh
    Main.Redraw_Probe
End Sub

