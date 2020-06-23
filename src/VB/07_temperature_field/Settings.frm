VERSION 5.00
Begin VB.Form Settings 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "参数设置"
   ClientHeight    =   9750
   ClientLeft      =   16065
   ClientTop       =   2820
   ClientWidth     =   5910
   LinkTopic       =   "Form2"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   9750
   ScaleWidth      =   5910
   Begin VB.Frame L_Frame 
      Caption         =   "潜热相关"
      Height          =   975
      Left            =   360
      TabIndex        =   27
      Top             =   7560
      Width           =   5295
      Begin VB.CheckBox Compute_L_Check 
         Caption         =   "计算潜热"
         Height          =   375
         Left            =   480
         TabIndex        =   28
         Top             =   360
         Value           =   1  'Checked
         Width           =   2055
      End
   End
   Begin VB.CommandButton Cancel_Button 
      Caption         =   "取消"
      Height          =   855
      Left            =   4080
      TabIndex        =   26
      Top             =   8640
      Width           =   1455
   End
   Begin VB.CommandButton Apply_Button 
      Caption         =   "应用"
      Height          =   855
      Left            =   2280
      TabIndex        =   25
      Top             =   8640
      Width           =   1455
   End
   Begin VB.CommandButton Confirm_Button 
      Caption         =   "确定"
      Height          =   855
      Left            =   360
      TabIndex        =   3
      Top             =   8640
      Width           =   1455
   End
   Begin VB.Frame Heat_Transfer_Coefficient_Frame 
      Caption         =   "传热系数"
      Height          =   2295
      Left            =   360
      TabIndex        =   2
      Top             =   5160
      Width           =   5295
      Begin VB.TextBox CA_Transfer_Box 
         Alignment       =   2  'Center
         Height          =   390
         Left            =   1680
         TabIndex        =   23
         Text            =   "29.03"
         Top             =   1680
         Width           =   2055
      End
      Begin VB.TextBox CS_Transfer_Box 
         Alignment       =   2  'Center
         Enabled         =   0   'False
         Height          =   390
         Left            =   1680
         TabIndex        =   22
         Text            =   "0"
         Top             =   1200
         Width           =   2055
      End
      Begin VB.TextBox SA_Transfer_Box 
         Alignment       =   2  'Center
         Height          =   375
         Left            =   1680
         TabIndex        =   21
         Text            =   "25.08"
         Top             =   720
         Width           =   2055
      End
      Begin VB.TextBox CC_Transfer_Box 
         Alignment       =   2  'Center
         Enabled         =   0   'False
         Height          =   375
         Left            =   1680
         TabIndex        =   17
         Text            =   "2000"
         Top             =   240
         Width           =   2055
      End
      Begin VB.Label CA_Transfer_Label 
         AutoSize        =   -1  'True
         Caption         =   "铸件/空气"
         Height          =   180
         Left            =   480
         TabIndex        =   20
         Top             =   1800
         Width           =   810
      End
      Begin VB.Label CS_Transfer_Label 
         AutoSize        =   -1  'True
         Caption         =   "铸件/铸型"
         Height          =   180
         Left            =   480
         TabIndex        =   19
         Top             =   1320
         Width           =   810
      End
      Begin VB.Label SA_Transfer_Label 
         AutoSize        =   -1  'True
         Caption         =   "铸型/空气"
         Height          =   180
         Left            =   480
         TabIndex        =   18
         Top             =   840
         Width           =   810
      End
      Begin VB.Label CC_Transfer_Label 
         AutoSize        =   -1  'True
         Caption         =   "铸件/冷铁"
         Height          =   180
         Left            =   480
         TabIndex        =   16
         Top             =   360
         Width           =   810
      End
   End
   Begin VB.Frame Start_Params_Frame 
      Caption         =   "初始温度"
      Height          =   2415
      Left            =   360
      TabIndex        =   1
      Top             =   2640
      Width           =   5295
      Begin VB.TextBox Air_T0_Box 
         Alignment       =   2  'Center
         Height          =   375
         Left            =   1680
         TabIndex        =   15
         Text            =   "30"
         Top             =   1800
         Width           =   2055
      End
      Begin VB.TextBox Chill_T0_Box 
         Alignment       =   2  'Center
         Height          =   375
         Left            =   1680
         TabIndex        =   14
         Text            =   "25"
         Top             =   1320
         Width           =   2055
      End
      Begin VB.TextBox Sand_T0_Box 
         Alignment       =   2  'Center
         Height          =   375
         Left            =   1680
         TabIndex        =   13
         Text            =   "30"
         Top             =   840
         Width           =   2055
      End
      Begin VB.TextBox Casting_T0_Box 
         Alignment       =   2  'Center
         Height          =   375
         Left            =   1680
         TabIndex        =   12
         Text            =   "973"
         Top             =   360
         Width           =   2055
      End
      Begin VB.Label Air_T0_Label 
         AutoSize        =   -1  'True
         Caption         =   "空气"
         Height          =   180
         Left            =   720
         TabIndex        =   11
         Top             =   1920
         Width           =   360
      End
      Begin VB.Label Chill_T0_Label 
         AutoSize        =   -1  'True
         Caption         =   "冷铁"
         Height          =   180
         Left            =   720
         TabIndex        =   10
         Top             =   1440
         Width           =   360
      End
      Begin VB.Label Sand_T0_Label 
         AutoSize        =   -1  'True
         Caption         =   "铸型"
         Height          =   180
         Left            =   720
         TabIndex        =   9
         Top             =   960
         Width           =   360
      End
      Begin VB.Label Casting_T0_Label 
         AutoSize        =   -1  'True
         Caption         =   "铸件"
         Height          =   180
         Left            =   720
         TabIndex        =   8
         Top             =   480
         Width           =   360
      End
   End
   Begin VB.Frame Basic_Params_Frame 
      Caption         =   "基础参数"
      Height          =   2055
      Left            =   360
      TabIndex        =   0
      Top             =   240
      Width           =   5295
      Begin VB.CommandButton Compute_Delta_T_Button 
         Caption         =   "自动计算时间步长"
         Height          =   855
         Left            =   4080
         TabIndex        =   24
         Top             =   600
         Width           =   975
      End
      Begin VB.TextBox Range_T_Box 
         Alignment       =   2  'Center
         Height          =   375
         Left            =   1680
         TabIndex        =   5
         Text            =   "20000"
         Top             =   1200
         Width           =   2055
      End
      Begin VB.TextBox Delta_T_Box 
         Alignment       =   2  'Center
         Height          =   375
         Left            =   1680
         TabIndex        =   4
         Text            =   "10"
         Top             =   600
         Width           =   2055
      End
      Begin VB.Label Range_T_Label 
         AutoSize        =   -1  'True
         Caption         =   "时间步数"
         Height          =   180
         Left            =   600
         TabIndex        =   7
         Top             =   1200
         Width           =   720
      End
      Begin VB.Label Delta_T_Label 
         AutoSize        =   -1  'True
         Caption         =   "时间步长"
         Height          =   180
         Left            =   600
         TabIndex        =   6
         Top             =   720
         Width           =   720
      End
   End
