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
        private bool _binarize = true;

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

            _numleds = (int)numLeds.Value * (int)numTiras.Value;

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
        public static Image RotateImage(Image img, float rotationAngle)
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
                    ReloadImage();
                }
                catch(Exception ex )
                {
                }
            }

        }

        private void ReloadImage()
        {
            if (_imagePath != null)
            {
                Bitmap img = new Bitmap(_imagePath);
               
                img = (Bitmap)ResizeImage(img);

                if (_binarize)
                {
                    img = BradleyAdaptiveThresholding.Process(img);
                }

                _imageWidth = img.Width;
                _imageHeight = img.Height;
                pictureBox2.Image = img;

                
                _matrix = GetMatrix(img, (int)numTiras.Value, (int)numRadios.Value,
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

        
             if (!System.IO.Directory.Exists("images"))
                System.IO.Directory.CreateDirectory("images");

             bmp.Save("images/img" + this.numLeds.Value.ToString() + ".png");

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

                int ledsxtira = numLeds / numTiras;

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

                        for (int l = 0; l < ledsxtira; l++)
                        {
                            int red = 0;
                            int green = 0;
                            int blue = 0;

                            //interpolacion
                            for (int j = -ledsOffset/2 + 1; j <= ledsOffset/2; j++)
                            {
                                int p = start + l * ledsOffset + j;
                                double x = p * Math.Sin(DegreeToRadian(grade)) + cx;
                                double y = p * Math.Cos(DegreeToRadian(grade)) + cy;

                                if (x > 0 && x < img.Width && y < img.Height && y > 0)
                                {
                                    Color c = ((Bitmap)img).GetPixel((int)x, (int)y);

                                    red += c.R;
                                    green += c.G;
                                    blue += c.B;
                                }
                            }

                            int index = l + (ledsxtira * i);
                            m[radio, index, 0] = red / ledsOffset;
                            m[radio, index, 1] = green / ledsOffset;
                            m[radio, index, 2] = blue / ledsOffset;
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
                
                int leds = (int)(_numleds / numTiras.Value);
                float angleOffset = (float)360 / (int)numRadios.Value;
                float tiraOffset = (float)360 / (float)numTiras.Value;
                float ledsxtira = (float)_numleds / (float)numTiras.Value;
                int l = 0;
                int tiras = (int)numTiras.Value;

                float firstangle = angleOffset * radio;
                for( int i = 0; i < numTiras.Value; i++)
                {
                    float angle = (firstangle + (tiraOffset * (float)i));

                    int startled = (int)(ledsxtira * i);

                    for (int j = 0; j < (int)ledsxtira; j++)
                    {
                        if ( (j+i) % tiras == 0)
                        {
                            l = startled + j;
                            double x = separacion * j * Math.Sin(DegreeToRadian(angle)) + cx;
                            double y = separacion * j * Math.Cos(DegreeToRadian(angle)) + cy;
                            double startx = start * Math.Sin(DegreeToRadian(angle));
                            double starty = start * Math.Cos(DegreeToRadian(angle));


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
            _numleds = (int)numLeds.Value * (int)numTiras.Value;
            backbufferContext.Clear(Color.White);
            ReloadImage();
        }

        private void numTiras_ValueChanged(object sender, EventArgs e)
        {
            _numleds = (int)numLeds.Value * (int)numTiras.Value;
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
            frmMatrix frmM = new frmMatrix(matrix, (int)_numleds / 2, (int)numRadios.Value);
            frmM.ShowDialog();
        }

        private int[, ,] ReduceMatrix(int[, ,] _matrix)
        {
            int numradios = (int)numRadios.Value;
            int totalleds = (int)numLeds.Value *  2;
            int tiras = (int)numTiras.Value;
            int ledsxtira = totalleds / tiras;
            int[, ,] m = new int[numradios, totalleds / 2, 3];

            for (int r = 0; r < numradios; r++)
            {
                int numTira = 0;
                int ledindex = 0;
                for (int l = 0; l < totalleds; l++ )
                {
                    if (l != 0 && l % ledsxtira == 0)
                        numTira++;

                    int led = l % ledsxtira;
                    if ((led + numTira) % tiras == 0)
                    {
                        m[r, ledindex,0] = _matrix[r, l,0];
                        m[r, ledindex, 1] = _matrix[r, l, 1];
                        m[r, ledindex++, 2] = _matrix[r, l, 2];
                    }
                   
                }
            }

            return m;
        }

        private void trackBar1_Scroll(object sender, EventArgs e)
        {
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


        
    }
}
