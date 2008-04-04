using Aga.Controls.Tree;

namespace P4UserSummary
{
    partial class MainWindow
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.DepotView = new Aga.Controls.Tree.TreeViewAdv();
            this.FileNameColumn = new Aga.Controls.Tree.TreeColumn();
            this.CheckInCountColumn = new Aga.Controls.Tree.TreeColumn();
            this.OverallLinesAlteredColumn = new Aga.Controls.Tree.TreeColumn();
            this.FileNameText = new Aga.Controls.Tree.NodeControls.NodeTextBox();
            this.CheckInCountText = new Aga.Controls.Tree.NodeControls.NodeTextBox();
            this.LinesChangedText = new Aga.Controls.Tree.NodeControls.NodeTextBox();
            this.Password = new System.Windows.Forms.TextBox();
            this.label4 = new System.Windows.Forms.Label();
            this.Client = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.User = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.P4Port = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.Rebuild = new System.Windows.Forms.Button();
            this.Path = new System.Windows.Forms.TextBox();
            this.label5 = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // DepotView
            // 
            this.DepotView.AllowColumnReorder = true;
            this.DepotView.AllowDrop = true;
            this.DepotView.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.DepotView.BackColor = System.Drawing.SystemColors.Window;
            this.DepotView.Columns.Add(this.FileNameColumn);
            this.DepotView.Columns.Add(this.CheckInCountColumn);
            this.DepotView.Columns.Add(this.OverallLinesAlteredColumn);
            this.DepotView.DefaultToolTipProvider = null;
            this.DepotView.DragDropMarkColor = System.Drawing.Color.Black;
            this.DepotView.GridLineStyle = ((Aga.Controls.Tree.GridLineStyle)((Aga.Controls.Tree.GridLineStyle.Horizontal | Aga.Controls.Tree.GridLineStyle.Vertical)));
            this.DepotView.LineColor = System.Drawing.SystemColors.ControlDark;
            this.DepotView.Location = new System.Drawing.Point(0, 153);
            this.DepotView.Model = null;
            this.DepotView.Name = "DepotView";
            this.DepotView.NodeControls.Add(this.FileNameText);
            this.DepotView.NodeControls.Add(this.CheckInCountText);
            this.DepotView.NodeControls.Add(this.LinesChangedText);
            this.DepotView.SelectedNode = null;
            this.DepotView.Size = new System.Drawing.Size(431, 437);
            this.DepotView.TabIndex = 0;
            this.DepotView.UseColumns = true;
            this.DepotView.ColumnClicked += new System.EventHandler<Aga.Controls.Tree.TreeColumnEventArgs>(this.DepotView_ColumnClicked);
            // 
            // FileNameColumn
            // 
            this.FileNameColumn.Header = "File Name";
            this.FileNameColumn.SortOrder = System.Windows.Forms.SortOrder.None;
            this.FileNameColumn.TooltipText = null;
            this.FileNameColumn.Width = 260;
            // 
            // CheckInCountColumn
            // 
            this.CheckInCountColumn.Header = "Check Ins";
            this.CheckInCountColumn.SortOrder = System.Windows.Forms.SortOrder.None;
            this.CheckInCountColumn.TooltipText = null;
            this.CheckInCountColumn.Width = 75;
            // 
            // OverallLinesAlteredColumn
            // 
            this.OverallLinesAlteredColumn.Header = "Overall Lines Altered";
            this.OverallLinesAlteredColumn.SortOrder = System.Windows.Forms.SortOrder.None;
            this.OverallLinesAlteredColumn.TooltipText = null;
            this.OverallLinesAlteredColumn.Width = 85;
            // 
            // FileNameText
            // 
            this.FileNameText.DataPropertyName = "ShortFileName";
            this.FileNameText.IncrementalSearchEnabled = true;
            this.FileNameText.LeftMargin = 3;
            this.FileNameText.ParentColumn = this.FileNameColumn;
            this.FileNameText.Trimming = System.Drawing.StringTrimming.EllipsisCharacter;
            this.FileNameText.UseCompatibleTextRendering = true;
            // 
            // CheckInCountText
            // 
            this.CheckInCountText.DataPropertyName = "CheckInCountAdjusted";
            this.CheckInCountText.IncrementalSearchEnabled = true;
            this.CheckInCountText.LeftMargin = 3;
            this.CheckInCountText.ParentColumn = this.CheckInCountColumn;
            // 
            // LinesChangedText
            // 
            this.LinesChangedText.DataPropertyName = "OverallLinesAlteredAdjusted";
            this.LinesChangedText.IncrementalSearchEnabled = true;
            this.LinesChangedText.LeftMargin = 3;
            this.LinesChangedText.ParentColumn = this.OverallLinesAlteredColumn;
            // 
            // Password
            // 
            this.Password.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.Password.Location = new System.Drawing.Point(86, 90);
            this.Password.Name = "Password";
            this.Password.PasswordChar = '*';
            this.Password.Size = new System.Drawing.Size(330, 20);
            this.Password.TabIndex = 27;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(13, 94);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(56, 13);
            this.label4.TabIndex = 26;
            this.label4.Text = "Password:";
            // 
            // Client
            // 
            this.Client.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.Client.Location = new System.Drawing.Point(86, 64);
            this.Client.Name = "Client";
            this.Client.Size = new System.Drawing.Size(330, 20);
            this.Client.TabIndex = 24;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(13, 68);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(36, 13);
            this.label3.TabIndex = 23;
            this.label3.Text = "Client:";
            // 
            // User
            // 
            this.User.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.User.Location = new System.Drawing.Point(86, 38);
            this.User.Name = "User";
            this.User.Size = new System.Drawing.Size(330, 20);
            this.User.TabIndex = 21;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(13, 42);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(32, 13);
            this.label2.TabIndex = 20;
            this.label2.Text = "User:";
            // 
            // P4Port
            // 
            this.P4Port.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.P4Port.Location = new System.Drawing.Point(86, 12);
            this.P4Port.Name = "P4Port";
            this.P4Port.Size = new System.Drawing.Size(330, 20);
            this.P4Port.TabIndex = 18;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(13, 16);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(41, 13);
            this.label1.TabIndex = 17;
            this.label1.Text = "Server:";
            // 
            // Rebuild
            // 
            this.Rebuild.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.Rebuild.Location = new System.Drawing.Point(0, 596);
            this.Rebuild.Name = "Rebuild";
            this.Rebuild.Size = new System.Drawing.Size(431, 23);
            this.Rebuild.TabIndex = 28;
            this.Rebuild.Text = "&Rebuild";
            this.Rebuild.UseVisualStyleBackColor = true;
            this.Rebuild.Click += new System.EventHandler(this.Rebuild_Click);
            // 
            // Path
            // 
            this.Path.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.Path.Location = new System.Drawing.Point(86, 117);
            this.Path.Name = "Path";
            this.Path.Size = new System.Drawing.Size(330, 20);
            this.Path.TabIndex = 30;
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(13, 121);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(32, 13);
            this.label5.TabIndex = 29;
            this.label5.Text = "Path:";
            // 
            // MainWindow
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(431, 619);
            this.Controls.Add(this.Path);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.Rebuild);
            this.Controls.Add(this.Password);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.Client);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.User);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.P4Port);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.DepotView);
            this.Name = "MainWindow";
            this.Text = "P4UserSummary";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.MainWindowClosing);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private TreeViewAdv DepotView;
        private TreeColumn FileNameColumn;
        private TreeColumn CheckInCountColumn;
        private TreeColumn OverallLinesAlteredColumn;
        private Aga.Controls.Tree.NodeControls.NodeTextBox FileNameText;
        private Aga.Controls.Tree.NodeControls.NodeTextBox CheckInCountText;
        private Aga.Controls.Tree.NodeControls.NodeTextBox LinesChangedText;
        private System.Windows.Forms.TextBox Password;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.TextBox Client;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox User;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox P4Port;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button Rebuild;
        private System.Windows.Forms.TextBox Path;
        private System.Windows.Forms.Label label5;
    }
}

