using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace ImageBreakdownBuildup
{
    class ImageBreakdownInfo : ImageWindowInfo
    {
        private RadioButton AverageColor;
        private GroupBox groupBox1;
        private GroupBox groupBox2;
        private Label label5;
        private Label label6;
        private Label label4;
        private Label label3;
        private NumericUpDown GridSpacingHeight;
        private NumericUpDown GridSpacingWidth;
        private NumericUpDown GridHeight;
        private NumericUpDown GridWidth;
        private RadioButton Original;
        private RadioButton BuiltUp;

        Main ParentImageWindow;
    
        public ImageBreakdownInfo( Main SetParent ) : base()
        {
            InitializeComponent();

            ParentImageWindow = SetParent;
        }

        private void InitializeComponent()
        {
            this.Original = new System.Windows.Forms.RadioButton();
            this.AverageColor = new System.Windows.Forms.RadioButton();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.GridSpacingHeight = new System.Windows.Forms.NumericUpDown();
            this.GridSpacingWidth = new System.Windows.Forms.NumericUpDown();
            this.GridHeight = new System.Windows.Forms.NumericUpDown();
            this.GridWidth = new System.Windows.Forms.NumericUpDown();
            this.label5 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.BuiltUp = new System.Windows.Forms.RadioButton();
            this.groupBox1.SuspendLayout();
            ( ( System.ComponentModel.ISupportInitialize )( this.GridSpacingHeight ) ).BeginInit();
            ( ( System.ComponentModel.ISupportInitialize )( this.GridSpacingWidth ) ).BeginInit();
            ( ( System.ComponentModel.ISupportInitialize )( this.GridHeight ) ).BeginInit();
            ( ( System.ComponentModel.ISupportInitialize )( this.GridWidth ) ).BeginInit();
            this.groupBox2.SuspendLayout();
            this.SuspendLayout();
            // 
            // Original
            // 
            this.Original.AutoSize = true;
            this.Original.Checked = true;
            this.Original.Location = new System.Drawing.Point( 21, 19 );
            this.Original.Name = "Original";
            this.Original.Size = new System.Drawing.Size( 60, 17 );
            this.Original.TabIndex = 4;
            this.Original.TabStop = true;
            this.Original.Text = "Original";
            this.Original.UseVisualStyleBackColor = true;
            this.Original.CheckedChanged += new System.EventHandler( this.Original_CheckedChanged );
            // 
            // AverageColor
            // 
            this.AverageColor.AutoSize = true;
            this.AverageColor.Location = new System.Drawing.Point( 21, 37 );
            this.AverageColor.Name = "AverageColor";
            this.AverageColor.Size = new System.Drawing.Size( 92, 17 );
            this.AverageColor.TabIndex = 5;
            this.AverageColor.TabStop = true;
            this.AverageColor.Text = "Average Color";
            this.AverageColor.UseVisualStyleBackColor = true;
            this.AverageColor.CheckedChanged += new System.EventHandler( this.AverageColor_CheckedChanged );
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
            this.groupBox1.Location = new System.Drawing.Point( 16, 105 );
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size( 218, 126 );
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
            this.GridSpacingHeight.TabIndex = 7;
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
            this.GridSpacingWidth.TabIndex = 6;
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
            this.GridHeight.TabIndex = 5;
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
            this.GridWidth.TabIndex = 4;
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
            this.label5.TabIndex = 3;
            this.label5.Text = "Spacing Height:";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point( 7, 71 );
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size( 80, 13 );
            this.label6.TabIndex = 2;
            this.label6.Text = "Spacing Width:";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point( 7, 40 );
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size( 41, 13 );
            this.label4.TabIndex = 1;
            this.label4.Text = "Height:";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point( 7, 20 );
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size( 38, 13 );
            this.label3.TabIndex = 0;
            this.label3.Text = "Width:";
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add( this.BuiltUp );
            this.groupBox2.Controls.Add( this.Original );
            this.groupBox2.Controls.Add( this.AverageColor );
            this.groupBox2.Location = new System.Drawing.Point( 109, 12 );
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size( 125, 87 );
            this.groupBox2.TabIndex = 7;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Draw Mode";
            // 
            // BuiltUp
            // 
            this.BuiltUp.AutoSize = true;
            this.BuiltUp.Location = new System.Drawing.Point( 21, 57 );
            this.BuiltUp.Name = "BuiltUp";
            this.BuiltUp.Size = new System.Drawing.Size( 62, 17 );
            this.BuiltUp.TabIndex = 6;
            this.BuiltUp.TabStop = true;
            this.BuiltUp.Text = "Built Up";
            this.BuiltUp.UseVisualStyleBackColor = true;
            this.BuiltUp.CheckedChanged += new System.EventHandler( this.BuiltUp_CheckedChanged );
            // 
            // ImageBreakdownInfo
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF( 6F, 13F );
            this.ClientSize = new System.Drawing.Size( 250, 242 );
            this.Controls.Add( this.groupBox2 );
            this.Controls.Add( this.groupBox1 );
            this.Name = "ImageBreakdownInfo";
            this.Controls.SetChildIndex( this.ImageWidth, 0 );
            this.Controls.SetChildIndex( this.ImageHeight, 0 );
            this.Controls.SetChildIndex( this.groupBox1, 0 );
            this.Controls.SetChildIndex( this.groupBox2, 0 );
            this.groupBox1.ResumeLayout( false );
            this.groupBox1.PerformLayout();
            ( ( System.ComponentModel.ISupportInitialize )( this.GridSpacingHeight ) ).EndInit();
            ( ( System.ComponentModel.ISupportInitialize )( this.GridSpacingWidth ) ).EndInit();
            ( ( System.ComponentModel.ISupportInitialize )( this.GridHeight ) ).EndInit();
            ( ( System.ComponentModel.ISupportInitialize )( this.GridWidth ) ).EndInit();
            this.groupBox2.ResumeLayout( false );
            this.groupBox2.PerformLayout();
            this.ResumeLayout( false );
            this.PerformLayout();

        }

        public override void UpdateSize( int SetWidth, int SetHeight )
        {
            base.UpdateSize( SetWidth, SetHeight );
            GridWidth.Maximum = GridSpacingWidth.Maximum = SetWidth;
            GridHeight.Maximum = GridSpacingHeight.Maximum = SetHeight;
        }

        private void Original_CheckedChanged( object sender, EventArgs e )
        {
            if( Original.Checked )
            {
                AverageColor.Checked = false;
                BuiltUp.Checked = false;
                ParentImageWindow.ShowOriginal();
            }
        }

        private void AverageColor_CheckedChanged( object sender, EventArgs e )
        {
            if( AverageColor.Checked )
            {
                Original.Checked = false;
                BuiltUp.Checked = false;
                ParentImageWindow.ShowAverageColor( Convert.ToInt32( GridWidth.Value ),
                                                    Convert.ToInt32( GridHeight.Value ),
                                                    Convert.ToInt32( GridSpacingWidth.Value ),
                                                    Convert.ToInt32( GridSpacingHeight.Value ) );
            }
        }

        private void BuiltUp_CheckedChanged( object sender, EventArgs e )
        {
            if( BuiltUp.Checked )
            {
                Original.Checked = false;
                AverageColor.Checked = false;
                ParentImageWindow.ShowBuildUp( Convert.ToInt32( GridWidth.Value ),
                                                    Convert.ToInt32( GridHeight.Value ),
                                                    Convert.ToInt32( GridSpacingWidth.Value ),
                                                    Convert.ToInt32( GridSpacingHeight.Value ) );
            }
        }
    }
}
