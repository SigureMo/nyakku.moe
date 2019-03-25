VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "Queue"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Private elements(200) As Variant
Private frontP As Integer
Private endP As Integer

Private Sub Class_Initialize()
    frontP = 0
    endP = 0
End Sub

Public Sub enqueue(value As Variant)
    elements(endP) = value
    endP = endP + 1
End Sub

Public Function dequeue() As Variant
    If isEmpty() Then
        MsgBox "¶ÓÁÐÎª¿Õ£¡"
    End If
    dequeue = elements(frontP)
    frontP = frontP + 1
End Function

Public Function isEmpty() As Boolean
    isEmpty = (frontP = endP)
End Function

Public Sub clear()
    While Not isEmpty()
        t = dequeue()
    Wend
End Sub
