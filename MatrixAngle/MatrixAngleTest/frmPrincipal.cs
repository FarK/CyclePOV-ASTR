using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using MatrixAngleTest.Properties;
using System.Drawing.Drawing2D;
using System.IO;

namespace MatrixAngleTest
{
    public partial class frmPrincipal : Form
    {
        private Dictionary<float, Image> _images = new Dictionary<float, Image>();
        private Timer _wheelTimer = new Timer();
        private float radio = 0;
        private string _imagePath;
        private int[,,] _matrix;
        private int _imageWidth = 0;
        private int _imageHeight = 0;
        Graphics backbufferContext;
        Graphics pictureboxContext;
        Bitmap backbuffer;
        private int _numleds;
        private double cx = -1;
        private double cy = -1;
        private bool _binarize = false;
        private bool _interpolated = true;

        public frmPrincipal()
        {
            InitializeComponent();
        }


        private void frmPrincipal_Load(object sender, EventArgs e)
        {
            //pictureBox1.Image = Resources.bike_wheel;
            //_imageWidth = Resources.bike_wheel.Width;
            //_imageHeight = Resources.bike_wheel.Height;


            backbuffer = new Bitmap(pictureBox1.Width, pictureBox1.Height);
            backbufferContext = Graphics.FromImage(backbuffer);
            backbufferContext.Clear(Color.White);
            pictureboxContext = pictureBox1.CreateGraphics();

            _wheelTimer.Interval = 1;
            _wheelTimer.Tick += new EventHandler(_wheelTimer_Tick);
            _wheelTimer.Enabled = true;

            _numleds = (int)numLeds.Value;

            //inicio
            _imagePath = "C:\\Users\\David\\Pictures\\2048px-User_Jette_awesome.svg.png";
            LoadImageList();
        }

        void _wheelTimer_Tick(object sender, EventArgs e)
        {
            radio = (radio + 1) % (int)numRadios.Value;

            if (_matrix != null)
            {
                DrawLeds(backbufferContext);
                pictureboxContext.DrawImage(backbuffer, new Point(0, 0));
            }
           
        }

        /// <summary>
        /// method to rotate an image either clockwise or counter-clockwise
        /// </summary>
        /// <param name="img">the image to be rotated</param>
        /// <param name="rotationAngle">the angle (in degrees).
        /// NOTE: 
        /// Positive values will rotate clockwise
        /// negative values will rotate counter-clockwise
        /// </param>
        /// <returns></returns>
        public Image RotateImage(Image img, float rotationAngle)
        {


            //create an empty Bitmap image
            Bitmap bmp = new Bitmap(img.Width, img.Height);

            //turn the Bitmap into a Graphics object
            Graphics gfx = Graphics.FromImage(bmp);

            //now we set the rotation point to the center of our image
            gfx.TranslateTransform((float)bmp.Width / 2, (float)bmp.Height / 2);

            //now rotate the image
            gfx.RotateTransform(rotationAngle);

            gfx.TranslateTransform(-(float)bmp.Width / 2, -(float)bmp.Height / 2);

            //set the InterpolationMode to HighQualityBicubic so to ensure a high
            //quality image once it is transformed to the specified size
            //gfx.InterpolationMode = InterpolationMode.HighQualityBicubic;

            //now draw our new image onto the graphics object
            gfx.DrawImage(img, new Rectangle(0, 0, img.Width, img.Height));

            //dispose of our Graphics object
            gfx.Dispose();

            if (!System.IO.Directory.Exists("images"))
                System.IO.Directory.CreateDirectory("images");

            bmp.Save("images/wheel" + rotationAngle.ToString() + ".png");

            //return the image
            return bmp;
        }

        private void abrirImagenToolStripMenuItem_Click(object sender, EventArgs e)
        {

            DialogResult r = openFileDialog1.ShowDialog();

            if (r == System.Windows.Forms.DialogResult.OK)
            {
                try
                {
                    _imagePath = openFileDialog1.FileName;
                    OpenImage();
                }
                catch(Exception ex )
                {
                }
            }

        }

        private void OpenImage()
        {
            if (_imagePath != null)
            {
                Bitmap img = GetImage();

                Add2ImageList(img);

                //escribimos a ficheros la lista de imagenes
                SaveImageList();



                _imageWidth = img.Width;
                _imageHeight = img.Height;
                pictureBox2.Image = img;


                _matrix = GetMatrix(img, 1, (int)numRadios.Value,
                                   _numleds, (int)pixelsDistance.Value, (int)this.ignorarCentro.Value);
            }
        }

