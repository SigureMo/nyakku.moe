VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "Stack"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Private elements(200) As Variant
Private size As Integer

Private Sub Class_Initialize()
    size = 0
End Sub

Public Sub push(value As Variant)
    elements(size) = value
    size = size + 1
End Sub

Public Function pop() As Variant
    If isEmpty() Then
        MsgBox "¶ÑÕ»Îª¿Õ£¡"
    End If
    size = size - 1
    pop = elements(size)
End Function

Public Function isEmpty() As Boolean
    isEmpty = (size = 0)
End Function

Public Function getElements() As Variant()
    getElements = elements
End Function

Public Sub clear()
    While Not isEmpty()
        t = pop()
    Wend
End Sub

Public Function peek() As Variant
    If isEmpty() Then
        MsgBox "¶ÑÕ»Îª¿Õ£¡"
    End If
    pop = elements(size - 1)
End Function
