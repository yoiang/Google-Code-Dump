using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace handsigns
{
    public partial class MainWindow : Form
    {
        #region Member Variables
        private int thumbIndex;
        private int indexIndex;
        private int middleIndex;
        private int ringIndex;
        private int pinkyIndex;
        #endregion

        public MainWindow()
        {
            InitializeComponent();

            handsign.Items.Add( new HandSignSelectionItem( "Hand Wave", "Used to greet others", 1, 1, 1, 1, 1 ) );
            handsign.Items.Add(new HandSignSelectionItem("The Finger", "Translates directly to \"Fuck you\"", 0, 2, 1, 2, 2));
            handsign.Items.Add(new HandSignSelectionItem("Peace Sign", 0, 1, 1, 2, 2));
            handsign.Items.Add(new HandSignSelectionItem("Gnarly Sign", 1, 2, 2, 2, 1));
            handsign.Items.Add(new HandSignSelectionItem("Number 1", 0, 1, 2, 2, 2));
            handsign.Items.Add(new HandSignSelectionItem("The Finger Fake Out", 0, 2, 2, 1, 2));

            Properties.Settings.Default.Upgrade();
            char[] splitOn = { ',' };
            string[] Last = Properties.Settings.Default.Last.Split( splitOn );
            if( Last.Length > 0 )
            {
                thumbIndex = Convert.ToInt32( Last[ 0 ] );
            }
            if( Last.Length > 1 )
            {
                indexIndex = Convert.ToInt32( Last[ 1 ] );
            }
            if( Last.Length > 2 )
            {
                middleIndex = Convert.ToInt32( Last[ 2 ] );
            }
            if( Last.Length > 3 )
            {
                ringIndex = Convert.ToInt32( Last[ 3 ] );
            }
            if( Last.Length > 4 )
            {
                pinkyIndex = Convert.ToInt32( Last[ 4 ] );
            }
            UpdateFingerImages();
        }

        private void UpdateFingerImages()
        {
            Bitmap[] thumbImages = { Properties.Resources._0_0, Properties.Resources._1_0 };
            UpdateImage( ref thumb, ref thumbIndex, thumbImages );

            Bitmap[] indexImages = { Properties.Resources._0_1, Properties.Resources._1_1, Properties.Resources._3_1 };
            UpdateImage(ref index, ref indexIndex, indexImages);
            
            Bitmap[] middleImages = { Properties.Resources._0_2, Properties.Resources._1_2, Properties.Resources._3_2 };
            UpdateImage(ref middle, ref middleIndex, middleImages);
            
            Bitmap[] ringImages = { Properties.Resources._0_3, Properties.Resources._1_3, Properties.Resources._3_3 };
            UpdateImage(ref ring, ref ringIndex, ringImages);
            
            Bitmap[] pinkyImages = { Properties.Resources._0_4, Properties.Resources._1_4, Properties.Resources._3_4 };
            UpdateImage(ref pinky, ref pinkyIndex, pinkyImages);
        }
        private void UpdateImage(ref PictureBox Update, ref int Index, Bitmap[] Images)
        {
            Index = Index % Images.Length;
            Update.Image = Images[Index];
        }

        #region Click Event Functions
        private void thumb_Click(object sender, EventArgs e)
        {
            ++thumbIndex;
            UpdateFingerImages();
        }

        private void index_Click(object sender, EventArgs e)
        {
            ++indexIndex;
            UpdateFingerImages();
        }

        private void middle_Click(object sender, EventArgs e)
        {
            ++middleIndex;
            UpdateFingerImages();
        }

        private void ring_Click(object sender, EventArgs e)
        {
            ++ringIndex;
            UpdateFingerImages();
        }

        private void pinky_Click(object sender, EventArgs e)
        {
            ++pinkyIndex;
            UpdateFingerImages();
        }
        #endregion

        private void handsign_SelectedIndexChanged(object sender, EventArgs e)
        {
            HandSignSelectionItem SelectedItem = (HandSignSelectionItem)handsign.Items[ handsign.SelectedIndex ];
            if (SelectedItem != null)
            {
                thumbIndex = SelectedItem.thumbIndex;
                indexIndex = SelectedItem.indexIndex;
                middleIndex = SelectedItem.middleIndex;
                ringIndex = SelectedItem.ringIndex;
                pinkyIndex = SelectedItem.pinkyIndex;
                UpdateFingerImages();
            }
        }

        private void OnClosing( object sender, FormClosingEventArgs e )
        {
            Properties.Settings.Default.Last = thumbIndex + "," + indexIndex + "," + middleIndex + "," + ringIndex + "," + pinkyIndex;
            Properties.Settings.Default.Save();
        }
    }

    class HandSignSelectionItem
    {
        public string Name;
        public string Description;
        public int thumbIndex;
        public int indexIndex;
        public int middleIndex;
        public int ringIndex;
        public int pinkyIndex;

        public HandSignSelectionItem(string SetName, string SetDescription, int SetthumbIndex, int SetindexIndex, int SetmiddleIndex, int SetringIndex, int SetpinkyIndex)
        {
            Name = SetName;
            Description = SetDescription;
            thumbIndex = SetthumbIndex;
            indexIndex = SetindexIndex;
            middleIndex = SetmiddleIndex;
            ringIndex = SetringIndex;
            pinkyIndex = SetpinkyIndex;
        }

        public HandSignSelectionItem(string SetName, int SetthumbIndex, int SetindexIndex, int SetmiddleIndex, int SetringIndex, int SetpinkyIndex)
        {
            Name = SetName;
            Description = "";
            thumbIndex = SetthumbIndex;
            indexIndex = SetindexIndex;
            middleIndex = SetmiddleIndex;
            ringIndex = SetringIndex;
            pinkyIndex = SetpinkyIndex;
        }

        override public string ToString()
        {
            if ( Description.Length > 0 )
                return Name + " - " + Description;
            return Name;
        }
    }
}
