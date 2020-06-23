VERSION 5.00
Begin VB.Form Form1
   Caption         =   "Form1"
   ClientHeight    =   4950
   ClientLeft      =   120
   ClientTop       =   465
   ClientWidth     =   5985
   LinkTopic       =   "Form1"
   ScaleHeight     =   4950
   ScaleWidth      =   5985
   StartUpPosition =   3  '����ȱʡ
   Begin VB.CommandButton Command1
      Caption         =   "Draw!"
      Height          =   735
      Left            =   3960
      TabIndex        =   0
      Top             =   3960
      Width           =   1695
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Dim cnt%

Private Sub Command1_Click()

    Dim w%, h%, r%, a!, Color
    w = Form1.Width
    h = Form1.Height
    r = 1000 '�����޸� Radius
    a = Sqr(2) * r
    Form1.Caption = "Canvas"
    Randomize

    If cnt Mod 3 = 0 Then
        Command1.Caption = "Draw a rectangle!"
        Color = RGB(Rnd * 255, Rnd * 255, Rnd * 255)
        Form1.FillStyle = vbFSSolid
        Form1.FillColor = Color
        Form1.Circle (w / 2, h / 2), r, Color
    ElseIf cnt Mod 3 = 1 Then
        Command1.Caption = "Clear!"
        Form1.Line ((w - a) / 2, (h - a) / 2)-((w + a) / 2, (h + a) / 2), RGB(Rnd * 255, Rnd * 255, Rnd * 255), BF
    ElseIf cnt Mod 3 = 2 Then
        Command1.Caption = "Draw a circle!"
        Cls
        'MsgBox cnt
    End If
    cnt = cnt + 1

End Sub

Private Sub Form_Load()
    cnt = 0
End Sub
