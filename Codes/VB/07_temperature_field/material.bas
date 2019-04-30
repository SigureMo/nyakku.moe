Attribute VB_Name = "Module1"
Public Type Material
    name As String
    type_ As String
    param1 As String
End Type

' 材料转换为输出文本
Public Function MaterialToString(m As Material) As String
    MaterialToString = m.name & "," & m.type_ & "," & m.param1
End Function

' 文本转换为材料
Public Function StringToMaterial(ByRef s As String) As Material
    Dim m As Material
    params = Split(s, ",")
    m.name = params(0)
    m.type_ = params(1)
    m.param1 = params(2)
    StringToMaterial = m
End Function

' 加载材料参数文件
Public Sub Load_Params(ByRef Material_List() As Material)
    Dim s As String
    Dim filename As String
    filename = App.Path & "\data\params.dat"
    i = 0
    Open filename For Input As #1
        Do While Not EOF(1)
            Line Input #1, s
            If Not (s = "" Or Mid(s, 1, 1) = "#") Then
                ReDim Preserve Material_List(i)
                Material_List(i) = StringToMaterial(s)
                i = i + 1
            End If
        Loop
    Close #1
End Sub
