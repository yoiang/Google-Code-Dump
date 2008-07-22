using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace Cell_Modular_Game_of_Life
{
    public partial class Main : Form
    {
        Cell[,] PetriDish;

        bool bMouseDown;
        bool bMouseDownSetAlive;

        Timer UpdateTimer;
        bool UpdateTimerPausedByMouseDown;

        public Main()
        {
            InitializeComponent();

            UpdateTimer = new Timer(); 
            UpdateTimer.Interval = 100; 
            UpdateTimer.Tick += new EventHandler(UpdatePetriDish); 

            CreatePetriDish(50,50);

            PetriDishPictureBox.Image = new Bitmap(500, 500);

            for (int X = 0; X < PetriDish.GetLength(0); X++)
            {
                for (int Y = 0; Y < PetriDish.GetLength(1); Y++)
                {
                    PetriDish[X, Y].DrawAt(CellLocationToImageLocation(new Point(X, Y)), PetriDishPictureBox.Image.Width / PetriDish.GetLength(0), (Bitmap)PetriDishPictureBox.Image);
                }
            }
        }

        public void CreatePetriDish(int SizeX, int SizeY)
        {
            PetriDish = new Cell[SizeX, SizeY];
            for (int X = 0; X < PetriDish.GetLength(0); X++)
            {
                for (int Y = 0; Y < PetriDish.GetLength(1); Y++)
                {
                    CreateCell(X, Y);
                }
            }
        }
        public void CreateCell(int AtX, int AtY)
        {
            if (AtX >= 0 && AtX < PetriDish.GetLength(0) && AtY >= 0 && AtY < PetriDish.GetLength(1))
            {
                Cell NewCell = new Cell();
                for (int X = -1; X <= 1; X++)
                {
                    for (int Y = -1; Y <= 1; Y++)
                    {
                        Cell Neighbor = GetCell(AtX + X, AtY + Y);
                        if (Neighbor != NewCell && Neighbor != null)
                        {
                            NewCell.SetNeighbor(X, Y, Neighbor);
                            Neighbor.SetNeighbor(-X, -Y, NewCell);
                        }
                    }
                }
                PetriDish[AtX, AtY] = NewCell;
            }
        }

        public Cell GetCell(int AtX, int AtY)
        {
            if (AtX >= 0 && AtX < PetriDish.GetLength(0) && AtY >= 0 && AtY < PetriDish.GetLength(1))
            {
                return PetriDish[AtX, AtY];
            }
            return null;
        }

        void UpdatePetriDish(object sender, EventArgs e)
        {
            for (int X = 0; X < PetriDish.GetLength(0); X++)
            {
                for (int Y = 0; Y < PetriDish.GetLength(1); Y++)
                {
                    PetriDish[X, Y].UpdateAliveNeighbors();
                }
            }

            for (int X = 0; X < PetriDish.GetLength(0); X++)
            {
                for (int Y = 0; Y < PetriDish.GetLength(1); Y++)
                {
                    PetriDish[X, Y].UpdateAlive();
                    PetriDish[X, Y].DrawAt(CellLocationToImageLocation(new Point(X, Y)), PetriDishPictureBox.Image.Width / PetriDish.GetLength(0), (Bitmap)PetriDishPictureBox.Image);
                }
            }
            PetriDishPictureBox.Invalidate();
        }

        private void MainKeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Enter)
            {
                if (UpdateTimer.Enabled)
                {
                    UpdateTimer.Stop();
                }
                else
                {
                    UpdateTimer.Start();
                }
            }
            else if (e.KeyCode == Keys.Space)
            {
                UpdatePetriDish(sender, e);
            }
        }

        public Point CellLocationToImageLocation(Point CellLocation)
        {
            Point ImageLocation = new Point();
            ImageLocation.X = (int)((float)CellLocation.X * ( (float)PetriDishPictureBox.Image.Width / (float) PetriDish.GetLength(0) ) );
            ImageLocation.Y = (int)((float)CellLocation.Y * ((float)PetriDishPictureBox.Image.Height / (float)PetriDish.GetLength(1)));
            return ImageLocation;
        }
        public Point ImageLocationToCellLocation(Point ImageLocation)
        {
            Point CellLocation = new Point();
            CellLocation.X = (int)((float)ImageLocation.X * ((float)PetriDish.GetLength(0) / (float)PetriDishPictureBox.Image.Width));
            CellLocation.Y = (int)((float)ImageLocation.Y * ((float)PetriDish.GetLength(1) / (float)PetriDishPictureBox.Image.Height));
            return CellLocation;
        }

        private void PetriDishMouseDown(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Left)
            {
                bMouseDown = true;
                bMouseDownSetAlive = true;
                if (UpdateTimer.Enabled)
                {
                    UpdateTimerPausedByMouseDown = true;
                    UpdateTimer.Stop();
                }

                int MouseX = e.X;
                int MouseY = e.Y;
                int RealX = (int)Math.Floor((float)PetriDishPictureBox.Image.Width * (float)(MouseX) / (float)PetriDishPictureBox.Width);
                int RealY = (int)Math.Floor((float)PetriDishPictureBox.Image.Height * (float)(MouseY) / (float)PetriDishPictureBox.Height);
                Point CellLocation = ImageLocationToCellLocation(new Point(RealX, RealY));
                Cell Toggle = GetCell(CellLocation.X, CellLocation.Y);
                if (Toggle != null)
                {
                    bMouseDownSetAlive = !Toggle.Alive;
                    Toggle.Alive = !Toggle.Alive;
                    Point RealLocation = CellLocationToImageLocation(CellLocation);
                    Toggle.DrawAt(RealLocation, PetriDishPictureBox.Image.Width / PetriDish.GetLength(0), (Bitmap)PetriDishPictureBox.Image);
                    PetriDishPictureBox.Invalidate();
                }
            }
            else if (e.Button == MouseButtons.Right)
            {
                UpdatePetriDish(sender, e);
            }
        }

        private void PetriDishMouseUp(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Left)
            {
                bMouseDown = false;

                if (UpdateTimerPausedByMouseDown)
                {
                    UpdateTimer.Start();
                    UpdateTimerPausedByMouseDown = false;
                }
            }
        }

        private void PetriDishMouseMove(object sender, MouseEventArgs e)
        {
            if (bMouseDown)
            {
                int MouseX = e.X;
                int MouseY = e.Y;
                int RealX = (int)Math.Floor((float)PetriDishPictureBox.Image.Width * (float)(MouseX) / (float)PetriDishPictureBox.Width);
                int RealY = (int)Math.Floor((float)PetriDishPictureBox.Image.Height * (float)(MouseY) / (float)PetriDishPictureBox.Height);
                Point CellLocation = ImageLocationToCellLocation(new Point(RealX, RealY));
                Cell Toggle = GetCell(CellLocation.X, CellLocation.Y);
                if (Toggle != null && Toggle.Alive != bMouseDownSetAlive)
                {
                    Toggle.Alive = bMouseDownSetAlive;
                    Point RealLocation = CellLocationToImageLocation(CellLocation);
                    Toggle.DrawAt(RealLocation, PetriDishPictureBox.Image.Width / PetriDish.GetLength(0), (Bitmap)PetriDishPictureBox.Image);
                    PetriDishPictureBox.Invalidate();
                }
            }
        }
    }
}
