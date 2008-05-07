namespace handsigns
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
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.middle = new System.Windows.Forms.PictureBox();
            this.ring = new System.Windows.Forms.PictureBox();
            this.pinky = new System.Windows.Forms.PictureBox();
            this.pictureBox5 = new System.Windows.Forms.PictureBox();
            this.index = new System.Windows.Forms.PictureBox();
            this.thumb = new System.Windows.Forms.PictureBox();
            this.pictureBox8 = new System.Windows.Forms.PictureBox();
            this.pictureBox9 = new System.Windows.Forms.PictureBox();
            this.handsign = new System.Windows.Forms.ComboBox();
            ( ( System.ComponentModel.ISupportInitialize )( this.pictureBox1 ) ).BeginInit();
            ( ( System.ComponentModel.ISupportInitialize )( this.middle ) ).BeginInit();
            ( ( System.ComponentModel.ISupportInitialize )( this.ring ) ).BeginInit();
            ( ( System.ComponentModel.ISupportInitialize )( this.pinky ) ).BeginInit();
            ( ( System.ComponentModel.ISupportInitialize )( this.pictureBox5 ) ).BeginInit();
            ( ( System.ComponentModel.ISupportInitialize )( this.index ) ).BeginInit();
            ( ( System.ComponentModel.ISupportInitialize )( this.thumb ) ).BeginInit();
            ( ( System.ComponentModel.ISupportInitialize )( this.pictureBox8 ) ).BeginInit();
            ( ( System.ComponentModel.ISupportInitialize )( this.pictureBox9 ) ).BeginInit();
            this.SuspendLayout();
            // 
            // pictureBox1
            // 
            this.pictureBox1.Image = global::handsigns.Properties.Resources.s1;
            this.pictureBox1.Location = new System.Drawing.Point( 0, 0 );
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size( 167, 30 );
            this.pictureBox1.TabIndex = 0;
            this.pictureBox1.TabStop = false;
            // 
            // middle
            // 
            this.middle.Image = global::handsigns.Properties.Resources._1_2;
            this.middle.Location = new System.Drawing.Point( 167, 0 );
            this.middle.Name = "middle";
            this.middle.Size = new System.Drawing.Size( 59, 219 );
            this.middle.TabIndex = 1;
            this.middle.TabStop = false;
            this.middle.Click += new System.EventHandler( this.middle_Click );
            // 
            // ring
            // 
            this.ring.Image = global::handsigns.Properties.Resources._1_3;
            this.ring.Location = new System.Drawing.Point( 226, 0 );
            this.ring.Name = "ring";
            this.ring.Size = new System.Drawing.Size( 57, 219 );
            this.ring.TabIndex = 2;
            this.ring.TabStop = false;
            this.ring.Click += new System.EventHandler( this.ring_Click );
            // 
            // pinky
            // 
            this.pinky.Image = global::handsigns.Properties.Resources._0_4;
            this.pinky.Location = new System.Drawing.Point( 283, 0 );
            this.pinky.Name = "pinky";
            this.pinky.Size = new System.Drawing.Size( 81, 219 );
            this.pinky.TabIndex = 3;
            this.pinky.TabStop = false;
            this.pinky.Click += new System.EventHandler( this.pinky_Click );
            // 
            // pictureBox5
            // 
            this.pictureBox5.Image = global::handsigns.Properties.Resources.s2;
            this.pictureBox5.Location = new System.Drawing.Point( 0, 30 );
            this.pictureBox5.Name = "pictureBox5";
            this.pictureBox5.Size = new System.Drawing.Size( 98, 189 );
            this.pictureBox5.TabIndex = 4;
            this.pictureBox5.TabStop = false;
            // 
            // index
            // 
            this.index.Image = global::handsigns.Properties.Resources._0_1;
            this.index.Location = new System.Drawing.Point( 98, 30 );
            this.index.Name = "index";
            this.index.Size = new System.Drawing.Size( 69, 189 );
            this.index.TabIndex = 5;
            this.index.TabStop = false;
            this.index.Click += new System.EventHandler( this.index_Click );
            // 
            // thumb
            // 
            this.thumb.Image = global::handsigns.Properties.Resources._0_0;
            this.thumb.Location = new System.Drawing.Point( 0, 219 );
            this.thumb.Name = "thumb";
            this.thumb.Size = new System.Drawing.Size( 121, 166 );
            this.thumb.TabIndex = 6;
            this.thumb.TabStop = false;
            this.thumb.Click += new System.EventHandler( this.thumb_Click );
            // 
            // pictureBox8
            // 
            this.pictureBox8.Image = global::handsigns.Properties.Resources.palm2;
            this.pictureBox8.Location = new System.Drawing.Point( 121, 219 );
            this.pictureBox8.Name = "pictureBox8";
            this.pictureBox8.Size = new System.Drawing.Size( 243, 222 );
            this.pictureBox8.TabIndex = 7;
            this.pictureBox8.TabStop = false;
            // 
            // pictureBox9
            // 
            this.pictureBox9.Image = global::handsigns.Properties.Resources.palm1;
            this.pictureBox9.Location = new System.Drawing.Point( 0, 385 );
            this.pictureBox9.Name = "pictureBox9";
            this.pictureBox9.Size = new System.Drawing.Size( 121, 56 );
            this.pictureBox9.TabIndex = 8;
            this.pictureBox9.TabStop = false;
            // 
            // handsign
            // 
            this.handsign.FormattingEnabled = true;
            this.handsign.Location = new System.Drawing.Point( 0, 441 );
            this.handsign.Name = "handsign";
            this.handsign.Size = new System.Drawing.Size( 364, 21 );
            this.handsign.TabIndex = 9;
            this.handsign.SelectedIndexChanged += new System.EventHandler( this.handsign_SelectedIndexChanged );
            // 
            // MainWindow
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF( 6F, 13F );
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size( 364, 462 );
            this.Controls.Add( this.handsign );
            this.Controls.Add( this.pictureBox9 );
            this.Controls.Add( this.pictureBox8 );
            this.Controls.Add( this.thumb );
            this.Controls.Add( this.index );
            this.Controls.Add( this.pictureBox5 );
            this.Controls.Add( this.pinky );
            this.Controls.Add( this.ring );
            this.Controls.Add( this.middle );
            this.Controls.Add( this.pictureBox1 );
            this.Name = "MainWindow";
            this.Text = "handsigns";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler( this.OnClosing );
            ( ( System.ComponentModel.ISupportInitialize )( this.pictureBox1 ) ).EndInit();
            ( ( System.ComponentModel.ISupportInitialize )( this.middle ) ).EndInit();
            ( ( System.ComponentModel.ISupportInitialize )( this.ring ) ).EndInit();
            ( ( System.ComponentModel.ISupportInitialize )( this.pinky ) ).EndInit();
            ( ( System.ComponentModel.ISupportInitialize )( this.pictureBox5 ) ).EndInit();
            ( ( System.ComponentModel.ISupportInitialize )( this.index ) ).EndInit();
            ( ( System.ComponentModel.ISupportInitialize )( this.thumb ) ).EndInit();
            ( ( System.ComponentModel.ISupportInitialize )( this.pictureBox8 ) ).EndInit();
            ( ( System.ComponentModel.ISupportInitialize )( this.pictureBox9 ) ).EndInit();
            this.ResumeLayout( false );

        }

        #endregion

        private System.Windows.Forms.PictureBox pictureBox1;
        private System.Windows.Forms.PictureBox middle;
        private System.Windows.Forms.PictureBox ring;
        private System.Windows.Forms.PictureBox pinky;
        private System.Windows.Forms.PictureBox pictureBox5;
        private System.Windows.Forms.PictureBox index;
        private System.Windows.Forms.PictureBox thumb;
        private System.Windows.Forms.PictureBox pictureBox8;
        private System.Windows.Forms.PictureBox pictureBox9;
        private System.Windows.Forms.ComboBox handsign;
    }
}

