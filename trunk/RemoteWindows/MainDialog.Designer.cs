namespace RemoteWindows
{
    partial class MainDialog
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
            this.tabPages = new System.Windows.Forms.TabControl();
            this.Main = new System.Windows.Forms.TabPage();
            this.Disable = new System.Windows.Forms.Button();
            this.Enable = new System.Windows.Forms.Button();
            this.Configuration = new System.Windows.Forms.TabPage();
            this.ConnectToDelete = new System.Windows.Forms.Button();
            this.ConnectToEdit = new System.Windows.Forms.Button();
            this.ConnectToAdd = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.ConnectToList = new System.Windows.Forms.ListBox();
            this.tabPages.SuspendLayout();
            this.Main.SuspendLayout();
            this.Configuration.SuspendLayout();
            this.SuspendLayout();
            // 
            // tabPages
            // 
            this.tabPages.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.tabPages.Controls.Add(this.Main);
            this.tabPages.Controls.Add(this.Configuration);
            this.tabPages.Location = new System.Drawing.Point(13, 13);
            this.tabPages.Multiline = true;
            this.tabPages.Name = "tabPages";
            this.tabPages.SelectedIndex = 0;
            this.tabPages.Size = new System.Drawing.Size(267, 247);
            this.tabPages.TabIndex = 0;
            // 
            // Main
            // 
            this.Main.Controls.Add(this.Disable);
            this.Main.Controls.Add(this.Enable);
            this.Main.Location = new System.Drawing.Point(4, 22);
            this.Main.Name = "Main";
            this.Main.Padding = new System.Windows.Forms.Padding(3);
            this.Main.Size = new System.Drawing.Size(259, 221);
            this.Main.TabIndex = 0;
            this.Main.Text = "Main";
            this.Main.UseVisualStyleBackColor = true;
            // 
            // Disable
            // 
            this.Disable.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.Disable.Location = new System.Drawing.Point(6, 78);
            this.Disable.Name = "Disable";
            this.Disable.Size = new System.Drawing.Size(247, 28);
            this.Disable.TabIndex = 2;
            this.Disable.Text = "&Disable";
            this.Disable.UseVisualStyleBackColor = true;
            this.Disable.Click += new System.EventHandler(this.Disable_Click);
            // 
            // Enable
            // 
            this.Enable.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.Enable.Location = new System.Drawing.Point(6, 35);
            this.Enable.Name = "Enable";
            this.Enable.Size = new System.Drawing.Size(247, 28);
            this.Enable.TabIndex = 0;
            this.Enable.Text = "&Enable";
            this.Enable.UseVisualStyleBackColor = true;
            this.Enable.Click += new System.EventHandler(this.Enable_Click);
            // 
            // Configuration
            // 
            this.Configuration.Controls.Add(this.ConnectToDelete);
            this.Configuration.Controls.Add(this.ConnectToEdit);
            this.Configuration.Controls.Add(this.ConnectToAdd);
            this.Configuration.Controls.Add(this.label1);
            this.Configuration.Controls.Add(this.ConnectToList);
            this.Configuration.Location = new System.Drawing.Point(4, 22);
            this.Configuration.Name = "Configuration";
            this.Configuration.Padding = new System.Windows.Forms.Padding(3);
            this.Configuration.Size = new System.Drawing.Size(259, 221);
            this.Configuration.TabIndex = 1;
            this.Configuration.Text = "Configuration";
            this.Configuration.UseVisualStyleBackColor = true;
            // 
            // ConnectToDelete
            // 
            this.ConnectToDelete.Location = new System.Drawing.Point(174, 190);
            this.ConnectToDelete.Name = "ConnectToDelete";
            this.ConnectToDelete.Size = new System.Drawing.Size(75, 24);
            this.ConnectToDelete.TabIndex = 4;
            this.ConnectToDelete.Text = "&Delete";
            this.ConnectToDelete.UseVisualStyleBackColor = true;
            // 
            // ConnectToEdit
            // 
            this.ConnectToEdit.Location = new System.Drawing.Point(92, 190);
            this.ConnectToEdit.Name = "ConnectToEdit";
            this.ConnectToEdit.Size = new System.Drawing.Size(75, 24);
            this.ConnectToEdit.TabIndex = 3;
            this.ConnectToEdit.Text = "&Edit";
            this.ConnectToEdit.UseVisualStyleBackColor = true;
            // 
            // ConnectToAdd
            // 
            this.ConnectToAdd.Location = new System.Drawing.Point(10, 190);
            this.ConnectToAdd.Name = "ConnectToAdd";
            this.ConnectToAdd.Size = new System.Drawing.Size(75, 24);
            this.ConnectToAdd.TabIndex = 2;
            this.ConnectToAdd.Text = "&Add";
            this.ConnectToAdd.UseVisualStyleBackColor = true;
            this.ConnectToAdd.Click += new System.EventHandler(this.ConnectToAdd_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(7, 7);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(66, 13);
            this.label1.TabIndex = 1;
            this.label1.Text = "Connect To:";
            // 
            // ConnectToList
            // 
            this.ConnectToList.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.ConnectToList.FormattingEnabled = true;
            this.ConnectToList.Location = new System.Drawing.Point(6, 23);
            this.ConnectToList.MultiColumn = true;
            this.ConnectToList.Name = "ConnectToList";
            this.ConnectToList.Size = new System.Drawing.Size(247, 160);
            this.ConnectToList.TabIndex = 0;
            // 
            // MainDialog
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(292, 274);
            this.Controls.Add(this.tabPages);
            this.Name = "MainDialog";
            this.Text = "Remote Windows";
            this.Load += new System.EventHandler(this.MainDialog_Load);
            this.tabPages.ResumeLayout(false);
            this.Main.ResumeLayout(false);
            this.Configuration.ResumeLayout(false);
            this.Configuration.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.TabControl tabPages;
        private System.Windows.Forms.TabPage Main;
        private System.Windows.Forms.Button Disable;
        private System.Windows.Forms.Button Enable;
        private System.Windows.Forms.TabPage Configuration;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.ListBox ConnectToList;
        private System.Windows.Forms.Button ConnectToDelete;
        private System.Windows.Forms.Button ConnectToEdit;
        private System.Windows.Forms.Button ConnectToAdd;

    }
}