        private void Add2ImageList(Bitmap img)
        {
            imageList1.Images.Add(img);
            ListViewItem lvi = new ListViewItem();
            lvi.ImageIndex = imageList1.Images.Count - 1;
            lvi.Tag = _imagePath;
            listView1.Items.Add(lvi);
        }

        private Bitmap GetImage()
        {
            Bitmap img = new Bitmap(_imagePath);

            img = (Bitmap)ResizeImage(img);

            if (_binarize)
            {
                img = BradleyAdaptiveThresholding.Process(img);
            }
            return img;
        }

        private void SaveImageList()
        {
            Application.DoEvents();
            StreamWriter sw = new StreamWriter("imagelist.txt");
            foreach (ListViewItem lvi in listView1.Items)
            {
                sw.WriteLine(lvi.Tag);
            }
            sw.Close();
        }

        private void LoadImageList()
        {
            StreamReader sr = new StreamReader("imagelist.txt");
            string line = sr.ReadLine();

            while (line != null)
            {
                _imagePath = line;
                Bitmap img = GetImage();
                Add2ImageList(img);

                line = sr.ReadLine();
            }
        }


        private void ReloadImage()
        {
            if (_imagePath != null)
            {
                Bitmap img = GetImage();
                
                _imageWidth = img.Width;
                _imageHeight = img.Height;
                pictureBox2.Image = img;

                
                _matrix = GetMatrix(img, 1, (int)numRadios.Value,
                                   _numleds, (int)pixelsDistance.Value, (int)this.ignorarCentro.Value);
            }
        }

        public Image ResizeImage(Image img)
        {
            int w = img.Width;
            int h = img.Height;
            

            float f = img.Width < img.Height ?
                (float)((float)_numleds*2 / img.Width) : (float)((float)_numleds*2 / img.Height);
                    


            return ResizeImage(img, (int)(w * f), (int)(h * f));
        }


        public Image ResizeImage(Image img, int width, int height)
        {
            //create an empty Bitmap image
            Bitmap bmp = new Bitmap(width, height);

            //turn the Bitmap into a Graphics object
            Graphics gfx = Graphics.FromImage(bmp);


            //gfx.ScaleTransform((float)width, (float)height);
            //now rotate the image
            
            //set the InterpolationMode to HighQualityBicubic so to ensure a high
            //quality image once it is transformed to the specified size
            gfx.SmoothingMode = SmoothingMode.HighQuality;
            gfx.InterpolationMode = InterpolationMode.HighQualityBicubic;
            gfx.PixelOffsetMode = PixelOffsetMode.HighQuality;

            //now draw our new image onto the graphics object
            gfx.DrawImage(img, new Rectangle(0, 0, width, height));

            //dispose of our Graphics object
            gfx.Dispose();

        
            //return the image
            return bmp;
        }

        public int[,,] GetMatrix(Image img, int numTiras, int numRadios, int numLeds, int ledsOffset, int percentCenterIgnore)
        {
            int[, ,] m = new int[numRadios, numLeds, 3];

            try
            {
                float pci = percentCenterIgnore / 100f;
                if (cx < 0)
                {
                    cx = img.Width / 2;
                    cy = img.Height / 2;
                }
                int minSize = Math.Min(img.Width, img.Height);
                int start = (int)(pci * (float)minSize);

                int ledsxradio = numLeds;
                float grade = 0;
                float radiooffset = (float)360 / numRadios;
                float tiraoffset = (float)numRadios / numTiras;

                int radio = 0;
                int r = 0;
                while (radio < numRadios)
                {
                    for (int i = 0; i < numTiras; i++)
                    {
                        r = (int)(radio + (tiraoffset * i));
                        grade = (r * radiooffset);

                        for (int l = 0; l < ledsxradio; l++)
                        {
                            int p = start + l * ledsOffset;
                            double x = p * Math.Cos(DegreeToRadian(grade)) + cx;
                            double y = p * -Math.Sin(DegreeToRadian(grade)) + cy;
                            x = Math.Round(x);
                            y = Math.Round(y);

                            int red;
                            int green;
                            int blue;
                            GetInterpolationColor(img, x, y, out red, out green, out blue);

                            int index = l + (ledsxradio * i);
                            m[radio, index, 0] = red;
                            m[radio, index, 1] = green;
                            m[radio, index, 2] = blue;
                        }
                    }

                    radio++;
                }
            }
            catch (Exception ex)
            {
            }

            return m;
        }

