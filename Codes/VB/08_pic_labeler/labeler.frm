VERSION 5.00
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.2#0"; "COMDLG32.OCX"
Object = "{6B7E6392-850A-101B-AFC0-4210102A8DA7}#1.3#0"; "COMCTL32.OCX"
Begin VB.Form Labeler_Form 
   Caption         =   "Labeler"
   ClientHeight    =   10245
   ClientLeft      =   225
   ClientTop       =   870
   ClientWidth     =   17940
   LinkTopic       =   "Form1"
   ScaleHeight     =   10245
   ScaleWidth      =   17940
   StartUpPosition =   3  '窗口缺省
   Begin VB.CommandButton Last_Button 
      Caption         =   "Last"
      Height          =   735
      Left            =   15000
      TabIndex        =   16
      Top             =   5880
      Width           =   2175
   End
   Begin ComctlLib.StatusBar StatusBar 
      Align           =   2  'Align Bottom
      Height          =   360
      Left            =   0
      TabIndex        =   15
      Top             =   9885
      Width           =   17940
      _ExtentX        =   31644
      _ExtentY        =   635
      SimpleText      =   ""
      _Version        =   327682
      BeginProperty Panels {0713E89E-850A-101B-AFC0-4210102A8DA7} 
         NumPanels       =   2
         BeginProperty Panel1 {0713E89F-850A-101B-AFC0-4210102A8DA7} 
            Object.Width           =   3528
            MinWidth        =   3528
            TextSave        =   ""
            Object.Tag             =   ""
         EndProperty
         BeginProperty Panel2 {0713E89F-850A-101B-AFC0-4210102A8DA7} 
            Object.Tag             =   ""
         EndProperty
      EndProperty
   End
   Begin MSComDlg.CommonDialog CommonDialog 
      Left            =   240
      Top             =   240
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   393216
   End
   Begin VB.CommandButton Skip_Command 
      Caption         =   "Skip"
      Height          =   735
      Left            =   15000
      TabIndex        =   13
      Top             =   8040
      Width           =   2175
   End
   Begin VB.Frame Labels_Frame 
      Caption         =   "Labels"
      Height          =   3855
      Left            =   15000
      TabIndex        =   2
      Top             =   1560
      Width           =   2295
      Begin VB.CommandButton Clear_Button 
         Caption         =   "Clear"
         Height          =   375
         Left            =   960
         TabIndex        =   14
         Top             =   3240
         Width           =   975
      End
      Begin VB.TextBox bw_Text 
         Height          =   270
         Left            =   960
         Locked          =   -1  'True
         TabIndex        =   12
         Text            =   "0"
         Top             =   2520
         Width           =   855
      End
      Begin VB.TextBox bh_Text 
         Height          =   270
         Left            =   960
         Locked          =   -1  'True
         TabIndex        =   11
         Text            =   "0"
         Top             =   2040
         Width           =   855
      End
      Begin VB.TextBox by_Text 
         Height          =   270
         Left            =   960
         Locked          =   -1  'True
         TabIndex        =   10
         Text            =   "0"
         Top             =   1560
         Width           =   855
      End
      Begin VB.TextBox bx_Text 
         Height          =   270
         Left            =   960
         Locked          =   -1  'True
         TabIndex        =   9
         Text            =   "0"
         Top             =   1080
         Width           =   855
      End
      Begin VB.TextBox pc_Text 
         Height          =   270
         Left            =   960
         Locked          =   -1  'True
         TabIndex        =   8
         Text            =   "0"
         Top             =   600
         Width           =   900
      End
      Begin VB.Label bw_Label 
         AutoSize        =   -1  'True
         Caption         =   "bw"
         Height          =   180
         Left            =   360
         TabIndex        =   7
         Top             =   2520
         Width           =   180
      End
      Begin VB.Label bh_Label 
         AutoSize        =   -1  'True
         Caption         =   "bh"
         Height          =   180
         Left            =   360
         TabIndex        =   6
         Top             =   2040
         Width           =   180
      End
      Begin VB.Label by_Label 
         AutoSize        =   -1  'True
         Caption         =   "by"
         Height          =   180
         Left            =   360
         TabIndex        =   5
         Top             =   1560
         Width           =   180
      End
      Begin VB.Label bx_Label 
         AutoSize        =   -1  'True
         Caption         =   "bx"
         Height          =   180
         Left            =   360
         TabIndex        =   4
         Top             =   1080
         Width           =   180
      End
      Begin VB.Label pc_Label 
         AutoSize        =   -1  'True
         Caption         =   "pc"
         Height          =   180
         Left            =   360
         TabIndex        =   3
         Top             =   600
         Width           =   180
      End
   End
   Begin VB.CommandButton Save_Button 
      Caption         =   "Save"
      Height          =   735
      Left            =   15000
      TabIndex        =   1
      Top             =   6960
      Width           =   2175
   End
   Begin VB.PictureBox PictureBox 
      AutoRedraw      =   -1  'True
      AutoSize        =   -1  'True
      Height          =   9600
      Left            =   120
      ScaleHeight     =   9540
      ScaleWidth      =   14340
      TabIndex        =   0
      Top             =   120
      Width           =   14400
   End
   Begin VB.Menu File 
      Caption         =   "File"
      Begin VB.Menu Open_Folder 
         Caption         =   "Open Folder"
      End
   End
   Begin VB.Menu Settings 
      Caption         =   "Settings"
      Begin VB.Menu Output_Path 
         Caption         =   "Output Path"
      End
   End
End
Attribute VB_Name = "Labeler_Form"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Dim pic_list() As String
Dim pic_cnt As Integer
Dim pic_num As Integer
Dim pic_H As Integer
Dim pic_W As Integer
Dim out_path As String
Dim start_x As Integer
Dim start_y As Integer

