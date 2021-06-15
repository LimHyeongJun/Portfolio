using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace RogueLikeGame {
    public partial class Form2 : Form {
        private string str;
        Label label;

        public Form2(string str) {
            this.str = str;

            InitializeComponent();
        }

        private void Form2_Shown(object sender, EventArgs e) {
            if(str.Equals("win")) {
                label = new System.Windows.Forms.Label();
                label.Location = new Point(40, 25);
                label.Font = new Font("맑은고딕", 14);
                label.AutoSize = true;
                label.Text = "You Win! Good Play!";
                this.Controls.Add(label);

                button1.Location = new Point(70, 90);
                button1.Size = new Size(120, 38);
                button1.Text = "확인";

                this.Size = new Size(270, 190);
            } else if(str.Equals("lose")) {
                label = new System.Windows.Forms.Label();
                label.Location = new Point(40, 25);
                label.Font = new Font("맑은고딕", 14);
                label.AutoSize = true;
                label.Text = "You Lose...Don't be disappointed";
                this.Controls.Add(label);

                button1.Location = new Point(130, 90);
                button1.Size = new Size(120, 38);
                button1.Text = "확인";
                this.Size = new Size(380, 190);
            }
        }

        private void Form2_FormClosing(object sender, FormClosingEventArgs e) {
            Environment.Exit(0);
            System.Diagnostics.Process.GetCurrentProcess().Kill();
            this.Close();
        }

        private void button1_Click(object sender, EventArgs e) {
            Environment.Exit(0);
            System.Diagnostics.Process.GetCurrentProcess().Kill();
            this.Close();
        }
    }
}
