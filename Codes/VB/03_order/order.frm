VERSION 5.00
Begin VB.Form Form1 
   Caption         =   "Form1"
   ClientHeight    =   4770
   ClientLeft      =   120
   ClientTop       =   465
   ClientWidth     =   7560
   LinkTopic       =   "Form1"
   ScaleHeight     =   4770
   ScaleWidth      =   7560
   StartUpPosition =   3  '窗口缺省
   Begin VB.CommandButton Command1 
      Caption         =   "排序"
      Height          =   1815
      Left            =   4200
      TabIndex        =   5
      Top             =   1200
      Width           =   1695
   End
   Begin VB.TextBox Text4 
      Height          =   615
      Left            =   1320
      TabIndex        =   4
      Top             =   3360
      Width           =   4455
   End
   Begin VB.TextBox Text3 
      Height          =   495
      Left            =   1320
      TabIndex        =   3
      Top             =   2520
      Width           =   2175
   End
   Begin VB.TextBox Text2 
      Height          =   495
      Left            =   1320
      TabIndex        =   2
      Top             =   1800
      Width           =   2175
   End
   Begin VB.TextBox Text1 
      Height          =   495
      Left            =   1320
      TabIndex        =   0
      Top             =   1080
      Width           =   2175
   End
   Begin VB.Label Label5 
      Caption         =   "排序结果"
      Height          =   495
      Left            =   240
      TabIndex        =   9
      Top             =   3480
      Width           =   855
   End
   Begin VB.Label Label4 
      Caption         =   "第三个数"
      Height          =   375
      Left            =   240
      TabIndex        =   8
      Top             =   2640
      Width           =   855
   End
   Begin VB.Label Label3 
      Caption         =   "第二个数"
      Height          =   375
      Left            =   240
      TabIndex        =   7
      Top             =   1920
      Width           =   855
   End
   Begin VB.Label Label2 
      Caption         =   "第一个数"
      Height          =   375
      Left            =   240
      TabIndex        =   6
      Top             =   1200
      Width           =   855
   End
   Begin VB.Label Label1 
      Alignment       =   2  'Center
      AutoSize        =   -1  'True
      Caption         =   "将三个数从大到小排序"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   12
         Charset         =   134
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   240
      Left            =   2280
      TabIndex        =   1
      Top             =   240
      Width           =   2400
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Public Sub check_TextBox(TextBox As Object, num As Integer)
    If TextBox.Text = "" Then
        MsgBox "文本框 " & num & " 不能为空！"
    ElseIf Not IsNumeric(TextBox.Text) Then
        MsgBox "请在文本框 " & num & " 输入纯数字！"
    End If
End Sub

Public Function order(ByRef a() As Single) As Single()
    length = UBound(a) - LBound(a) + 1
    Dim tmp!
    i = 0
    While i < length
        j = i + 1
        While j < length
            If a(i) < a(j) Then
                tmp = a(j)
                a(j) = a(i)
                a(i) = tmp
           End If
           j = j + 1
        Wend
        i = i + 1
    Wend
    order = a
End Function

Public Function print_array(ByRef a() As Single) As String
    s = ""
    For Each c In a
        s = s & c & ";"
    Next c
    print_array = s
End Function

Private Sub Command1_Click()
    Dim a(2) As Single
    Call check_TextBox(Text1, 1)
    Call check_TextBox(Text2, 2)
    Call check_TextBox(Text3, 3)
    
    a(0) = Val(Text1.Text)
    a(1) = Val(Text2.Text)
    a(2) = Val(Text3.Text)
    
    Call order(a)
    Text4.Text = print_array(a)

End Sub

Private Sub Form_Load()
    Text4.Locked = True
End Sub
