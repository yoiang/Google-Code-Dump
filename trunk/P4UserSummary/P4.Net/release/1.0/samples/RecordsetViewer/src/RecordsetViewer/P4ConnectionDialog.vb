Public Class P4ConnectionDialog

    Private _p4 As P4API.P4Connection

    Public Overloads Function Show() As P4API.P4Connection
        _p4 = New P4API.P4Connection()

        _p4.Connect()
        txtPORT.Text = _p4.Port
        txtClient.Text = _p4.Client
        txtUser.Text = _p4.User

        SetIcons()
        MyBase.ShowDialog()

        Return _p4
    End Function

    Private Sub SetIcons()
        If _p4 Is Nothing Then Exit Sub

        Dim oldCursor As Cursor
        oldCursor = Me.Cursor
        Me.Cursor = Cursors.WaitCursor

        Try
            
            'If we got this far, then we connected to a valid server
            picPort.Image = ImageList2.Images(0)

            Dim rs As P4API.P4RecordSet
            rs = _p4.Run("info")

            If rs(0)("userName") = "*unknown*" Then
                picUser.Image = ImageList2.Images(1)
            Else
                picUser.Image = ImageList2.Images(0)
            End If

            If rs(0)("clientName") = "*unknown*" Then
                picClient.Image = ImageList2.Images(1)
            Else
                picClient.Image = ImageList2.Images(0)
            End If

            If _p4.IsValidConnection(True, False) Then
                picPassword.Image = ImageList2.Images(0)
                txtPassword.Enabled = False
                txtPassword.Text = "<valid login>"
                txtPassword.PasswordChar = String.Empty
            Else
                picPassword.Image = ImageList2.Images(1)
                txtPassword.Enabled = True
                txtPassword.Text = String.Empty
                txtPassword.PasswordChar = "*"
            End If
        Catch ex As Exception
            ' The likely exception, is total failure to connect!
            picPort.Image = ImageList2.Images(1)
            picUser.Image = ImageList2.Images(1)
            picClient.Image = ImageList2.Images(1)
            picPassword.Image = ImageList2.Images(1)
            Exit Sub
        Finally
            _p4.Disconnect()
            Me.Cursor = oldCursor
        End Try
    End Sub

    Private Sub UpdateValues()
        _p4 = New P4API.P4Connection()
        _p4.Port = txtPORT.Text
        _p4.User = txtUser.Text
        _p4.Client = txtClient.Text
        If Len(txtPassword.Text) > 0 Then
            Try
                _p4.Connect()
                _p4.Login(txtPassword.Text)
            Catch
                ' Do nothing -- IsValidConnection will hit later
            End Try
        End If

    End Sub

    Private Sub cmdConnect_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles cmdConnect.Click
        UpdateValues()
        Me.Close()
    End Sub

    Private Sub cmdTest_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles cmdTest.Click
        UpdateValues()
        SetIcons()
    End Sub

    Private Sub cmdCancel_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles cmdCancel.Click
        _p4 = Nothing
        Me.Close()
    End Sub
End Class