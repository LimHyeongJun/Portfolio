using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;

namespace 가계부 {
    public partial class Form1 : Form {
        public Form1() {
            InitializeComponent();
        }
        private Dictionary<string, string> expenditureList = new Dictionary<string, string>();
        private Dictionary<string, string> incomeList = new Dictionary<string, string>();

        private string path;
        private string dirPath;

        //폼을 로드할 때 현재 달을 가져와서 lbl_month의 텍스트 바꿔주고 init()함수로 초기화 한다.
        //그 후 현재 실행프로그램이 있는 폴더의 경로를 path와 dirPath에 저장하고 AutoLoad()함수를 호출해 저장되어 있는 파일이 있다면 불러온다.
        private void Form1_Load(object sender, EventArgs e) {
            string curMonth = DateTime.Now.ToString("yyyy.MM.");
            string[] temp = curMonth.Split('.');
            int year = Int32.Parse(temp[0]);
            int month = Int32.Parse(temp[1]);

            lbl_month.Text = year + "." + month + ".";

            path = System.Reflection.Assembly.GetExecutingAssembly().Location;
            path = System.IO.Path.GetDirectoryName(path); //실행프로그램 있는 폴더의 경로 가져옴

            path = path + "\\Data";
            dirPath = path;

            AutoLoad();
        }

        //이전 달로 넘어간다.lbl_month의 값을 바꿔주고 AutoLoad()함수 실행해서 파일 있으면 자동 로드한다.
        private void btn_PreviousMonth_Click(object sender, EventArgs e) {
            string[] temp = lbl_month.Text.Split('.');
            int year = Int32.Parse(temp[0]);
            int month = Int32.Parse(temp[1]);

            if (month == 1) {
                year--;
                month = 12;
            } else {
                month--;
            }
            lbl_month.Text = year + "." + month + ".";

            AutoLoad();
        }

        //다음 달로 넘어간다. lbl_month의 값 바꿔주고 마찬가지로 AutoLoad()함수 실행한다.
        private void btn_NextMonth_Click(object sender, EventArgs e) {
            string[] temp = lbl_month.Text.Split('.');
            int year = Int32.Parse(temp[0]);
            int month = Int32.Parse(temp[1]);

            if (month == 12) {
                year++;
                month = 1;
            } else {
                month++;
            }
            lbl_month.Text = year + "." + month + ".";

            AutoLoad();
        }

        //자동 불러오기 함수
        public void AutoLoad() {
            string[] temp = lbl_month.Text.Split('.'); //현재달을 나와있는 라벨을 .을 기준으로 나눔
            string filepath = dirPath + "\\" + lbl_month.Text + ".txt"; //파일 경로를 현재 디렉토리 경로가 저장된 dirPath에 lbl_month의 텍스트 붙임

            if (System.IO.File.Exists(filepath)) { //만약 파일이 존재한다면
                init(); //폼의 값들 초기화해줌

                string text = System.IO.File.ReadAllText(filepath); //파일 읽어옴
                string[] temp1 = text.Split('/'); //   '/'를 기준으로 앞은 지출, 뒤는 수입이므로 나눈다.
                string expenditureText = temp1[0]; //지출 쪽 text
                string incomeText = temp1[1]; //수입 쪽 text

                string[] splitExpend = null;

                if (!expenditureText.Equals("noExpenditure")) //지출쪽이 noExpenditure text가 아니여야 지출에 저장된 값이 있음
                    splitExpend = expenditureText.Split('-');

                string[] splitIncome = null;

                if (!incomeText.Equals("noIncome")) //수입쪽이 noExpenditure text가 아니여야 수입에 저장된 값이 있음
                    splitIncome = incomeText.Split('-');

                if (splitExpend != null) { //만약 splitExpend가 null이면 지출 쪽에는 저장된 값이 없으므로 여길 건너뛴다.
                    foreach (var obj in splitExpend) { //행마다의 구분은 -로 하고, 내역과 금액은 ,로 구분한다.
                        string[] arr = obj.Split(','); //내역과 금액을 , 로 구분한다.
                        ListViewItem list = new ListViewItem(arr);
                        lvwExpenditure.Items.Add(list); //가져온 것을 지출 쪽 ListView에 추가한다.

                        expenditureList.Add(arr[0], arr[1]); //그리고 리스트에도 추가해준다.

                        string[] str = lbl_AllExpenditure.Text.Split(':'); //여기서 총 지출이 얼마인지 계산
                        string[] result = str[1].Split('원');
                        int curExpenditure = Int32.Parse(result[0]);
                        int expenditureTotal = curExpenditure + Int32.Parse(arr[1]);
                        lbl_AllExpenditure.Text = "총 지출 : " + expenditureTotal + "원";

                        str = lbl_TotalMoney.Text.Split(':'); //여기서 총 자산이 얼마인지 계산
                        result = str[1].Split('원');
                        int curTotal = Int32.Parse(result[0]);
                        int total = curTotal - Int32.Parse(arr[1]);
                        lbl_TotalMoney.Text = "총 자산 : " + total + "원";
                    }
                }

                if (splitIncome != null) { //만약 splitIncome이 null이면 수입 쪽에 저장된 값이 없으므로 넘어가게 된다. 아래쪽 코드는 위의 지출쪽과 똑같이 진행된다.
                    foreach (var obj in splitIncome) {
                        string[] arr = obj.Split(',');
                        ListViewItem list = new ListViewItem(arr);
                        lvwIncome.Items.Add(list);

                        incomeList.Add(arr[0], arr[1]);

                        string[] str = lbl_AllIncome.Text.Split(':');
                        string[] result = str[1].Split('원');
                        int curIncome = Int32.Parse(result[0]);
                        int incomeTotal = curIncome + Int32.Parse(arr[1]);
                        lbl_AllIncome.Text = "총 지출 : " + incomeTotal + "원";

                        str = lbl_TotalMoney.Text.Split(':');
                        result = str[1].Split('원');
                        int curTotal = Int32.Parse(result[0]);
                        int total = curTotal + Int32.Parse(arr[1]);
                        lbl_TotalMoney.Text = "총 자산 : " + total + "원";
                    }
                }
            } else { //경로에 파일이 존재하지 않는다면 그냥 초기화만 해준다.
                init();
            }
        }

