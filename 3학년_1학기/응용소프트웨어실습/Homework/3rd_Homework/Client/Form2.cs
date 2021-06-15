using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Drawing.Drawing2D;
using System.Threading;
using System.Net.Sockets;
using System.IO;
using System.Windows;

namespace Client {
    public partial class Form2 : Form {
        private bool pencil;
        private bool line;
        private bool rect;
        private bool circle;
        private Point start;
        private Point finish;
        private Pen pen;
        private int thick;
        private bool isSolid;
        private ClientPencil mypencils;
        private ClientLines mylines;
        private ClientRect myrect;
        private ClientCircle mycircle;
        private ClientPointArr pointArr;
        private Color lineColor;
        private Color fillColor;
        private SolidBrush brush;
        private bool isBrush;
        Bitmap bitmap;


        TcpClient m_Client;
        public NetworkStream m_Stream;

        private Thread m_ThReader;

        public Form2(TcpClient m_Client) {
            this.m_Client = m_Client;
            m_Stream = m_Client.GetStream();
            m_ThReader = new Thread(Receive);
            m_ThReader.Start();

            InitializeComponent();

            SetupVar();
        }

        public void Receive() {
            try {
                while (true) {
                    byte[] array = new byte[4000000];
                    m_Stream.Read(array, 0, array.Length);

                    Thread.Sleep(100);

                    MemoryStream mStream = new MemoryStream();
                    mStream.Write(array, 0, array.Length);
                    mStream.Seek(0, SeekOrigin.Begin);

                    Bitmap bm = new Bitmap(mStream);

                    m_Stream = m_Client.GetStream();

                    Graphics g = panel1.CreateGraphics();

                    g.SmoothingMode = System.Drawing.Drawing2D.SmoothingMode.AntiAlias;
                    g.DrawImage(bm, 0, 0);
                    bitmap = bm;
                }
            } catch {
            }
        }

        private void SetupVar() {
            thick = 1;
            isSolid = true;
            pencil = true;
            line = false;
            rect = false;
            circle = false;
            brush = new SolidBrush(Color.White);
            start = new Point(0, 0);
            finish = new Point(0, 0);
            pen = new Pen(Color.Black);
            mypencils = new ClientPencil();
            mylines = new ClientLines();
            myrect = new ClientRect();
            mycircle = new ClientCircle();
            pointArr = new ClientPointArr();
            line1Button.Checked = true;
            line3Button.Checked = false;
            line5Button.Checked = false;
            line7Button.Checked = false;
            line9Button.Checked = false;
            isBrush = false;
        }

        private void panel1_MouseDown(object sender, MouseEventArgs e) {
            pointArr.Clear();

            start.X = e.X;
            start.Y = e.Y;
            if (pencil == true) {
                pointArr.Add(start);
            }
        }

        private void panel1_MouseMove(object sender, MouseEventArgs e) {
            if ((start.X == 0) && (start.Y == 0))
                return;

            finish.X = e.X;
            finish.Y = e.Y;

            if (btn_Fill.Checked)
                isBrush = true;
            else
                isBrush = false;

            if (pencil == true) {
                pointArr.Add(finish);
                pointArr.sort();
                if (btn_Fill.Checked)
                    mypencils.setPoint(pointArr.getList(), thick, isSolid, lineColor);
                else
                    mypencils.setPoint(pointArr.getList(), thick, isSolid, Color.Black);
            }
            if (line == true) {
                if (btn_Fill.Checked)
                    mylines.setPoint(start, finish, thick, isSolid, lineColor);
                else
                    mylines.setPoint(start, finish, thick, isSolid, Color.Black);
            }
            if (rect == true) {
                if (btn_Fill.Checked)
                    myrect.setRect(start, finish, thick, isSolid, isBrush, lineColor, fillColor);
                else
                    myrect.setRect(start, finish, thick, isSolid, isBrush, Color.Black, Color.White);
            }
            if (circle == true) {
                if (btn_Fill.Checked)
                    mycircle.setRectC(start, finish, thick, isSolid, isBrush, lineColor, fillColor);
                else
                    mycircle.setRectC(start, finish, thick, isSolid, isBrush, Color.Black, Color.White);
            }

            panel1.Invalidate(true);
            panel1.Update();
        }

