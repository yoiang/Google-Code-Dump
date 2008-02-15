using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Net;
using System.Net.Sockets;

namespace RemoteWindows
{
    public partial class MainDialog : Form
    {
        public MainDialog()
        {
            InitializeComponent();
        }

        public SocketMainConnection MainConnection;

        private void MainDialog_Load(object sender, EventArgs e)
        {
            UpdateEnableButtons();
        }

        private void Enable_Click(object sender, EventArgs e)
        {
            EnableMainConnection();
            EnableRemoteConnections();

            UpdateEnableButtons();
        }

        private void Disable_Click(object sender, EventArgs e)
        {
            DisableMainConnection();
            DisableRemoteConnections();

            UpdateEnableButtons();
        }

        private void UpdateEnableButtons()
        {
            if (MainConnection == null || !MainConnection.IsBound)
            {
                Enable.Enabled = true;
                Disable.Enabled = false;
            }
            else
            {
                Enable.Enabled = false;
                Disable.Enabled = true;
            }
        }

        private void ConnectToAdd_Click(object sender, EventArgs e)
        {
            ConnectToAddDialog AddDialog = new ConnectToAddDialog();
            AddDialog.ShowDialog(this);
            if (AddDialog.Hostname.Length > 0)
            {
                ConnectToList.Items.Add(AddDialog.Hostname);
            }
        }

        //----------------------------------------------------------------------------------------
        private void EnableMainConnection()
        {
            MainConnection = new SocketMainConnection();
            MainConnection.Enable(Properties.Settings.Default.Port, Properties.Settings.Default.MaxConnections);
        }

        private void DisableMainConnection()
        {
            MainConnection.Disable();
            MainConnection = null;
        }

        public void EnableRemoteConnections()
        {
        }

        public void DisableRemoteConnections()
        {
        }
    }
}