        private static void GetInterpolationColor(Image img, double x, double y, out int red, out int green, out int blue)
        {

            float[,] cm = new float[,] 
                        { 
                            {0, 1, 1, 1, 0},
                            {1, 2, 4, 3, 1},
                            {2, 4, 5, 4, 2},
                            {1, 2, 4, 3, 1},
                            {0, 1, 1, 1, 0}
                        };

            float sum = 0;
            int i = 0, j = 0;
            for (i = 0; i < 5; i++)
                for (j = 0; j < 5; j++)
                    sum += cm[i, j];


            int count = 0;
            red = 0; green = 0; blue = 0;
            x -= 2; y -= 2;
            i = -2; 
            for (; i < 3; i++)
            {
                j = -2;
                for (; j < 3; j++)
                {
                    if (x + i >= 0 && x + i < img.Width &&
                        y + j >= 0 && y + j < img.Height)
                    {
                        Color c = ((Bitmap)img).GetPixel((int)x + i, (int)y + j);

                        float f = ((float)cm[i+2, j+2] / sum);
                        red += (int)((float)c.R * f);
                        green += (int)((float)c.G * f);
                        blue += (int)((float)c.B * f);

                    }
                }

            }
            if (red == 0 && green == 0 && blue == 0)
                red = red;



        }

        private double DegreeToRadian(double angle)
        {
            return Math.PI * angle / 180.0;
        }

      
        private void DrawLeds(Graphics g)
        {
            if (_matrix != null)
            {
                float pci = (int)ignorarCentro.Value / 100f;
                int minSize = Math.Min(_imageWidth, _imageHeight);
                int start = (int)(pci * (float)minSize);

                int separacion = 5;
                double cx = pictureBox1.Width / 2;
                double cy = pictureBox1.Height / 2;
                
                int leds = (int)(_numleds);
                float angleOffset = (float)360 / (int)numRadios.Value;
                float ledxradio = (float)_numleds;
                int l = 0;
                int radio = 0;

                float firstangle = angleOffset * this.radio;
                float radios90grades = (int)numRadios.Value / 4;

                for( int i = 0; i < 4; i++)
                {
                    float angle = (firstangle + (angleOffset * 3* radios90grades * i));
                    radio = (int)(this.radio + (3* radios90grades * i)) % (int)numRadios.Value;


                    for (int j = 0; j < (int)ledxradio; j++)
                    {
                        if ( (j+i) % 2 == 0)
                        {
                            l = j;
                            double x = separacion * j * Math.Cos(DegreeToRadian(angle)) + cx;
                            double y = separacion * j * -Math.Sin(DegreeToRadian(angle)) + cy;
                            double startx = start * Math.Cos(DegreeToRadian(angle));
                            double starty = start * -Math.Sin(DegreeToRadian(angle));

                            int red = _matrix[(int)radio, l, 0];
                            int green = _matrix[(int)radio, l, 1];
                            int blue = _matrix[(int)radio, l, 2];

                            Color c = Color.FromArgb(red, green, blue);
                            Brush brush = new System.Drawing.SolidBrush(c);
                            g.FillEllipse(brush, new Rectangle((int)(x + startx), (int)(y + starty), separacion, separacion));
                        }
                    }
                }

            }
        }


        private void pixelsDistance_ValueChanged(object sender, EventArgs e)
        {
            backbufferContext.Clear(Color.White);
            ReloadImage();
        }

        private void ignorarCentro_ValueChanged(object sender, EventArgs e)
        {
            backbufferContext.Clear(Color.White);
            ReloadImage();
        }

        private void numLeds_ValueChanged(object sender, EventArgs e)
        {
            _numleds = (int)numLeds.Value * (int)1;
            backbufferContext.Clear(Color.White);
            ReloadImage();
        }

        private void numTiras_ValueChanged(object sender, EventArgs e)
        {
            _numleds = (int)numLeds.Value * (int)1;
            backbufferContext.Clear(Color.White);
            ReloadImage();
        }

        private void numRadios_ValueChanged(object sender, EventArgs e)
        {
            backbufferContext.Clear(Color.White);
            ReloadImage();
        }

        private void matrizToolStripMenuItem_Click(object sender, EventArgs e)
        {
            int[, ,] matrix = ReduceMatrix(_matrix);
            frmMatrix frmM = new frmMatrix(matrix, (int)_numleds, (int)numRadios.Value);
            frmM.ShowDialog();
        }