        //ListView, textbox, label등을 초기화시키는 함수
        public void init() {
            lvwExpenditure.Clear();
            lvwIncome.Clear();
            txt_ExpenditureContent.Clear();
            txt_ExpenditureMoney.Clear();
            txt_IncomeContent.Clear();
            txt_IncomeMoney.Clear();
            lbl_AllExpenditure.Text = "총 지출 : 0원";
            lbl_AllIncome.Text = "총 수입 : 0원";
            lbl_TotalMoney.Text = "총 자산 : 0원";
            expenditureList.Clear();
            incomeList.Clear();

            lvwExpenditure.View = View.Details;
            lvwExpenditure.Columns.Add("이름");
            lvwExpenditure.Columns.Add("지출");
            lvwExpenditure.Columns[0].Width = 130;
            lvwExpenditure.Columns[1].Width = -2;

            lvwIncome.View = View.Details;
            lvwIncome.Columns.Add("이름");
            lvwIncome.Columns.Add("수입");
            lvwIncome.Columns[0].Width = 130;
            lvwIncome.Columns[1].Width = -2;
        }

        //지출 쪽 등록 누르면 동작하는 함수
        private void btn_ExpenditureEnroll_Click(object sender, EventArgs e) {
            string content = txt_ExpenditureContent.Text;
            string money = txt_ExpenditureMoney.Text;

            string[] str = new string[] { content, money };
            ListViewItem list = new ListViewItem(str);
            lvwExpenditure.Items.Add(list); //지출 쪽 ListView에 내역과 금액 추가

            expenditureList.Add(content, money); //list에도 추가

            str = lbl_AllExpenditure.Text.Split(':'); //총 지출 금액 계산
            string[] result = str[1].Split('원');
            int curExpenditure = Int32.Parse(result[0]);
            int expenditureTotal = curExpenditure + Int32.Parse(money);
            lbl_AllExpenditure.Text = "총 지출 : " + expenditureTotal + "원";

            str = lbl_TotalMoney.Text.Split(':'); //총 자산 계산
            result = str[1].Split('원');
            int curTotal = Int32.Parse(result[0]);
            int total = curTotal - Int32.Parse(money);
            lbl_TotalMoney.Text = "총 자산 : " + total + "원";

            txt_ExpenditureContent.Clear(); //textbox들 clear
            txt_ExpenditureMoney.Clear();
            txt_ExpenditureContent.Focus();
        }

        //지출 쪽 제거 버튼 누를 경우
        private void btn_ExpenditureRemove_Click(object sender, EventArgs e) {
            if (lvwExpenditure.FocusedItem == null) return; //누른게 없으면 첫번째 아이템
            string removedItem = lvwExpenditure.FocusedItem.Text; //removedItem에는 누른 줄의 내역 이름이 들어간다.
            lvwExpenditure.FocusedItem.Remove(); //listview에서 focus된 줄을 지운다.

            string removedMoney = expenditureList[removedItem]; //focus된 줄의 돈 내용은 list에서 Key를 이용해 찾는다.
            expenditureList.Remove(removedItem); //list에서 해당 Key를 갖는 것을 지운다.

            string[] str = lbl_AllExpenditure.Text.Split(':'); //총 지출 계산
            string[] result = str[1].Split('원');
            int curExpenditure = Int32.Parse(result[0]);
            int expenditureTotal = curExpenditure - Int32.Parse(removedMoney);
            lbl_AllExpenditure.Text = "총 지출 : " + expenditureTotal + "원";

            str = lbl_TotalMoney.Text.Split(':'); //총 자산 계산
            result = str[1].Split('원');
            int curTotal = Int32.Parse(result[0]);
            int total = curTotal + Int32.Parse(removedMoney);
            lbl_TotalMoney.Text = "총 자산 : " + total + "원";
        }

