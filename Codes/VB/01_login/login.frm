VERSION 5.00
Begin VB.Form Form1 
   Caption         =   "Form1"
   ClientHeight    =   3015
   ClientLeft      =   120
   ClientTop       =   465
   ClientWidth     =   4560
   LinkTopic       =   "Form1"
   ScaleHeight     =   3015
   ScaleWidth      =   4560
   StartUpPosition =   3  '窗口缺省
   Begin VB.CommandButton Command1 
      Caption         =   "输入密码："
      Height          =   255
      Left            =   600
      TabIndex        =   4
      Top             =   2040
      Width           =   1455
   End
   Begin VB.TextBox Text2 
      Height          =   375
      Left            =   2400
      Locked          =   -1  'True
      TabIndex        =   2
      Top             =   2040
      Width           =   1815
   End
   Begin VB.TextBox Text1 
      Height          =   375
      Left            =   2400
      TabIndex        =   1
      Top             =   1320
      Width           =   1815
   End
   Begin VB.Label Label2 
      Caption         =   "输入用户名："
      Height          =   375
      Left            =   720
      TabIndex        =   3
      Top             =   1440
      Width           =   1215
   End
   Begin VB.Label Label1 
      Caption         =   "欢迎登录"
      BeginProperty Font 
         Name            =   "华文楷体"
         Size            =   18
         Charset         =   134
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   495
      Left            =   1440
      TabIndex        =   0
      Top             =   360
      Width           =   1575
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub Command1_Click()
    Text2.Locked = False
    Text2.PasswordChar = "*"
End Sub