        private int[, ,] ReduceMatrix(int[, ,] _matrix)
        {
            int numradios = (int)numRadios.Value;
            int totalleds = (int)numLeds.Value;
            int ledsxtira = totalleds;
            int[, ,] m = new int[numradios, totalleds, 3];
            int rsource = 0;

            if (_matrix != null)
            {
                float pci = (int)ignorarCentro.Value / 100f;
                int minSize = Math.Min(_imageWidth, _imageHeight);
                int start = (int)(pci * (float)minSize);

                int separacion = 5;
                double cx = pictureBox1.Width / 2;
                double cy = pictureBox1.Height / 2;

                int leds = (int)(_numleds);
                float angleOffset = (float)360 / (int)numRadios.Value;
                float ledxradio = (float)_numleds;
                int l = 0;
                int radio = 0;

                for (int r = 0; r < numradios; r++)
                {
                    float firstangle = angleOffset * r;
                    float radios90grades = (int)numRadios.Value / 4;
                    l = 0;

                    for (int i = 0; i < 2; i++)
                    {
                        
                        float angle = (firstangle + (angleOffset * 3 * radios90grades * i));
                        radio = (int)(r + (3 * radios90grades * i)) % (int)numRadios.Value;

                        for (int j = 0; j < (int)ledxradio; j++)
                        {
                            if ((j + i) % 2 == 0)
                            {
                   
                                double x = separacion * j * Math.Cos(DegreeToRadian(angle)) + cx;
                                double y = separacion * j * -Math.Sin(DegreeToRadian(angle)) + cy;
                                double startx = start * Math.Cos(DegreeToRadian(angle));
                                double starty = start * -Math.Sin(DegreeToRadian(angle));

                                int red = _matrix[(int)radio, j, 0];
                                int green = _matrix[(int)radio, j, 1];
                                int blue = _matrix[(int)radio, j, 2];

                                m[r, l, 0] = red;
                                m[r, l, 1] = green;
                                m[r, l++, 2] = blue;
                            }
                        }
                    }

                }

            }
            //for (int r = 0; r < numradios; r++)
            //{
            //    int numTira = 0;
            //    int ledindex = 0;
            //    rsource = r;
            //    for (int l = 0; l < totalleds; l++ )
            //    {
            //        if (l != 0 && l % ledsxtira == 0)
            //        {
            //            numTira++;
            //            rsource -= (numradios / 4) - 1;
            //            if (rsource < 0)
            //            {
            //                rsource = numradios - rsource;
            //            }
            //            rsource %= (numradios - 1);

            //        }

            //        int led = l % ledsxtira;
            //        if ((led + numTira) % 2 == 0)
            //        {
            //            m[r, ledindex,0] = _matrix[rsource, l,0];
            //            m[r, ledindex, 1] = _matrix[rsource, l, 1];
            //            m[r, ledindex++, 2] = _matrix[rsource, l, 2];
            //        }
                   
            //    }
            //}

            return m;
        }

        private void trackBar1_Scroll(object sender, EventArgs e)
        {
            radio = 0;
            backbufferContext.Clear(Color.White);
            _wheelTimer.Interval = trackBar1.Value;
        }

        private void pictureBox2_Click(object sender, EventArgs e)
        {
            
        }

        private void pictureBox2_MouseDown(object sender, MouseEventArgs e)
        {
            double fx = (double)_imageWidth / pictureBox2.Width;
            double fy = (double)_imageHeight / pictureBox2.Height;
            cx = e.X * fx;
            cy = e.Y * fy;
            ReloadImage();
        }

        private void listView1_SelectedIndexChanged(object sender, EventArgs e)
        {
            foreach (ListViewItem item in listView1.SelectedItems)
            {
                _imagePath = (string)item.Tag;
                ReloadImage();
                break;
            }
        }

        private void listView1_MouseClick(object sender, MouseEventArgs e)
        {
            if (e.Button == System.Windows.Forms.MouseButtons.Right)
            {
                cm_Eliminar.Show(Cursor.Position);
            }
        }

        private void eliminarToolStripMenuItem_Click(object sender, EventArgs e)
        {
            
            foreach (ListViewItem item in listView1.SelectedItems)
            {
                listView1.Items.Remove(item);
                break;
            }

            SaveImageList();
        }


        
    }
}
