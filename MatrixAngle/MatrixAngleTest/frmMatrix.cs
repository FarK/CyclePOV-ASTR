using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace MatrixAngleTest
{
    public partial class frmMatrix : Form
    {
        private List<int[,,]> _lmatrix;
        private int _leds;
        private int _numRadios;
        private int[] _startAnimationIndex;
        private int[] _animationDuration;
        public frmMatrix(List<int [,,]> lmatrix, int[] startAnimationIndex, int[] animationDuration, int leds, int numRadios )
        {
            InitializeComponent();

            _lmatrix = lmatrix;
            _startAnimationIndex = startAnimationIndex;
            _animationDuration = animationDuration;
            _leds = leds;
            _numRadios = numRadios;

            //Rellenamos la lista de puertos
            foreach (string port in System.IO.Ports.SerialPort.GetPortNames())
                portsListCB.Items.Add(port);

        }

        private void frmMatrix_Load(object sender, EventArgs e)
        {
            StringBuilder sb = new StringBuilder();


            sb.Append("#define NUM_IMAGES ");
            sb.Append(_lmatrix.Count);
            sb.Append("\r\n");
            sb.Append("#define NUM_ANIMATIONS ");
            sb.Append(_startAnimationIndex.Length);
            sb.Append("\r\n\r\n");

            //Animation start index array
            sb.Append("const CPU_INT16U animationIndex[NUM_ANIMATIONS] {");
            foreach (int index in _startAnimationIndex)
            {
                sb.Append(index.ToString());
                sb.Append(",");
            }
            sb.Remove(sb.Length - 1, 1);
            sb.Append("}");

            //Animation duration array
            sb.Append("const CPU_INT16U animationDuration[NUM_ANIMATIONS] {");
            foreach (int duration in _animationDuration)
            {
                sb.Append(duration.ToString());
                sb.Append(",");
            }
            sb.Remove(sb.Length - 1, 1);
            sb.Append("}");

            //Matrices
            sb.Append(string.Format("const CPU_INT08U images[NUM_IMAGES][NUM_SPOKES][NUM_LEDS][3] = {{\r\n", _numRadios, _leds));
            int red = 0, green = 0, blue = 0;

            foreach (int[, ,] matrix in _lmatrix)
            {
                sb.Append("{\r\n");

                for (int r = 0; r < _numRadios; r++)
                {
                    sb.Append("\t{\r\n\t\t");
                    for (int l = 0; l < _leds; l++)
                    {
                        sb.Append("{");
                        red = matrix[r, l, 0];
                        green = matrix[r, l, 1];
                        blue = matrix[r, l, 2];
                        sb.Append(string.Format("{0},{1},{2}", green, red, blue));
                        sb.Append("},");

                        if (l % 5 == 0 && l != 0)
                            sb.Append("\r\n\t\t");
                    }

                    sb.Remove(sb.Length - 1, 1);
                    sb.Append("\r\n\t},\r\n");
                }


                sb.Remove(sb.Length - 3, 3);

                sb.Append("\r\n},");
            }

            sb.Remove(sb.Length - 1, 1);
            sb.Append("};");

            ////////////////////////////////////////////////////////////////
            ////// LISTA DE BYTES 
            ////////////////////////////////////////////////////////////////
            //sb.Append("\r\n\r\n\r\n\r\n\r\n\r\n";
            //for (int r = 0; r < _numRadios; r++)
            //{
            //    for (int l = 0; l < _leds; l++)
            //    {
            //        red = _matrix[r, l, 0];
            //        green = _matrix[r, l, 1];
            //        blue = _matrix[r, l, 2];
            //        sb.Append(string.Format("{0} {1} {2} ", green, red, blue);
            //    }
            //}
            //str = str.Substring(0, str.Length - 1);

            textBox1.Text = sb.ToString();

        }

        private void sendBT_Click(object sender, EventArgs e)
        {
            //Configure and open serial port
            if (serialPort.IsOpen) serialPort.Close();
            serialPort.PortName = (string)portsListCB.SelectedItem;
            serialPort.BaudRate = 2400;
            serialPort.Open();

            byte[] buff = {0};

            byte[] aux = new byte[] { 6, 6, 6, (byte)_numRadios, (byte)_leds };
            int i = 0;

            //for( byte b = 0; b <= (byte)255; b++)
            //    serialPort.Write(new byte[] { b }, 0, 1);

            while (i < aux.Length)
            {
                serialPort.Write(new byte[] { aux[i] }, 0, 1);
                //System.Threading.Thread.Sleep(40);
                i++;
            }
            

            for (i = 0; i < _numRadios; i++)
                for (int j = 0; j < _leds; j++)
                    for (int k = 0; k < 3; k++){
                        buff[0] = (byte)_lmatrix[0][i,j,k];
                        serialPort.Write(buff, 0, 1);
                        //System.Threading.Thread.Sleep(40);
                    }

            serialPort.Close();
        }

        private void updateCB(object sender, EventArgs e)
        {
            //Rellenamos la lista de puertos
            portsListCB.Items.Clear();
            foreach (string port in System.IO.Ports.SerialPort.GetPortNames())
                portsListCB.Items.Add(port);
        }

    }
}
