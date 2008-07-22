namespace System.Windows.Forms
{
    partial class ImageWindowInfo
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose( bool disposing )
        {
            if( disposing && ( components != null ) )
            {
                components.Dispose();
            }
            base.Dispose( disposing );
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.ImageWidth = new System.Windows.Forms.Label();
            this.ImageHeight = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point( 13, 13 );
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size( 38, 13 );
            this.label1.TabIndex = 0;
            this.label1.Text = "Width:";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point( 13, 30 );
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size( 41, 13 );
            this.label2.TabIndex = 1;
            this.label2.Text = "Height:";
            // 
            // ImageWidth
            // 
            this.ImageWidth.AutoSize = true;
            this.ImageWidth.Location = new System.Drawing.Point( 57, 13 );
            this.ImageWidth.Name = "ImageWidth";
            this.ImageWidth.Size = new System.Drawing.Size( 10, 13 );
            this.ImageWidth.TabIndex = 2;
            this.ImageWidth.Text = "-";
            // 
            // ImageHeight
            // 
            this.ImageHeight.AutoSize = true;
            this.ImageHeight.Location = new System.Drawing.Point( 57, 30 );
            this.ImageHeight.Name = "ImageHeight";
            this.ImageHeight.Size = new System.Drawing.Size( 10, 13 );
            this.ImageHeight.TabIndex = 3;
            this.ImageHeight.Text = "-";
            // 
            // ImageWindowInfo
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF( 6F, 13F );
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size( 114, 55 );
            this.ControlBox = false;
            this.Controls.Add( this.ImageHeight );
            this.Controls.Add( this.ImageWidth );
            this.Controls.Add( this.label2 );
            this.Controls.Add( this.label1 );
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.SizableToolWindow;
            this.Name = "ImageWindowInfo";
            this.Text = "Image Info";
            this.ResumeLayout( false );
            this.PerformLayout();

        }

        #endregion

        private Label label1;
        private Label label2;
        protected Label ImageWidth;
        protected Label ImageHeight;
    }
}