using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using P4API;
using Aga.Controls.Tree;
using System.Threading;
using System.Text.RegularExpressions;

namespace P4UserSummary
{
    public partial class MainWindow : Form
    {
        public P4Connection Connection;
        public Thread BuildTreeThread;

        public MainWindow()
        {
            InitializeComponent();
            Connection = new P4Connection();
            Connect();
        }

        public void Connect()
        {
            Connection.Connect();
            UpdateDialog();
        }

        public void UpdateDialog()
        {
            P4Port.Text = Connection.Port;
            User.Text = Connection.User;
            Client.Text = Connection.Client;
        }

        public void UpdateConnection()
        {
            Connection.Disconnect();
            Connection.Port = P4Port.Text;
            Connection.User = User.Text;
            Connection.Client = Client.Text;
        }
        
        private void Rebuild_Click(object sender, EventArgs e)
        {
            if (Rebuild.FlatStyle == FlatStyle.Standard)
            {
                UpdateConnection();
                Connect();
                if (Connection.IsValidConnection(true, true) && Path.Text.Length > 0)
                {
                    BuildTree();
                }
            }
            else
            {
                AbortBuildTree();
            }
        }

        private void DepotView_ColumnClicked(object sender, Aga.Controls.Tree.TreeColumnEventArgs Event)
        {
            if (Event.Column.SortOrder == SortOrder.Ascending)
                Event.Column.SortOrder = SortOrder.Descending;
            else
                Event.Column.SortOrder = SortOrder.Ascending;

            (DepotView.Model as Aga.Controls.Tree.SortedTreeModel).Comparer = new FileDepotNodeSorter(Event.Column.Header, Event.Column.SortOrder);
        }

        public void MainWindowClosing(object sender, FormClosingEventArgs e)
        {
            AbortBuildTree();
        }

        private void BuildTree()
        {
            AbortBuildTree();

            DepotView.Model = new SortedTreeModel(new TreeModel());
            BuildTreeThread = new Thread(new ThreadStart(BuildTreeThreadJob));
            BuildTreeThread.Start();
        }

        private void AbortBuildTree()
        {
            if (BuildTreeThread != null)
            {
                BuildTreeThread.Abort();
                BuildTreeThread = null;
            }

            UpdateButtonDone();
        }

        private void BuildTreeThreadJob()
        {
            Invoke(new MethodInvoker(UpdateButtonRequestingChangesFromPerforce));
            List<FileChangeInfo> Files = new List<FileChangeInfo>();
            GetAllUserChangeListFiles(ref Files, Connection.User);

            Invoke(new MethodInvoker(UpdateButtonUpdatingTree));
            TreeModel InnerTreeModel = (TreeModel)((SortedTreeModel)DepotView.Model).InnerModel;
            FillDepotTree(ref Files, ref InnerTreeModel, true);

            Invoke(new MethodInvoker(UpdateButtonRequestingDiffsFromPerforce));
            GetDiffLineCounts(ref Files);

            Invoke(new MethodInvoker(UpdateButtonUpdatingTree));
            FillDepotTree(ref Files, ref InnerTreeModel);

            Invoke(new MethodInvoker(UpdateButtonDone));
        }

        private void GetAllUserChangeListFiles(ref List<FileChangeInfo> Files, string UserName)
        {
            P4RecordSet AllChangeLists = Connection.Run("changes", "-u", UserName, "-s", "submitted", Path.Text);
            foreach (P4Record Record in AllChangeLists.Records)
            {
                GetChangeFiles(Record, ref Files);
            }
        }

        private void GetChangeFiles(P4Record Change, ref List<FileChangeInfo> Files)
        {
            string[] SplitOn = { "..." };
            string[] AllowPath = Path.Text.Split(SplitOn, StringSplitOptions.RemoveEmptyEntries);

            string ChangeListNumber = Change.Fields["change"];
            P4RecordSet AllChanges = Connection.Run("describe", ChangeListNumber);
            foreach (P4Record Record in AllChanges.Records)
            {
                string[] DepotFile = Record.ArrayFields["depotFile"];
                string[] Revision = Record.ArrayFields["rev"];

                for (int TravResults = 0; TravResults < DepotFile.Length; ++ TravResults )
                {
                    if (AllowPath.Length > 0 && DepotFile[TravResults].IndexOf(AllowPath[0]) != 0)
                    {
                        continue;
                    }
                    FileChangeInfo Add = new FileChangeInfo();
                    Add.FileName = DepotFile[TravResults];
                    Add.Revision = Convert.ToInt32(Revision[TravResults]);
                    Add.ChangeList = Convert.ToInt32(ChangeListNumber);
                    Files.Add(Add);
                }
            }
        }

