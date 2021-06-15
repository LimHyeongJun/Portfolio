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

namespace 지뢰찾기 {
    public delegate void DataGetEventHandler(string data1);
    public partial class Difficulty : Form {
        public DataGetEventHandler DataSendEvent; //form2, form3와 데이터 주고받을 핸들러
        private PlayBoard playboard;
        private ReplayForm replay;

        public Difficulty() {
            InitializeComponent();
        }

        //확인버튼 누르면 실행되는 함수
        private void btn_OK_Click(object sender, EventArgs e) {
            if(rdoBeginner.Checked) { 
                this.Visible = false;
                playboard = new PlayBoard(9, 9, 10); //초급은 행9, 열9, 지뢰10을 PlayBoard에 인자로 넘김
                playboard.DataSendEvent += new DataGetEventHandler(this.CreateForm3); //form2에서 받은 값에 따라 form3를 어떻게 생성될지 결정
                playboard.Show();
            } else if(rdoMiddle.Checked) {
                this.Visible = false;
                playboard = new PlayBoard(16, 16, 40);
                playboard.DataSendEvent += new DataGetEventHandler(this.CreateForm3);
                playboard.Show();
            } else if(rdoAdvanced.Checked) {
                this.Visible = false;
                playboard = new PlayBoard(16, 30, 99);
                playboard.DataSendEvent += new DataGetEventHandler(this.CreateForm3);
                playboard.Show();
            }
        }

        //form2에서 게임을 하다가 이기거나 지면 데이터를 form1으로 넘겨주는데 
        //lose면 form3에 lose를 win이면 form3에 win을 보낸다.
        private void CreateForm3(string data) {
            if(data.Equals("lose")) {
                replay = new ReplayForm(data);
                replay.DataSendEvent += new DataGetEventHandler(this.Reset);
                replay.Show();
            } else if(data.Equals("win")) {
                replay = new ReplayForm(data);
                replay.DataSendEvent += new DataGetEventHandler(this.Reset);
                replay.Show();
            }
        }

        //form3로 보낸 데이터가 yes라면 다시 시작하는 것이므로 form1만 보이게 하고
        //form2, form3는 Visible 값 변경해서 보이지 않도록 한다.
        private void Reset(string data) {
            if(data.Equals("yes")) {
                this.Visible = true;
                rdoBeginner.Checked = false;
                rdoMiddle.Checked = false;
                rdoAdvanced.Checked = false;

                playboard.Visible = false;
                replay.Visible = false;
            }
        }

        private void Difficulty_FormClosing(object sender, FormClosingEventArgs e) {
            Environment.Exit(0);
            System.Diagnostics.Process.GetCurrentProcess().Kill();
            this.Close();
        }

        //form1이 로드 될때마다 버튼들은 눌리지 않은 상태에서 시작한다.
        private void Difficulty_Load(object sender, EventArgs e) {
            rdoBeginner.Checked = false;
            rdoMiddle.Checked = false;
            rdoAdvanced.Checked = false;
        }
    }
}