        private void panel1_Paint(object sender, PaintEventArgs e) {
            e.Graphics.SmoothingMode = System.Drawing.Drawing2D.SmoothingMode.AntiAlias;

            if (bitmap != null)
                e.Graphics.DrawImage(bitmap, 0, 0);

            bool tempBrush = false;

            if (pencil == true) {
                int count = pointArr.getList().Count;
                List<Point> tempList = pointArr.getList();

                for (int j = 0; j < count - 1; j++) {
                    pen.Width = mypencils.getThick();
                    pen.Color = mypencils.getColor();
                    pen.DashStyle = DashStyle.Solid;
                    e.Graphics.DrawLine(pen, tempList[j], tempList[j + 1]);
                }
            } else if (line == true) {
                pen.Width = mylines.getThick();
                pen.Color = mylines.getColor();
                pen.DashStyle = DashStyle.Solid;
                e.Graphics.DrawLine(pen, mylines.getPoint1(), mylines.getPoint2());
            } else if (rect == true) {
                pen.Width = myrect.getThick();
                pen.DashStyle = DashStyle.Solid;
                brush = myrect.getBrush();
                pen.Color = myrect.getLineColor();
                tempBrush = myrect.brushDecide();
                e.Graphics.DrawRectangle(pen, myrect.getRect());
                if (tempBrush)
                    e.Graphics.FillRectangle(brush, myrect.getRect());
            } else if (circle == true) {
                pen.Width = mycircle.getThick();
                pen.DashStyle = DashStyle.Solid;
                brush = mycircle.getBrush();
                tempBrush = mycircle.brushDecide();
                pen.Color = mycircle.getLineColor();
                e.Graphics.DrawEllipse(pen, mycircle.getRectC());
                if (tempBrush)
                    e.Graphics.FillEllipse(brush, mycircle.getRectC());
            }

            pen.Width = thick;
            pen.DashStyle = DashStyle.Solid;
        }

        private void panel1_MouseUp(object sender, MouseEventArgs e) { //안에서는 ","로 구분하고 각각 끼리는 "-"로 구분. 색깔은 "/"로 구분
            start.X = 0;
            start.Y = 0;
            finish.X = 0;
            finish.Y = 0;

            Bitmap bmp = new Bitmap(panel1.Width, panel1.Height);
            panel1.DrawToBitmap(bmp, new Rectangle(0, 0, bmp.Width, bmp.Height));
            MemoryStream ms = new MemoryStream();
            bmp.Save(ms, System.Drawing.Imaging.ImageFormat.Bmp);
            ms.Position = 0;
            byte[] data = ms.ToArray();

            bitmap = bmp;

            Graphics g = panel1.CreateGraphics();
            g.SmoothingMode = System.Drawing.Drawing2D.SmoothingMode.AntiAlias;
            g.DrawImage(bmp, 0, 0);

            Send(data);
        }

        private void Send(byte[] byteArr) {
            try {
                m_Stream.Write(byteArr, 0, byteArr.Length);
                m_Stream.Flush();
            } catch {
                MessageBox.Show("Send 오류 남");
            }
        }

        private void Form2_FormClosing(object sender, FormClosingEventArgs e) {
            Environment.Exit(0);
            System.Diagnostics.Process.GetCurrentProcess().Kill();
            this.Close();
        }

        private void pencilButton_Click(object sender, EventArgs e) {
            pencil = true;
            line = false;
            rect = false;
            circle = false;
            penMenuBar.Image = pencilButton.Image;
        }

        private void lineButton_Click(object sender, EventArgs e) {
            pencil = false;
            line = true;
            rect = false;
            circle = false;
            penMenuBar.Image = lineButton.Image;
        }

        private void circleButton_Click(object sender, EventArgs e) {
            pencil = false;
            line = false;
            rect = false;
            circle = true;
            penMenuBar.Image = circleButton.Image;
        }

        private void rectButton_Click(object sender, EventArgs e) {
            pencil = false;
            line = false;
            rect = true;
            circle = false;
            penMenuBar.Image = rectButton.Image;
        }

        private void line1Button_Click(object sender, EventArgs e) {
            thick = 1;
            isSolid = true;
            lineMenuBar.Text = "1";
            lineMenuBar.Image = line1Button.Image;
        }

        private void line3Button_Click(object sender, EventArgs e) {
            thick = 3;
            isSolid = true;
            lineMenuBar.Text = "3";
            lineMenuBar.Image = line3Button.Image;
        }

        private void line5Button_Click(object sender, EventArgs e) {
            thick = 5;
            isSolid = true;
            lineMenuBar.Text = "5";
            lineMenuBar.Image = line5Button.Image;
        }

        private void line7Button_Click(object sender, EventArgs e) {
            thick = 7;
            isSolid = true;
            lineMenuBar.Text = "7";
            lineMenuBar.Image = line7Button.Image;
        }

        private void line9Button_Click(object sender, EventArgs e) {
            thick = 9;
            isSolid = true;
            lineMenuBar.Text = "9";
            lineMenuBar.Image = line9Button.Image;
        }

        private void btn_Fill_Click(object sender, EventArgs e) {
            if (btn_Fill.Checked) {
                btn_Fill.CheckState = CheckState.Unchecked;
                fillColor = Color.White;
                lineColor = Color.Black;
            } else {
                btn_Fill.CheckState = CheckState.Checked;
                fillColor = btn_fillColor.BackColor;
                lineColor = btn_lineColor.BackColor;
            }
        }

        private void btn_lineColor_Click(object sender, EventArgs e) {
            cld1.ShowDialog();
            lineColor = cld1.Color;
            btn_lineColor.BackColor = cld1.Color;
        }

        private void btn_fillColor_Click(object sender, EventArgs e) {
            cld2.ShowDialog();
            fillColor = cld2.Color;
            btn_fillColor.BackColor = cld2.Color;
        }
    }
}
