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
    public partial class LoginForm : Form {
        public DataGetEventHandler DataSendEvent;

        Kalendar ks;

        private string path;
        private string autoLoginPath;

        public LoginForm(Kalendar ks) {
            this.ks = ks;

            InitializeComponent();

            ks._driverService = ChromeDriverService.CreateDefaultService();
            ks._driverService.HideCommandPromptWindow = true;

            ks._defaultOptions = new ChromeOptions();
            ks._defaultOptions.AddArgument("disable-gpu");
            ks._headlessOptions = new ChromeOptions();
            ks._headlessOptions.AddArgument("disable-gpu");
            ks._headlessOptions.AddArgument("headless");
        }


        private void LoginForm_Load(object sender, EventArgs e) {
            path = System.Reflection.Assembly.GetExecutingAssembly().Location;
            path = System.IO.Path.GetDirectoryName(path);

            autoLoginPath = path + "\\autoLogin.txt";
            if (System.IO.File.Exists(autoLoginPath)) {
                string text = System.IO.File.ReadAllText(autoLoginPath);
                string[] temp = text.Split(' ');
                if (temp[0].Equals("true") && temp[1] != null && temp[2] != null) { //자동로그인이 체크되어 있으면
                    chb_autoLogin.Checked = true;
                    txt_id.Text = temp[1];
                    txt_pw.Text = temp[2];
                    //this.ActiveControl = txt_pw;
                }
            }
        }

        private void btn_login_Click(object sender, EventArgs e) {
            klasLogin(ks);
        }

        private bool WaitForVisible(By by) {
            WebDriverWait wait = new WebDriverWait(ks._driver, TimeSpan.FromSeconds(20));

            try {
                wait.Until(SeleniumExtras.WaitHelpers.ExpectedConditions.ElementIsVisible(by));
            } catch (Exception e) {
                return false;
            }

            return true;
        }

        private bool WaitForInvisible(By by) {
            WebDriverWait wait = new WebDriverWait(ks._driver, TimeSpan.FromSeconds(20));

            try {
                wait.Until(SeleniumExtras.WaitHelpers.ExpectedConditions.InvisibilityOfElementLocated(by));
            } catch (Exception e) {
                return false;
            }

            return true;
        }

        private bool klasLogin(Kalendar ks) {
            string userID = txt_id.Text;
            string userPW = txt_pw.Text;

            if (string.IsNullOrEmpty(userID) && string.IsNullOrEmpty(userPW)) {
                MessageBox.Show("아이디 또는 패스워드를 입력해주세요.");
                return false;
            }

            if (ks._driver == null) {
                if (chb_headless.Checked == false)
                    ks._driver = new ChromeDriver(ks._driverService, ks._headlessOptions);
                else
                    ks._driver = new ChromeDriver(ks._driverService, ks._defaultOptions);
            } else {
                ks._driver.Quit();
                if (chb_headless.Checked == false)
                    ks._driver = new ChromeDriver(ks._driverService, ks._headlessOptions);
                else
                    ks._driver = new ChromeDriver(ks._driverService, ks._defaultOptions);
            }

            ks._driver.Navigate().GoToUrl("https://klas.kw.ac.kr");
            WaitForInvisible(By.ClassName("vld-background"));

            if (!WaitForVisible(By.XPath("//*[@id=\"loginId\"]"))) {
                MessageBox.Show("접속에 실패했습니다.");
                return false;
            }

            if (btn_login.Text.Equals("로그인")) {
                var klasid = ks._driver.FindElementByXPath("//*[@id='loginId']");
                var klaspw = ks._driver.FindElementByXPath("//*[@id='loginPwd']");

                klasid.SendKeys(txt_id.Text);
                klaspw.SendKeys(txt_pw.Text);

                var loginbtn = ks._driver.FindElementByXPath("/html/body/div[1]/div/div/div[2]/form/div[2]/button");
                loginbtn.Click();

                if (chb_autoLogin.Checked) {
                    string result = "true " + txt_id.Text + " " + txt_pw.Text;
                    System.IO.File.WriteAllText(autoLoginPath, result);
                } else {
                    string result = "false ";
                    System.IO.File.WriteAllText(autoLoginPath, result);
                }

                if (WaitForVisible(By.XPath("//*[@id=\"appModule\"]/div/div[1]"))) {

                    DataSendEvent("loginOk");
                    this.Hide();
                    return true;
                } else {
                    MessageBox.Show("로그인에 실패했습니다.\n아이디와 패스워드를 다시 입력하세요.");
                    ks._driver.Close();
                    return false;
                }
            }
            return true;
        }
    }
}
