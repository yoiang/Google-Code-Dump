using System;
using System.Windows.Forms;
using System.Drawing;

namespace ImageBreakdownBuildup
{
    public partial class Main : System.Windows.Forms.ImageWindow
    {
        public Bitmap OriginalBitmap;
        public AverageColorBitmap AverageColorBitmap;
        public BuildUpBitmap BuildUpBitmap;
        string BuildUpSourceFolder;

        public Main( string FileName, string SetBuildUpSourceFolder )
            : base( FileName )
        {
            InitializeComponent();

            OriginalBitmap = Bitmap;
            BuildUpSourceFolder = SetBuildUpSourceFolder;
        }

        public override ImageWindowInfo ConstructDefaultImageWindowInfo()
        {
            return new ImageBreakdownInfo( this );
        }

        public void ShowOriginal()
        {
            SetImage( OriginalBitmap );
        }

        public void ShowAverageColor( int GridWidth, int GridHeight, int GridSpacingWidth, int GridSpacingHeight )
        {
            UpdateAverageColorBitmap( GridWidth, GridHeight, GridSpacingWidth, GridSpacingHeight );
            SetImage( AverageColorBitmap );
        }

        public void ShowBuildUp( int GridWidth, int GridHeight, int GridSpacingWidth, int GridSpacingHeight, int Tolerance )
        {
            UpdateAverageColorBitmap( GridWidth, GridHeight, GridSpacingWidth, GridSpacingHeight );
            BuildUpBitmap = new BuildUpBitmap( OriginalBitmap, AverageColorBitmap, BuildUpSourceFolder, Tolerance );
            SetImage( BuildUpBitmap );
        }

        private void UpdateAverageColorBitmap( int GridWidth, int GridHeight, int GridSpacingWidth, int GridSpacingHeight )
        {
            if( AverageColorBitmap == null )
            {
                AverageColorBitmap = new AverageColorBitmap( OriginalBitmap, GridWidth, GridHeight, GridSpacingWidth, GridSpacingHeight );
            } else
            {
                AverageColorBitmap.Update( OriginalBitmap, GridWidth, GridHeight, GridSpacingWidth, GridSpacingHeight );
            }
        }
    }
}
