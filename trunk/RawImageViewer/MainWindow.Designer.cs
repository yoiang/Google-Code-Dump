namespace RawImageViewer
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
            this.ImageFileNameLabel = new System.Windows.Forms.Label();
            this.OpenFileButton = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.HeaderSize = new System.Windows.Forms.NumericUpDown();
            this.ImageWidth = new System.Windows.Forms.NumericUpDown();
            this.ImageFormat = new System.Windows.Forms.TextBox();
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.ImageHeight = new System.Windows.Forms.Label();
            this.PixelSize = new System.Windows.Forms.Label();
            this.MouseY = new System.Windows.Forms.Label();
            this.MouseX = new System.Windows.Forms.Label();
            this.label8 = new System.Windows.Forms.Label();
            this.label9 = new System.Windows.Forms.Label();
            this.MouseGreen = new System.Windows.Forms.Label();
            this.MouseRed = new System.Windows.Forms.Label();
            this.label12 = new System.Windows.Forms.Label();
            this.label13 = new System.Windows.Forms.Label();
            this.MouseBlue = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            ( ( System.ComponentModel.ISupportInitialize )( this.HeaderSize ) ).BeginInit();
            ( ( System.ComponentModel.ISupportInitialize )( this.ImageWidth ) ).BeginInit();
            this.SuspendLayout();
            // 
            // ImageFileNameLabel
            // 
            this.ImageFileNameLabel.AutoSize = true;
            this.ImageFileNameLabel.Location = new System.Drawing.Point( 60, 14 );
            this.ImageFileNameLabel.Name = "ImageFileNameLabel";
            this.ImageFileNameLabel.Size = new System.Drawing.Size( 31, 13 );
            this.ImageFileNameLabel.TabIndex = 0;
            this.ImageFileNameLabel.Text = "none";
            // 
            // OpenFileButton
            // 
            this.OpenFileButton.Location = new System.Drawing.Point( 13, 9 );
            this.OpenFileButton.Name = "OpenFileButton";
            this.OpenFileButton.Size = new System.Drawing.Size( 41, 23 );
            this.OpenFileButton.TabIndex = 1;
            this.OpenFileButton.Text = "&File...";
            this.OpenFileButton.UseVisualStyleBackColor = true;
            this.OpenFileButton.Click += new System.EventHandler( this.OpenFileButton_Click );
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point( 19, 50 );
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size( 68, 13 );
            this.label1.TabIndex = 2;
            this.label1.Text = "Header Size:";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point( 19, 76 );
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size( 70, 13 );
            this.label2.TabIndex = 4;
            this.label2.Text = "Image Width:";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point( 19, 102 );
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size( 42, 13 );
            this.label3.TabIndex = 6;
            this.label3.Text = "Format:";
            // 
            // HeaderSize
            // 
            this.HeaderSize.Location = new System.Drawing.Point( 89, 48 );
            this.HeaderSize.Maximum = new decimal( new int[] {
            100000,
            0,
            0,
            0} );
            this.HeaderSize.Name = "HeaderSize";
            this.HeaderSize.Size = new System.Drawing.Size( 74, 20 );
            this.HeaderSize.TabIndex = 8;
            this.HeaderSize.ValueChanged += new System.EventHandler( this.HeaderSizeChanged );
            // 
            // ImageWidth
            // 
            this.ImageWidth.Location = new System.Drawing.Point( 89, 73 );
            this.ImageWidth.Maximum = new decimal( new int[] {
            100000,
            0,
            0,
            0} );
            this.ImageWidth.Minimum = new decimal( new int[] {
            1,
            0,
            0,
            0} );
            this.ImageWidth.Name = "ImageWidth";
            this.ImageWidth.Size = new System.Drawing.Size( 74, 20 );
            this.ImageWidth.TabIndex = 9;
            this.ImageWidth.Value = new decimal( new int[] {
            1,
            0,
            0,
            0} );
            this.ImageWidth.ValueChanged += new System.EventHandler( this.ImageWidthChanged );
            // 
            // ImageFormat
            // 
            this.ImageFormat.Location = new System.Drawing.Point( 89, 99 );
            this.ImageFormat.Name = "ImageFormat";
            this.ImageFormat.Size = new System.Drawing.Size( 159, 20 );
            this.ImageFormat.TabIndex = 7;
            this.ImageFormat.TextChanged += new System.EventHandler( this.ImageFormatChanged );
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point( 169, 73 );
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size( 73, 13 );
            this.label4.TabIndex = 10;
            this.label4.Text = "Image Height:";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point( 169, 50 );
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size( 55, 13 );
            this.label5.TabIndex = 11;
            this.label5.Text = "Pixel Size:";
            // 
            // ImageHeight
            // 
            this.ImageHeight.AutoSize = true;
            this.ImageHeight.Location = new System.Drawing.Point( 248, 73 );
            this.ImageHeight.Name = "ImageHeight";
            this.ImageHeight.Size = new System.Drawing.Size( 13, 13 );
            this.ImageHeight.TabIndex = 12;
            this.ImageHeight.Text = "?";
            // 
            // PixelSize
            // 
            this.PixelSize.AutoSize = true;
            this.PixelSize.Location = new System.Drawing.Point( 248, 50 );
            this.PixelSize.Name = "PixelSize";
            this.PixelSize.Size = new System.Drawing.Size( 13, 13 );
            this.PixelSize.TabIndex = 13;
            this.PixelSize.Text = "?";
            // 
            // MouseY
            // 
            this.MouseY.AutoSize = true;
            this.MouseY.Location = new System.Drawing.Point( 89, 149 );
            this.MouseY.Name = "MouseY";
            this.MouseY.Size = new System.Drawing.Size( 13, 13 );
            this.MouseY.TabIndex = 17;
            this.MouseY.Text = "?";
            // 
            // MouseX
            // 
            this.MouseX.AutoSize = true;
            this.MouseX.Location = new System.Drawing.Point( 89, 131 );
            this.MouseX.Name = "MouseX";
            this.MouseX.Size = new System.Drawing.Size( 13, 13 );
            this.MouseX.TabIndex = 16;
            this.MouseX.Text = "?";
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point( 66, 149 );
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size( 17, 13 );
            this.label8.TabIndex = 15;
            this.label8.Text = "Y:";
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point( 66, 131 );
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size( 17, 13 );
            this.label9.TabIndex = 14;
            this.label9.Text = "X:";
            // 
            // MouseGreen
            // 
            this.MouseGreen.AutoSize = true;
            this.MouseGreen.Location = new System.Drawing.Point( 178, 149 );
            this.MouseGreen.Name = "MouseGreen";
            this.MouseGreen.Size = new System.Drawing.Size( 13, 13 );
            this.MouseGreen.TabIndex = 21;
            this.MouseGreen.Text = "?";
            // 
            // MouseRed
            // 
            this.MouseRed.AutoSize = true;
            this.MouseRed.Location = new System.Drawing.Point( 178, 131 );
            this.MouseRed.Name = "MouseRed";
            this.MouseRed.Size = new System.Drawing.Size( 13, 13 );
            this.MouseRed.TabIndex = 20;
            this.MouseRed.Text = "?";
            // 
            // label12
            // 
            this.label12.AutoSize = true;
            this.label12.Location = new System.Drawing.Point( 133, 149 );
            this.label12.Name = "label12";
            this.label12.Size = new System.Drawing.Size( 39, 13 );
            this.label12.TabIndex = 19;
            this.label12.Text = "Green:";
            // 
            // label13
            // 
            this.label13.AutoSize = true;
            this.label13.Location = new System.Drawing.Point( 133, 131 );
            this.label13.Name = "label13";
            this.label13.Size = new System.Drawing.Size( 30, 13 );
            this.label13.TabIndex = 18;
            this.label13.Text = "Red:";
            // 
            // MouseBlue
            // 
            this.MouseBlue.AutoSize = true;
            this.MouseBlue.Location = new System.Drawing.Point( 178, 166 );
            this.MouseBlue.Name = "MouseBlue";
            this.MouseBlue.Size = new System.Drawing.Size( 13, 13 );
            this.MouseBlue.TabIndex = 23;
            this.MouseBlue.Text = "?";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point( 133, 166 );
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size( 31, 13 );
            this.label7.TabIndex = 22;
            this.label7.Text = "Blue:";
            // 
            // MainWindow
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF( 6F, 13F );
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size( 276, 188 );
            this.Controls.Add( this.MouseBlue );
            this.Controls.Add( this.label7 );
            this.Controls.Add( this.MouseGreen );
            this.Controls.Add( this.MouseRed );
            this.Controls.Add( this.label12 );
            this.Controls.Add( this.label13 );
            this.Controls.Add( this.MouseY );
            this.Controls.Add( this.MouseX );
            this.Controls.Add( this.label8 );
            this.Controls.Add( this.label9 );
            this.Controls.Add( this.PixelSize );
            this.Controls.Add( this.ImageHeight );
            this.Controls.Add( this.label5 );
            this.Controls.Add( this.label4 );
            this.Controls.Add( this.ImageWidth );
            this.Controls.Add( this.HeaderSize );
            this.Controls.Add( this.ImageFormat );
            this.Controls.Add( this.label3 );
            this.Controls.Add( this.label2 );
            this.Controls.Add( this.label1 );
            this.Controls.Add( this.OpenFileButton );
            this.Controls.Add( this.ImageFileNameLabel );
            this.Name = "MainWindow";
            this.Text = "Raw Image Viewer";
            this.Shown += new System.EventHandler( this.OnShown );
            ( ( System.ComponentModel.ISupportInitialize )( this.HeaderSize ) ).EndInit();
            ( ( System.ComponentModel.ISupportInitialize )( this.ImageWidth ) ).EndInit();
            this.ResumeLayout( false );
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label ImageFileNameLabel;
        private System.Windows.Forms.Button OpenFileButton;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.NumericUpDown HeaderSize;
        private System.Windows.Forms.NumericUpDown ImageWidth;
        private System.Windows.Forms.TextBox ImageFormat;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label ImageHeight;
        private System.Windows.Forms.Label PixelSize;
        private System.Windows.Forms.Label MouseY;
        private System.Windows.Forms.Label MouseX;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.Label MouseGreen;
        private System.Windows.Forms.Label MouseRed;
        private System.Windows.Forms.Label label12;
        private System.Windows.Forms.Label label13;
        private System.Windows.Forms.Label MouseBlue;
        private System.Windows.Forms.Label label7;
    }
}

