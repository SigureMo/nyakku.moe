Attribute VB_Name = "Module1"
Public Type Material
    name As String
    type As String
    rho As String
    c As String
    k As String
    Tl As String
    Ts As String
    L As String
End Type

' 公用数据部分
Public Materials(2) As Material
Public SAND%, CASTING%, CHILL%
Public range_x%, range_y%
Public color_arr
Public T0(3)
Public TT(3, 3)
Public delta_t
Public range_t

Public Sub Init_Material_Params()
    SAND = 0
    CASTING = 1
    CHILL = 2
    AIR = 3
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
    m.type = params(1)
    m.rho = params(2)
    m.c = params(3)
    m.k = params(4)
    m.Tl = params(5)
    m.Ts = params(6)
    m.L = params(7)
    StringToMaterial = m
End Function