End
Attribute VB_Name = "Settings"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub Form_Load()
    Delta_T_Box.Text = delta_t
    Range_T_Box.Text = range_t
    Sand_T0_Box.Text = T0(SAND)
    Casting_T0_Box.Text = T0(CASTING)
    Chill_T0_Box.Text = T0(CHILL)
    Air_T0_Box.Text = T0(AIR)
    CC_Transfer_Box.Text = TT(CHILL, CASTING)
    SA_Transfer_Box.Text = TT(SAND, AIR)
    CS_Transfer_Box.Text = TT(CASTING, SAND)
    CA_Transfer_Box.Text = TT(CASTING, AIR)
    Compute_L_Check.Value = compute_L
End Sub

Private Sub Confirm_Button_Click()
    If Set_Params Then
        Unload Me
    End If
End Sub

Private Sub Apply_Button_Click()
    Set_Params
End Sub

Private Sub Cancel_Button_Click()
    Unload Me
End Sub

Private Sub Compute_Delta_T_Button_Click()
    Delta_T_Box.Text = Round(Get_Delta_T * 0.9, 3)
End Sub

Private Function Get_Delta_T() As Single
    Dim min_d!, max_d!, delta_t!, delta_t1!, delta_t2!
    Dim h!, M_Casting As Material, M_Sand As Material
    If Main.delta_x < Main.delta_y Then
        min_d = Main.delta_x
        max_d = Main.delta_y
    Else
        min_d = Main.delta_y
        max_d = Main.delta_x
    End If
    
    M_Casting = Materials(CASTING)
    M_Sand = Materials(SAND)
    h = Val(SA_Transfer_Box.Text)
    
    delta_t1 = 1 / 4 * min_d ^ 2 * M_Casting.c * M_Casting.rho / M_Casting.k
    delta_t2 = 1 / 4 * min_d ^ 2 * M_Sand.c * M_Sand.rho / M_Sand.k / (1 + h * max_d / M_Sand.k)
    
    If delta_t1 < delta_t2 Then
        delta_t = delta_t1
    Else
        delta_t = delta_t2
    End If
    Get_Delta_T = delta_t
End Function

Private Function Set_Params() As Boolean
    Set_Params = True
    If Val(Delta_T_Box.Text) > Get_Delta_T Then
        res = MsgBox("时间步长过大，可能导致模型不收敛，确定继续吗？", vbYesNo, "提示")
        If res = vbNo Then
            Set_Params = False
            Exit Function
        End If
    End If
    delta_t = Val(Delta_T_Box.Text)
    range_t = Val(Range_T_Box.Text)
    T0(SAND) = Val(Sand_T0_Box.Text)
    T0(CASTING) = Val(Casting_T0_Box.Text)
    T0(CHILL) = Val(Chill_T0_Box.Text)
    T0(AIR) = Val(Air_T0_Box.Text)
    TT(CHILL, CASTING) = Val(CC_Transfer_Box.Text): TT(CASTING, CHILL) = Val(CC_Transfer_Box.Text)
    TT(SAND, AIR) = Val(SA_Transfer_Box.Text): TT(AIR, SAND) = Val(SA_Transfer_Box.Text)
    TT(CASTING, SAND) = Val(CS_Transfer_Box.Text): TT(SAND, CASTING) = Val(CS_Transfer_Box.Text)
    TT(CASTING, AIR) = Val(CA_Transfer_Box.Text): TT(AIR, CASTING) = Val(CA_Transfer_Box.Text)
    compute_L = Compute_L_Check.Value
    Main.Compute_Button.Enabled = True
End Function
