namespace MatrixAngleTest
{
    partial class frmMatrix
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.textBox1 = new System.Windows.Forms.TextBox();
            this.sendBT = new System.Windows.Forms.Button();
            this.portsListCB = new System.Windows.Forms.ComboBox();
            this.serialPort = new System.IO.Ports.SerialPort(this.components);
            this.SuspendLayout();
            // 
            // textBox1
            // 
            this.textBox1.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.textBox1.Location = new System.Drawing.Point(0, 0);
            this.textBox1.Multiline = true;
            this.textBox1.Name = "textBox1";
            this.textBox1.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.textBox1.Size = new System.Drawing.Size(622, 346);
            this.textBox1.TabIndex = 0;
            // 
            // sendBT
            // 
            this.sendBT.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.sendBT.Location = new System.Drawing.Point(535, 352);
            this.sendBT.Name = "sendBT";
            this.sendBT.Size = new System.Drawing.Size(75, 23);
            this.sendBT.TabIndex = 1;
            this.sendBT.Text = "Enviar";
            this.sendBT.UseVisualStyleBackColor = true;
            this.sendBT.Visible = false;
            this.sendBT.Click += new System.EventHandler(this.sendBT_Click);
            // 
            // portsListCB
            // 
            this.portsListCB.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.portsListCB.FormattingEnabled = true;
            this.portsListCB.Location = new System.Drawing.Point(408, 352);
            this.portsListCB.Name = "portsListCB";
            this.portsListCB.Size = new System.Drawing.Size(121, 21);
            this.portsListCB.TabIndex = 2;
            this.portsListCB.Visible = false;
            this.portsListCB.DropDown += new System.EventHandler(this.updateCB);
            // 
            // serialPort
            // 
            this.serialPort.BaudRate = 4800;
            // 
            // frmMatrix
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(622, 375);
            this.Controls.Add(this.portsListCB);
            this.Controls.Add(this.sendBT);
            this.Controls.Add(this.textBox1);
            this.Name = "frmMatrix";
            this.Text = "frmMatrix";
            this.Load += new System.EventHandler(this.frmMatrix_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox textBox1;
        private System.Windows.Forms.Button sendBT;
        private System.Windows.Forms.ComboBox portsListCB;
        private System.IO.Ports.SerialPort serialPort;
    }
}