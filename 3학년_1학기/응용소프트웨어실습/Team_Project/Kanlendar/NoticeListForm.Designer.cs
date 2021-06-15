namespace Kanlendar {
    partial class NoticeListForm {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing) {
            if (disposing && (components != null)) {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent() {
            this.lvw_Notice = new System.Windows.Forms.ListView();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.rdo_twoMonth = new System.Windows.Forms.RadioButton();
            this.rdo_oneMonth = new System.Windows.Forms.RadioButton();
            this.rdo_threeWeek = new System.Windows.Forms.RadioButton();
            this.rdo_twoWeek = new System.Windows.Forms.RadioButton();
            this.rdo_oneWeek = new System.Windows.Forms.RadioButton();
            this.groupBox2.SuspendLayout();
            this.SuspendLayout();
            // 
            // lvw_Notice
            // 
            this.lvw_Notice.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.lvw_Notice.FullRowSelect = true;
            this.lvw_Notice.GridLines = true;
            this.lvw_Notice.HideSelection = false;
            this.lvw_Notice.Location = new System.Drawing.Point(14, 99);
            this.lvw_Notice.MultiSelect = false;
            this.lvw_Notice.Name = "lvw_Notice";
            this.lvw_Notice.Size = new System.Drawing.Size(594, 196);
            this.lvw_Notice.TabIndex = 14;
            this.lvw_Notice.UseCompatibleStateImageBehavior = false;
            this.lvw_Notice.MouseDoubleClick += new System.Windows.Forms.MouseEventHandler(this.lvw_Notice_MouseDoubleClick);
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.rdo_twoMonth);
            this.groupBox2.Controls.Add(this.rdo_oneMonth);
            this.groupBox2.Controls.Add(this.rdo_threeWeek);
            this.groupBox2.Controls.Add(this.rdo_twoWeek);
            this.groupBox2.Controls.Add(this.rdo_oneWeek);
            this.groupBox2.Location = new System.Drawing.Point(159, 19);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(300, 60);
            this.groupBox2.TabIndex = 13;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "공지사항 가져오기";
            // 
            // rdo_twoMonth
            // 
            this.rdo_twoMonth.AutoSize = true;
            this.rdo_twoMonth.Location = new System.Drawing.Point(229, 24);
            this.rdo_twoMonth.Name = "rdo_twoMonth";
            this.rdo_twoMonth.Size = new System.Drawing.Size(51, 19);
            this.rdo_twoMonth.TabIndex = 4;
            this.rdo_twoMonth.TabStop = true;
            this.rdo_twoMonth.Text = "2달";
            this.rdo_twoMonth.UseVisualStyleBackColor = true;
            this.rdo_twoMonth.CheckedChanged += new System.EventHandler(this.rdo_CheckedChanged);
            // 
            // rdo_oneMonth
            // 
            this.rdo_oneMonth.AutoSize = true;
            this.rdo_oneMonth.Location = new System.Drawing.Point(172, 25);
            this.rdo_oneMonth.Name = "rdo_oneMonth";
            this.rdo_oneMonth.Size = new System.Drawing.Size(51, 19);
            this.rdo_oneMonth.TabIndex = 3;
            this.rdo_oneMonth.TabStop = true;
            this.rdo_oneMonth.Text = "1달";
            this.rdo_oneMonth.UseVisualStyleBackColor = true;
            this.rdo_oneMonth.CheckedChanged += new System.EventHandler(this.rdo_CheckedChanged);
            // 
            // rdo_threeWeek
            // 
            this.rdo_threeWeek.AutoSize = true;
            this.rdo_threeWeek.Location = new System.Drawing.Point(120, 25);
            this.rdo_threeWeek.Name = "rdo_threeWeek";
            this.rdo_threeWeek.Size = new System.Drawing.Size(51, 19);
            this.rdo_threeWeek.TabIndex = 2;
            this.rdo_threeWeek.TabStop = true;
            this.rdo_threeWeek.Text = "3주";
            this.rdo_threeWeek.UseVisualStyleBackColor = true;
            this.rdo_threeWeek.CheckedChanged += new System.EventHandler(this.rdo_CheckedChanged);
            // 
            // rdo_twoWeek
            // 
            this.rdo_twoWeek.AutoSize = true;
            this.rdo_twoWeek.Location = new System.Drawing.Point(63, 24);
            this.rdo_twoWeek.Name = "rdo_twoWeek";
            this.rdo_twoWeek.Size = new System.Drawing.Size(51, 19);
            this.rdo_twoWeek.TabIndex = 1;
            this.rdo_twoWeek.TabStop = true;
            this.rdo_twoWeek.Text = "2주";
            this.rdo_twoWeek.UseVisualStyleBackColor = true;
            this.rdo_twoWeek.CheckedChanged += new System.EventHandler(this.rdo_CheckedChanged);
            // 
            // rdo_oneWeek
            // 
            this.rdo_oneWeek.AutoSize = true;
            this.rdo_oneWeek.Location = new System.Drawing.Point(7, 25);
            this.rdo_oneWeek.Name = "rdo_oneWeek";
            this.rdo_oneWeek.Size = new System.Drawing.Size(51, 19);
            this.rdo_oneWeek.TabIndex = 0;
            this.rdo_oneWeek.TabStop = true;
            this.rdo_oneWeek.Text = "1주";
            this.rdo_oneWeek.UseVisualStyleBackColor = true;
            this.rdo_oneWeek.CheckedChanged += new System.EventHandler(this.rdo_CheckedChanged);
            // 
            // NoticeListForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(623, 314);
            this.Controls.Add(this.lvw_Notice);
            this.Controls.Add(this.groupBox2);
            this.Name = "NoticeListForm";
            this.Text = "NoticeListForm";
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.NoticeListForm_FormClosed);
            this.Load += new System.EventHandler(this.NoticeForm_Load);
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.ListView lvw_Notice;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.RadioButton rdo_twoMonth;
        private System.Windows.Forms.RadioButton rdo_oneMonth;
        private System.Windows.Forms.RadioButton rdo_threeWeek;
        private System.Windows.Forms.RadioButton rdo_twoWeek;
        private System.Windows.Forms.RadioButton rdo_oneWeek;
    }
}