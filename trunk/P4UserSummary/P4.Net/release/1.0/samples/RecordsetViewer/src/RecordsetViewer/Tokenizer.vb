Option Strict On
Imports System.Text
Public Class Tokenizer
    Public Shared Function Tokenize(ByVal s As String) As TokenCollection
        Dim tokens As New TokenCollection()
        Dim i As Integer
        Dim inQuote As Boolean = False
        Dim sb As New StringBuilder()
        Dim aChar As String
        Dim chars() As Char

        Dim quoteChar As String = ""
        s = s.Trim()
        If s <> String.Empty Then
            chars = s.ToCharArray
            For i = 0 To chars.Length - 1
                aChar = chars(i)
                Select Case aChar
                    Case """"c, "'"c
                        If quoteChar = "" Then
                            quoteChar = aChar
                            inQuote = Not inQuote
                        ElseIf quoteChar = aChar Then
                            inQuote = Not inQuote
                            quoteChar = ""
                            If sb.Length > 0 Then
                                tokens.Add(sb.ToString)
                                sb = New StringBuilder()
                            End If
                        Else
                            sb.Append(aChar)
                        End If
                    Case " "c, Chr(9), Chr(10), Chr(13)
                        If Not inQuote Then
                            If sb.Length > 0 Then
                                tokens.Add(sb.ToString)
                                sb = New StringBuilder()
                            End If
                        Else
                            sb.Append(aChar)
                        End If
                    Case Else
                        sb.Append(aChar)
                End Select
            Next
        End If
        If sb.Length > 0 Then
            tokens.Add(sb.ToString)
        End If
        Return tokens
    End Function
End Class
