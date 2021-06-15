using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Windows.Forms.VisualStyles;

//Selenium Library
using OpenQA.Selenium;
using OpenQA.Selenium.Chrome;
using OpenQA.Selenium.Support.UI;

namespace Kanlendar
{
    public delegate void DataGetEventHandler(string data1);
    public partial class Kalendar : Form
    {
        public DataGetEventHandler DataSendEvent;

        // Selenium Var
        public ChromeDriverService _driverService = null;
        public ChromeOptions _defaultOptions = null;
        public ChromeOptions _headlessOptions = null;
        public ChromeDriver _driver = null;

        // Notice Var
        private string seleniumPath;
        private string lvwPath;
        private Dictionary<string, List<By>> dictNotices;
        private int decideNum = 1;
        private NoticeListForm noticeListForm;
        private NoticeShowForm noticeShowForm;

        // Assignment Var
        private string assignPath;

        // Calander Var
        public Point MousePoint;
        public Size CalenderSize;
        public DateTime DT = DateTime.Now;
        public Cell[] cell = new Cell[40];
        public string path;
        public string DD = null;
        public bool Open = false;
        public MemoPlan memo;

        public Kalendar()
        {
            InitializeComponent();
            this.Size = new Size(this.Size.Width, Screen.PrimaryScreen.WorkingArea.Height);
            CalenderSize = this.Size;
            InitCell();
            lbl_YM.Text = DT.ToString("yyyy-MM");
            path = Application.StartupPath + @"\SavePlan\" + lbl_YM.Text + "-" + DD + ".txt";

            // Selenium Path
            seleniumPath = System.Reflection.Assembly.GetExecutingAssembly().Location;
            seleniumPath = System.IO.Path.GetDirectoryName(seleniumPath);
            assignPath = seleniumPath + "\\assignList.txt";

            // openfileDialog
            ofd.InitialDirectory = Environment.GetFolderPath(Environment.SpecialFolder.Desktop);
            ofd.FileName = "";

            string directory_path = "SavePlan";
            string directory_colorPath = "SaveColor";
            if (!Directory.Exists(Application.StartupPath + @"\SavePlan\") || !Directory.Exists(Application.StartupPath + @"\SaveColor\"))
            {
                Directory.CreateDirectory(directory_path);
                Directory.CreateDirectory(directory_colorPath);
            }
            this.Refresh();
            DayView.MouseClick += new MouseEventHandler(LeaveMemo);
            pnl_top.MouseClick += new MouseEventHandler(LeaveMemo);
            label1.MouseClick += new MouseEventHandler(LeaveMemo);
            label2.MouseClick += new MouseEventHandler(LeaveMemo);
            label3.MouseClick += new MouseEventHandler(LeaveMemo);
            label4.MouseClick += new MouseEventHandler(LeaveMemo);
            label5.MouseClick += new MouseEventHandler(LeaveMemo);
            label6.MouseClick += new MouseEventHandler(LeaveMemo);
            label7.MouseClick += new MouseEventHandler(LeaveMemo);
            SetDay(DateTime.Now);

            this.lbl_YM.Location = new Point(pnl_top.Width / 2, 12);
            this.pre_month.Location = new Point(lbl_YM.Location.X - 50, this.Location.Y);
            this.next_month.Location = new Point(lbl_YM.Location.X + 80, this.Location.Y);
        }

        #region Calendar Method
        public void LeaveMemo(object sender, EventArgs e)
        {
            if (!Open)
            {
                return;
            }

            memo.SavePlan();
            memo.Close();
            Open = false;
        }

        private void pnlTop_MouseDown(object sender, MouseEventArgs e)
        {
            MousePoint = new Point(e.X, e.Y);
        }

        private void pnlTop_MouseMove(object sender, MouseEventArgs e)
        {
            if ((e.Button & MouseButtons.Left) == MouseButtons.Left)
            {
                Location = new Point(this.Left - (MousePoint.X - e.X), this.Top - (MousePoint.Y - e.Y));
            }
        }

        private void btnClose_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void btnBigger_Click(object sender, EventArgs e)
        {
            if (CalenderSize == this.Size)
            {
                this.Size = new System.Drawing.Size(Screen.PrimaryScreen.WorkingArea.Width,
                            Screen.PrimaryScreen.WorkingArea.Height);
                this.Location = new Point(Screen.PrimaryScreen.WorkingArea.Width / 2 - this.Size.Width / 2,
                            Screen.PrimaryScreen.WorkingArea.Height / 2 - this.Size.Height / 2);
                this.lbl_YM.Location = new Point(pnl_top.Width / 2, 12);
                this.pre_month.Location = new Point(lbl_YM.Location.X - 50, this.Location.Y);
                this.next_month.Location = new Point(lbl_YM.Location.X + 80, this.Location.Y);
            }
            else
            {
                this.Size = CalenderSize;
                this.lbl_YM.Location = new Point(pnl_top.Width / 2, 12);
                this.pre_month.Location = new Point(lbl_YM.Location.X - 50, this.Location.Y);
                this.next_month.Location = new Point(lbl_YM.Location.X + 80, this.Location.Y);
            }
        }

        public void InitCell()
        {
            for (int i = 0; i < 40; i++)
            {
                cell[i] = new Cell();
                cell[i].Padding = new Padding(0);
                cell[i].Dock = DockStyle.Fill;
                cell[i].Margin = new Padding(0);
                //이벤트
                cell[i].DayLabel.DoubleClick += new EventHandler(DoubleClickEvent);
                cell[i].DayLabel.MouseClick += new MouseEventHandler(LeaveMemo);
                cell[i].MyList.MouseClick += new MouseEventHandler(LeaveMemo);
                cell[i].KwList.MouseClick += new MouseEventHandler(LeaveMemo);
                cell[i].KwList.MouseDoubleClick += kwList_MouseDoubleClick;
            }
        }

        public void DoubleClickEvent(object sender, EventArgs e)
        {
            Point parentPoint = this.Location;
            Label label = sender as Label;
            memo = new MemoPlan(lbl_YM.Text, label.Text, this);//년 월을 가져옴   
            memo.StartPosition = FormStartPosition.Manual;
            if (Cursor.Position.Y > this.Location.Y + this.Size.Height - memo.Size.Height)
                memo.Location = new Point(Cursor.Position.X, this.Location.Y + Size.Height - memo.Size.Height);
            else
                memo.Location = new Point(Cursor.Position.X, Cursor.Position.Y);     
            memo.Owner = this;
            memo.Show();
            Open = true;
        }

        public void PutCheckList(string day)
        {
            path = Application.StartupPath + @"\SavePlan\" + lbl_YM.Text + "-" + Convert.ToString(day) + ".txt";
            if (File.Exists(path))
            {
                StreamReader sr = new StreamReader(path);

                string line;
                cell[Int32.Parse(day)].MyList.Items.Clear();
                while ((line = sr.ReadLine()) != null)
                {
                    while (!string.IsNullOrEmpty(line))
                    {
                        cell[Int32.Parse(day)].MyList.Items.Add(line); //checkbox도 모든 체크박스 각각에 넣어야함
                        line = sr.ReadLine();
                    }
                }
                sr.Close();
            }
        }

        public void PutColor(string day)
        {
            path = Application.StartupPath + @"\SaveColor\" + lbl_YM.Text + "-" + Convert.ToString(day) + ".txt";
            if (File.Exists(path))
            {
                StreamReader sr = new StreamReader(path);

                string line;
                while ((line = sr.ReadLine()) != null)
                {
                    if (line == "Red")
                        cell[Int32.Parse(day)].DayLabel.BackColor = Color.Red;
                    if (line == "Blue")
                        cell[Int32.Parse(day)].DayLabel.BackColor = Color.Blue;
                    if (line == "Green")
                        cell[Int32.Parse(day)].DayLabel.BackColor = Color.Green;
                    if (line == "Yellow")
                        cell[Int32.Parse(day)].DayLabel.BackColor = Color.Yellow;
                    if (line == "Transparent")
                        cell[Int32.Parse(day)].DayLabel.BackColor = Color.Transparent;
                    line = sr.ReadLine();
                }
                sr.Close();
            }
        }

        public void SetView(int start, int end)
        {
            int row = 0;
            int col = start;
            int index = 0;
            for (int i = 0; i < end; i++)
            {
                index = i + start;
                path = Application.StartupPath + @"\SavePlan\" + lbl_YM.Text + "-" + Convert.ToString(i) + ".txt";
                if (File.Exists(path))
                {
                    StreamReader sr = new StreamReader(path);

                    string line;
                    while ((line = sr.ReadLine()) != null)
                    {
                        while (!string.IsNullOrEmpty(line))
                        {
                            cell[i].MyList.Items.Add(line); //checkbox도 모든 체크박스 각각에 넣어야함
                            line = sr.ReadLine();
                        }
                    }
                    sr.Close();
                }
                path = Application.StartupPath + @"\SaveColor\" + lbl_YM.Text + "-" + Convert.ToString(i) + ".txt";
                if (File.Exists(path))
                {
                    StreamReader sr = new StreamReader(path);

                    string line;
                    line = sr.ReadLine();
                    if (line == "Red")
                        cell[i].DayLabel.BackColor = Color.Red;
                    if (line == "Blue")
                        cell[i].DayLabel.BackColor = Color.Blue;
                    if (line == "Green")
                        cell[i].DayLabel.BackColor = Color.Green;
                    if (line == "Yellow")
                        cell[i].DayLabel.BackColor = Color.Yellow;

                    sr.Close();
                }
                DayView.Controls.Add(cell[index], col, row);
                //날짜로드
                col++;
                if (col % 7 == 0)
                {
                    row++;
                    col = 0;
                }
            }
        }

        public void SetDay(DateTime dtValue)
        {
            ClearCell();
            DateTime Start = new DateTime(dtValue.Year, dtValue.Month, 1);
            int End = DateTime.DaysInMonth(dtValue.Year, dtValue.Month);
            int Week = (int)Start.DayOfWeek;
            for (int i = 1; i <= End; i++)
            {
                int index = i + Week - 1;
                cell[index].DayLabel.Text = i.ToString();
            }
            SetView(Week, End);
            refreshAssignToDate();
        }

        public void ClearCell()
        {
            for (int i = 0; i < 40; i++)
            {
                cell[i].MyList.Items.Clear();
                cell[i].KwList.Items.Clear();
                cell[i].DayLabel.BackColor = Color.Transparent;
            }
            DayView.Controls.Clear();
        }

        private void btnHidding_Click(object sender, EventArgs e)
        {
            this.WindowState = FormWindowState.Minimized;
        }

        private void pre_month_Click(object sender, EventArgs e)
        {
            DateTime dt = DT.AddMonths(-1);
            lbl_YM.Text = dt.ToString("yyyy-MM");
            SetDay(dt);
            DT = dt;
        }

        private void next_month_Click(object sender, EventArgs e)
        {
            DateTime dt = DT.AddMonths(1);
            lbl_YM.Text = dt.ToString("yyyy-MM");
            SetDay(dt);
            DT = dt;
        }
        #endregion

        #region Selenium Login Method
        private void btn_Login_Click(object sender, EventArgs e)
        {
            if (btn_Login.Text.Equals("로그인"))
            {
                LoginForm loginform = new LoginForm(this);
                loginform.DataSendEvent += new DataGetEventHandler(this.loginOK);
                loginform.Show();
            }
            else
            {
                if (_driver != null)
                    _driver.Quit();
                btn_Login.Text = "로그인";
            }
        }

        private void loginOK(string data)
        {
            if (data.Equals("loginOk"))
            {
                btn_Login.Text = "로그아웃";
            }
        }

        public bool WaitForVisible(By by)
        {
            WebDriverWait wait = new WebDriverWait(_driver, TimeSpan.FromSeconds(10));

            try
            {
                wait.Until(SeleniumExtras.WaitHelpers.ExpectedConditions.ElementIsVisible(by));
            }
            catch (Exception e)
            {
                return false;
            }

            return true;
        }

        public bool WaitForInvisible(By by)
        {
            WebDriverWait wait = new WebDriverWait(_driver, TimeSpan.FromSeconds(10));

            try
            {
                wait.Until(SeleniumExtras.WaitHelpers.ExpectedConditions.InvisibilityOfElementLocated(by));
            }
            catch (Exception e)
            {
                return false;
            }

            return true;
        }

        private void Kalendar_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (_driver != null)
                _driver.Quit();
        }
        #endregion

        #region Crawling
        private bool crawlingNotice()
        {
            if (_driver == null)
            {
                MessageBox.Show("로그인 후 이용할 수 있습니다.");

                return false;
            }

            decideNum = 1;

            string lvwString = null;

            _driver.Navigate().GoToUrl("https://klas.kw.ac.kr/std/lis/sport/d052b8f845784c639f036b102fdc3023/BoardListStdPage.do");
            if (!WaitForVisible(By.CssSelector(".card")))
            {
                MessageBox.Show("실패했습니다");
                return false;
            }

            try
            {
                WaitForInvisible(By.ClassName("vld-background"));
                var subjectList = _driver.FindElementByXPath("//*[@id=\"appSelectSubj\"]/div[2]/div/div[2]/select");
                var selectList = new SelectElement(subjectList);
                IList<IWebElement> options = subjectList.FindElements(By.TagName("option"));
                int index = 0;
                dictNotices = new Dictionary<string, List<By>>();

                try
                {
                    foreach (IWebElement option in options)
                    {
                        selectList.SelectByIndex(index++);

                        WaitForInvisible(By.ClassName("vld-background"));

                        var pageTable = _driver.FindElementByXPath("//*[@id=\"appModule\"]/ul");
                        IList<IWebElement> pageList = pageTable.FindElements(By.TagName("li"));

                        if (pageList.Count == 3)
                        { //공지사항 페이지가 1개일 때
                            string subjStr = option.Text.Trim().Split('(')[0];
                            var assignTable = _driver.FindElementByXPath("//*[@id=\"appModule\"]/table/tbody");

                            IList<IWebElement> assignList = assignTable.FindElements(By.TagName("tr"));
                            int numAssign = 1;
                            List<By> xpaths = new List<By>();

                            foreach (IWebElement element in assignList)
                            {
                                string xpath = "//*[@id=\"appModule\"]/table/tbody/tr";
                                xpath += ("[" + numAssign++ + "]");
                                xpaths.Add(By.XPath(xpath));
                            }

                            dictNotices.Add(subjStr + " 1", xpaths);

                            foreach (IWebElement element in assignList)
                            {
                                IList<IWebElement> tdlist = element.FindElements(By.TagName("td"));
                                if (tdlist.Count == 0) throw new Exception();
                                if (tdlist[0].Text == "글이 없습니다.") break;

                                string title = tdlist[1].Text;
                                string date = tdlist[4].Text;

                                lvwString += subjStr + "♣" + title + "♣" + date + "▣";
                            }
                        }
                        else if (pageList.Count > 3)
                        {
                            for (int k = 1; k < pageList.Count - 1; k++)
                            {
                                IList<IWebElement> aList = pageTable.FindElements(By.TagName("a"));
                                if (aList.Count == 0) throw new Exception();

                                aList[k].Click();
                                WaitForInvisible(By.ClassName("vld-background"));

                                string subjStr = option.Text.Trim().Split('(')[0];
                                var assignTable = _driver.FindElementByXPath("//*[@id=\"appModule\"]/table/tbody");

                                IList<IWebElement> assignList = assignTable.FindElements(By.TagName("tr"));
                                int numAssign = 1;
                                List<By> xpaths = new List<By>();

                                foreach (IWebElement element in assignList)
                                {
                                    string xpath = "//*[@id=\"appModule\"]/table/tbody/tr";
                                    xpath += ("[" + numAssign++ + "]");
                                    xpaths.Add(By.XPath(xpath));
                                }

                                dictNotices.Add(subjStr + " " + k.ToString(), xpaths);

                                foreach (IWebElement element in assignList)
                                {
                                    IList<IWebElement> tdlist = element.FindElements(By.TagName("td"));
                                    if (tdlist.Count == 0) throw new Exception();
                                    if (tdlist[0].Text == "글이 없습니다.") break;

                                    string title = tdlist[1].Text;
                                    string date = tdlist[4].Text;

                                    lvwString += subjStr + "♣" + title + "♣" + date + "▣";
                                }
                            }
                        }
                    }
                    lvwPath = seleniumPath + "\\lvwPath.txt";

                    WaitForInvisible(By.ClassName("vld-background"));

                    int lvwStringLength = lvwString.Length;
                    lvwString = lvwString.Substring(0, lvwStringLength - 1);
                    System.IO.File.WriteAllText(lvwPath, lvwString);
                    decideNum = 0;
                    return true;
                }
                catch (Exception ex)
                {
                    MessageBox.Show(ex.ToString());
                    return false;
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.ToString());
                return false;
            }
        }

        private bool crawlingAssign()
        {
            if (_driver == null)
            {
                MessageBox.Show("로그인 후 이용할 수 있습니다.");
                return false;
            }

            _driver.Navigate().GoToUrl("https://klas.kw.ac.kr/std/lis/evltn/TaskStdPage.do");
            if (!WaitForVisible(By.CssSelector(".card")))
            {
                MessageBox.Show("실패했습니다");
                return false;
            }
            try
            {
                var subjectList = _driver.FindElementByXPath("//*[@id=\"appSelectSubj\"]/div[2]/div/div[2]/select");
                var selectList = new SelectElement(subjectList);
                IList<IWebElement> options = subjectList.FindElements(By.TagName("option"));
                int index = 0;
                List<string> assignFile = new List<string>();

                try
                {
                    foreach (IWebElement option in options)
                    {
                        selectList.SelectByIndex(index++);
                        WaitForInvisible(By.ClassName("vld-background"));

                        string subjStr = option.Text.Trim().Split('(')[0];
                        var assignTable = _driver.FindElementByXPath("//*[@id=\"appModule\"]/div/div[2]/table");

                        IList<IWebElement> assignList = assignTable.FindElements(By.TagName("tbody"));
                        int numAssign = 1;
                        //List<By> xpaths = new List<By>();

                        //foreach (IWebElement element in assignList)
                        //{
                        //    string xpath = "//*[@id=\"appModule\"]/div/div[2]/table/tbody";
                        //    xpath += ("[" + numAssign++ + "]");
                        //    xpaths.Add(By.XPath(xpath));
                        //}

                        foreach (IWebElement element in assignList)
                        {
                            IList<IWebElement> tdlist = element.FindElements(By.TagName("td"));
                            if (tdlist.Count == 0) throw new Exception();
                            if (tdlist[0].Text == "출제된 레포트가 없습니다.") break;

                            string title = tdlist[1].Text;
                            string date = tdlist[2].Text;
                            string checkSubmit = tdlist[3].Text;

                            string assign = subjStr + "@" + title + "@" + date + "@" + checkSubmit;
                            assignFile.Add(assign);
                        }
                    }

                    assignPath = seleniumPath + "\\assignList.txt";

                    WaitForInvisible(By.ClassName("vld-background"));
                    string assignString = null;

                    foreach (string assign in assignFile)
                    {
                        assignString += (assign + "\n");
                    }
                    System.IO.File.WriteAllText(assignPath, assignString);
                    return true;
                }
                catch (Exception ex)
                {
                    MessageBox.Show(ex.ToString());
                    return false;
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.ToString());
                return false;
            }
        }

        private void refreshAssignToDate()
        {
            if (!System.IO.File.Exists(assignPath)) return;

            string[] assignString = System.IO.File.ReadAllLines(assignPath);
            

            for(int i = 0; i < 40; i++)
            {
                cell[i].KwList.Items.Clear();
            }

            foreach (string assign in assignString)
            {
                string subject = assign.Split('@')[0].Trim();
                string title = assign.Split('@')[1];
                string deadline = assign.Split('@')[2].Split('~')[1].Trim().Split(' ')[0];
                string submit = assign.Split('@')[3];

                string year = deadline.Split('-')[0];
                string month = deadline.Split('-')[1];
                string day = deadline.Split('-')[2];

                if(lbl_YM.Text.Equals(year + "-" + month))
                {
                    for(int i = 0; i < 40; i++)
                    {
                        if (cell[i].DayLabel.Text.Equals(day))
                        {
                            if (submit.Equals("제출"))
                            {
                                cell[i].KwList.Items.Add(subject + " - " + title, true);
                                cell[i].KwList.SetItemCheckState(cell[i].KwList.Items.Count - 1, CheckState.Indeterminate);
                            }
                            else
                            {
                                cell[i].KwList.Items.Add(subject + " - " + title, false);
                            }

                            if (cell[i].KwList.CheckedIndices.Count < cell[i].KwList.Items.Count) cell[i].DayLabel.BackColor = Color.Red;
                            else cell[i].DayLabel.BackColor = Color.Transparent;
                            break;
                        }
                    }
                }                
            }

        }

        private void btn_Refresh_Click(object sender, EventArgs e)
        {
            if(!crawlingNotice() || !crawlingAssign())
            {
                MessageBox.Show("크롤링 도중 문제가 생겼습니다.");
                return;
            }

            for(int i = 0; i < 40; i++)
            {
                cell[i].KwList.Items.Clear();
            }

            refreshAssignToDate();
        }

        private void btn_ShowNotice_Click(object sender, EventArgs e)
        {
            if (decideNum == 1)
            {
                MessageBox.Show("새로고침을 누른 뒤에 공지사항을 볼 수 있습니다.");
                return;
            }

            noticeListForm = new NoticeListForm(dictNotices, _driver);
            noticeListForm.DataSendEvent += new DataGetEventHandler(this.CreateNoticeShowForm);
            noticeListForm.Show();
        }

        private void CreateNoticeShowForm(string data)
        {
            if (data.Equals("NoticeListForm close"))
            {
                noticeListForm.Visible = false;
            }
            else
            {
                string[] temp = data.Split('▦');
                noticeShowForm = new NoticeShowForm(temp[0], _driver, temp[1]);
                noticeShowForm.DataSendEvent += new DataGetEventHandler(this.NoticeShowFormCloseMethod);
                noticeShowForm.Show();
                WaitForInvisible(By.ClassName("vld-background"));
            }
        }

        private void NoticeShowFormCloseMethod(string data)
        {
            if (data.Equals("NoticeShowForm close"))
            {
                noticeShowForm.Visible = false;
            }
        }

        private void kwList_MouseDoubleClick(object sender, EventArgs e)
        {
            CheckedListBox checkedList = sender as CheckedListBox;

            if (checkedList.SelectedIndex == -1) {
                return;
            }

            int index = checkedList.SelectedIndex;

            if (_driver == null)
            {
                if (checkedList.GetItemChecked(index))
                {
                    checkedList.SetItemChecked(index, false);
                }
                MessageBox.Show("로그인 후 이용할 수 있습니다.");
                return;
            }

            if (checkedList.GetItemCheckState(index) == CheckState.Indeterminate)
            {
                return;
            }

            _driver.Navigate().GoToUrl("https://klas.kw.ac.kr/std/lis/evltn/TaskStdPage.do");
            if (!WaitForVisible(By.CssSelector(".card")))
            {
                if (checkedList.GetItemChecked(index))
                {
                    checkedList.SetItemChecked(index, false);
                }
                MessageBox.Show("실패했습니다");
                return;
            }
            
            string selectedString = checkedList.Items[index].ToString();
            string selectSubj = selectedString.Split('-')[0].Trim() + " ";
            string selectTitle = selectedString.Split('-')[1].Trim();

            var subjectList = _driver.FindElementByXPath("//*[@id=\"appSelectSubj\"]/div[2]/div/div[2]/select");
            var selectList = new SelectElement(subjectList);
            IList<IWebElement> options = subjectList.FindElements(By.TagName("option"));

            foreach (IWebElement option in options)
            {
                if (option.Text.Trim().Split('(')[0].Equals(selectSubj))
                {
                    selectList.SelectByText(option.Text);
                    WaitForInvisible(By.ClassName("vld-background"));
                    break;
                }
            }

            var assignTable = _driver.FindElementByXPath("//*[@id=\"appModule\"]/div/div[2]/table");
            IList<IWebElement> assignList = assignTable.FindElements(By.TagName("tbody"));
            try
            {
                foreach (IWebElement element in assignList)
                {
                    IList<IWebElement> tdlist = element.FindElements(By.TagName("td"));
                    if (tdlist.Count == 0) throw new Exception();
                    if (tdlist[0].Text == "출제된 레포트가 없습니다.") break;

                    if (tdlist[1].Text.Equals(selectTitle))
                    {
                        var lookupButton = tdlist[4].FindElement(By.TagName("button"));
                        lookupButton.Click();
                        WaitForInvisible(By.ClassName("vld-background"));

                        var submitFile = _driver.FindElementByXPath("//*[@id=\"appModule\"]/table[2]/tbody/tr[1]/td/div/input");
                        if (ofd.ShowDialog() == DialogResult.OK)
                        {
                            if (string.IsNullOrEmpty(ofd.FileName))
                            {
                                if (checkedList.GetItemChecked(index))
                                {
                                    checkedList.SetItemChecked(index, false);
                                }
                                MessageBox.Show("제출할 과제를 선택해주세요.");
                                return;
                            };

                            submitFile.SendKeys(ofd.FileName);
                            // 제목
                            _driver.FindElementByXPath("//*[@id=\"appModule\"]/table[2]/tbody/tr[2]/td/input").SendKeys(selectTitle + " 과제입니다");

                            // 내용
                            _driver.FindElementByXPath("//*[@id=\"textarea\"]").SendKeys(selectTitle + " 과제입니다.");

                            // 제출
                            _driver.FindElementByXPath("//*[@id=\"appModule\"]/div[4]/button[1]").Click();

                            checkedList.SetItemCheckState(checkedList.Items.IndexOf(selectedString), CheckState.Indeterminate);
                            saveAssign();
                            return;
                        }
                        else
                        {
                            if (checkedList.GetItemChecked(index))
                            {
                                checkedList.SetItemChecked(index, false);
                            }
                            MessageBox.Show("제출할 과제를 선택해주세요.");
                            return;
                        }
                    }
                }
            }
            catch
            {
                if (checkedList.GetItemChecked(index))
                {
                    checkedList.SetItemChecked(index, false);
                }
                MessageBox.Show("제출 기한이 아니거나 없는 과제입니다.");
                return;
            }
        }

        private void btnUpload_Click(object sender, EventArgs e)
        {
            if (_driver == null)
            {
                MessageBox.Show("로그인 후 이용할 수 있습니다.");
                return;
            }

            FileUpload fu = new FileUpload(this);

            for (int i = 0; i < 40; i++)
            {
                if (cell[i].KwList.Items.Count > 0 && cell[i].KwList.CheckedItems.Count < cell[i].KwList.Items.Count)
                {
                    fu.ComboDate.Items.Add(lbl_YM.Text + "-" + cell[i].DayLabel.Text);
                }
            }

            DialogResult dResult = fu.ShowDialog();
            if (dResult == DialogResult.OK)
            {
                MessageBox.Show("과제가 업로드 되었습니다.");
            }
            else
            {
                MessageBox.Show("과제 업로드에 실패했습니다.");
            }
        }

        public void saveAssign()
        {
            if (!System.IO.File.Exists(assignPath)) return;

            string[] assignString = File.ReadAllLines(assignPath);
            int index = 0;
            foreach (string assign in assignString)
            {
                string subject = assign.Split('@')[0].Trim();
                string title = assign.Split('@')[1];
                string deadline = assign.Split('@')[2].Split('~')[1].Trim().Split(' ')[0];
                string submit = assign.Split('@')[3];

                string year = deadline.Split('-')[0];
                string month = deadline.Split('-')[1];
                string day = deadline.Split('-')[2];

                if (submit.Equals("미제출"))
                {
                    if (lbl_YM.Text.Equals(year + "-" + month))
                    {
                        for (int i = 0; i < 40; i++)
                        {
                            if (cell[i].DayLabel.Text.Equals(day))
                            {
                                if (cell[i].KwList.GetItemCheckState(cell[i].KwList.Items.IndexOf(subject + " - " + title)) == CheckState.Indeterminate)
                                {
                                    string replaceAssign = assign.Replace("미제출", "제출");

                                    assignString[index] = replaceAssign;
                                    break;
                                }
                            }
                        }
                    }
                }
                index++;
            }
            File.WriteAllLines(assignPath, assignString);

            refreshAssignToDate();
        }
    }
    #endregion

}