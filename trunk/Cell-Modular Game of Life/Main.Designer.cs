namespace Cell_Modular_Game_of_Life
{
    partial class Main
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
            this.PetriDishPictureBox = new System.Windows.Forms.PictureBox();
            ((System.ComponentModel.ISupportInitialize)(this.PetriDishPictureBox)).BeginInit();
            this.SuspendLayout();
            // 
            // PetriDishPictureBox
            // 
            this.PetriDishPictureBox.Dock = System.Windows.Forms.DockStyle.Fill;
            this.PetriDishPictureBox.Location = new System.Drawing.Point(0, 0);
            this.PetriDishPictureBox.Name = "PetriDishPictureBox";
            this.PetriDishPictureBox.Size = new System.Drawing.Size(389, 363);
            this.PetriDishPictureBox.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.PetriDishPictureBox.TabIndex = 0;
            this.PetriDishPictureBox.TabStop = false;
            this.PetriDishPictureBox.MouseMove += new System.Windows.Forms.MouseEventHandler(this.PetriDishMouseMove);
            this.PetriDishPictureBox.MouseDown += new System.Windows.Forms.MouseEventHandler(this.PetriDishMouseDown);
            this.PetriDishPictureBox.MouseUp += new System.Windows.Forms.MouseEventHandler(this.PetriDishMouseUp);
            // 
            // Main
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(389, 363);
            this.Controls.Add(this.PetriDishPictureBox);
            this.Name = "Main";
            this.Text = "Cell-Modular Game of Life";
            this.KeyDown += new System.Windows.Forms.KeyEventHandler(this.MainKeyDown);
            ((System.ComponentModel.ISupportInitialize)(this.PetriDishPictureBox)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.PictureBox PetriDishPictureBox;
    }
}

