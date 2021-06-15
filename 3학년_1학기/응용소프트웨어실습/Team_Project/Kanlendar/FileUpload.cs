using OpenQA.Selenium.Chrome;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

using OpenQA.Selenium;
//using OpenQA.Selenium.Chrome;
using OpenQA.Selenium.Support.UI;

namespace Kanlendar
{
    public partial class FileUpload : Form
    {
        private Kalendar kalendar;

        public FileUpload(Kalendar kalendar)
        {
            InitializeComponent();
            this.kalendar = kalendar;
            cmbDate.Text = "날짜 (yyyy-MM-dd)";
            cmbAssign.Text = "과제";
        }

        public ComboBox ComboDate
        {
            set { cmbDate = value; }
            get { return cmbDate; }
        }

        private void assign_DragEnter(object sender, DragEventArgs e)
        {
            string[] fileNames = (string[])e.Data.GetData(DataFormats.FileDrop);
            txtAssign.Text = fileNames[0];
        }

        private void assign_DragDrop(object sender, DragEventArgs e)
        {
            if (e.Data.GetDataPresent(DataFormats.FileDrop))
                e.Effect = DragDropEffects.Copy;
        }

        private void btnSubmit_Click(object sender, EventArgs e)
        {
            if (kalendar._driver == null)
            {
                MessageBox.Show("로그인 후 이용할 수 있습니다.");
                this.DialogResult = DialogResult.Cancel;
            }

            kalendar._driver.Navigate().GoToUrl("https://klas.kw.ac.kr/std/lis/evltn/TaskStdPage.do");
            if (!kalendar.WaitForVisible(By.CssSelector(".card")))
            {
                MessageBox.Show("실패했습니다");
                this.DialogResult = DialogResult.Cancel;
                return;
            }

            string selectedString = cmbAssign.SelectedItem.ToString();
            string selectSubj = selectedString.Split('-')[0].Trim() + " ";
            string selectTitle = selectedString.Split('-')[1].Trim();

            var subjectList = kalendar._driver.FindElementByXPath("//*[@id=\"appSelectSubj\"]/div[2]/div/div[2]/select");
            var selectList = new SelectElement(subjectList);
            IList<IWebElement> options = subjectList.FindElements(By.TagName("option"));

            foreach (IWebElement option in options)
            {
                if (option.Text.Trim().Split('(')[0].Equals(selectSubj))
                {
                    selectList.SelectByText(option.Text);
                    kalendar.WaitForInvisible(By.ClassName("vld-background"));
                    break;
                }
            }

            var assignTable = kalendar._driver.FindElementByXPath("//*[@id=\"appModule\"]/div/div[2]/table");
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
                        kalendar.WaitForInvisible(By.ClassName("vld-background"));

                        var submitFile = kalendar._driver.FindElementByXPath("//*[@id=\"appModule\"]/table[2]/tbody/tr[1]/td/div/input");
                        if (string.IsNullOrEmpty(txtAssign.Text)) { MessageBox.Show("파일을 업로드해주세요"); return; }
                        else
                        {
                            submitFile.SendKeys(txtAssign.Text);
                            // 제목
                            kalendar._driver.FindElementByXPath("//*[@id=\"appModule\"]/table[2]/tbody/tr[2]/td/input").SendKeys(selectTitle + " 과제입니다");

                            // 내용
                            kalendar._driver.FindElementByXPath("//*[@id=\"textarea\"]").SendKeys(selectTitle + " 과제입니다.");

                            // 제출
                            kalendar._driver.FindElementByXPath("//*[@id=\"appModule\"]/div[4]/button[1]").Click();

                            for (int i = 0; i < 40; i++)
                            {
                                if (cmbDate.SelectedItem.ToString().Split('-')[2].Equals(kalendar.cell[i].DayLabel.Text))
                                {
                                    if (kalendar.cell[i].KwList.Items.Contains(cmbAssign.Text))
                                    {
                                        kalendar.cell[i].KwList.SetItemCheckState(kalendar.cell[i].KwList.Items.IndexOf(cmbAssign.Text), CheckState.Indeterminate);
                                    }
                                }
                            }
                            kalendar.saveAssign();
                            this.DialogResult = DialogResult.OK;
                            return;
                        }
                    }
                }
            }
            catch
            {
                MessageBox.Show("제출 기한이 아니거나 없는 과제입니다.");
                this.DialogResult = DialogResult.Cancel;
                return;
            }
        }

        private void cmbDate_SelectedIndexChanged(object sender, EventArgs e)
        {
            cmbAssign.Items.Clear();
            cmbDate.SelectedItem.ToString();
            for (int i = 0; i < 40; i++)
            {
                if (cmbDate.SelectedItem.ToString().Split('-')[2].Equals(kalendar.cell[i].DayLabel.Text))
                {
                    int j = 0;
                    foreach(object assign in kalendar.cell[i].KwList.Items)
                    {
                        if(kalendar.cell[i].KwList.GetItemChecked(j++) == false)
                            cmbAssign.Items.Add(assign.ToString());
                    }
                }
            }
        }
    }
}