        private void GetDiffLineCounts(ref List<FileChangeInfo> Files)
        {
            foreach ( FileChangeInfo File in Files )
            {
                if (File.Revision > 1)
                {
                    P4UnParsedRecordSet UnDiffs = Connection.RunUnParsed("diff2", File.FileName + "#" + (File.Revision - 1), File.FileName + "#" + File.Revision);
                    foreach (string Message in UnDiffs.Messages)
                    {
                        File.LinesAddedCount += GetLinesAffectedCount(Message, "[\\d]+a([\\d]+),([\\d]+)\\n",1);
                        File.LinesAddedCount += GetLinesAffectedCount(Message, "([\\d]+)a([\\d]+)\\n");
                        File.LinesChangedCount += GetLinesAffectedCount(Message, "([\\d]+)c([\\d]+)\\n", 1);
                        File.LinesChangedCount += GetLinesAffectedCount(Message, "[\\d]+c([\\d]+),([\\d]+)\\n");
                        File.LinesChangedCount += GetLinesAffectedCount(Message, "[\\d]+,([\\d]+)c([\\d]+)\\n");
                        File.LinesDeletedCount += GetLinesAffectedCount(Message, "[\\d]+,([\\d]+)d([\\d]+)\\n");
                    }
                }
            }
        }

        private int GetLinesAffectedCount(string DiffLine, string DiffMatch)
        {
            return GetLinesAffectedCount(DiffLine, DiffMatch, 0);
        }
        private int GetLinesAffectedCount(string DiffLine, string DiffMatch, int PadFound)
        {
            int LinesAffected = 0;
            Regex RegexObj = new Regex(DiffMatch);
            Match MatchResults = RegexObj.Match(DiffLine);
            while (MatchResults.Success)
            {
                if (MatchResults.Groups.Count == 3)
                {
                    int Value0 = Convert.ToInt32(MatchResults.Groups[1].ToString()), Value1 = Convert.ToInt32(MatchResults.Groups[2].ToString());

                    if (Value0 > Value1)
                    {
                        LinesAffected += Value0 - Value1 + PadFound;
                    }
                    else
                    {
                        LinesAffected += Value1 - Value0 + PadFound;
                    }
                }
                MatchResults = MatchResults.NextMatch();
            }
            return LinesAffected;
        }

        private void FillDepotTree(ref List<FileChangeInfo> Files, ref TreeModel DepotTree)
        {
            FillDepotTree(ref Files, ref DepotTree, false);
        }

        private void FillDepotTree(ref List<FileChangeInfo> Files, ref TreeModel DepotTree, bool bIncrimentCheckinCount )
        {
            FolderInformation Root;
            if (DepotTree.Nodes.Count == 0)
            {
                Root = new FolderInformation("//");
                DepotTree.Nodes.Add(Root);
            }
            else
            {
                Root = (FolderInformation)DepotTree.Nodes[0];
            }
            foreach (FileChangeInfo File in Files)
            {
                string[] delimiters = { "//", "/" };
                string[] FileSplit = File.FileName.Split(delimiters, StringSplitOptions.RemoveEmptyEntries);

                int CurrentIndex = 0;
                while (CurrentIndex < FileSplit.Length && FileSplit[CurrentIndex].Length == 0)
                {
                    ++CurrentIndex;
                }

                FileInformation Add = new FileInformation(File.FileName);
                Add.Depth = CurrentIndex;
                Add.AddCounts(File, bIncrimentCheckinCount);
                Root.AddFile(Add, FileSplit, CurrentIndex);
            }
        }

        private void UpdateButtonRequestingChangesFromPerforce()
        {
            Rebuild.FlatStyle = FlatStyle.Flat;
            Rebuild.Text = "Requesting changes from Perforce...";
        }

        private void UpdateButtonUpdatingTree()
        {
            Rebuild.FlatStyle = FlatStyle.Flat;
            Rebuild.Text = "Updating tree...";
        }

        private void UpdateButtonRequestingDiffsFromPerforce()
        {
            Rebuild.FlatStyle = FlatStyle.Flat;
            Rebuild.Text = "Requesting diffs from Perforce...";
        }

        private void UpdateButtonDone()
        {
            Rebuild.FlatStyle = FlatStyle.Standard;
            Rebuild.Text = "&Rebuild";
        }
    }

    public class FileChangeInfo
    {
        public string FileName;
        public int ChangeList;
        public int Revision;

        public int LinesAddedCount;
        public int LinesChangedCount;
        public int LinesDeletedCount;
        public FileChangeInfo()
        {
            FileName = "";
            ChangeList = -1;
            Revision = -1;
        }
    }
}