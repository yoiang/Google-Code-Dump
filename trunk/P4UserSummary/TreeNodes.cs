using System;
using System.Collections.Generic;
using System.Windows.Forms;

namespace P4UserSummary
{
    public class FileInformation : Aga.Controls.Tree.Node, IComparable
    {
        #region Member Variables
        private string szShortFileName;
        private string szFullFileName;

        private int nDepth;

        private int nCheckInCount;

        private int nLinesChangedCount;
        private int nLinesAddedCount;
        private int nLinesDeletedCount;
        #endregion

        #region Properties
        public string FullFileName { get { return szFullFileName; } set { szFullFileName = value; } }
        public string ShortFileName { get { return szShortFileName; } set { szShortFileName = value; } }

        public int Depth { get { return nDepth; } set { nDepth = value; } }

        public int CheckInCount { get { return nCheckInCount; } set { nCheckInCount = value; } }
        public string CheckInCountAdjusted 
        {
            get
            {
                string Result = "";
                for ( int TravDepth = 0; TravDepth < Depth; ++ TravDepth )
                {
                    Result += " ";
                }
                return Result + CheckInCount;
            }
        }

        public int OverallLinesAltered { get { return LinesChangedCount + LinesAddedCount + LinesDeletedCount; } }
        public string OverallLinesAlteredAdjusted
        {
            get
            {
                if (OverallLinesAltered < 0)
                {
                    return "???";
                }
                string Result = "";
                for (int TravDepth = 0; TravDepth < Depth; ++TravDepth)
                {
                    Result += " ";
                }
                return Result + OverallLinesAltered;
            }
        }
        public int LinesChangedCount { get { return nLinesChangedCount; } set { nLinesChangedCount = value; } }
        public string LinesChangedCountAdjusted
        {
            get
            {
                if (LinesChangedCount == -1)
                {
                    return "???";
                }
                string Result = "";
                for (int TravDepth = 0; TravDepth < Depth; ++TravDepth)
                {
                    Result += " ";
                }
                return Result + LinesChangedCount;
            }
        }
        public int LinesAddedCount { get { return nLinesAddedCount; } set { nLinesAddedCount = value; } }
        public string LinesAddedCountAdjusted
        {
            get
            {
                if (LinesAddedCount == -1)
                {
                    return "???";
                }
                string Result = "";
                for (int TravDepth = 0; TravDepth < Depth; ++TravDepth)
                {
                    Result += " ";
                }
                return Result + LinesAddedCount;
            }
        }
        public int LinesDeletedCount { get { return nLinesDeletedCount; } set { nLinesDeletedCount = value; } }
        public string LinesDeletedCountAdjusted
        {
            get
            {
                if (LinesDeletedCount == -1)
                {
                    return "???";
                }
                string Result = "";
                for (int TravDepth = 0; TravDepth < Depth; ++TravDepth)
                {
                    Result += " ";
                }
                return Result + LinesDeletedCount;
            }
        }
        #endregion

        public FileInformation(string SetFullFileName)
        {
            FullFileName = SetFullFileName;

            char[] delimiters = { '/' };
            string[] FileSplit = FullFileName.Split(delimiters);
            if (FileSplit.Length > 0 && FileSplit[FileSplit.Length - 1].Length > 0)
            {
                ShortFileName = FileSplit[FileSplit.Length - 1];
            }
            else
            {
                ShortFileName = FullFileName;
            }
            CheckInCount = 0;
            LinesAddedCount = 0;
            LinesChangedCount = 0;
            LinesDeletedCount = 0;
            Depth = 0;
            nLinesChangedCount = 0;
        }

        #region Comparison Functions
        public int CompareTo(object obj)
        {
            return CompareCheckInCountTo(obj);
        }

        public int CompareCheckInCountTo(object obj)
        {
            if (obj as FileInformation != null)
            {
                FileInformation Right = (FileInformation)obj;
                if (CheckInCount < Right.CheckInCount)
                {
                    return -1;
                }
                else if (CheckInCount == Right.CheckInCount)
                {
                    return 0;
                }
                else
                {
                    return 1;
                }
            }
            return 0;
        }

        public int CompareFileNameTo(object obj)
        {
            if (obj as FileInformation != null)
            {
                FileInformation Right = (FileInformation)obj;
                return string.Compare( ShortFileName, Right.ShortFileName);
            }
            return 0;
        }
        #endregion

        public void AddCounts(FileInformation Add)
        {
            CheckInCount += Add.CheckInCount;
            LinesAddedCount += Add.LinesAddedCount;
            LinesChangedCount += Add.LinesChangedCount;
            LinesDeletedCount += Add.LinesDeletedCount;
        }

        public void AddCounts(FileChangeInfo Add)
        {
            AddCounts(Add, false);
        }

        public void AddCounts(FileChangeInfo Add, bool bIncrimentCheckInCount)
        {
            if (bIncrimentCheckInCount)// craphack
            {
                CheckInCount += 1;
            }
            LinesAddedCount += Add.LinesAddedCount;
            LinesChangedCount += Add.LinesChangedCount;
            LinesDeletedCount += Add.LinesDeletedCount;
        }
    }

    public class FolderInformation : FileInformation
    {
        public System.Collections.Generic.Dictionary<string, FileInformation> Contained;

        public FolderInformation(string SetFullFileName)
            : base(SetFullFileName)
        {
            Contained = new System.Collections.Generic.Dictionary<string, FileInformation>();
        }

        public void AddFile(FileInformation Add, string[] FileSplit, int Depth)
        {
            AddCounts(Add);

            if (!Contained.ContainsKey(FileSplit[Depth].ToUpper()))
            {
                if (Depth == FileSplit.Length - 1)
                {
                    Nodes.Add(Add);
                    Add.Depth = Depth;
                    Contained.Add(FileSplit[Depth].ToUpper(), Add);
                }
                else
                {
                    FolderInformation NewFolder = new FolderInformation(FileSplit[Depth]);
                    NewFolder.Depth = Depth;
                    NewFolder.CheckInCount = Add.CheckInCount;
                    
                    Nodes.Add(NewFolder);
                    Contained.Add(FileSplit[Depth].ToUpper(), NewFolder);
                }
            }
            else
            {
                if (Contained[FileSplit[Depth].ToUpper()].GetType() == typeof(FolderInformation))
                {
                    ((FolderInformation)(Contained[FileSplit[Depth].ToUpper()])).AddFile(Add, FileSplit, Depth + 1);
                }
                else if (Contained[FileSplit[Depth].ToUpper()].GetType() == typeof(FileInformation))
                {
                    ((FileInformation)(Contained[FileSplit[Depth].ToUpper()])).AddCounts( Add );
                }
            }
        }
    }

    public class FileDepotNodeSorter : System.Collections.IComparer
    {
   		private string Mode;
		private SortOrder Order;

        public FileDepotNodeSorter(string SetMode, SortOrder SetOrder)
		{
            Mode = SetMode;
            Order = SetOrder;
		}

        public int Compare(object x, object y)
        {
            object Left, Right;
            if (Order == SortOrder.Ascending)
            {
                Left = y;
                Right = x;
            }
            else
            {
                Left = x;
                Right = y;
            }
            if (Right as FileInformation != null)
            {
                if (Mode == "File Name")
                {
                    return ((FileInformation)Left).CompareFileNameTo(Right);
                }
                else if (Mode == "Check Ins")
                {
                    return ((FileInformation)Left).CompareCheckInCountTo(Right);
                }
            }
            return 0;
        }
    }

}
