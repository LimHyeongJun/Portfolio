using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Kanlendar {
    public partial class MemoPlan : Form {
        string Param = string.Empty;
        string MY = string.Empty;
        bool isMove;
        Point fpt;        
        Kalendar start;
        public Point MousePoint;
        public bool LeavePoint = false;
        public MemoPlan(string MY, string param, Kalendar start) {
            Param = param; //날짜
            this.MY = MY;   //년월                        
            InitializeComponent();
            this.start = start;                                                
        }       
        
        private void btn_red_Click(object sender, EventArgs e) {
            lbl_date.BackColor = Color.Red;
            string path = Application.StartupPath + @"\SavePlan\" + lbl_date.Text + ".txt";
            string colorPath = Application.StartupPath + @"\SaveColor\" + lbl_date.Text + ".txt";
            StreamWriter sw = new StreamWriter(colorPath);
            sw.WriteLine("Red");
            sw.Close();
            SavePlan();
            SaveColor(Color.Red);
            this.Close();

        }

        private void btn_yellow_Click(object sender, EventArgs e) {
            lbl_date.BackColor = Color.Yellow;
            string colorPath = Application.StartupPath + @"\SaveColor\" + lbl_date.Text + ".txt";
            StreamWriter sw = new StreamWriter(colorPath);
            sw.WriteLine("Yellow");
            sw.Close();
            SavePlan();
            SaveColor(Color.Yellow);
            this.Close();
        }

        private void btn_green_Click(object sender, EventArgs e) {
            lbl_date.BackColor = Color.Green;
            string colorPath = Application.StartupPath + @"\SaveColor\" + lbl_date.Text + ".txt";
            StreamWriter sw = new StreamWriter(colorPath);
            sw.WriteLine("Green");
            sw.Close();
            SavePlan();
            SaveColor(Color.Green);
            this.Close();
        }

        private void btn_blue_Click(object sender, EventArgs e) {
            lbl_date.BackColor = Color.Blue;
            string colorPath = Application.StartupPath + @"\SaveColor\" + lbl_date.Text + ".txt";
            StreamWriter sw = new StreamWriter(colorPath);
            sw.WriteLine("Blue");
            sw.Close();
            SavePlan();
            SaveColor(Color.Blue);
            this.Close();
        }

        private void btn_white_Click(object sender, EventArgs e) {
            lbl_date.BackColor = Color.Transparent;
            string colorPath = Application.StartupPath + @"\SaveColor\" + lbl_date.Text + ".txt";
            StreamWriter sw = new StreamWriter(colorPath);
            sw.WriteLine("Transparent");
            sw.Close();
            SavePlan();
            SaveColor(Color.Transparent);
            this.Close();
        }

        private void MemoPlan_Load(object sender, EventArgs e) {
            btn_yellow.BackColor = Color.Yellow;
            btn_green.BackColor = Color.Green;
            btn_red.BackColor = Color.Red;
            btn_white.BackColor = Color.White;
            btn_blue.BackColor = Color.Blue;
            this.lbl_date.Text = MY + "-" + Param;//년 월 일
            MousePoint = Cursor.Position;
            
            if (File.Exists(Application.StartupPath + @"\SavePlan\" + lbl_date.Text + ".txt"))
                readFile();            
        }
        
        public void SavePlan() {
            string path = Application.StartupPath + @"\SavePlan\" + lbl_date.Text + ".txt";//월로 저장함            
            StreamWriter sw = new StreamWriter(path);
            sw.WriteLine(txt_plan.Text + "\n");//내부내용
            sw.Close();
            start.PutCheckList(Param);            
        }
        public void SaveColor(Color color) {
            string path = Application.StartupPath + @"\SaveColor\" + lbl_date.Text + ".txt";//월로 저장함            
            StreamWriter sw = new StreamWriter(path);
            string _color = null;
            if (color == Color.Red) _color = "Red";            
            if (color == Color.Yellow) _color = "Yellow";
            if (color == Color.Green) _color = "Green";
            if (color == Color.Blue) _color = "Blue";
            if (color == Color.Transparent) _color = "Transparent";

            sw.WriteLine(_color + "\n");//내부내용
            sw.Close();
            start.PutColor(Param);
        }

        private void btn_save_Click(object sender, EventArgs e) {            
           
        }

        private void readFile() {
            try {
                string path = Application.StartupPath + @"\SavePlan\" + lbl_date.Text + ".txt";
                if (File.Exists(path)) {


                    StreamReader sr = new StreamReader(path);

                    string line;

                    while ((line = sr.ReadLine()) != null) {

                        //line = sr.ReadLine();
                        while (!string.IsNullOrEmpty(line)) {
                            this.txt_plan.Text += line;
                            this.txt_plan.Text += "\r\n";
                            line = sr.ReadLine();
                        }

                    }
                    sr.Close();
                }
            }
            catch (FileNotFoundException e) {
            }
        }

        //패널 움직이게
        private void pnlTop_MouseDown(object sender, MouseEventArgs e) {
            isMove = true;
            fpt = new Point(e.X, e.Y);
        }
        private void pnlTop_MouseUp(object sender, MouseEventArgs e) {
            isMove = false;
        }
        private void pnlTop_MouseMove(object sender, MouseEventArgs e) {
            if (isMove && (e.Button & MouseButtons.Left) == MouseButtons.Left)
                Location = new Point(this.Left - (fpt.X - e.X), this.Top - (fpt.Y - e.Y));
        }
    }
}
