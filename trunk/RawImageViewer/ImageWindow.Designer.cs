namespace RawImageViewer
{
    partial class ImageWindow
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
            this.Image = new System.Windows.Forms.PictureBox();
            ( ( System.ComponentModel.ISupportInitialize )( this.Image ) ).BeginInit();
            this.SuspendLayout();
            // 
            // Image
            // 
            this.Image.BackgroundImageLayout = System.Windows.Forms.ImageLayout.None;
            this.Image.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.Image.Cursor = System.Windows.Forms.Cursors.Cross;
            this.Image.Dock = System.Windows.Forms.DockStyle.Fill;
            this.Image.Location = new System.Drawing.Point( 0, 0 );
            this.Image.Name = "Image";
            this.Image.Size = new System.Drawing.Size( 372, 354 );
            this.Image.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.Image.TabIndex = 0;
            this.Image.TabStop = false;
            this.Image.MouseMove += new System.Windows.Forms.MouseEventHandler( this.PictureBoxOnMouseMove );
            // 
            // ImageWindow
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF( 6F, 13F );
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size( 372, 354 );
            this.ControlBox = false;
            this.Controls.Add( this.Image );
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.SizableToolWindow;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "ImageWindow";
            this.ShowIcon = false;
            this.Text = "ImageWindow";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler( this.OnClosing );
            ( ( System.ComponentModel.ISupportInitialize )( this.Image ) ).EndInit();
            this.ResumeLayout( false );

        }

        #endregion

        private System.Windows.Forms.PictureBox Image;
    }
}