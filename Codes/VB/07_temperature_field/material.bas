Attribute VB_Name = "Module1"
Public Type Material
    name As String
    type_ As String
    param1 As String
End Type

' 保存前处理文件
Public Sub Save_Materials(ByRef Materials() As Material)
    Dim filename As String
    Dim m As Object
    filename = "data/mesh.dat"
    Open filename For Output As #1
    For i = 0 To 2
        Print #1, Materials(i).name & "," & Materials(i).type_ & "," & Materials(i).param1
    Next i
    Close #1
End Sub

' 加载前处理文件
Public Sub Load_Materials(ByRef Materials() As Material)
    Dim filename As String
    Dim s As String
    filename = "data/mesh.dat"
    Open filename For Input As #1
    For i = 0 To 2
        Line Input #1, s
        If Not s = "" Then
            params = Split(s, ",")
            Materials(i).name = params(0)
            Materials(i).type_ = params(1)
            Materials(i).param1 = params(2)
        End If
    Next i
    Close #1
End Sub

' 加载材料参数文件
Public Sub Load_Params(ByRef Material_List() As Material)
    Dim s As String
    Dim filename As String
    filename = "data/params.dat"
    i = 0
    Open filename For Input As #1
    Do While Not EOF(1)
        Line Input #1, s
        If Not (s = "" Or Mid(s, 1, 1) = "#") Then
            params = Split(s, ",")
            ReDim Preserve Material_List(i)
            Material_List(i).name = params(0)
            Material_List(i).type_ = params(1)
            Material_List(i).param1 = params(2)
            i = i + 1
        End If
    Loop
    Close #1
End Sub
