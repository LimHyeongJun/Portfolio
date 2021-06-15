using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

//Selenium Library
using OpenQA.Selenium;
using OpenQA.Selenium.Chrome;
using OpenQA.Selenium.Support.UI;

namespace Kanlendar {
    public partial class NoticeListForm : Form {
        public DataGetEventHandler DataSendEvent;

        private int curMonth;
        private int curDay;

        private string path;
        private string lvwPath;

        private Dictionary<string, List<By>> dictNotices;
        protected ChromeDriver _driver = null;

        public NoticeListForm(Dictionary<string, List<By>> dictNotices, ChromeDriver _driver) {
            this.dictNotices = dictNotices;
            this._driver = _driver;

            InitializeComponent();
        }

        private void NoticeForm_Load(object sender, EventArgs e) {
            lvw_Notice.View = View.Details;

            lvw_Notice.Columns.Add("subject", "과목");
            lvw_Notice.Columns.Add("title", "제목");
            lvw_Notice.Columns.Add("date", "작성일");

            string curDate = DateTime.Now.ToString("MM-dd");
            string[] kk = curDate.Split('-');
            curMonth = Int32.Parse(kk[0]);
            curDay = Int32.Parse(kk[1]);

            for (int i = 0; i < lvw_Notice.Columns.Count; i++) {
                if (i == 1) {
                    lvw_Notice.Columns[i].Width = lvw_Notice.Width / 2;
                } else {
                    lvw_Notice.Columns[i].Width = lvw_Notice.Width / 4;
                }
                lvw_Notice.Columns[i].TextAlign = HorizontalAlignment.Left;
            }

            path = System.Reflection.Assembly.GetExecutingAssembly().Location;
            path = System.IO.Path.GetDirectoryName(path);
            lvwPath = path + "\\lvwPath.txt";


            rdo_twoWeek.Checked = false;
            rdo_threeWeek.Checked = false;
            rdo_oneMonth.Checked = false;
            rdo_twoMonth.Checked = false;
            rdo_oneWeek.Checked = false;
        }

        private bool WaitForVisible(By by) {
            WebDriverWait wait = new WebDriverWait(_driver, TimeSpan.FromSeconds(20));

            try {
                wait.Until(SeleniumExtras.WaitHelpers.ExpectedConditions.ElementIsVisible(by));
            } catch (Exception e) {
                return false;
            }

            return true;
        }

        private bool WaitForInvisible(By by) {
            WebDriverWait wait = new WebDriverWait(_driver, TimeSpan.FromSeconds(20));

            try {
                wait.Until(SeleniumExtras.WaitHelpers.ExpectedConditions.InvisibilityOfElementLocated(by));
            } catch (Exception e) {
                return false;
            }

            return true;
        }


