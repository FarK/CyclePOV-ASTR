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
        private int[,,] _matrix;
        private int _leds;
        private int _numRadios;
        public frmMatrix(int [,,] matrix, int leds, int numRadios )
        {
            InitializeComponent();

            _matrix = matrix;
            _leds = leds;
            _numRadios = numRadios;

            //Rellenamos la lista de puertos
            foreach (string port in System.IO.Ports.SerialPort.GetPortNames())
                portsListCB.Items.Add(port);

        }

        private void frmMatrix_Load(object sender, EventArgs e)
        {
            string str = string.Format("#DEFINE NUMRADIOS {0}\r\n", _numRadios);
            str += string.Format("#DEFINE LEDSXRADIO {0}\r\n", _leds / 2);
            str += string.Format("#DEFINE RESOLUTIONLED {0}\r\n\r\n", _leds);

            str += string.Format("uint8_t matrix[NUMRADIOS][RESOLUTIONLED][3] = {{\r\n", _numRadios, _leds);
            int red = 0, green = 0, blue = 0;

            for (int r = 0; r < _numRadios; r++)
            {
                str += "\t{\r\n\t\t";
                for (int l = 0; l < _leds; l++)
                {
                    str += "{";
                    red = _matrix[r,l,0];
                    green = _matrix[r,l,1];
                    blue = _matrix[r,l,2];
                    str += string.Format("{0},{1},{2}", red, green, blue);
                    str += "},";

                    if (l % 5 == 0 && l != 0)
                        str += "\r\n\t\t";
                }

                str = str.Substring(0,str.Length - 1);
                str += "\r\n\t},\r\n";
            }

            
            str = str.Substring(0, str.Length - 3);

            str += "\r\n};";

            textBox1.Text = str;

        }

        private void sendBT_Click(object sender, EventArgs e)
        {
            //Configure and open serial port
            if (serialPort.IsOpen) serialPort.Close();
            serialPort.PortName = (string)portsListCB.SelectedItem;
            serialPort.BaudRate = 4800;
            serialPort.Open();

            byte[] buff = {0};

            for (int i = 0; i < _matrix.GetLength(0); i++)
                for (int j = 0; j < _matrix.GetLength(1); j++)
                    for (int k = 0; k < _matrix.GetLength(2); k++){
                        buff[0] = (byte)_matrix[i,j,k];
                        serialPort.Write(buff, 0, 1);
                    }
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
