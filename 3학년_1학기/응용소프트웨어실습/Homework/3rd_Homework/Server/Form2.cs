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
using System.Drawing.Imaging;
using System.Runtime.InteropServices;
using System.Drawing.Drawing2D;

namespace Server {
    public partial class Form2 : Form {
        private byte[] recevbyte = new byte[4000000];
        private Bitmap bitmap;

        private string ipAddress;
        private int Port;
        private TcpListener m_Listener;
        private TcpClient m_Client;

        public NetworkStream m_Stream;

        private Thread m_thServer;
        private String path;

        public static int count = 0; //클라이언트 얼마나 들어왔는지 판단하는 변수

        private TcpClient[] arr_Client = new TcpClient[20]; //클라이언트 저장하는 배열
        private bool[] arr_bConnect = new bool[20]; //클라이언트랑 연결되어있는지 확인하는 배열
        private Thread[] arr_Thread = new Thread[20]; //스레드 저장하는 배열

        public Form2(string ip, int port) {
            ipAddress = ip;
            Port = port;

            InitializeComponent();

            SetupVar();
        }

        private void SetupVar() {
            path = System.Reflection.Assembly.GetExecutingAssembly().Location;
            path = System.IO.Path.GetDirectoryName(path); //실행프로그램 있는 폴더의 경로 가져옴
            path += "\\image";
        }

        private void panel1_Paint(object sender, PaintEventArgs e) {
            e.Graphics.SmoothingMode = System.Drawing.Drawing2D.SmoothingMode.AntiAlias;

            if (bitmap != null)
                e.Graphics.DrawImage(bitmap, 0, 0);
        }

        private void Form2_Shown(object sender, EventArgs e) {
            if (System.IO.File.Exists(path)) {
                recevbyte = System.IO.File.ReadAllBytes(path);

                MemoryStream mStream = new MemoryStream();
                mStream.Write(recevbyte, 0, recevbyte.Length);
                mStream.Seek(0, SeekOrigin.Begin);


                bitmap = new Bitmap(mStream);

                panel1.Invalidate(true);
                panel1.Update();
            }
            m_thServer = new Thread(ServerStart);
            m_thServer.Start();
        }

        private void ServerStart() {
            try {
                for (int i = 0; i < 20; i++) {
                    arr_Client[i] = null;
                    arr_bConnect[i] = false;
                    arr_Thread[i] = null;
                }

                IPAddress localAddr = IPAddress.Parse(ipAddress);
                m_Listener = new TcpListener(localAddr, Port);
                m_Listener.Start();

                while (true) {
                    m_Client = m_Listener.AcceptTcpClient(); //여기서 계속 기다리게 됨
                    count++;

                    if (m_Client.Connected) {
                        m_Stream = m_Client.GetStream();

                        Bitmap bmp = new Bitmap(panel1.Width, panel1.Height);
                        panel1.DrawToBitmap(bmp, new Rectangle(0, 0, bmp.Width, bmp.Height));
                        MemoryStream ms = new MemoryStream();
                        bmp.Save(ms, System.Drawing.Imaging.ImageFormat.Bmp);
                        ms.Position = 0;
                        byte[] data = ms.ToArray();

                        Thread.Sleep(100);

                        m_Stream.Write(data, 0, data.Length);
                        m_Stream.Flush();
                        bitmap = bmp;
                        recevbyte = data;

                        arr_Client[count - 1] = m_Client;
                        arr_bConnect[count - 1] = true;

                        arr_Thread[count - 1] = new Thread(Receive);
                        arr_Thread[count - 1].Start(); //각 스레드별로 text를 받으면 Receive함수 실행하도록 한다.
                    }
                }
            } catch {
                return;
            }
        }

        public void Receive() {
            try {
                int presentCount = count;

                NetworkStream tempStream = arr_Client[presentCount - 1].GetStream();
                while (true) {
                    tempStream.Read(recevbyte, 0, recevbyte.Length);

                    MemoryStream mStream = new MemoryStream();
                    mStream.Write(recevbyte, 0, recevbyte.Length);
                    mStream.Seek(0, SeekOrigin.Begin);

                    bitmap = new Bitmap(mStream);

                    Graphics g = panel1.CreateGraphics();
                    g.SmoothingMode = System.Drawing.Drawing2D.SmoothingMode.AntiAlias;
                    g.DrawImage(bitmap, 0, 0);

                    SendByteAll(recevbyte);
                }
            } catch {
            }
        }

        public void SendByteAll(byte[] arr) {
            for (int i = 0; i < 20; i++) {
                if (!arr_bConnect[i])
                    continue;

                NetworkStream tempStream = arr_Client[i].GetStream();
                
                tempStream.Write(recevbyte, 0, recevbyte.Length);
                tempStream.Flush();
            }
        }

        private void Form2_FormClosing(object sender, FormClosingEventArgs e) {
            System.IO.File.WriteAllBytes(path, recevbyte);

            Environment.Exit(0);
            System.Diagnostics.Process.GetCurrentProcess().Kill();
            this.Close();
        }
    }
}
