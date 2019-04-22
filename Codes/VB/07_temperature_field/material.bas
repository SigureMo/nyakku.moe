Attribute VB_Name = "Module1"
Public Type Material
    name As String
    type_ As String
    param1 As String
End Type

Public Sub Save_Materials()
    Dim filename As String
    filename = "data/mesh.dat"
    Open filename For Output As #1
    For Each m In Materials
        Print #1, m.name & "," & m.type_ & "," & m.param1
    Next m
    Close #1
End Sub

Public Sub Load_Materials()
    Dim filename As String
    Dim s As String
    filename = "data/mesh.dat"
    Open filename For Input As #1
    For i = 0 To 2
        Input #1, s
        params = Split(s, ",")
        Materials(i).name = params(0)
        Materials(i).type_ = params(1)
        Materials(i).param1 = params(2)
    Next i
End Sub
