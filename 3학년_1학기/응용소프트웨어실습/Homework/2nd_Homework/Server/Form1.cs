using System;
using System.Collections.Generic;
using System.Drawing;
using System.Windows.Forms;
using System.Threading;
using System.Net.Sockets;
using System.Net;
using System.IO;

namespace Server {
    public partial class ServerForm : Form {
        private TcpListener m_Listener;
        private TcpClient m_Client;

        public NetworkStream m_Stream;
        public StreamReader m_Read;

        private Thread m_thServer;

        public static int count = 0; //클라이언트 얼마나 들어왔는지 판단하는 변수

        public Dictionary<TcpClient, string> clientList = new Dictionary<TcpClient, string>(); //클라이언트랑 클라이언트에서 받은 nickname 저장

        private TcpClient[] arr_Client = new TcpClient[20]; //클라이언트 저장하는 배열
        private bool[] arr_bConnect = new bool[20]; //클라이언트랑 연결되어있는지 확인하는 배열
        private Thread[] arr_Thread = new Thread[20]; //스레드 저장하는 배열
        private string[] arr_Username = new string[20]; //클라이언트별 닉네임 저장하는 배열

        public ServerForm() {
            InitializeComponent();
        }

        //서버의 전체textbox에 출력해주는 함수
        public void Message(string msg) { 
            this.Invoke(new MethodInvoker(delegate () {
                txt_all.AppendText(msg + "\r\n");
                txt_all.Focus();
                txt_all.ScrollToCaret();
                txt_send.Focus();
            }));
        }

        //서버는 받은 메시지 출력, 클라이언트 전체에는 메시지 보내줌
        public void SendMessageAll(string message, string user_name, bool flag) {
            this.Invoke(new MethodInvoker(delegate () {
                string receivedHost = message.Substring(0, message.IndexOf(" "));

                if (receivedHost == "Server") {
                    for (int i = 0; i < 20; ++i) {
                        if (!arr_bConnect[i])
                            continue;
                        NetworkStream stream = arr_Client[i].GetStream();
                        StreamWriter tempWriter = new StreamWriter(stream);

                        tempWriter.WriteLine(message);
                        tempWriter.Flush();
                    }
                    Message(message);
                } else if (flag == true) {
                    string whoLeave = "";
                    int temp = 1;
                    for (int i = 0; i < 20; i++) {
                        if (user_name == arr_Username[i]) {
                            arr_bConnect[i] = false;
                            continue;
                        }

                        NetworkStream stream = arr_Client[i].GetStream();
                        StreamWriter tempWriter = new StreamWriter(stream);
                        string text = "";

                        text = "System : " + user_name + " 님께서 종료하셨습니다.";
                        whoLeave = text;

                        tempWriter.WriteLine(text);
                        tempWriter.Flush();

                        if (temp == 1) {
                            Message(whoLeave);
                            temp--;
                        }
                    }
                    
                } else {
                    for (int i = 0; i < 20; i++) {
                        if (receivedHost == arr_Username[i] || !arr_bConnect[i])
                            continue;

                        NetworkStream stream = arr_Client[i].GetStream();
                        StreamWriter tempWriter = new StreamWriter(stream);

                        tempWriter.WriteLine(message);
                        tempWriter.Flush();
                    }
                    Message(message);
                }
            }));
        }

        //보내기 버튼 눌렀을 때 발생하는 함수
        private void btn_Send_Click(object sender, EventArgs e) { 
            string message = "Server : " + txt_send.Text;
            SendMessageAll(message, "System", false);
            txt_send.Text = "";
        }

        //서버 시작 버튼 눌렀을 때
        private void btn_ServerStart_Click(object sender, EventArgs e) { 
            if (btn_ServerStart.Text == "서버 시작") { //서버 스레드 시작
                m_thServer = new Thread(new ThreadStart(ServerStart));
                m_thServer.Start();

                btn_ServerStart.Text = "서버 종료";
                btn_ServerStart.ForeColor = Color.Red;
            } else {
                ServerStop();
                btn_ServerStart.Text = "서버 시작";
                btn_ServerStart.ForeColor = Color.Black;
            }
        }

