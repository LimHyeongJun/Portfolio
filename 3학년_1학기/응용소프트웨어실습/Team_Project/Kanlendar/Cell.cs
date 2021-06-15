using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Kanlendar {
    public partial class Cell : UserControl {
        public Cell() {
            SetCell();
            InitializeComponent();
            this.SetStyle(ControlStyles.DoubleBuffer |
               ControlStyles.UserPaint |
               ControlStyles.AllPaintingInWmPaint,
               true);
            this.UpdateStyles();
        }

        public CheckedListBox MyList {
            set { clb_my = value; }
            get { return clb_my; }
        }
        public CheckedListBox KwList {
            set { clb_kw = value; }
            get { return clb_kw; }
        }
        public Label DayLabel {
            set { lb_day = value; }
            get { return lb_day; }
        }
        public void SetCell() {
            this.Dock = DockStyle.Fill;
            this.Padding = new Padding(0);
            this.Margin = new Padding(0);            
        }

        private void clb_my_MouseLeave(object sender, EventArgs e)
        {
            (sender as CheckedListBox).ClearSelected();
        }

        private void clb_kw_MouseLeave(object sender, EventArgs e)
        {
            (sender as CheckedListBox).ClearSelected();
        }

        private void clb_kw_MouseClick(object sender, MouseEventArgs e)
        {
            CheckedListBox list = sender as CheckedListBox;
        }

        private void clb_kw_ItemCheck(object sender, ItemCheckEventArgs e)
        {
            if (e.CurrentValue == CheckState.Indeterminate) e.NewValue = CheckState.Indeterminate;
        }
    }
}
