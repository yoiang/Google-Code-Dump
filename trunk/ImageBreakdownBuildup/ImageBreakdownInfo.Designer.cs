using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace ImageBreakdownBuildup
{
    partial class ImageBreakdownInfo
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
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.GridSpacingHeight = new System.Windows.Forms.NumericUpDown();
            this.GridSpacingWidth = new System.Windows.Forms.NumericUpDown();
            this.GridHeight = new System.Windows.Forms.NumericUpDown();
            this.GridWidth = new System.Windows.Forms.NumericUpDown();
            this.label5 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.BuiltUp = new System.Windows.Forms.RadioButton();
            this.Original = new System.Windows.Forms.RadioButton();
            this.AverageColor = new System.Windows.Forms.RadioButton();
            this.label7 = new System.Windows.Forms.Label();
            this.Tolerance = new System.Windows.Forms.NumericUpDown();
            this.Save = new System.Windows.Forms.Button();
            this.groupBox1.SuspendLayout();
            ( ( System.ComponentModel.ISupportInitialize )( this.GridSpacingHeight ) ).BeginInit();
            ( ( System.ComponentModel.ISupportInitialize )( this.GridSpacingWidth ) ).BeginInit();
            ( ( System.ComponentModel.ISupportInitialize )( this.GridHeight ) ).BeginInit();
            ( ( System.ComponentModel.ISupportInitialize )( this.GridWidth ) ).BeginInit();
            ( ( System.ComponentModel.ISupportInitialize )( this.Tolerance ) ).BeginInit();
            this.SuspendLayout();
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add( this.GridSpacingHeight );
            this.groupBox1.Controls.Add( this.GridSpacingWidth );
            this.groupBox1.Controls.Add( this.GridHeight );
            this.groupBox1.Controls.Add( this.GridWidth );
            this.groupBox1.Controls.Add( this.label5 );
            this.groupBox1.Controls.Add( this.label6 );
            this.groupBox1.Controls.Add( this.label4 );
            this.groupBox1.Controls.Add( this.label3 );
            this.groupBox1.Location = new System.Drawing.Point( 131, 7 );
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size( 146, 126 );
            this.groupBox1.TabIndex = 6;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Grid";
            // 
            // GridSpacingHeight
            // 
            this.GridSpacingHeight.Location = new System.Drawing.Point( 95, 89 );
            this.GridSpacingHeight.Maximum = new decimal( new int[] {
            99999,
            0,
            0,
            0} );
            this.GridSpacingHeight.Name = "GridSpacingHeight";
            this.GridSpacingHeight.Size = new System.Drawing.Size( 43, 20 );
            this.GridSpacingHeight.TabIndex = 19;
            this.GridSpacingHeight.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            // 
            // GridSpacingWidth
            // 
            this.GridSpacingWidth.Location = new System.Drawing.Point( 95, 69 );
            this.GridSpacingWidth.Maximum = new decimal( new int[] {
            99999,
            0,
            0,
            0} );
            this.GridSpacingWidth.Name = "GridSpacingWidth";
            this.GridSpacingWidth.Size = new System.Drawing.Size( 43, 20 );
            this.GridSpacingWidth.TabIndex = 17;
            this.GridSpacingWidth.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            // 
            // GridHeight
            // 
            this.GridHeight.Location = new System.Drawing.Point( 52, 38 );
            this.GridHeight.Maximum = new decimal( new int[] {
            99999,
            0,
            0,
            0} );
            this.GridHeight.Minimum = new decimal( new int[] {
            1,
            0,
            0,
            0} );
            this.GridHeight.Name = "GridHeight";
            this.GridHeight.Size = new System.Drawing.Size( 39, 20 );
            this.GridHeight.TabIndex = 15;
            this.GridHeight.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            this.GridHeight.Value = new decimal( new int[] {
            1,
            0,
            0,
            0} );
            // 
            // GridWidth
            // 
            this.GridWidth.Location = new System.Drawing.Point( 52, 18 );
            this.GridWidth.Maximum = new decimal( new int[] {
            99999,
            0,
            0,
            0} );
            this.GridWidth.Minimum = new decimal( new int[] {
            1,
            0,
            0,
            0} );
            this.GridWidth.Name = "GridWidth";
            this.GridWidth.Size = new System.Drawing.Size( 39, 20 );
            this.GridWidth.TabIndex = 13;
            this.GridWidth.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            this.GridWidth.Value = new decimal( new int[] {
            1,
            0,
            0,
            0} );
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point( 7, 91 );
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size( 83, 13 );
            this.label5.TabIndex = 18;
            this.label5.Text = "Spa&cing Height:";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point( 7, 71 );
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size( 80, 13 );
            this.label6.TabIndex = 16;
            this.label6.Text = "S&pacing Width:";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point( 7, 40 );
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size( 41, 13 );
            this.label4.TabIndex = 14;
            this.label4.Text = "&Height:";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point( 7, 20 );
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size( 38, 13 );
            this.label3.TabIndex = 12;
            this.label3.Text = "&Width:";
            // 
            // BuiltUp
            // 
            this.BuiltUp.AutoSize = true;
            this.BuiltUp.Location = new System.Drawing.Point( 12, 86 );
            this.BuiltUp.Name = "BuiltUp";
            this.BuiltUp.Size = new System.Drawing.Size( 62, 17 );
            this.BuiltUp.TabIndex = 9;
            this.BuiltUp.TabStop = true;
            this.BuiltUp.Text = "&Built Up";
            this.BuiltUp.UseVisualStyleBackColor = true;
            this.BuiltUp.Click += new System.EventHandler( this.BuiltUp_Clicked );
            // 
            // Original
            // 
            this.Original.AutoSize = true;
            this.Original.Checked = true;
            this.Original.Location = new System.Drawing.Point( 12, 48 );
            this.Original.Name = "Original";
            this.Original.Size = new System.Drawing.Size( 60, 17 );
            this.Original.TabIndex = 7;
            this.Original.TabStop = true;
            this.Original.Text = "&Original";
            this.Original.UseVisualStyleBackColor = true;
            this.Original.Click += new System.EventHandler( this.Original_Clicked );
            // 
            // AverageColor
            // 
            this.AverageColor.AutoSize = true;
            this.AverageColor.Location = new System.Drawing.Point( 12, 66 );
            this.AverageColor.Name = "AverageColor";
            this.AverageColor.Size = new System.Drawing.Size( 92, 17 );
            this.AverageColor.TabIndex = 8;
            this.AverageColor.TabStop = true;
            this.AverageColor.Text = "&Average Color";
            this.AverageColor.UseVisualStyleBackColor = true;
            this.AverageColor.Click += new System.EventHandler( this.AverageColor_Clicked );
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point( 18, 111 );
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size( 58, 13 );
            this.label7.TabIndex = 10;
            this.label7.Text = "&Tolerance:";
            // 
            // Tolerance
            // 
            this.Tolerance.Location = new System.Drawing.Point( 79, 108 );
            this.Tolerance.Maximum = new decimal( new int[] {
            442,
            0,
            0,
            0} );
            this.Tolerance.Name = "Tolerance";
            this.Tolerance.Size = new System.Drawing.Size( 46, 20 );
            this.Tolerance.TabIndex = 11;
            // 
            // Save
            // 
            this.Save.Location = new System.Drawing.Point( 202, 139 );
            this.Save.Name = "Save";
            this.Save.Size = new System.Drawing.Size( 75, 23 );
            this.Save.TabIndex = 12;
            this.Save.Text = "&Save...";
            this.Save.UseVisualStyleBackColor = true;
            this.Save.Click += new System.EventHandler( this.Save_Click );
            // 
            // ImageBreakdownInfo
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF( 6F, 13F );
            this.ClientSize = new System.Drawing.Size( 286, 168 );
            this.Controls.Add( this.Tolerance );
            this.Controls.Add( this.label7 );
            this.Controls.Add( this.Save );
            this.Controls.Add( this.groupBox1 );
            this.Controls.Add( this.Original );
            this.Controls.Add( this.AverageColor );
            this.Controls.Add( this.BuiltUp );
            this.Name = "ImageBreakdownInfo";
            this.Controls.SetChildIndex( this.BuiltUp, 0 );
            this.Controls.SetChildIndex( this.AverageColor, 0 );
            this.Controls.SetChildIndex( this.Original, 0 );
            this.Controls.SetChildIndex( this.groupBox1, 0 );
            this.Controls.SetChildIndex( this.Save, 0 );
            this.Controls.SetChildIndex( this.label7, 0 );
            this.Controls.SetChildIndex( this.Tolerance, 0 );
            this.Controls.SetChildIndex( this.ImageWidth, 0 );
            this.Controls.SetChildIndex( this.ImageHeight, 0 );
            this.groupBox1.ResumeLayout( false );
            this.groupBox1.PerformLayout();
            ( ( System.ComponentModel.ISupportInitialize )( this.GridSpacingHeight ) ).EndInit();
            ( ( System.ComponentModel.ISupportInitialize )( this.GridSpacingWidth ) ).EndInit();
            ( ( System.ComponentModel.ISupportInitialize )( this.GridHeight ) ).EndInit();
            ( ( System.ComponentModel.ISupportInitialize )( this.GridWidth ) ).EndInit();
            ( ( System.ComponentModel.ISupportInitialize )( this.Tolerance ) ).EndInit();
            this.ResumeLayout( false );
            this.PerformLayout();

        }
        #endregion

        private GroupBox groupBox1;
        private Label label5;
        private Label label6;
        private Label label4;
        private Label label3;
        private NumericUpDown GridSpacingHeight;
        private NumericUpDown GridSpacingWidth;
        private NumericUpDown GridHeight;
        private NumericUpDown GridWidth;
        private RadioButton BuiltUp;
        private RadioButton Original;
        private RadioButton AverageColor;
        private Label label7;
        private NumericUpDown Tolerance;
        private Button Save;

    }
}
