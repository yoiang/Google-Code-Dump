using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace ImageBreakdownBuildup
{
    partial class ImageBreakdownInfo : ImageWindowInfo
    {
        Main ParentImageWindow;
    
        public ImageBreakdownInfo( Main SetParent ) : base()
        {
            InitializeComponent();

            ParentImageWindow = SetParent;
        }

        public override void UpdateSize( int SetWidth, int SetHeight )
        {
            base.UpdateSize( SetWidth, SetHeight );
            GridWidth.Maximum = GridSpacingWidth.Maximum = SetWidth;
            GridHeight.Maximum = GridSpacingHeight.Maximum = SetHeight;
        }

        private void Original_Clicked( object sender, EventArgs e )
        {
            AverageColor.Checked = false;
            BuiltUp.Checked = false;
            Save.Enabled = false;
            ParentImageWindow.ShowOriginal();
        }

        private void AverageColor_Clicked( object sender, EventArgs e )
        {
            Original.Checked = false;
            BuiltUp.Checked = false;
            Save.Enabled = true;
            ParentImageWindow.ShowAverageColor( Convert.ToInt32( GridWidth.Value ),
                                                Convert.ToInt32( GridHeight.Value ),
                                                Convert.ToInt32( GridSpacingWidth.Value ),
                                                Convert.ToInt32( GridSpacingHeight.Value ) );
        }

        private void BuiltUp_Clicked( object sender, EventArgs e )
        {
            Original.Checked = false;
            AverageColor.Checked = false;
            Save.Enabled = true;
            ParentImageWindow.ShowBuildUp( Convert.ToInt32( GridWidth.Value ),
                                           Convert.ToInt32( GridHeight.Value ),
                                           Convert.ToInt32( GridSpacingWidth.Value ),
                                           Convert.ToInt32( GridSpacingHeight.Value ),
                                           Convert.ToInt32( Tolerance.Value ) );
        }

        private void Save_Click( object sender, EventArgs e )
        {
            SaveFileDialog SaveDialog = new SaveFileDialog();
            SaveDialog.DefaultExt = ".jpg";
            SaveDialog.AddExtension = true;
            SaveDialog.Filter = "JPG file|*.jpg";
            DialogResult Result = SaveDialog.ShowDialog( this );
            if( Result == DialogResult.OK )
            {
                if( AverageColor.Checked )
                {
                    ( ( System.Drawing.Bitmap )ParentImageWindow.AverageColorBitmap ).Save( SaveDialog.FileName );
                } else if( BuiltUp.Checked )
                {
                    ( ( System.Drawing.Bitmap )ParentImageWindow.BuildUpBitmap ).Save( SaveDialog.FileName );
                }
            }
        }
    }
}