        private void rdo_CheckedChanged(object sender, EventArgs e) {
            lvw_Notice.Items.Clear();
            string lvwString = System.IO.File.ReadAllText(lvwPath);

            string[] temp = lvwString.Split('▣');

            if (rdo_oneWeek.Checked) {
                foreach (var line in temp) {
                    string[] splitLine = line.Split('♣');
                    string[] kk = splitLine[2].Split('-');

                    int month = Int32.Parse(kk[1]);
                    int day = Int32.Parse(kk[2]);

                    int minusCurday = curDay - 7; //minusCurday가 0 이하이면 저번달로 넘어감
                    if (minusCurday <= 0) {
                        string previousDate = previousMonthDay(curMonth, curDay, 7);
                        temp = previousDate.Split('-');

                        int previousMonth = Int32.Parse(temp[0]);
                        int previousDay = Int32.Parse(temp[1]);

                        if (month < previousMonth)
                            continue;
                        else if (month == previousMonth && day < previousDay)
                            continue;
                    } else if (minusCurday > 0) {
                        if (month < curMonth)
                            continue;
                        else if (month == curMonth && day < minusCurday)
                            continue;
                    }
                    var lvwItem = new ListViewItem(new string[lvw_Notice.Columns.Count]);

                    for (int i = 0; i < lvw_Notice.Columns.Count; i++)
                        lvwItem.SubItems[i].Name = lvw_Notice.Columns[i].Name;

                    lvwItem.SubItems["subject"].Text = splitLine[0];
                    lvwItem.SubItems["title"].Text = splitLine[1];
                    lvwItem.SubItems["date"].Text = splitLine[2];

                    lvw_Notice.Items.Add(lvwItem);
                }

            } else if (rdo_twoWeek.Checked) {
                foreach (var line in temp) {
                    string[] splitLine = line.Split('♣');
                    string[] kk = splitLine[2].Split('-');

                    int month = Int32.Parse(kk[1]);
                    int day = Int32.Parse(kk[2]);

                    int minusCurday = curDay - 14; //minusCurday가 0 이하이면 저번달로 넘어감
                    if (minusCurday <= 0) {
                        string previousDate = previousMonthDay(curMonth, curDay, 14);
                        temp = previousDate.Split('-');

                        int previousMonth = Int32.Parse(temp[0]);
                        int previousDay = Int32.Parse(temp[1]);

                        if (month < previousMonth)
                            continue;
                        else if (month == previousMonth && day < previousDay)
                            continue;
                    } else if (minusCurday > 0) {
                        if (month < curMonth)
                            continue;
                        else if (month == curMonth && day < minusCurday)
                            continue;
                    }
                    var lvwItem = new ListViewItem(new string[lvw_Notice.Columns.Count]);

                    for (int i = 0; i < lvw_Notice.Columns.Count; i++)
                        lvwItem.SubItems[i].Name = lvw_Notice.Columns[i].Name;

                    lvwItem.SubItems["subject"].Text = splitLine[0];
                    lvwItem.SubItems["title"].Text = splitLine[1];
                    lvwItem.SubItems["date"].Text = splitLine[2];

                    lvw_Notice.Items.Add(lvwItem);
                }
            } else if (rdo_threeWeek.Checked) {
                foreach (var line in temp) {
                    string[] splitLine = line.Split('♣');
                    string[] kk = splitLine[2].Split('-');

                    int month = Int32.Parse(kk[1]);
                    int day = Int32.Parse(kk[2]);

                    int minusCurday = curDay - 21; //minusCurday가 0 이하이면 저번달로 넘어감
                    if (minusCurday <= 0) {
                        string previousDate = previousMonthDay(curMonth, curDay, 21);
                        temp = previousDate.Split('-');

                        int previousMonth = Int32.Parse(temp[0]);
                        int previousDay = Int32.Parse(temp[1]);

                        if (month < previousMonth)
                            continue;
                        else if (month == previousMonth && day < previousDay)
                            continue;
                    } else if (minusCurday > 0) {
                        if (month < curMonth)
                            continue;
                        else if (month == curMonth && day < minusCurday)
                            continue;
                    }
                    var lvwItem = new ListViewItem(new string[lvw_Notice.Columns.Count]);

                    for (int i = 0; i < lvw_Notice.Columns.Count; i++)
                        lvwItem.SubItems[i].Name = lvw_Notice.Columns[i].Name;

                    lvwItem.SubItems["subject"].Text = splitLine[0];
                    lvwItem.SubItems["title"].Text = splitLine[1];
                    lvwItem.SubItems["date"].Text = splitLine[2];

                    lvw_Notice.Items.Add(lvwItem);
                }
            } else if (rdo_oneMonth.Checked) {
                foreach (var line in temp) {
                    string[] splitLine = line.Split('♣');
                    string[] kk = splitLine[2].Split('-');

                    int month = Int32.Parse(kk[1]);
                    int day = Int32.Parse(kk[2]);

                    if (month < curMonth - 1)
                        continue;
                    else if (month <= curMonth - 1 && day < curDay)
                        continue;

                    var lvwItem = new ListViewItem(new string[lvw_Notice.Columns.Count]);

                    for (int i = 0; i < lvw_Notice.Columns.Count; i++)
                        lvwItem.SubItems[i].Name = lvw_Notice.Columns[i].Name;

                    lvwItem.SubItems["subject"].Text = splitLine[0];
                    lvwItem.SubItems["title"].Text = splitLine[1];
                    lvwItem.SubItems["date"].Text = splitLine[2];

                    lvw_Notice.Items.Add(lvwItem);
                }
            } else if (rdo_twoMonth.Checked) {
                foreach (var line in temp) {
                    string[] splitLine = line.Split('♣');
                    string[] kk = splitLine[2].Split('-');

                    int month = Int32.Parse(kk[1]);
                    int day = Int32.Parse(kk[2]);

                    if (month < curMonth - 2)
                        continue;
                    else if (month <= curMonth - 2 && day < curDay)
                        continue;

                    var lvwItem = new ListViewItem(new string[lvw_Notice.Columns.Count]);

                    for (int i = 0; i < lvw_Notice.Columns.Count; i++)
                        lvwItem.SubItems[i].Name = lvw_Notice.Columns[i].Name;

                    lvwItem.SubItems["subject"].Text = splitLine[0];
                    lvwItem.SubItems["title"].Text = splitLine[1];
                    lvwItem.SubItems["date"].Text = splitLine[2];

                    lvw_Notice.Items.Add(lvwItem);
                }
            }
        }

