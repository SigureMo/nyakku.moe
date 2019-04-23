VERSION 5.00
Object = "{6B7E6392-850A-101B-AFC0-4210102A8DA7}#1.3#0"; "COMCTL32.OCX"
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

Private Sub Data_Import_Button_Click()
    Call Load_Materials(Materials)
    Dim s As String
    Dim i%
    Dim begin_grid
    begin_grid = False
    i = 0
    Open "data/mesh.dat" For Input As #1
    Do While Not EOF(1)
        Line Input #1, s
        If Not s = "" Then
            If begin_grid = False Then
                If Split(s, ":")(0) = "RANGE" Then
                    range_x = Val(Split(Split(s, ":")(1), ",")(0))
                    range_y = Val(Split(Split(s, ":")(1), ",")(1))
                    begin_grid = True
                    ReDim Preserve Material_Matrix(range_x - 1, range_y - 1)
                    ReDim Preserve Temperature_Matrix(range_x - 1, range_y - 1)
                    ReDim Preserve Tmp_Matrix(range_x - 1, range_y - 1)
                End If
            Else
                j = 0
                For Each c In Split(s, ",")
                    Material_Matrix(i, j) = Val(c)
                    j = j + 1
                Next c
                i = i + 1
            End If
        End If
    Loop
    Close #1
    Loaded = True
End Sub

Private Sub Form_Load()
    PI = 3.1415926
    Loaded = False
    Init_ShadeGuide
End Sub

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

Private Function Get_Color(t As Integer) As Variant
    Dim i%
    i = t / 100
    delta = PI / 16
    Get_Color = RGB((Sin(delta * i - PI / 2) + 1) * 255 / 2, Sin(delta * i) * 255, (Sin(delta * i + PI / 2) + 1) * 255 / 2)
End Function
