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
    public partial class ReplayForm : Form {
        public DataGetEventHandler DataSendEvent;
        private string result;

        //ReplayForm은 이겼으면 win, 졌으면 lose를 데이터로 받는데 그걸 result에 저장하게 된다.
        public ReplayForm(string result) {
            this.result = result;
            InitializeComponent();
        }

        private void ReplayForm_FormClosing(object sender, FormClosingEventArgs e) {
            Environment.Exit(0);
            System.Diagnostics.Process.GetCurrentProcess().Kill();
            this.Close();
        }

        //리플레이 폼이 로드 될 때 result의 값에 따라 결과 라벨의 텍스트를 변경해준다.
        private void ReplayForm_Load(object sender, EventArgs e) {
            if (this.result.Equals("win")) {
                lbl_result.Text = "You Win!";
            } else if (this.result.Equals("lose")) {
                lbl_result.Text = "You Lose!";
            }
        }

        //Yes! 버튼이 눌릴 경우 form1에 yes를 전달하게 되고 form1은 form2와 form3를 안보이게 하고 다시 시작하게 된다.
        private void btn_Yes_Click(object sender, EventArgs e) {
            DataSendEvent("yes");
        }

        //No! 가 눌릴 경우는 전체 다 종료하게 된다.
        private void btn_No_Click(object sender, EventArgs e) {
            Environment.Exit(0);
            System.Diagnostics.Process.GetCurrentProcess().Kill();
            this.Close();
        }
    }
}
