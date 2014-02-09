﻿namespace MatrixAngleTest
{
    partial class frmPrincipal
    {
        /// <summary>
        /// Variable del diseñador requerida.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Limpiar los recursos que se estén utilizando.
        /// </summary>
        /// <param name="disposing">true si los recursos administrados se deben eliminar; false en caso contrario, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Código generado por el Diseñador de Windows Forms

        /// <summary>
        /// Método necesario para admitir el Diseñador. No se puede modificar
        /// el contenido del método con el editor de código.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.abrirImagenToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.matrizToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.openFileDialog1 = new System.Windows.Forms.OpenFileDialog();
            this.label1 = new System.Windows.Forms.Label();
            this.numLeds = new System.Windows.Forms.NumericUpDown();
            this.numRadios = new System.Windows.Forms.NumericUpDown();
            this.label3 = new System.Windows.Forms.Label();
            this.pixelsDistance = new System.Windows.Forms.NumericUpDown();
            this.label4 = new System.Windows.Forms.Label();
            this.ignorarCentro = new System.Windows.Forms.NumericUpDown();
            this.label5 = new System.Windows.Forms.Label();
            this.pictureBox2 = new System.Windows.Forms.PictureBox();
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.trackBar1 = new System.Windows.Forms.TrackBar();
            this.imageList1 = new System.Windows.Forms.ImageList(this.components);
            this.listView1 = new System.Windows.Forms.ListView();
            this.cm_Eliminar = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.eliminarToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.menuStrip1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numLeds)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numRadios)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pixelsDistance)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.ignorarCentro)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox2)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackBar1)).BeginInit();
            this.cm_Eliminar.SuspendLayout();
            this.SuspendLayout();
            // 
            // menuStrip1
            // 
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.abrirImagenToolStripMenuItem,
            this.matrizToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(1064, 24);
            this.menuStrip1.TabIndex = 2;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // abrirImagenToolStripMenuItem
            // 
            this.abrirImagenToolStripMenuItem.Name = "abrirImagenToolStripMenuItem";
            this.abrirImagenToolStripMenuItem.Size = new System.Drawing.Size(88, 20);
            this.abrirImagenToolStripMenuItem.Text = "Abrir imagen";
            this.abrirImagenToolStripMenuItem.Click += new System.EventHandler(this.abrirImagenToolStripMenuItem_Click);
            // 
            // matrizToolStripMenuItem
            // 
            this.matrizToolStripMenuItem.Name = "matrizToolStripMenuItem";
            this.matrizToolStripMenuItem.Size = new System.Drawing.Size(52, 20);
            this.matrizToolStripMenuItem.Text = "Matriz";
            this.matrizToolStripMenuItem.Click += new System.EventHandler(this.matrizToolStripMenuItem_Click);
            // 
            // openFileDialog1
            // 
            this.openFileDialog1.Filter = "PNG|*.png|BMP|*.bmp|JPG|*.jpg|GIF|*.gif";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(193, 376);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(54, 13);
            this.label1.TabIndex = 4;
            this.label1.Text = "Num. leds";
            // 
            // numLeds
            // 
            this.numLeds.Location = new System.Drawing.Point(263, 374);
            this.numLeds.Maximum = new decimal(new int[] {
            200,
            0,
            0,
            0});
            this.numLeds.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.numLeds.Name = "numLeds";
            this.numLeds.Size = new System.Drawing.Size(44, 20);
            this.numLeds.TabIndex = 5;
            this.numLeds.Value = new decimal(new int[] {
            28,
            0,
            0,
            0});
            this.numLeds.ValueChanged += new System.EventHandler(this.numLeds_ValueChanged);
            // 
            // numRadios
            // 
            this.numRadios.Location = new System.Drawing.Point(263, 452);
            this.numRadios.Maximum = new decimal(new int[] {
            500,
            0,
            0,
            0});
            this.numRadios.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.numRadios.Name = "numRadios";
            this.numRadios.Size = new System.Drawing.Size(44, 20);
            this.numRadios.TabIndex = 9;
            this.numRadios.Value = new decimal(new int[] {
            128,
            0,
            0,
            0});
            this.numRadios.ValueChanged += new System.EventHandler(this.numRadios_ValueChanged);
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(193, 454);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(63, 13);
            this.label3.TabIndex = 8;
            this.label3.Text = "Num. radios";
            // 
            // pixelsDistance
            // 
            this.pixelsDistance.Location = new System.Drawing.Point(306, 338);
            this.pixelsDistance.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.pixelsDistance.Name = "pixelsDistance";
            this.pixelsDistance.Size = new System.Drawing.Size(44, 20);
            this.pixelsDistance.TabIndex = 11;
            this.pixelsDistance.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.pixelsDistance.ValueChanged += new System.EventHandler(this.pixelsDistance_ValueChanged);
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(193, 340);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(107, 13);
            this.label4.TabIndex = 10;
            this.label4.Text = "Distancia entre pixels";
            // 
            // ignorarCentro
            // 
            this.ignorarCentro.Location = new System.Drawing.Point(306, 309);
            this.ignorarCentro.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.ignorarCentro.Name = "ignorarCentro";
            this.ignorarCentro.Size = new System.Drawing.Size(44, 20);
            this.ignorarCentro.TabIndex = 13;
            this.ignorarCentro.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.ignorarCentro.ValueChanged += new System.EventHandler(this.ignorarCentro_ValueChanged);
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(193, 311);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(93, 13);
            this.label5.TabIndex = 12;
            this.label5.Text = "Ignorar centro (%) ";
            // 
            // pictureBox2
            // 
            this.pictureBox2.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.pictureBox2.Location = new System.Drawing.Point(194, 27);
            this.pictureBox2.Name = "pictureBox2";
            this.pictureBox2.Size = new System.Drawing.Size(400, 225);
            this.pictureBox2.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.pictureBox2.TabIndex = 3;
            this.pictureBox2.TabStop = false;
            this.pictureBox2.Click += new System.EventHandler(this.pictureBox2_Click);
            this.pictureBox2.MouseDown += new System.Windows.Forms.MouseEventHandler(this.pictureBox2_MouseDown);
            // 
            // pictureBox1
            // 
            this.pictureBox1.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.pictureBox1.Location = new System.Drawing.Point(621, 27);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(431, 404);
            this.pictureBox1.TabIndex = 0;
            this.pictureBox1.TabStop = false;
            // 
            // trackBar1
            // 
            this.trackBar1.Location = new System.Drawing.Point(196, 259);
            this.trackBar1.Maximum = 1000;
            this.trackBar1.Minimum = 1;
            this.trackBar1.Name = "trackBar1";
            this.trackBar1.Size = new System.Drawing.Size(398, 45);
            this.trackBar1.TabIndex = 14;
            this.trackBar1.Value = 1;
            this.trackBar1.Scroll += new System.EventHandler(this.trackBar1_Scroll);
            // 
            // imageList1
            // 
            this.imageList1.ColorDepth = System.Windows.Forms.ColorDepth.Depth8Bit;
            this.imageList1.ImageSize = new System.Drawing.Size(64, 64);
            this.imageList1.TransparentColor = System.Drawing.Color.Transparent;
            // 
            // listView1
            // 
            this.listView1.LargeImageList = this.imageList1;
            this.listView1.Location = new System.Drawing.Point(12, 27);
            this.listView1.Name = "listView1";
            this.listView1.Size = new System.Drawing.Size(176, 466);
            this.listView1.SmallImageList = this.imageList1;
            this.listView1.TabIndex = 15;
            this.listView1.UseCompatibleStateImageBehavior = false;
            this.listView1.SelectedIndexChanged += new System.EventHandler(this.listView1_SelectedIndexChanged);
            this.listView1.MouseClick += new System.Windows.Forms.MouseEventHandler(this.listView1_MouseClick);
            // 
            // cm_Eliminar
            // 
            this.cm_Eliminar.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.eliminarToolStripMenuItem});
            this.cm_Eliminar.Name = "cm_Eliminar";
            this.cm_Eliminar.Size = new System.Drawing.Size(153, 48);
            this.cm_Eliminar.Text = "Eliminar";
            // 
            // eliminarToolStripMenuItem
            // 
            this.eliminarToolStripMenuItem.Name = "eliminarToolStripMenuItem";
            this.eliminarToolStripMenuItem.Size = new System.Drawing.Size(152, 22);
            this.eliminarToolStripMenuItem.Text = "Eliminar";
            this.eliminarToolStripMenuItem.Click += new System.EventHandler(this.eliminarToolStripMenuItem_Click);
            // 
            // frmPrincipal
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1064, 505);
            this.Controls.Add(this.listView1);
            this.Controls.Add(this.trackBar1);
            this.Controls.Add(this.ignorarCentro);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.pixelsDistance);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.numRadios);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.numLeds);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.pictureBox2);
            this.Controls.Add(this.pictureBox1);
            this.Controls.Add(this.menuStrip1);
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "frmPrincipal";
            this.Text = "Wheel leds";
            this.Load += new System.EventHandler(this.frmPrincipal_Load);
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numLeds)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numRadios)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pixelsDistance)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.ignorarCentro)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox2)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackBar1)).EndInit();
            this.cm_Eliminar.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.PictureBox pictureBox1;
        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem abrirImagenToolStripMenuItem;
        private System.Windows.Forms.OpenFileDialog openFileDialog1;
        private System.Windows.Forms.PictureBox pictureBox2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.NumericUpDown numLeds;
        private System.Windows.Forms.NumericUpDown numRadios;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.NumericUpDown pixelsDistance;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.NumericUpDown ignorarCentro;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.ToolStripMenuItem matrizToolStripMenuItem;
        private System.Windows.Forms.TrackBar trackBar1;
        private System.Windows.Forms.ImageList imageList1;
        private System.Windows.Forms.ListView listView1;
        private System.Windows.Forms.ContextMenuStrip cm_Eliminar;
        private System.Windows.Forms.ToolStripMenuItem eliminarToolStripMenuItem;
    }
}

