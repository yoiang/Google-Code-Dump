<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> _
Partial Class RecordsetViewer
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
        Dim resources As System.ComponentModel.ComponentResourceManager = New System.ComponentModel.ComponentResourceManager(GetType(RecordsetViewer))
        Me.txtCommand = New System.Windows.Forms.TextBox
        Me.Label1 = New System.Windows.Forms.Label
        Me.txtArguments = New System.Windows.Forms.TextBox
        Me.Label2 = New System.Windows.Forms.Label
        Me.TabControl1 = New System.Windows.Forms.TabControl
        Me.TabRecords = New System.Windows.Forms.TabPage
        Me.SplitContainer2 = New System.Windows.Forms.SplitContainer
        Me.gridFields = New System.Windows.Forms.DataGridView
        Me.Var = New System.Windows.Forms.DataGridViewTextBoxColumn
        Me.Value = New System.Windows.Forms.DataGridViewTextBoxColumn
        Me.gridArrayFields = New System.Windows.Forms.DataGridView
        Me.DataGridViewTextBoxColumn1 = New System.Windows.Forms.DataGridViewTextBoxColumn
        Me.Index = New System.Windows.Forms.DataGridViewTextBoxColumn
        Me.DataGridViewTextBoxColumn2 = New System.Windows.Forms.DataGridViewTextBoxColumn
        Me.TabProperties = New System.Windows.Forms.TabPage
        Me.txtErrors = New System.Windows.Forms.TextBox
        Me.Label5 = New System.Windows.Forms.Label
        Me.txtWarnings = New System.Windows.Forms.TextBox
        Me.Label4 = New System.Windows.Forms.Label
        Me.txtMessages = New System.Windows.Forms.TextBox
        Me.Label3 = New System.Windows.Forms.Label
        Me.btnRun = New System.Windows.Forms.Button
        Me.picMessage = New System.Windows.Forms.PictureBox
        Me.picWarning = New System.Windows.Forms.PictureBox
        Me.picError = New System.Windows.Forms.PictureBox
        Me.ImageList1 = New System.Windows.Forms.ImageList(Me.components)
        Me.TabControl1.SuspendLayout()
        Me.TabRecords.SuspendLayout()
        Me.SplitContainer2.Panel1.SuspendLayout()
        Me.SplitContainer2.Panel2.SuspendLayout()
        Me.SplitContainer2.SuspendLayout()
        CType(Me.gridFields, System.ComponentModel.ISupportInitialize).BeginInit()
        CType(Me.gridArrayFields, System.ComponentModel.ISupportInitialize).BeginInit()
        Me.TabProperties.SuspendLayout()
        CType(Me.picMessage, System.ComponentModel.ISupportInitialize).BeginInit()
        CType(Me.picWarning, System.ComponentModel.ISupportInitialize).BeginInit()
        CType(Me.picError, System.ComponentModel.ISupportInitialize).BeginInit()
        Me.SuspendLayout()
        '
        'txtCommand
        '
        Me.txtCommand.Location = New System.Drawing.Point(91, 12)
        Me.txtCommand.Name = "txtCommand"
        Me.txtCommand.Size = New System.Drawing.Size(151, 20)
        Me.txtCommand.TabIndex = 0
        '
        'Label1
        '
        Me.Label1.AutoSize = True
        Me.Label1.Font = New System.Drawing.Font("Microsoft Sans Serif", 8.25!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Label1.Location = New System.Drawing.Point(9, 15)
        Me.Label1.Name = "Label1"
        Me.Label1.Size = New System.Drawing.Size(65, 13)
        Me.Label1.TabIndex = 1
        Me.Label1.Text = "Command:"
        '
        'txtArguments
        '
        Me.txtArguments.Anchor = CType(((System.Windows.Forms.AnchorStyles.Top Or System.Windows.Forms.AnchorStyles.Left) _
                    Or System.Windows.Forms.AnchorStyles.Right), System.Windows.Forms.AnchorStyles)
        Me.txtArguments.Location = New System.Drawing.Point(91, 41)
        Me.txtArguments.Multiline = True
        Me.txtArguments.Name = "txtArguments"
        Me.txtArguments.ScrollBars = System.Windows.Forms.ScrollBars.Both
        Me.txtArguments.Size = New System.Drawing.Size(385, 40)
        Me.txtArguments.TabIndex = 3
        '
        'Label2
        '
        Me.Label2.AutoSize = True
        Me.Label2.Font = New System.Drawing.Font("Microsoft Sans Serif", 8.25!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Label2.Location = New System.Drawing.Point(9, 41)
        Me.Label2.Name = "Label2"
        Me.Label2.Size = New System.Drawing.Size(70, 13)
        Me.Label2.TabIndex = 4
        Me.Label2.Text = "Arguments:"
        '
        'TabControl1
        '
        Me.TabControl1.Anchor = CType((((System.Windows.Forms.AnchorStyles.Top Or System.Windows.Forms.AnchorStyles.Bottom) _
                    Or System.Windows.Forms.AnchorStyles.Left) _
                    Or System.Windows.Forms.AnchorStyles.Right), System.Windows.Forms.AnchorStyles)
        Me.TabControl1.Controls.Add(Me.TabRecords)
        Me.TabControl1.Controls.Add(Me.TabProperties)
        Me.TabControl1.Location = New System.Drawing.Point(7, 98)
        Me.TabControl1.Name = "TabControl1"
        Me.TabControl1.SelectedIndex = 0
        Me.TabControl1.Size = New System.Drawing.Size(469, 454)
        Me.TabControl1.TabIndex = 5
        '
        'TabRecords
        '
        Me.TabRecords.Controls.Add(Me.SplitContainer2)
        Me.TabRecords.Location = New System.Drawing.Point(4, 22)
        Me.TabRecords.Name = "TabRecords"
        Me.TabRecords.Padding = New System.Windows.Forms.Padding(3)
        Me.TabRecords.Size = New System.Drawing.Size(461, 428)
        Me.TabRecords.TabIndex = 2
        Me.TabRecords.Text = "Records"
        '
        'SplitContainer2
        '
        Me.SplitContainer2.Dock = System.Windows.Forms.DockStyle.Fill
        Me.SplitContainer2.Location = New System.Drawing.Point(3, 3)
        Me.SplitContainer2.Name = "SplitContainer2"
        Me.SplitContainer2.Orientation = System.Windows.Forms.Orientation.Horizontal
        '
        'SplitContainer2.Panel1
        '
        Me.SplitContainer2.Panel1.Controls.Add(Me.gridFields)
        '
        'SplitContainer2.Panel2
        '
        Me.SplitContainer2.Panel2.Controls.Add(Me.gridArrayFields)
        Me.SplitContainer2.Size = New System.Drawing.Size(455, 422)
        Me.SplitContainer2.SplitterDistance = 285
        Me.SplitContainer2.TabIndex = 10
        '
        'gridFields
        '
        Me.gridFields.AllowUserToAddRows = False
        Me.gridFields.AllowUserToDeleteRows = False
        Me.gridFields.AllowUserToOrderColumns = True
        Me.gridFields.AllowUserToResizeRows = False
        Me.gridFields.AutoSizeColumnsMode = System.Windows.Forms.DataGridViewAutoSizeColumnsMode.AllCells
        Me.gridFields.ClipboardCopyMode = System.Windows.Forms.DataGridViewClipboardCopyMode.Disable
        Me.gridFields.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize
        Me.gridFields.Columns.AddRange(New System.Windows.Forms.DataGridViewColumn() {Me.Var, Me.Value})
        Me.gridFields.Dock = System.Windows.Forms.DockStyle.Fill
        Me.gridFields.Location = New System.Drawing.Point(0, 0)
        Me.gridFields.Name = "gridFields"
        Me.gridFields.ReadOnly = True
        Me.gridFields.SelectionMode = System.Windows.Forms.DataGridViewSelectionMode.FullRowSelect
        Me.gridFields.ShowEditingIcon = False
        Me.gridFields.Size = New System.Drawing.Size(455, 285)
        Me.gridFields.TabIndex = 12
        '
        'Var
        '
        Me.Var.HeaderText = "Var"
        Me.Var.Name = "Var"
        Me.Var.ReadOnly = True
        Me.Var.Width = 48
        '
        'Value
        '
        Me.Value.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.Fill
        Me.Value.HeaderText = "Value"
        Me.Value.MinimumWidth = 30
        Me.Value.Name = "Value"
        Me.Value.ReadOnly = True
        '
        'gridArrayFields
        '
        Me.gridArrayFields.AllowUserToAddRows = False
        Me.gridArrayFields.AllowUserToDeleteRows = False
        Me.gridArrayFields.AllowUserToOrderColumns = True
        Me.gridArrayFields.AllowUserToResizeRows = False
        Me.gridArrayFields.AutoSizeColumnsMode = System.Windows.Forms.DataGridViewAutoSizeColumnsMode.AllCells
        Me.gridArrayFields.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize
        Me.gridArrayFields.Columns.AddRange(New System.Windows.Forms.DataGridViewColumn() {Me.DataGridViewTextBoxColumn1, Me.Index, Me.DataGridViewTextBoxColumn2})
        Me.gridArrayFields.Dock = System.Windows.Forms.DockStyle.Fill
        Me.gridArrayFields.Location = New System.Drawing.Point(0, 0)
        Me.gridArrayFields.Name = "gridArrayFields"
        Me.gridArrayFields.SelectionMode = System.Windows.Forms.DataGridViewSelectionMode.FullRowSelect
        Me.gridArrayFields.ShowEditingIcon = False
        Me.gridArrayFields.Size = New System.Drawing.Size(455, 133)
        Me.gridArrayFields.TabIndex = 10
        '
        'DataGridViewTextBoxColumn1
        '
        Me.DataGridViewTextBoxColumn1.HeaderText = "Var"
        Me.DataGridViewTextBoxColumn1.Name = "DataGridViewTextBoxColumn1"
        Me.DataGridViewTextBoxColumn1.Width = 48
        '
        'Index
        '
        Me.Index.HeaderText = "Index"
        Me.Index.Name = "Index"
        Me.Index.Width = 58
        '
        'DataGridViewTextBoxColumn2
        '
        Me.DataGridViewTextBoxColumn2.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.Fill
        Me.DataGridViewTextBoxColumn2.HeaderText = "Value"
        Me.DataGridViewTextBoxColumn2.MinimumWidth = 30
        Me.DataGridViewTextBoxColumn2.Name = "DataGridViewTextBoxColumn2"
        '
        'TabProperties
        '
        Me.TabProperties.Controls.Add(Me.txtErrors)
        Me.TabProperties.Controls.Add(Me.Label5)
        Me.TabProperties.Controls.Add(Me.txtWarnings)
        Me.TabProperties.Controls.Add(Me.Label4)
        Me.TabProperties.Controls.Add(Me.txtMessages)
        Me.TabProperties.Controls.Add(Me.Label3)
        Me.TabProperties.Location = New System.Drawing.Point(4, 22)
        Me.TabProperties.Name = "TabProperties"
        Me.TabProperties.Padding = New System.Windows.Forms.Padding(3)
        Me.TabProperties.Size = New System.Drawing.Size(489, 414)
        Me.TabProperties.TabIndex = 0
        Me.TabProperties.Text = "Properties"
        '
        'txtErrors
        '
        Me.txtErrors.Anchor = CType(((System.Windows.Forms.AnchorStyles.Top Or System.Windows.Forms.AnchorStyles.Left) _
                    Or System.Windows.Forms.AnchorStyles.Right), System.Windows.Forms.AnchorStyles)
        Me.txtErrors.Location = New System.Drawing.Point(9, 298)
        Me.txtErrors.Multiline = True
        Me.txtErrors.Name = "txtErrors"
        Me.txtErrors.ReadOnly = True
        Me.txtErrors.Size = New System.Drawing.Size(484, 106)
        Me.txtErrors.TabIndex = 5
        '
        'Label5
        '
        Me.Label5.AutoSize = True
        Me.Label5.Location = New System.Drawing.Point(6, 281)
        Me.Label5.Name = "Label5"
        Me.Label5.Size = New System.Drawing.Size(34, 13)
        Me.Label5.TabIndex = 4
        Me.Label5.Text = "Errors"
        '
        'txtWarnings
        '
        Me.txtWarnings.Anchor = CType(((System.Windows.Forms.AnchorStyles.Top Or System.Windows.Forms.AnchorStyles.Left) _
                    Or System.Windows.Forms.AnchorStyles.Right), System.Windows.Forms.AnchorStyles)
        Me.txtWarnings.Location = New System.Drawing.Point(9, 160)
        Me.txtWarnings.Multiline = True
        Me.txtWarnings.Name = "txtWarnings"
        Me.txtWarnings.ReadOnly = True
        Me.txtWarnings.Size = New System.Drawing.Size(484, 106)
        Me.txtWarnings.TabIndex = 3
        '
        'Label4
        '
        Me.Label4.AutoSize = True
        Me.Label4.Location = New System.Drawing.Point(6, 143)
        Me.Label4.Name = "Label4"
        Me.Label4.Size = New System.Drawing.Size(52, 13)
        Me.Label4.TabIndex = 2
        Me.Label4.Text = "Warnings"
        '
        'txtMessages
        '
        Me.txtMessages.Anchor = CType(((System.Windows.Forms.AnchorStyles.Top Or System.Windows.Forms.AnchorStyles.Left) _
                    Or System.Windows.Forms.AnchorStyles.Right), System.Windows.Forms.AnchorStyles)
        Me.txtMessages.Location = New System.Drawing.Point(9, 24)
        Me.txtMessages.Multiline = True
        Me.txtMessages.Name = "txtMessages"
        Me.txtMessages.ReadOnly = True
        Me.txtMessages.Size = New System.Drawing.Size(484, 106)
        Me.txtMessages.TabIndex = 1
        '
        'Label3
        '
        Me.Label3.AutoSize = True
        Me.Label3.Location = New System.Drawing.Point(6, 7)
        Me.Label3.Name = "Label3"
        Me.Label3.Size = New System.Drawing.Size(55, 13)
        Me.Label3.TabIndex = 0
        Me.Label3.Text = "Messages"
        '
        'btnRun
        '
        Me.btnRun.Anchor = CType((System.Windows.Forms.AnchorStyles.Top Or System.Windows.Forms.AnchorStyles.Right), System.Windows.Forms.AnchorStyles)
        Me.btnRun.Location = New System.Drawing.Point(397, 10)
        Me.btnRun.Name = "btnRun"
        Me.btnRun.Size = New System.Drawing.Size(79, 23)
        Me.btnRun.TabIndex = 6
        Me.btnRun.Text = "Run"
        '
        'picMessage
        '
        Me.picMessage.Anchor = CType((System.Windows.Forms.AnchorStyles.Top Or System.Windows.Forms.AnchorStyles.Right), System.Windows.Forms.AnchorStyles)
        Me.picMessage.Image = CType(resources.GetObject("picMessage.Image"), System.Drawing.Image)
        Me.picMessage.Location = New System.Drawing.Point(376, 84)
        Me.picMessage.Name = "picMessage"
        Me.picMessage.Size = New System.Drawing.Size(32, 32)
        Me.picMessage.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage
        Me.picMessage.TabIndex = 9
        Me.picMessage.TabStop = False
        Me.picMessage.Visible = False
        '
        'picWarning
        '
        Me.picWarning.Anchor = CType((System.Windows.Forms.AnchorStyles.Top Or System.Windows.Forms.AnchorStyles.Right), System.Windows.Forms.AnchorStyles)
        Me.picWarning.Image = CType(resources.GetObject("picWarning.Image"), System.Drawing.Image)
        Me.picWarning.Location = New System.Drawing.Point(409, 84)
        Me.picWarning.Name = "picWarning"
        Me.picWarning.Size = New System.Drawing.Size(32, 32)
        Me.picWarning.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage
        Me.picWarning.TabIndex = 9
        Me.picWarning.TabStop = False
        Me.picWarning.Visible = False
        '
        'picError
        '
        Me.picError.Anchor = CType((System.Windows.Forms.AnchorStyles.Top Or System.Windows.Forms.AnchorStyles.Right), System.Windows.Forms.AnchorStyles)
        Me.picError.Image = CType(resources.GetObject("picError.Image"), System.Drawing.Image)
        Me.picError.Location = New System.Drawing.Point(442, 84)
        Me.picError.Name = "picError"
        Me.picError.Size = New System.Drawing.Size(32, 32)
        Me.picError.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage
        Me.picError.TabIndex = 10
        Me.picError.TabStop = False
        Me.picError.Visible = False
        '
        'ImageList1
        '
        Me.ImageList1.ImageStream = CType(resources.GetObject("ImageList1.ImageStream"), System.Windows.Forms.ImageListStreamer)
        Me.ImageList1.TransparentColor = System.Drawing.Color.Transparent
        Me.ImageList1.Images.SetKeyName(0, "error.ico")
        Me.ImageList1.Images.SetKeyName(1, "Info.ico")
        Me.ImageList1.Images.SetKeyName(2, "Warning_.ico")
        '
        'RecordsetViewer
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(6.0!, 13.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.ClientSize = New System.Drawing.Size(484, 564)
        Me.Controls.Add(Me.picError)
        Me.Controls.Add(Me.picWarning)
        Me.Controls.Add(Me.picMessage)
        Me.Controls.Add(Me.btnRun)
        Me.Controls.Add(Me.TabControl1)
        Me.Controls.Add(Me.Label2)
        Me.Controls.Add(Me.txtArguments)
        Me.Controls.Add(Me.Label1)
        Me.Controls.Add(Me.txtCommand)
        Me.MinimumSize = New System.Drawing.Size(500, 600)
        Me.Name = "RecordsetViewer"
        Me.Text = "P4 Recordset Viewer"
        Me.TabControl1.ResumeLayout(False)
        Me.TabRecords.ResumeLayout(False)
        Me.SplitContainer2.Panel1.ResumeLayout(False)
        Me.SplitContainer2.Panel2.ResumeLayout(False)
        Me.SplitContainer2.ResumeLayout(False)
        CType(Me.gridFields, System.ComponentModel.ISupportInitialize).EndInit()
        CType(Me.gridArrayFields, System.ComponentModel.ISupportInitialize).EndInit()
        Me.TabProperties.ResumeLayout(False)
        Me.TabProperties.PerformLayout()
        CType(Me.picMessage, System.ComponentModel.ISupportInitialize).EndInit()
        CType(Me.picWarning, System.ComponentModel.ISupportInitialize).EndInit()
        CType(Me.picError, System.ComponentModel.ISupportInitialize).EndInit()
        Me.ResumeLayout(False)
        Me.PerformLayout()

    End Sub
    Friend WithEvents txtCommand As System.Windows.Forms.TextBox
    Friend WithEvents Label1 As System.Windows.Forms.Label
    Friend WithEvents txtArguments As System.Windows.Forms.TextBox
    Friend WithEvents Label2 As System.Windows.Forms.Label
    Friend WithEvents TabControl1 As System.Windows.Forms.TabControl
    Friend WithEvents TabProperties As System.Windows.Forms.TabPage
    Friend WithEvents Label3 As System.Windows.Forms.Label
    Friend WithEvents txtMessages As System.Windows.Forms.TextBox
    Friend WithEvents txtErrors As System.Windows.Forms.TextBox
    Friend WithEvents Label5 As System.Windows.Forms.Label
    Friend WithEvents txtWarnings As System.Windows.Forms.TextBox
    Friend WithEvents Label4 As System.Windows.Forms.Label
    Friend WithEvents btnRun As System.Windows.Forms.Button
    Friend WithEvents TabRecords As System.Windows.Forms.TabPage
    Friend WithEvents SplitContainer2 As System.Windows.Forms.SplitContainer
    Friend WithEvents gridFields As System.Windows.Forms.DataGridView
    Friend WithEvents Var As System.Windows.Forms.DataGridViewTextBoxColumn
    Friend WithEvents Value As System.Windows.Forms.DataGridViewTextBoxColumn
    Friend WithEvents gridArrayFields As System.Windows.Forms.DataGridView
    Friend WithEvents DataGridViewTextBoxColumn1 As System.Windows.Forms.DataGridViewTextBoxColumn
    Friend WithEvents Index As System.Windows.Forms.DataGridViewTextBoxColumn
    Friend WithEvents DataGridViewTextBoxColumn2 As System.Windows.Forms.DataGridViewTextBoxColumn
    Friend WithEvents picMessage As System.Windows.Forms.PictureBox
    Friend WithEvents picWarning As System.Windows.Forms.PictureBox
    Friend WithEvents picError As System.Windows.Forms.PictureBox
    Friend WithEvents ImageList1 As System.Windows.Forms.ImageList

End Class
