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
using System.IO;

namespace Client {
    public partial class Form1 : Form {
        TcpClient m_Client;
        public NetworkStream m_Stream;
        public StreamReader m_Read;
        public StreamWriter m_Write;

        private Form2 form2;

        public Form1() {
            InitializeComponent();
        }

        private void btn_ServerConnect_Click(object sender, EventArgs e) {
            ServerConnect();
        }

        private void ServerConnect() {
            m_Client = new TcpClient();
            try {
                int port = Int32.Parse(txt_Port.Text);
                m_Client.Connect(txt_IP.Text, port);
            } catch {
                MessageBox.Show("연결되지 않았습니다.\r\nIP와 Port Number를 다시 입력하세요");

                return;
            }

            m_Stream = m_Client.GetStream();
            form2 = new Form2(m_Client);
            form2.Show();

            this.Visible = false;
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e) {
            Environment.Exit(0);
            System.Diagnostics.Process.GetCurrentProcess().Kill();
            this.Close();
        }

        private void txt_Port_KeyDown(object sender, KeyEventArgs e) {
            if (e.KeyCode == Keys.Enter) {
                ServerConnect();
            }
        }
    }
}
