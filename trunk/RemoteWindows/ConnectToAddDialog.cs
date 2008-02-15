using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace RemoteWindows
{
    public partial class ConnectToAddDialog : Form
    {
        public ConnectToAddDialog()
        {
            InitializeComponent();
            UpdateOkButton();
        }

        private void UpdateOkButton()
        {
            if (this.HostnameBox.Text.Length <= 0)
            {
                this.Ok.Enabled = false;
            }
            else
            {
                this.Ok.Enabled = true;
            }
        }

        private void Hostname_TextChanged(object sender, EventArgs e)
        {
            UpdateOkButton();
        }

        private void Ok_Click(object sender, EventArgs e)
        {
            Close();
        }

        private void Cancel_Click(object sender, EventArgs e)
        {
            this.HostnameBox.Text = "";
            Close();
        }

        public string Hostname
        {
            get { return HostnameBox.Text; }
            set { HostnameBox.Text = value; HostnameBox.Refresh(); }
        }
    }
}