        public string previousMonthDay(int month, int day, int minusNum) {
            int remainMinumNum = minusNum;
            for (int i = day; i > 0; i--) {
                remainMinumNum--;
            }
            int returnMonth = month - 1;
            int returnDay = 0;
            if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
                returnDay = 31 - remainMinumNum;
            else if (month == 4 || month == 6 || month == 9 || month == 11)
                returnDay = 30 - remainMinumNum;
            else if (month == 2)
                returnDay = 29 - remainMinumNum;
            string returnStr = returnMonth + "-" + returnDay;
            return returnStr;
        }

        private void lvw_Notice_MouseDoubleClick(object sender, MouseEventArgs e) {
            _driver.Navigate().GoToUrl("https://klas.kw.ac.kr/std/lis/sport/d052b8f845784c639f036b102fdc3023/BoardListStdPage.do");
            if (!WaitForVisible(By.CssSelector(".card"))) {
                MessageBox.Show("실패했습니다");
                return;
            }
            WaitForInvisible(By.ClassName("vld-background"));

            string selectSubj = lvw_Notice.FocusedItem.SubItems["subject"].Text;
            string selectTitle = lvw_Notice.FocusedItem.SubItems["title"].Text;

            var subjectList = _driver.FindElementByXPath("//*[@id=\"appSelectSubj\"]/div[2]/div/div[2]/select");
            var selectList = new SelectElement(subjectList);
            IList<IWebElement> options = subjectList.FindElements(By.TagName("option"));

            foreach (IWebElement option in options) {
                if (option.Text.Trim().Split('(')[0].Equals(selectSubj)) {
                    selectList.SelectByText(option.Text);

                    break;
                }
            }
            WaitForInvisible(By.ClassName("vld-background"));

            var pageTable = _driver.FindElementByXPath("//*[@id=\"appModule\"]/ul");
            IList<IWebElement> pageList = pageTable.FindElements(By.TagName("li"));

            List<By> assignXpaths = new List<By>();

            if (pageList.Count == 3) {
                assignXpaths = dictNotices[selectSubj + " 1"];
                WaitForInvisible(By.ClassName("vld-background"));

                foreach (By xpath in assignXpaths) {
                    IList<IWebElement> tdlist = _driver.FindElement(xpath).FindElements(By.TagName("td"));
                    if (tdlist.Count == 0) throw new Exception();
                    if (tdlist[0].Text == "글이 없습니다.") break;

                    if (tdlist[1].Text.Equals(selectTitle)) {
                        tdlist[1].Click();
                        WaitForInvisible(By.ClassName("vld-background"));

                        var contentDiv = _driver.FindElementByXPath("//*[@id=\"appModule\"]/div[2]/div[3]/div");

                        string text = selectTitle + "▦" + contentDiv.Text;
                        DataSendEvent(text);

                        break;
                    }
                }
            } else if (pageList.Count > 3) {
                try {
                    for (int k = 1; k < pageList.Count - 1; k++) {
                        string subj = selectSubj + " " + k.ToString();
                        assignXpaths = dictNotices[subj];
                        WaitForInvisible(By.ClassName("vld-background"));
                        IList<IWebElement> aList = _driver.FindElementByXPath("//*[@id=\"appModule\"]/ul").FindElements(By.TagName("a"));
                        if (aList.Count == 0) throw new Exception();

                        aList[k].Click();
                        WaitForInvisible(By.ClassName("vld-background"));

                        foreach (By xpath in assignXpaths) {
                            IList<IWebElement> tdlist = _driver.FindElement(xpath).FindElements(By.TagName("td"));
                            if (tdlist.Count == 0) throw new Exception();
                            if (tdlist[0].Text == "글이 없습니다.") break;

                            if (tdlist[1].Text.Equals(selectTitle)) {
                                tdlist[1].Click();
                                WaitForInvisible(By.ClassName("vld-background"));

                                var contentDiv = _driver.FindElementByXPath("//*[@id=\"appModule\"]/div[2]/div[3]/div");

                                string text = selectTitle + "▦" + contentDiv.Text;
                                DataSendEvent(text);

                                break;
                            }
                        }
                    }
                } catch {

                }
            }
        }

        private void NoticeListForm_FormClosed(object sender, FormClosedEventArgs e) {
            DataSendEvent("NoticeListForm close");
        }
    }
}