' 初始化参数
Private Sub Form_Load()
    pic_cnt = 0
    pic_num = 0
    pic_H = PictureBox.Height
    pic_W = PictureBox.Width
    out_path = App.path & "\out.csv"
    start_x = -1
End Sub

' 显示选择文件夹对话框
Public Function ShowFolderDialog() As String
    ' src: http://blog.sina.com.cn/s/blog_ab179db901015a64.html
    Dim spShell, spFolder, spFolderItem, spPath As String
    Const WINDOW_HANDLE = 0
    Const NO_OPTIONS = 0
    Set spShell = CreateObject("Shell.Application")
    Set spFolder = spShell.BrowseForFolder(WINDOW_HANDLE, "选择目录:", NO_OPTIONS, "C:\Scripts")
    
    If spFolder Is Nothing Then
        ShowFolderDialog = ""
    Else
        Set spFolderItem = spFolder.Self
        spPath = spFolderItem.path
        spPath = Replace(spPath, "\", "\")
        ShowFolderDialog = spPath
    End If
End Function

' 选择图片所在文件夹
Private Sub Open_Folder_Click()
    Dim path As String
    path = ShowFolderDialog()
    
    ' src: https://zhidao.baidu.com/question/279803154.html
    Dim fso As Object
    Dim folder As Object
    Dim subfolder As Object
    Dim File As Object
    Dim pic_path As Object
    Set fso = CreateObject("scripting.filesystemobject") '创建FSO对象
    If path = "" Then
        Exit Sub
    End If
    Set folder = fso.GetFolder(path)
    For Each pic_path In folder.Files '遍历根文件夹下的文件
        pic_num = pic_num + 1
        ReDim Preserve pic_list(pic_num) As String
        pic_list(pic_num - 1) = pic_path
    Next
    Set fso = Nothing
    Set folder = Nothing
    ShowImage (pic_cnt)
End Sub

' 显示某张图片
Private Sub ShowImage(num As Integer)
    pc_Text.Text = 0
    bx_Text.Text = 0
    by_Text.Text = 0
    bh_Text.Text = 0
    bw_Text.Text = 0
    If num >= pic_num Then
        MsgBox "没有更多图片了！"
        Exit Sub
    End If
    PictureBox.Picture = LoadPicture(pic_list(num))
    PictureBox.Height = pic_H
    PictureBox.Width = pic_W
    PictureBox.PaintPicture PictureBox, 0, 0, PictureBox.Width, PictureBox.Height
    pic_cnt = num + 1
    StatusBar.Panels(2).Text = pic_cnt & "/" & pic_num
End Sub

' 修改输出路径
Private Sub Output_Path_Click()
    On Error GoTo ErrHandler
    Dim filename As String
    filename = out_path
    CommonDialog.CancelError = True
    CommonDialog.Flags = cdlOFNHideReadOnly
    CommonDialog.Filter = "All Files (*.*)|*.*|Text Files (*.txt)|*.txt|Csv Files (*.csv)|*.csv"
    CommonDialog.filename = filename
    CommonDialog.FilterIndex = 3
    CommonDialog.ShowOpen
    out_path = CommonDialog.filename
ErrHandler:
    Exit Sub
End Sub

' 写入一行数据
Private Sub write_line(line As String)
    Open out_path For Append As #1
        Print #1, line
    Close #1
End Sub

' 保存回调
Private Sub Save_Button_Click()
    Call write_line(pic_list(pic_cnt - 1) & "," & pc_Text & "," & bx_Text & "," & by_Text & "," & bh_Text & "," & bw_Text)
    ShowImage (pic_cnt)
    start_x = -1
End Sub

' 鼠标移动回调
Private Sub picturebox_MouseMove(Button As Integer, Shift As Integer, x As Single, y As Single)
    StatusBar.Panels(1).Text = "(" & Round(x / pic_W, 3) & ", " & Round(y / pic_H, 3) & ")"
End Sub

' 书包点击回调
Private Sub picturebox_MouseDown(Button As Integer, Shift As Integer, x As Single, y As Single)
    If start_x = -1 Then
        start_x = Int(x)
        start_y = Int(y)
    Else
        Call select_area(start_x, start_y, Int(x), Int(y))
        start_x = -1
    End If
End Sub

' 框选点击区域
Private Sub select_area(start_x As Integer, start_y As Integer, end_x As Integer, end_y As Integer)
    ShowImage (pic_cnt - 1)
    PictureBox.DrawWidth = 3
    PictureBox.Line (start_x, start_y)-(end_x, start_y), vbRed
    PictureBox.Line (start_x, end_y)-(end_x, end_y), vbRed
    PictureBox.Line (start_x, start_y)-(start_x, end_y), vbRed
    PictureBox.Line (end_x, start_y)-(end_x, end_y), vbRed
    pc_Text.Text = 1
    bx_Text.Text = Round((start_x + end_x) / 2 / pic_W, 3)
    by_Text.Text = Round((start_y + end_y) / 2 / pic_H, 3)
    bh_Text.Text = Round(Abs(end_y - start_y) / pic_H, 3)
    bw_Text.Text = Round(Abs(end_x - start_x) / pic_W, 3)
End Sub

' 清空回调
Private Sub Clear_Button_Click()
    ShowImage (pic_cnt - 1)
End Sub

' 上一张回调
Private Sub Last_Button_Click()
    start_x = -1
    ShowImage (pic_cnt - 2)
End Sub

' 跳过回调
Private Sub Skip_Command_Click()
    start_x = -1
    ShowImage (pic_cnt)
End Sub
