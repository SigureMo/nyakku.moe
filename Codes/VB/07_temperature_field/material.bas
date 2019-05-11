Attribute VB_Name = "Module1"
Public Type Material
    name As String
    type As Integer
    rho As Single
    c As Single
    k As Single
    Tl As Single
    Ts As Single
    L As Single
End Type

' 公用数据部分
Public Materials(2) As Material
Public SAND%, CASTING%, CHILL%, AIR%
Public range_x%, range_y%
Public color_arr
Public T0(3) ' 始温数组
Public TT(3, 3) ' 传热矩阵
Public delta_t
Public range_t
Public compute_L%

Public Sub Init_Material_Params()
    SAND = 0
    CASTING = 1
    CHILL = 2
    AIR = 3
    delta_t = 10
    range_t = 20000
    T0(SAND) = 30
    T0(CASTING) = 973
    T0(CHILL) = 25
    T0(AIR) = 30
    TT(CHILL, CASTING) = 2000: TT(CASTING, CHILL) = 2000
    TT(SAND, AIR) = 25.08: TT(AIR, SAND) = 25.08
    TT(CASTING, SAND) = 0: TT(SAND, CASTING) = 0
    TT(CASTING, AIR) = 29.03: TT(AIR, CASTING) = 29.03
    compute_L = 1
    color_arr = Array(vbYellow, vbRed, vbBlue)
End Sub

' 材料转换为输出文本
Public Function MaterialToString(m As Material) As String
    MaterialToString = m.name & "," & m.type & "," & m.rho & "," & m.c & "," & m.k & "," & m.Tl & "," & m.Ts & "," & m.L
End Function

' 文本转换为材料
Public Function StringToMaterial(ByRef s As String) As Material
    Dim m As Material
    params = Split(s, ",")
    m.name = params(0)
    m.type = Val(params(1))
    m.rho = Val(params(2))
    m.c = Val(params(3))
    m.k = Val(params(4))
    m.Tl = Val(params(5))
    m.Ts = Val(params(6))
    m.L = Val(params(7))
    StringToMaterial = m
End Function
