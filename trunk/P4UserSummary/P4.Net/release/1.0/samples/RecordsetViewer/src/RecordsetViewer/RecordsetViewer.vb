'/*
' * P4.Net *
'Copyright (c) 2006 Shawn Hladky
'
'Permission is hereby granted, free of charge, to any person obtaining a copy of this software 
'and associated documentation files (the "Software"), to deal in the Software without 
'restriction, including without limitation the rights to use, copy, modify, merge, publish, 
'distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the 
'Software is furnished to do so, subject to the following conditions:
'
'The above copyright notice and this permission notice shall be included in all copies or 
'substantial portions of the Software.
'
'THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING 
'BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND 
'NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, 
'DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
'OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. 
' */


Public Class RecordsetViewer

    Private _recordset As P4API.P4RecordSet
    Private _recordIndex As Integer
    Private _p4 As P4API.P4Connection

    Private Sub RecordsetViewer_Load(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles MyBase.Load
        _p4 = P4ConnectionDialog.Show()
        If _p4 Is Nothing Then End
        SplitContainer2.Visible = False
        picMessage.Image = ImageList1.Images(1)
        picWarning.Image = ImageList1.Images(2)
        picError.Image = ImageList1.Images(0)
    End Sub

    Private Sub btnRun_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles btnRun.Click
        RunCommand()
    End Sub

    Private Sub RunCommand()

        Dim args As New List(Of String)
        Dim s As String

        If txtCommand.Text = "" Then
            MessageBox.Show("Must enter a command!")
            Exit Sub
        End If

        Me.Enabled = False
        ' save the old cursor
        Dim oldCursor As Cursor
        oldCursor = Me.Cursor

        _p4.ExceptionLevel = P4API.P4ExceptionLevels.NoExceptionOnErrors
        _p4.Connect()

        Dim tokens As TokenCollection
        tokens = Tokenizer.Tokenize(txtArguments.Text)
        For Each s In tokens
            args.Add(s)
        Next

        ' change the cursor to the one you want
        Me.Cursor = Cursors.WaitCursor

        _recordset = _p4.Run(txtCommand.Text, args.ToArray())
        _recordIndex = 0

        PaintStrings()
        PaintRecords()

        If (_recordset.Records.Length = 0) Then
            'default to the Messages tab
            Me.TabControl1.SelectTab(1)
        Else
            'default to the records tab
            Me.TabControl1.SelectTab(0)
        End If

        _p4.Disconnect()

        ' restore the old cursor or else you may never get it back
        Me.Cursor = oldCursor
        Me.Enabled = True

    End Sub

    Private Sub PaintArrayFields(ByVal record As P4API.P4Record)
        If record.ArrayFields.Count = 0 Then
            SplitContainer2.Panel2Collapsed = True
            Exit Sub
        End If
        SplitContainer2.Panel2Collapsed = False
        gridArrayFields.Columns.Clear()
        gridArrayFields.Columns.Add("index", "Index")

        Dim key As String
        For Each key In record.ArrayFields.Keys
            If Not gridArrayFields.Columns.Contains(key) Then
                gridArrayFields.Columns.Add(key, key)
            End If
        Next
        For Each key In record.ArrayFields.Keys
            Dim s As String()
            Dim i As Integer
            s = record.ArrayFields(key)
            For i = 0 To s.Length - 1
                While gridArrayFields.RowCount <= i
                    gridArrayFields.Rows.Add()
                End While
                gridArrayFields.Rows(i).Cells(key).Value = record.ArrayFields(key)(i)
                gridArrayFields.Rows(i).Cells("index").Value = i
            Next

        Next
    End Sub

    Private Sub PaintRecords()

        If _recordset.Records.Length = 0 Then
            Exit Sub
        End If

        gridFields.Rows.Clear()
        gridArrayFields.Rows.Clear()

        gridFields.Columns.Clear()
        gridArrayFields.Columns.Clear()
        SplitContainer2.Panel2Collapsed = True
        SplitContainer2.Visible = True

        'add a column to store the record number
        gridFields.Columns.Add("record", "Record")

        ' spin all the records and build columns for every key
        Dim key As String
        Dim record As P4API.P4Record
        For Each record In _recordset
            For Each key In record.Fields.Keys
                If Not gridFields.Columns.Contains(key) Then
                    gridFields.Columns.Add(key, key)
                End If
            Next
            For Each key In record.ArrayFields.Keys
                If Not gridArrayFields.Columns.Contains(key) Then
                    gridArrayFields.Columns.Add(key, key)
                End If
            Next
        Next

        For Each record In _recordset
            Dim rowIndex As Integer
            rowIndex = gridFields.Rows.Add()
            gridFields.Rows(rowIndex).Cells("record").Value = rowIndex
            For Each key In record.Fields.Keys
                gridFields.Rows(rowIndex).Cells(key).Value = record.Fields(key)
            Next
        Next

        PaintArrayFields(_recordset(0))

    End Sub

    Private Sub PaintStrings()
        Dim s As String
        txtMessages.Text = ""
        For Each s In _recordset.Messages
            txtMessages.Text = txtMessages.Text & s & vbCrLf
        Next
        If _recordset.Messages.Length = 0 Then
            picMessage.Visible = False
        Else
            picMessage.Visible = True
        End If

        txtWarnings.Text = ""
        For Each s In _recordset.Warnings
            txtWarnings.Text = txtWarnings.Text & s & vbCrLf
        Next
        If _recordset.Warnings.Length = 0 Then
            picWarning.Visible = False
        Else
            picWarning.Visible = True
        End If

        txtErrors.Text = ""
        For Each s In _recordset.Errors
            txtErrors.Text = txtErrors.Text & s & vbCrLf
        Next
        If _recordset.Errors.Length = 0 Then
            picError.Visible = False
        Else
            picError.Visible = True
        End If

    End Sub

    Private Sub gridFields_CellClick(ByVal sender As System.Object, ByVal e As System.Windows.Forms.DataGridViewCellEventArgs) Handles gridFields.CellClick
        If e.RowIndex >= 0 Then
            Dim recordIndex As Integer
            Dim record As P4API.P4Record
            recordIndex = gridFields.Rows(e.RowIndex).Cells("record").Value
            record = _recordset(recordIndex)
            PaintArrayFields(record)
        End If
    End Sub

    Private Sub txtCommand_TextChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles txtCommand.TextChanged

    End Sub

    Private Sub picError_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles picError.Click

    End Sub
End Class
