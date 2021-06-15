using System;
using System.Windows.Forms;
using System.Threading;
using System.Net.Sockets;
using System.IO;


namespace Client {
    public partial class ClientForm : Form {
        TcpClient m_Client;
        public NetworkStream m_Stream;
        public StreamReader m_Read;
        public StreamWriter m_Write;

        private Thread m_ThReader;

        private bool m_bConnect = false;

        public ClientForm() {
            InitializeComponent();
        }

        //클라이언트에서 받을 때 실행되는 함수.
        public void Receive() {
            try {
                m_Write.WriteLine(txt_NickName.Text);
                m_Write.Flush();
                while (true) {
                    string szMessage = m_Read.ReadLine();
                    
                    if (szMessage.Equals("ServerExit")) {
                        Message("서버가 종료되었습니다.");
                        DisConnect();
                    } else if (szMessage == "System : " + txt_NickName.Text + " 님께서 입장하셨습니다.")
                        continue;
                    else if (szMessage.Equals("ServerStop")) {
                        btn_ConnectServer.Text = "서버 연결";
                        m_Stream.Close();
                        m_Read.Close();
                        m_Write.Close();
                        Message("서버가 연결을 끊었습니다.");
                        m_ThReader.Abort();
                    } else if (szMessage != null)
                        Message(szMessage);
                }
            }catch {
                Message("Receive 과정에서 오류 발생");
            }
        }

        public void Message(string msg) {
            if (m_bConnect) {
                this.Invoke(new MethodInvoker(delegate () {
                    txt_all.AppendText(msg + "\r\n");
                    txt_all.Focus();
                    txt_all.ScrollToCaret();
                    txt_send.Focus();
                }));
            }
        }

        private void btn_Send_Click(object sender, EventArgs e) {
            Send();
        }

        //보내기 버튼, 보내는 textbox에서 엔터키 눌렸을 때 실행되는 함수
        public void Send() {
            try {
                string nickname = txt_NickName.Text;
                string message = nickname + " : " + txt_send.Text;

                m_Write.WriteLine(message);
                m_Write.Flush();

                Message(nickname + " : " + txt_send.Text);
                txt_send.Text = "";
            } catch {
                Message("데이터 전송 실패\r\n");
            }
        }

        //텍스트 보내는 textbox에서 엔터키 눌리면 Send()실행
        private void txt_send_KeyDown(object sender, KeyEventArgs e) {
            if (e.KeyCode == Keys.Enter)
                Send();
        }
        
        public void Connect() {
            m_Client = new TcpClient();
            try {
                int port = Int32.Parse(txt_PortNumber.Text);
                m_Client.Connect(txt_IPAddress.Text, port);
            } catch {
                return;
            }
            m_bConnect = true;

            Message("연결을 시작합니다.");

            m_Stream = m_Client.GetStream();

            m_Read = new StreamReader(m_Stream);
            m_Write = new StreamWriter(m_Stream);

            m_Write.WriteLine(txt_NickName.Text);
            m_Stream.Flush();
            
            m_ThReader = new Thread(new ThreadStart(Receive));
            m_ThReader.Start();
        }

        public void DisConnect() {
            string text = "leaveChat";
            m_Write.WriteLine(text);
            m_Write.Flush();

            Message("Client가 종료됨");
        }

        private void btn_ConnectServer_Click(object sender, EventArgs e) {
            if (btn_ConnectServer.Text == "서버 연결") {
                Connect();
            } 
        }

        private void btn_exit_Click(object sender, EventArgs e) {
            string text = "leaveChat";
            m_Write.WriteLine(text);
            m_Write.Flush();

            Application.ExitThread();
            Environment.Exit(0);
        }

        private void ClientForm_FormClosing(object sender, FormClosingEventArgs e) {
            if (m_bConnect) {
                Thread exitThread = new Thread(DisConnect);
                exitThread.Start();
            }
            Application.ExitThread();
            Environment.Exit(0);
        }

        //연결 해제 버튼 눌렀을 때 실행됨.
        private void btn_ReleaseConnect_Click(object sender, EventArgs e) {
            string text = "leaveChat ";
            m_Write.WriteLine(text);
            m_Write.Flush();

            Message("연결을 해제합니다.");

            m_bConnect = false;
        }

        //port number 입력하는 곳에서는 숫자만 입력 가능하게 함.
        private void OnlyDigit(object sender, KeyPressEventArgs e) {
            e.Handled = !(char.IsControl(e.KeyChar) || char.IsDigit(e.KeyChar));
        }
    }
}
