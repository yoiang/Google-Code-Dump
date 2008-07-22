using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace System.Windows.Forms
{
    public partial class ImageWindowInfo : Form
    {
        public ImageWindowInfo()
        {
            InitializeComponent();
        }

        public virtual void UpdateSize( int SetWidth, int SetHeight )
        {
            if( SetWidth == 0 || SetHeight == 0 )
            {
                ImageWidth.Text = "-";
                ImageHeight.Text = "-";
            } else
            {
                ImageWidth.Text = SetWidth.ToString();
                ImageHeight.Text = SetHeight.ToString();
            }
        }
    }
}
