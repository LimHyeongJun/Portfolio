namespace Kanlendar {
    partial class Cell {
        /// <summary> 
        /// 필수 디자이너 변수입니다.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary> 
        /// 사용 중인 모든 리소스를 정리합니다.
        /// </summary>
        /// <param name="disposing">관리되는 리소스를 삭제해야 하면 true이고, 그렇지 않으면 false입니다.</param>
        protected override void Dispose(bool disposing) {
            if (disposing && (components != null)) {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region 구성 요소 디자이너에서 생성한 코드

        /// <summary> 
        /// 디자이너 지원에 필요한 메서드입니다. 
        /// 이 메서드의 내용을 코드 편집기로 수정하지 마세요.
        /// </summary>
        private void InitializeComponent() {
            this.tableLayoutPanel1 = new System.Windows.Forms.TableLayoutPanel();
            this.clb_kw = new System.Windows.Forms.CheckedListBox();
            this.lb_day = new System.Windows.Forms.Label();
            this.clb_my = new System.Windows.Forms.CheckedListBox();
            this.tableLayoutPanel1.SuspendLayout();
            this.SuspendLayout();
            // 
            // tableLayoutPanel1
            // 
            this.tableLayoutPanel1.ColumnCount = 1;
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutPanel1.Controls.Add(this.clb_kw, 0, 2);
            this.tableLayoutPanel1.Controls.Add(this.lb_day, 0, 0);
            this.tableLayoutPanel1.Controls.Add(this.clb_my, 0, 1);
            this.tableLayoutPanel1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tableLayoutPanel1.Location = new System.Drawing.Point(0, 0);
            this.tableLayoutPanel1.Margin = new System.Windows.Forms.Padding(0);
            this.tableLayoutPanel1.Name = "tableLayoutPanel1";
            this.tableLayoutPanel1.RowCount = 3;
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 20F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 40F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 40F));
            this.tableLayoutPanel1.Size = new System.Drawing.Size(150, 150);
            this.tableLayoutPanel1.TabIndex = 0;
            // 
            // clb_kw
            // 
            this.clb_kw.AllowDrop = true;
            this.clb_kw.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.clb_kw.Dock = System.Windows.Forms.DockStyle.Fill;
            this.clb_kw.FormattingEnabled = true;
            this.clb_kw.HorizontalScrollbar = true;
            this.clb_kw.IntegralHeight = false;
            this.clb_kw.Location = new System.Drawing.Point(0, 90);
            this.clb_kw.Margin = new System.Windows.Forms.Padding(0);
            this.clb_kw.Name = "clb_kw";
            this.clb_kw.Size = new System.Drawing.Size(150, 60);
            this.clb_kw.TabIndex = 2;
            this.clb_kw.ItemCheck += new System.Windows.Forms.ItemCheckEventHandler(this.clb_kw_ItemCheck);
            this.clb_kw.MouseLeave += new System.EventHandler(this.clb_kw_MouseLeave);
            // 
            // lb_day
            // 
            this.lb_day.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.lb_day.AutoSize = true;
            this.lb_day.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.lb_day.Font = new System.Drawing.Font("Arial", 16.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lb_day.Location = new System.Drawing.Point(0, 0);
            this.lb_day.Margin = new System.Windows.Forms.Padding(0);
            this.lb_day.Name = "lb_day";
            this.lb_day.Size = new System.Drawing.Size(150, 30);
            this.lb_day.TabIndex = 0;
            this.lb_day.Text = "label1";
            // 
            // clb_my
            // 
            this.clb_my.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.clb_my.Dock = System.Windows.Forms.DockStyle.Fill;
            this.clb_my.FormattingEnabled = true;
            this.clb_my.HorizontalScrollbar = true;
            this.clb_my.IntegralHeight = false;
            this.clb_my.Location = new System.Drawing.Point(0, 30);
            this.clb_my.Margin = new System.Windows.Forms.Padding(0);
            this.clb_my.Name = "clb_my";
            this.clb_my.Size = new System.Drawing.Size(150, 60);
            this.clb_my.TabIndex = 1;
            this.clb_my.MouseLeave += new System.EventHandler(this.clb_my_MouseLeave);
            // 
            // Cell
            // 
            this.AllowDrop = true;
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.tableLayoutPanel1);
            this.Name = "Cell";
            this.tableLayoutPanel1.ResumeLayout(false);
            this.tableLayoutPanel1.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel1;
        private System.Windows.Forms.Label lb_day;
        private System.Windows.Forms.CheckedListBox clb_my;
        private System.Windows.Forms.CheckedListBox clb_kw;
    }
}
