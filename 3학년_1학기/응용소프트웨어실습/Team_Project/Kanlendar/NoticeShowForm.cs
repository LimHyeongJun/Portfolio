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
    public partial class NoticeShowForm : Form {
        public DataGetEventHandler DataSendEvent;

        private string noticeText = null;
        protected ChromeDriver _driver = null;
        private string title = null;

        public NoticeShowForm(string title, ChromeDriver _driver, string noticeText) {
            this.title = title;
            this.noticeText = noticeText;
            this._driver = _driver;

            InitializeComponent();
        }

        private void Form3_Load(object sender, EventArgs e) {
            this.Text = title;
            txt_notice.Text += noticeText;

            txt_notice.Focus();
        }

        private void Form3_FormClosed(object sender, FormClosedEventArgs e) {
            DataSendEvent("NoticeShowForm close");
        }
    }
}
