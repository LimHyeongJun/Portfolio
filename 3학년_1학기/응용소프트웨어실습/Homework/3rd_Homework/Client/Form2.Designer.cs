namespace Client {
    partial class Form2 {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing) {
            if (disposing && (components != null)) {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent() {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form2));
            this.toolStrip1 = new System.Windows.Forms.ToolStrip();
            this.penMenuBar = new System.Windows.Forms.ToolStripDropDownButton();
            this.pencilButton = new System.Windows.Forms.ToolStripMenuItem();
            this.lineButton = new System.Windows.Forms.ToolStripMenuItem();
            this.circleButton = new System.Windows.Forms.ToolStripMenuItem();
            this.rectButton = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
            this.lineMenuBar = new System.Windows.Forms.ToolStripDropDownButton();
            this.line1Button = new System.Windows.Forms.ToolStripMenuItem();
            this.line3Button = new System.Windows.Forms.ToolStripMenuItem();
            this.line5Button = new System.Windows.Forms.ToolStripMenuItem();
            this.line7Button = new System.Windows.Forms.ToolStripMenuItem();
            this.line9Button = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator2 = new System.Windows.Forms.ToolStripSeparator();
            this.btn_Fill = new System.Windows.Forms.ToolStripButton();
            this.btn_lineColor = new System.Windows.Forms.ToolStripButton();
            this.btn_fillColor = new System.Windows.Forms.ToolStripButton();
            this.cld1 = new System.Windows.Forms.ColorDialog();
            this.cld2 = new System.Windows.Forms.ColorDialog();
            this.panel1 = new Client.DoubleBufferPanel();
            this.toolStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // toolStrip1
            // 
            this.toolStrip1.ImageScalingSize = new System.Drawing.Size(20, 20);
            this.toolStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.penMenuBar,
            this.toolStripSeparator1,
            this.lineMenuBar,
            this.toolStripSeparator2,
            this.btn_Fill,
            this.btn_lineColor,
            this.btn_fillColor});
            this.toolStrip1.Location = new System.Drawing.Point(0, 0);
            this.toolStrip1.Name = "toolStrip1";
            this.toolStrip1.Size = new System.Drawing.Size(800, 27);
            this.toolStrip1.TabIndex = 0;
            this.toolStrip1.Text = "toolStrip1";
            // 
            // penMenuBar
            // 
            this.penMenuBar.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.penMenuBar.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.pencilButton,
            this.lineButton,
            this.circleButton,
            this.rectButton});
            this.penMenuBar.Image = ((System.Drawing.Image)(resources.GetObject("penMenuBar.Image")));
            this.penMenuBar.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.penMenuBar.Name = "penMenuBar";
            this.penMenuBar.Size = new System.Drawing.Size(34, 24);
            this.penMenuBar.Text = "toolStripButton1";
            // 
            // pencilButton
            // 
            this.pencilButton.Image = ((System.Drawing.Image)(resources.GetObject("pencilButton.Image")));
            this.pencilButton.Name = "pencilButton";
            this.pencilButton.Size = new System.Drawing.Size(125, 26);
            this.pencilButton.Text = "Pencil";
            this.pencilButton.Click += new System.EventHandler(this.pencilButton_Click);
            // 
            // lineButton
            // 
            this.lineButton.Image = ((System.Drawing.Image)(resources.GetObject("lineButton.Image")));
            this.lineButton.Name = "lineButton";
            this.lineButton.Size = new System.Drawing.Size(125, 26);
            this.lineButton.Text = "Line";
            this.lineButton.Click += new System.EventHandler(this.lineButton_Click);
            // 
            // circleButton
            // 
            this.circleButton.Image = ((System.Drawing.Image)(resources.GetObject("circleButton.Image")));
            this.circleButton.Name = "circleButton";
            this.circleButton.Size = new System.Drawing.Size(125, 26);
            this.circleButton.Text = "Circle";
            this.circleButton.Click += new System.EventHandler(this.circleButton_Click);
            // 
            // rectButton
            // 
            this.rectButton.Image = ((System.Drawing.Image)(resources.GetObject("rectButton.Image")));
            this.rectButton.Name = "rectButton";
            this.rectButton.Size = new System.Drawing.Size(125, 26);
            this.rectButton.Text = "Rect";
            this.rectButton.Click += new System.EventHandler(this.rectButton_Click);
            // 
            // toolStripSeparator1
            // 
            this.toolStripSeparator1.Name = "toolStripSeparator1";
            this.toolStripSeparator1.Size = new System.Drawing.Size(6, 27);
            // 
            // lineMenuBar
            // 
            this.lineMenuBar.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.line1Button,
            this.line3Button,
            this.line5Button,
            this.line7Button,
            this.line9Button});
            this.lineMenuBar.Image = ((System.Drawing.Image)(resources.GetObject("lineMenuBar.Image")));
            this.lineMenuBar.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.lineMenuBar.Name = "lineMenuBar";
            this.lineMenuBar.Size = new System.Drawing.Size(51, 24);
            this.lineMenuBar.Text = "1";
            // 
            // line1Button
            // 
            this.line1Button.Image = ((System.Drawing.Image)(resources.GetObject("line1Button.Image")));
            this.line1Button.Name = "line1Button";
            this.line1Button.Size = new System.Drawing.Size(92, 26);
            this.line1Button.Text = "1";
            this.line1Button.Click += new System.EventHandler(this.line1Button_Click);
            // 
            // line3Button
            // 
            this.line3Button.Image = ((System.Drawing.Image)(resources.GetObject("line3Button.Image")));
            this.line3Button.Name = "line3Button";
            this.line3Button.Size = new System.Drawing.Size(92, 26);
            this.line3Button.Text = "3";
            this.line3Button.Click += new System.EventHandler(this.line3Button_Click);
            // 
            // line5Button
            // 
            this.line5Button.Image = ((System.Drawing.Image)(resources.GetObject("line5Button.Image")));
            this.line5Button.Name = "line5Button";
            this.line5Button.Size = new System.Drawing.Size(92, 26);
            this.line5Button.Text = "5";
            this.line5Button.Click += new System.EventHandler(this.line5Button_Click);
            // 
            // line7Button
            // 
            this.line7Button.Image = ((System.Drawing.Image)(resources.GetObject("line7Button.Image")));
            this.line7Button.Name = "line7Button";
            this.line7Button.Size = new System.Drawing.Size(92, 26);
            this.line7Button.Text = "7";
            this.line7Button.Click += new System.EventHandler(this.line7Button_Click);
            // 
            // line9Button
            // 
            this.line9Button.Image = ((System.Drawing.Image)(resources.GetObject("line9Button.Image")));
            this.line9Button.Name = "line9Button";
            this.line9Button.Size = new System.Drawing.Size(92, 26);
            this.line9Button.Text = "9";
            this.line9Button.Click += new System.EventHandler(this.line9Button_Click);
            // 
            // toolStripSeparator2
            // 
            this.toolStripSeparator2.Name = "toolStripSeparator2";
            this.toolStripSeparator2.Size = new System.Drawing.Size(6, 27);
            // 
            // btn_Fill
            // 
            this.btn_Fill.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Text;
            this.btn_Fill.Image = ((System.Drawing.Image)(resources.GetObject("btn_Fill.Image")));
            this.btn_Fill.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.btn_Fill.Name = "btn_Fill";
            this.btn_Fill.Size = new System.Drawing.Size(58, 24);
            this.btn_Fill.Text = "채우기";
            this.btn_Fill.Click += new System.EventHandler(this.btn_Fill_Click);
            // 
            // btn_lineColor
            // 
            this.btn_lineColor.BackColor = System.Drawing.Color.Black;
            this.btn_lineColor.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.None;
            this.btn_lineColor.Image = ((System.Drawing.Image)(resources.GetObject("btn_lineColor.Image")));
            this.btn_lineColor.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.btn_lineColor.Name = "btn_lineColor";
            this.btn_lineColor.Size = new System.Drawing.Size(23, 24);
            this.btn_lineColor.Text = "toolStripButton1";
            this.btn_lineColor.Click += new System.EventHandler(this.btn_lineColor_Click);
            // 
            // btn_fillColor
            // 
            this.btn_fillColor.BackColor = System.Drawing.Color.Gray;
            this.btn_fillColor.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.None;
            this.btn_fillColor.Image = ((System.Drawing.Image)(resources.GetObject("btn_fillColor.Image")));
            this.btn_fillColor.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.btn_fillColor.Name = "btn_fillColor";
            this.btn_fillColor.Size = new System.Drawing.Size(23, 24);
            this.btn_fillColor.Text = "toolStripButton3";
            this.btn_fillColor.Click += new System.EventHandler(this.btn_fillColor_Click);
            // 
            // panel1
            // 
            this.panel1.BackColor = System.Drawing.Color.White;
            this.panel1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.panel1.Location = new System.Drawing.Point(0, 27);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(800, 423);
            this.panel1.TabIndex = 1;
            this.panel1.Paint += new System.Windows.Forms.PaintEventHandler(this.panel1_Paint);
            this.panel1.MouseDown += new System.Windows.Forms.MouseEventHandler(this.panel1_MouseDown);
            this.panel1.MouseMove += new System.Windows.Forms.MouseEventHandler(this.panel1_MouseMove);
            this.panel1.MouseUp += new System.Windows.Forms.MouseEventHandler(this.panel1_MouseUp);
            // 
            // Form2
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this.panel1);
            this.Controls.Add(this.toolStrip1);
            this.Name = "Form2";
            this.Text = "MultiPaintClient";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Form2_FormClosing);
            this.toolStrip1.ResumeLayout(false);
            this.toolStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ToolStrip toolStrip1;
        private System.Windows.Forms.ToolStripDropDownButton penMenuBar;
        private System.Windows.Forms.ToolStripMenuItem pencilButton;
        private System.Windows.Forms.ToolStripMenuItem lineButton;
        private System.Windows.Forms.ToolStripMenuItem circleButton;
        private System.Windows.Forms.ToolStripMenuItem rectButton;
        private System.Windows.Forms.ToolStripDropDownButton lineMenuBar;
        private System.Windows.Forms.ToolStripMenuItem line1Button;
        private System.Windows.Forms.ToolStripMenuItem line3Button;
        private System.Windows.Forms.ToolStripMenuItem line5Button;
        private System.Windows.Forms.ToolStripMenuItem line7Button;
        private System.Windows.Forms.ToolStripMenuItem line9Button;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator2;
        private System.Windows.Forms.ToolStripButton btn_Fill;
        private System.Windows.Forms.ToolStripButton btn_lineColor;
        private System.Windows.Forms.ToolStripButton btn_fillColor;
        private System.Windows.Forms.ColorDialog cld1;
        private System.Windows.Forms.ColorDialog cld2;
        private DoubleBufferPanel panel1;
        //private DoubleBufferPanel panel1;
    }
}