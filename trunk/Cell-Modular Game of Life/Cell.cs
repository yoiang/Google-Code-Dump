using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Cell_Modular_Game_of_Life
{
    public class Cell
    {
        public bool Alive;
        Cell[,] Neighbors;
        int AliveNeighbors;

        public Cell()
        {
            Alive = false;
            Neighbors = new Cell[3, 3];
            AliveNeighbors = 0;
        }

        public Cell GetNeighbor(int OffsetX, int OffsetY)
        {
            OffsetX = AdjustOffsetForArray(OffsetX);
            OffsetY = AdjustOffsetForArray(OffsetY);
            return Neighbors[OffsetX, OffsetY];
        }
        public void SetNeighbor(int OffsetX, int OffsetY, Cell SetAs)
        {
            OffsetX = AdjustOffsetForArray(OffsetX);
            OffsetY = AdjustOffsetForArray(OffsetY);
            Neighbors[OffsetX, OffsetY] = SetAs;
        }

        public void UpdateAliveNeighbors()
        {
            for (int X = -1; X <= 1; X++)
            {
                for (int Y = -1; Y <= 1; Y++)
                {
                    Cell Neighbor = GetNeighbor(X, Y);
                    if (Neighbor != null && Neighbor != this)
                    {
                        if (Neighbor.Alive)
                        {
                            AliveNeighbors++;
                        }
                    }
                }
            }
        }

        public void UpdateAlive()
        {
            Alive = Alive && (AliveNeighbors == 2 || AliveNeighbors == 3 ) || !Alive && AliveNeighbors == 3;
            AliveNeighbors = 0;
        }

        private int AdjustOffsetForArray(int Offset)
        {
            if (Offset != 0)
            {
                Offset = Offset / Math.Abs(Offset);
            }
            return Offset + 1;
        }

        public void DrawAt( System.Drawing.Point Location, int Size, System.Drawing.Bitmap SetOn )
        {
            System.Drawing.Color DrawColor;
            if (Alive)
            {
                DrawColor = System.Drawing.Color.Green;
            }
            else
            {
                DrawColor = System.Drawing.Color.Black;
            }

            for (int X = 0; X < Size; X++)
            {
                for (int Y = 0; Y < Size; Y++)
                {
                    SetOn.SetPixel(Location.X + X, Location.Y + Y, DrawColor);
                }
            }
        }
    }
}
