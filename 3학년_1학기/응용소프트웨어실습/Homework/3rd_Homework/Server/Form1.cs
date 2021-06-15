using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Threading;
using System.Net.Sockets;
using System.Net;
using System.IO;
using System.IO.Compression;

namespace Server {
    public partial class Form1 : Form {
        private Form2 form2;

        public Form1() {
            InitializeComponent();
        }

        private void btn_ServerStart_Click(object sender, EventArgs e) {
            ServerStart();
        }

        private void ServerStart() {
            form2 = new Form2(txt_IP.Text, Int32.Parse(txt_Port.Text));
            form2.Show();

            this.Visible = false;
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e) {
            Environment.Exit(0);
            System.Diagnostics.Process.GetCurrentProcess().Kill();
            this.Close();
        }

        private void OnlyDigit(object sender, KeyPressEventArgs e) {
            e.Handled = !(char.IsControl(e.KeyChar) || char.IsDigit(e.KeyChar));
        }

        private void txt_Port_KeyDown(object sender, KeyEventArgs e) {
            if (e.KeyCode == Keys.Enter) {
                ServerStart();
            }
        }
    }
}
