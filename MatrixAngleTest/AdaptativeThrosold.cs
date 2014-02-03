using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;
using System.Drawing.Imaging;

namespace MatrixAngleTest
{
    public class BradleyAdaptiveThresholding
    {
        public static Bitmap Process(Bitmap image)
        {
            image = ToGray(image);

            int i, j;
            long sum = 0;
            int count = 0;
            int index;
            int x1, y1, x2, y2;
            int S = image.Width / 8;
            float T = 0.15f;
            int s2 = S / 2;
            int w = image.Width;
            int h = image.Height;

            // create the integral image
            long[] integralImg = new long[w * h];

            for (i = 0; i < w; i++)
            {

                // reset this column sum
                sum = 0;

                for (j = 0; j < h; j++)
                {
                    index = j * w + i;

                    //sum += data[i, j, 0];
                    sum += image.GetPixel(i, j).R;
                    if (i == 0)
                        integralImg[index] = sum;
                    else
                        integralImg[index] = integralImg[index - 1] + sum;
                }
            }

            Bitmap bin = new Bitmap(w, h);
            //Emgu.CV.Image<Gray, byte> bin = new Emgu.CV.Image<Gray, byte>(w, h, new Gray(0));
            //byte[, ,] binData = bin.Data;
            // perform thresholding
            for (i = 0; i < w; i++)
            {
                for (j = 0; j < h; j++)
                {
                    index = j * w + i;

                    // set the SxS region
                    x1 = i - s2; x2 = i + s2;
                    y1 = j - s2; y2 = j + s2;

                    // check the border
                    if (x1 < 0) x1 = 0;
                    if (x2 >= w) x2 = w - 1;
                    if (y1 < 0) y1 = 0;
                    if (y2 >= h) y2 = h - 1;

                    count = (x2 - x1) * (y2 - y1);

                    // I(x,y)=s(x2,y2)-s(x1,y2)-s(x2,y1)+s(x1,x1)
                    sum = integralImg[y2 * w + x2] -
                             integralImg[y1 * w + x2] -
                             integralImg[y2 * w + x1] +
                             integralImg[y1 * w + x1];

                    if ((long)(image.GetPixel(i,j).R * count) < (long)(sum * (1.0 - T)))
                        bin.SetPixel(i,j, Color.Black);
                    else
                        bin.SetPixel(i,j, Color.White);

                    //if ((long)(data[i, j, 0] * count) < (long)(sum * (1.0 - T)))
                    //    binData[i, j, 0] = 0;
                    //else
                    //    binData[i, j, 0] = 255;
                }
            }


            return bin;
        }

        public static Bitmap ToGray(Bitmap original)
        {
            //create a blank bitmap the same size as original
            Bitmap newBitmap = new Bitmap(original.Width, original.Height);

            //get a graphics object from the new image
            Graphics g = Graphics.FromImage(newBitmap);

            //create the grayscale ColorMatrix
            ColorMatrix colorMatrix = new ColorMatrix(
               new float[][] 
              {
                 new float[] {.3f, .3f, .3f, 0, 0},
                 new float[] {.59f, .59f, .59f, 0, 0},
                 new float[] {.11f, .11f, .11f, 0, 0},
                 new float[] {0, 0, 0, 1, 0},
                 new float[] {0, 0, 0, 0, 1}
              });

            //create some image attributes
            ImageAttributes attributes = new ImageAttributes();

            //set the color matrix attribute
            attributes.SetColorMatrix(colorMatrix);

            //draw the original image on the new image
            //using the grayscale color matrix
            g.DrawImage(original, new Rectangle(0, 0, original.Width, original.Height),
               0, 0, original.Width, original.Height, GraphicsUnit.Pixel, attributes);

            //dispose the Graphics object
            g.Dispose();
            return newBitmap;
        }
    }

    
}