        //서버 시작 누르고 시작되는 함수. while문 돌면서 클라이언트가 들어올 때마다 스레드 실행함.
        private void ServerStart() { 
            try {
                for (int i = 0; i < 20; i++) {
                    arr_Client[i] = null;
                    arr_bConnect[i] = false;
                    arr_Thread[i] = null;
                    arr_Username[i] = null;
                }

                IPAddress localAddr = IPAddress.Parse(txt_IPAddress.Text);
                int port = Int32.Parse(txt_PortNumber.Text);

                m_Listener = new TcpListener(localAddr, port);
                m_Listener.Start();

                while (true) {
                    m_Client = m_Listener.AcceptTcpClient(); //여기서 계속 기다리게 됨
                    count++;

                    if (m_Client.Connected) {
                        m_Stream = m_Client.GetStream();
                        m_Read = new StreamReader(m_Stream);

                        string user_name = m_Read.ReadLine(); //클라이언트로부터 닉네임 받음

                        clientList.Add(m_Client, user_name); //클라이언트와 닉네임 저장

                        arr_Client[count - 1] = m_Client;
                        arr_bConnect[count - 1] = true;
                        arr_Username[count - 1] = user_name;

                        string temp = "System : " + user_name + " 님께서 입장하셨습니다.";
                        SendMessageAll(temp, user_name, false); //서버와 전체 클라이언트에 누가 들어왔는지 알려줌

                        arr_Thread[count - 1] = new Thread(Receive);
                        arr_Thread[count - 1].Start(); //각 스레드별로 text를 받으면 Receive함수 실행하도록 한다.
                    }
                }
            } catch {
                Message("시작 도중 오류 발생");
                return;
            }
        }

        //클라이언트에게 내용 받는 함수. 각 스레드별로 다른 stream을 가져야 하므로 아래에서처럼 read, write 하는 스트림을 각각 생성해준다.
        public void Receive() {
            try {
                int presentCount = count;
                NetworkStream tempStream = arr_Client[presentCount - 1].GetStream();

                StreamReader tempReader = new StreamReader(tempStream);
                StreamWriter tempWriter = new StreamWriter(tempStream);
                while (arr_bConnect[presentCount - 1]) { //클라이언트랑 연결이 되어 있다면
                    string szMessage = tempReader.ReadLine(); //메시지를 읽는다.
                    string sz_username = clientList[arr_Client[presentCount - 1]]; //닉네임은 저장된 값을 가져온다.

                    if(szMessage.Equals("leaveChat ")) {
                        SendMessageAll(szMessage, sz_username, true);
                        arr_bConnect[presentCount - 1] = false;
                        clientList.Remove(arr_Client[presentCount - 1]);
                        arr_Client[presentCount - 1] = null;
                        arr_Thread[presentCount - 1] = null;
                        arr_Username[presentCount - 1] = null;
                    }
                    else if (szMessage != null) //leaveChat이 아닐 경우는 서버, 클라이언트 전체에 받은 메시지 출력하도록 한다.
                        SendMessageAll(szMessage, sz_username, false);
                }
            } catch {
            }
        }

        //종료될 때 실행되는 함수
        public void DisConnect() {
            try {
                foreach (var temp in clientList) {
                    TcpClient tempClient = temp.Key;
                    NetworkStream exitstream = tempClient.GetStream();
                    StreamWriter exitWriter = new StreamWriter(exitstream);

                    exitWriter.WriteLine("server exit");
                    exitWriter.Flush();
                    exitstream.Close();
                    exitWriter.Close();
                }
                m_Read.Close();
                m_Stream.Close();

                Message("연결을 중단합니다.");
            } catch {
                Message("연결을 끊는 중 오류가 발생했습니다.");
            }
        }

        //서버 멈추는 함수
        private void ServerStop() {
            m_thServer.Abort();
        }

        //Port Number에서 숫자만 입력되게 하는 함수
        private void OnlyDigit(object sender, KeyPressEventArgs e) {
            e.Handled = !(char.IsControl(e.KeyChar) || char.IsDigit(e.KeyChar));
        }

        //종료 버튼 눌렀을 때 실행되는 함수
        private void btn_exit_Click(object sender, EventArgs e) {
            DisConnect();
            Application.ExitThread();
            Environment.Exit(0);
        }

        //내용 입력하는 textbox에서 엔터 눌렀을 경우 내용 보내지게 함.
        private void txt_send_KeyDown(object sender, KeyEventArgs e) {
            if (e.KeyCode == Keys.Enter) {
                string message = "Server : " + txt_send.Text;
                SendMessageAll(message, "System", false);
                txt_send.Text = "";
            }
        }

        //서버 폼이 닫히기 전에 발생하는 함수.
        private void ServerForm_FormClosing(object sender, FormClosingEventArgs e) {
            foreach (var temp in clientList) {
                TcpClient tempClient = temp.Key;
                NetworkStream exitstream = tempClient.GetStream();
                StreamWriter exitWriter = new StreamWriter(exitstream);

                exitWriter.WriteLine("ServerExit");
                exitWriter.Flush();
            }
            DisConnect();
            Application.ExitThread();
            Environment.Exit(0);
        }
    }
}
