<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> _
Partial Class P4ConnectionDialog
    Inherits System.Windows.Forms.Form

    'Form overrides dispose to clean up the component list.
    <System.Diagnostics.DebuggerNonUserCode()> _
    Protected Overrides Sub Dispose(ByVal disposing As Boolean)
        If disposing AndAlso components IsNot Nothing Then
            components.Dispose()
        End If
        MyBase.Dispose(disposing)
    End Sub

    'Required by the Windows Form Designer
    Private components As System.ComponentModel.IContainer

    'NOTE: The following procedure is required by the Windows Form Designer
    'It can be modified using the Windows Form Designer.  
    'Do not modify it using the code editor.
    <System.Diagnostics.DebuggerStepThrough()> _
    Private Sub InitializeComponent()
        Me.components = New System.ComponentModel.Container
        Dim resources As System.ComponentModel.ComponentResourceManager = New System.ComponentModel.ComponentResourceManager(GetType(P4ConnectionDialog))
        Me.Label1 = New System.Windows.Forms.Label
        Me.Label2 = New System.Windows.Forms.Label
        Me.Label3 = New System.Windows.Forms.Label
        Me.Label4 = New System.Windows.Forms.Label
        Me.txtPORT = New System.Windows.Forms.TextBox
        Me.txtUser = New System.Windows.Forms.TextBox
        Me.txtClient = New System.Windows.Forms.TextBox
        Me.txtPassword = New System.Windows.Forms.TextBox
        Me.cmdConnect = New System.Windows.Forms.Button
        Me.picPort = New System.Windows.Forms.PictureBox
        Me.ImageList1 = New System.Windows.Forms.ImageList(Me.components)
        Me.ImageList2 = New System.Windows.Forms.ImageList(Me.components)
        Me.picUser = New System.Windows.Forms.PictureBox
        Me.picClient = New System.Windows.Forms.PictureBox
        Me.picPassword = New System.Windows.Forms.PictureBox
        Me.cmdTest = New System.Windows.Forms.Button
        Me.cmdCancel = New System.Windows.Forms.Button
        CType(Me.picPort, System.ComponentModel.ISupportInitialize).BeginInit()
        CType(Me.picUser, System.ComponentModel.ISupportInitialize).BeginInit()
        CType(Me.picClient, System.ComponentModel.ISupportInitialize).BeginInit()
        CType(Me.picPassword, System.ComponentModel.ISupportInitialize).BeginInit()
        Me.SuspendLayout()
        '
        'Label1
        '
        Me.Label1.AutoSize = True
        Me.Label1.Location = New System.Drawing.Point(26, 13)
        Me.Label1.Name = "Label1"
        Me.Label1.Size = New System.Drawing.Size(53, 13)
        Me.Label1.TabIndex = 0
        Me.Label1.Text = "P4PORT:"
        '
        'Label2
        '
        Me.Label2.AutoSize = True
        Me.Label2.Location = New System.Drawing.Point(26, 40)
        Me.Label2.Name = "Label2"
        Me.Label2.Size = New System.Drawing.Size(32, 13)
        Me.Label2.TabIndex = 0
        Me.Label2.Text = "User:"
        '
        'Label3
        '
        Me.Label3.AutoSize = True
        Me.Label3.Location = New System.Drawing.Point(26, 66)
        Me.Label3.Name = "Label3"
        Me.Label3.Size = New System.Drawing.Size(36, 13)
        Me.Label3.TabIndex = 0
        Me.Label3.Text = "Client:"
        '
        'Label4
        '
        Me.Label4.AutoSize = True
        Me.Label4.Location = New System.Drawing.Point(26, 92)
        Me.Label4.Name = "Label4"
        Me.Label4.Size = New System.Drawing.Size(56, 13)
        Me.Label4.TabIndex = 0
        Me.Label4.Text = "Password:"
        '
        'txtPORT
        '
        Me.txtPORT.Location = New System.Drawing.Point(105, 13)
        Me.txtPORT.Name = "txtPORT"
        Me.txtPORT.Size = New System.Drawing.Size(243, 20)
        Me.txtPORT.TabIndex = 2
        '
        'txtUser
        '
        Me.txtUser.Location = New System.Drawing.Point(105, 40)
        Me.txtUser.Name = "txtUser"
        Me.txtUser.Size = New System.Drawing.Size(243, 20)
        Me.txtUser.TabIndex = 3
        '
        'txtClient
        '
        Me.txtClient.Location = New System.Drawing.Point(105, 66)
        Me.txtClient.Name = "txtClient"
        Me.txtClient.Size = New System.Drawing.Size(243, 20)
        Me.txtClient.TabIndex = 4
        '
        'txtPassword
        '
        Me.txtPassword.Location = New System.Drawing.Point(105, 92)
        Me.txtPassword.Name = "txtPassword"
        Me.txtPassword.PasswordChar = Global.Microsoft.VisualBasic.ChrW(42)
        Me.txtPassword.Size = New System.Drawing.Size(243, 20)
        Me.txtPassword.TabIndex = 5
        '
        'cmdConnect
        '
        Me.cmdConnect.Location = New System.Drawing.Point(272, 124)
        Me.cmdConnect.Name = "cmdConnect"
        Me.cmdConnect.Size = New System.Drawing.Size(75, 23)
        Me.cmdConnect.TabIndex = 1
        Me.cmdConnect.Text = "&Connect"
        Me.cmdConnect.UseVisualStyleBackColor = True
        '
        'picPort
        '
        Me.picPort.Location = New System.Drawing.Point(4, 11)
        Me.picPort.Name = "picPort"
        Me.picPort.Size = New System.Drawing.Size(16, 16)
        Me.picPort.TabIndex = 3
        Me.picPort.TabStop = False
        '
        'ImageList1
        '
        Me.ImageList1.ColorDepth = System.Windows.Forms.ColorDepth.Depth8Bit
        Me.ImageList1.ImageSize = New System.Drawing.Size(16, 16)
        Me.ImageList1.TransparentColor = System.Drawing.Color.Transparent
        '
        'ImageList2
        '
        Me.ImageList2.ImageStream = CType(resources.GetObject("ImageList2.ImageStream"), System.Windows.Forms.ImageListStreamer)
        Me.ImageList2.TransparentColor = System.Drawing.Color.Transparent
        Me.ImageList2.Images.SetKeyName(0, "Check.ico")
        Me.ImageList2.Images.SetKeyName(1, "Warning.ico")
        '
        'picUser
        '
        Me.picUser.Location = New System.Drawing.Point(4, 37)
        Me.picUser.Name = "picUser"
        Me.picUser.Size = New System.Drawing.Size(16, 16)
        Me.picUser.TabIndex = 3
        Me.picUser.TabStop = False
        '
        'picClient
        '
        Me.picClient.Location = New System.Drawing.Point(4, 63)
        Me.picClient.Name = "picClient"
        Me.picClient.Size = New System.Drawing.Size(16, 16)
        Me.picClient.TabIndex = 3
        Me.picClient.TabStop = False
        '
        'picPassword
        '
        Me.picPassword.Location = New System.Drawing.Point(4, 89)
        Me.picPassword.Name = "picPassword"
        Me.picPassword.Size = New System.Drawing.Size(16, 16)
        Me.picPassword.TabIndex = 3
        Me.picPassword.TabStop = False
        '
        'cmdTest
        '
        Me.cmdTest.Location = New System.Drawing.Point(191, 124)
        Me.cmdTest.Name = "cmdTest"
        Me.cmdTest.Size = New System.Drawing.Size(75, 23)
        Me.cmdTest.TabIndex = 6
        Me.cmdTest.Text = "&Test"
        Me.cmdTest.UseVisualStyleBackColor = True
        '
        'cmdCancel
        '
        Me.cmdCancel.Location = New System.Drawing.Point(4, 124)
        Me.cmdCancel.Name = "cmdCancel"
        Me.cmdCancel.Size = New System.Drawing.Size(75, 23)
        Me.cmdCancel.TabIndex = 7
        Me.cmdCancel.Text = "C&ancel"
        Me.cmdCancel.UseVisualStyleBackColor = True
        '
        'P4ConnectionDialog
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(6.0!, 13.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.ClientSize = New System.Drawing.Size(360, 159)
        Me.ControlBox = False
        Me.Controls.Add(Me.picPassword)
        Me.Controls.Add(Me.picClient)
        Me.Controls.Add(Me.picUser)
        Me.Controls.Add(Me.picPort)
        Me.Controls.Add(Me.cmdCancel)
        Me.Controls.Add(Me.cmdTest)
        Me.Controls.Add(Me.cmdConnect)
        Me.Controls.Add(Me.txtPassword)
        Me.Controls.Add(Me.txtClient)
        Me.Controls.Add(Me.txtUser)
        Me.Controls.Add(Me.txtPORT)
        Me.Controls.Add(Me.Label4)
        Me.Controls.Add(Me.Label3)
        Me.Controls.Add(Me.Label2)
        Me.Controls.Add(Me.Label1)
        Me.MinimizeBox = False
        Me.Name = "P4ConnectionDialog"
        Me.SizeGripStyle = System.Windows.Forms.SizeGripStyle.Hide
        Me.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent
        Me.Text = "Perforce Connection Dialog"
        CType(Me.picPort, System.ComponentModel.ISupportInitialize).EndInit()
        CType(Me.picUser, System.ComponentModel.ISupportInitialize).EndInit()
        CType(Me.picClient, System.ComponentModel.ISupportInitialize).EndInit()
        CType(Me.picPassword, System.ComponentModel.ISupportInitialize).EndInit()
        Me.ResumeLayout(False)
        Me.PerformLayout()

    End Sub
    Friend WithEvents Label1 As System.Windows.Forms.Label
    Friend WithEvents Label2 As System.Windows.Forms.Label
    Friend WithEvents Label3 As System.Windows.Forms.Label
    Friend WithEvents Label4 As System.Windows.Forms.Label
    Friend WithEvents txtPORT As System.Windows.Forms.TextBox
    Friend WithEvents txtUser As System.Windows.Forms.TextBox
    Friend WithEvents txtClient As System.Windows.Forms.TextBox
    Friend WithEvents txtPassword As System.Windows.Forms.TextBox
    Friend WithEvents cmdConnect As System.Windows.Forms.Button
    Friend WithEvents picPort As System.Windows.Forms.PictureBox
    Friend WithEvents ImageList1 As System.Windows.Forms.ImageList
    Friend WithEvents ImageList2 As System.Windows.Forms.ImageList
    Friend WithEvents picUser As System.Windows.Forms.PictureBox
    Friend WithEvents picClient As System.Windows.Forms.PictureBox
    Friend WithEvents picPassword As System.Windows.Forms.PictureBox
    Friend WithEvents cmdTest As System.Windows.Forms.Button
    Friend WithEvents cmdCancel As System.Windows.Forms.Button
End Class