        //수입 쪽 등록 버튼 누를 경우. 매커니즘은 위의 지출 쪽 등록 버튼과 동일하다.
        private void btn_IncomeEnroll_Click(object sender, EventArgs e) {
            string content = txt_IncomeContent.Text;
            string money = txt_IncomeMoney.Text;

            string[] str = new string[] { content, money };
            ListViewItem list = new ListViewItem(str);
            lvwIncome.Items.Add(list);

            incomeList.Add(content, money);

            str = lbl_AllIncome.Text.Split(':');
            string[] result = str[1].Split('원');
            int curIncome = Int32.Parse(result[0]);
            int incomeTotal = curIncome + Int32.Parse(money);
            lbl_AllIncome.Text = "총 지출 : " + incomeTotal + "원";

            str = lbl_TotalMoney.Text.Split(':');
            result = str[1].Split('원');
            int curTotal = Int32.Parse(result[0]);
            int total = curTotal + Int32.Parse(money);
            lbl_TotalMoney.Text = "총 자산 : " + total + "원";

            txt_IncomeContent.Clear();
            txt_IncomeMoney.Clear();
            txt_IncomeContent.Focus();
        }

        //수입 쪽 제거 버튼 누를 경우. 매커니즘은 마찬가지로 위의 지출 쪽 제거 버튼과 동일하다.
        private void btn_IncomeRemove_Click(object sender, EventArgs e) {
            if (lvwIncome.FocusedItem == null) return;
            string removedItem = lvwIncome.FocusedItem.Text;
            lvwIncome.FocusedItem.Remove();

            string removedMoney = incomeList[removedItem];
            incomeList.Remove(removedItem);

            string[] str = lbl_AllIncome.Text.Split(':');
            string[] result = str[1].Split('원');
            int curIncome = Int32.Parse(result[0]);
            int incomeTotal = curIncome - Int32.Parse(removedMoney);
            lbl_AllIncome.Text = "총 지출 : " + incomeTotal + "원";

            str = lbl_TotalMoney.Text.Split(':');
            result = str[1].Split('원');
            int curTotal = Int32.Parse(result[0]);
            int total = curTotal - Int32.Parse(removedMoney);
            lbl_TotalMoney.Text = "총 자산 : " + total + "원";
        }

        //가계부 저장 버튼 누를 경우 실행된다.
        private void btn_Save_Click(object sender, EventArgs e) {
            int expenditureCount = lvwExpenditure.Items.Count; //지출 쪽에 listview에 아이템이 몇 개인지
            int incomeCount = lvwIncome.Items.Count; //수입 쪽 listview에 아이템이 몇 개인지

            string saveStr = null; //파일에 저장할 string을 선언

            if (expenditureCount > 0) { //지출 쪽 listview에 아이템이 있으면 for문 돌면서 형식에 맞게 saveStr에 내용 추가
                foreach (var temp in expenditureList) {
                    string name = temp.Key;
                    string money = temp.Value;
                    if (expenditureCount == 1) { //지출 쪽 마지막에서는 - 대신에 /로 지출과 수입을 구분한다.
                        string s = name + "," + money + "/";
                        saveStr += s;
                        break;
                    }
                    string str = name + "," + money + "-"; //이름과 돈 사이는 , 로 구분하고 다음 아이템과는 -로 구분
                    saveStr += str;
                    expenditureCount--;
                }
            } else if (expenditureCount == 0) { //만약 지출 쪽에 아무 내용이 없으면 noExpenditure/ 추가
                saveStr += "noExpenditure/";
            }

            if (incomeCount > 0) { //수입 쪽도 지출 쪽과 같은 매커니즘
                foreach (var temp in incomeList) {
                    string name = temp.Key;
                    string money = temp.Value;
                    if (incomeCount == 1) {
                        string s = name + "," + money;
                        saveStr += s;
                        break;
                    }
                    string str = name + "," + money + "-";
                    saveStr += str;
                    incomeCount--;
                }
            } else if (incomeCount == 0) {
                saveStr += "noIncome";
            }

            try { //여기서는 Data 디렉토리가 없으면 디렉토리 생성
                System.IO.DirectoryInfo di = new System.IO.DirectoryInfo(path);
                if (di.Exists == false)
                    di.Create();
            } catch (Exception err) {
                MessageBox.Show(err.Message.ToString());
            }

            string plus = lbl_month.Text;
            path = path + "\\" + plus + ".txt"; //path를 lbl_month의 텍스트와 .txt를 붙여서 저장
            try {
                System.IO.File.WriteAllText(path, saveStr); //해당 path에 saveStr에 저장된 내용을 쓴다.
                path = dirPath; //path를 Data디렉토리 경로로 다시 바꿔준다.
            } catch (Exception err) {
                MessageBox.Show(err.Message.ToString());
            }
        }

        //돈을 입력하는 textbox에서는 숫자만 입력되게 한다.
        private void txt_money_KeyPress(object sender, KeyPressEventArgs e) {
            if (char.IsDigit(e.KeyChar) || e.KeyChar == Convert.ToChar(Keys.Back)) return;
            e.Handled = true;
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e) {
            Environment.Exit(0);
            System.Diagnostics.Process.GetCurrentProcess().Kill();
            this.Close();
        }
    }
}
