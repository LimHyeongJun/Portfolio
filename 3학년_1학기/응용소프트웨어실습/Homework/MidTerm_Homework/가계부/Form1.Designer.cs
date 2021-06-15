namespace 가계부 {
    partial class Form1 {
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

        #region Windows Form 디자이너에서 생성한 코드

        /// <summary>
        /// 디자이너 지원에 필요한 메서드입니다. 
        /// 이 메서드의 내용을 코드 편집기로 수정하지 마세요.
        /// </summary>
        private void InitializeComponent() {
            this.btn_NextMonth = new System.Windows.Forms.Button();
            this.btn_PreviousMonth = new System.Windows.Forms.Button();
            this.lbl_month = new System.Windows.Forms.Label();
            this.lvwExpenditure = new System.Windows.Forms.ListView();
            this.lvwIncome = new System.Windows.Forms.ListView();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.txt_ExpenditureContent = new System.Windows.Forms.TextBox();
            this.txt_ExpenditureMoney = new System.Windows.Forms.TextBox();
            this.txt_IncomeContent = new System.Windows.Forms.TextBox();
            this.txt_IncomeMoney = new System.Windows.Forms.TextBox();
            this.btn_ExpenditureEnroll = new System.Windows.Forms.Button();
            this.btn_ExpenditureRemove = new System.Windows.Forms.Button();
            this.btn_IncomeRemove = new System.Windows.Forms.Button();
            this.btn_IncomeEnroll = new System.Windows.Forms.Button();
            this.lbl_AllExpenditure = new System.Windows.Forms.Label();
            this.lbl_AllIncome = new System.Windows.Forms.Label();
            this.lbl_TotalMoney = new System.Windows.Forms.Label();
            this.btn_Save = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // btn_NextMonth
            // 
            this.btn_NextMonth.Location = new System.Drawing.Point(468, 36);
            this.btn_NextMonth.Name = "btn_NextMonth";
            this.btn_NextMonth.Size = new System.Drawing.Size(35, 31);
            this.btn_NextMonth.TabIndex = 1;
            this.btn_NextMonth.Text = "▶";
            this.btn_NextMonth.UseVisualStyleBackColor = true;
            this.btn_NextMonth.Click += new System.EventHandler(this.btn_NextMonth_Click);
            // 
            // btn_PreviousMonth
            // 
            this.btn_PreviousMonth.Location = new System.Drawing.Point(206, 39);
            this.btn_PreviousMonth.Name = "btn_PreviousMonth";
            this.btn_PreviousMonth.Size = new System.Drawing.Size(35, 31);
            this.btn_PreviousMonth.TabIndex = 0;
            this.btn_PreviousMonth.Text = "◀";
            this.btn_PreviousMonth.UseVisualStyleBackColor = true;
            this.btn_PreviousMonth.Click += new System.EventHandler(this.btn_PreviousMonth_Click);
            // 
            // lbl_month
            // 
            this.lbl_month.AutoSize = true;
            this.lbl_month.Font = new System.Drawing.Font("굴림", 16.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(129)));
            this.lbl_month.Location = new System.Drawing.Point(317, 42);
            this.lbl_month.Name = "lbl_month";
            this.lbl_month.Size = new System.Drawing.Size(89, 28);
            this.lbl_month.TabIndex = 2;
            this.lbl_month.Text = "label1";
            // 
            // lvwExpenditure
            // 
            this.lvwExpenditure.FullRowSelect = true;
            this.lvwExpenditure.HideSelection = false;
            this.lvwExpenditure.Location = new System.Drawing.Point(34, 102);
            this.lvwExpenditure.Name = "lvwExpenditure";
            this.lvwExpenditure.Size = new System.Drawing.Size(328, 161);
            this.lvwExpenditure.TabIndex = 3;
            this.lvwExpenditure.UseCompatibleStateImageBehavior = false;
            // 
            // lvwIncome
            // 
            this.lvwIncome.FullRowSelect = true;
            this.lvwIncome.HideSelection = false;
            this.lvwIncome.Location = new System.Drawing.Point(374, 102);
            this.lvwIncome.Name = "lvwIncome";
            this.lvwIncome.Size = new System.Drawing.Size(328, 161);
            this.lvwIncome.TabIndex = 4;
            this.lvwIncome.UseCompatibleStateImageBehavior = false;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(54, 287);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(82, 15);
            this.label1.TabIndex = 5;
            this.label1.Text = "지출 내역 :";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(54, 320);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(82, 15);
            this.label2.TabIndex = 6;
            this.label2.Text = "지출 금액 :";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(399, 287);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(82, 15);
            this.label3.TabIndex = 7;
            this.label3.Text = "수입 내역 :";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(399, 320);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(87, 15);
            this.label4.TabIndex = 8;
            this.label4.Text = "수입 금액 : ";
            // 
            // txt_ExpenditureContent
            // 
            this.txt_ExpenditureContent.Location = new System.Drawing.Point(143, 284);
            this.txt_ExpenditureContent.Name = "txt_ExpenditureContent";
            this.txt_ExpenditureContent.Size = new System.Drawing.Size(118, 25);
            this.txt_ExpenditureContent.TabIndex = 9;
            // 
            // txt_ExpenditureMoney
            // 
            this.txt_ExpenditureMoney.Location = new System.Drawing.Point(143, 315);
            this.txt_ExpenditureMoney.Name = "txt_ExpenditureMoney";
            this.txt_ExpenditureMoney.Size = new System.Drawing.Size(118, 25);
            this.txt_ExpenditureMoney.TabIndex = 10;
            this.txt_ExpenditureMoney.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.txt_money_KeyPress);
            // 
            // txt_IncomeContent
            // 
            this.txt_IncomeContent.Location = new System.Drawing.Point(487, 284);
            this.txt_IncomeContent.Name = "txt_IncomeContent";
            this.txt_IncomeContent.Size = new System.Drawing.Size(118, 25);
            this.txt_IncomeContent.TabIndex = 11;
            // 
            // txt_IncomeMoney
            // 
            this.txt_IncomeMoney.Location = new System.Drawing.Point(487, 318);
            this.txt_IncomeMoney.Name = "txt_IncomeMoney";
            this.txt_IncomeMoney.Size = new System.Drawing.Size(118, 25);
            this.txt_IncomeMoney.TabIndex = 12;
            this.txt_IncomeMoney.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.txt_money_KeyPress);
            // 
            // btn_ExpenditureEnroll
            // 
            this.btn_ExpenditureEnroll.Location = new System.Drawing.Point(267, 284);
            this.btn_ExpenditureEnroll.Name = "btn_ExpenditureEnroll";
            this.btn_ExpenditureEnroll.Size = new System.Drawing.Size(75, 28);
            this.btn_ExpenditureEnroll.TabIndex = 13;
            this.btn_ExpenditureEnroll.Text = "등록";
            this.btn_ExpenditureEnroll.UseVisualStyleBackColor = true;
            this.btn_ExpenditureEnroll.Click += new System.EventHandler(this.btn_ExpenditureEnroll_Click);
            // 
            // btn_ExpenditureRemove
            // 
            this.btn_ExpenditureRemove.Location = new System.Drawing.Point(267, 315);
            this.btn_ExpenditureRemove.Name = "btn_ExpenditureRemove";
            this.btn_ExpenditureRemove.Size = new System.Drawing.Size(75, 26);
            this.btn_ExpenditureRemove.TabIndex = 14;
            this.btn_ExpenditureRemove.Text = "제거";
            this.btn_ExpenditureRemove.UseVisualStyleBackColor = true;
            this.btn_ExpenditureRemove.Click += new System.EventHandler(this.btn_ExpenditureRemove_Click);
            // 
            // btn_IncomeRemove
            // 
            this.btn_IncomeRemove.Location = new System.Drawing.Point(627, 318);
            this.btn_IncomeRemove.Name = "btn_IncomeRemove";
            this.btn_IncomeRemove.Size = new System.Drawing.Size(75, 25);
            this.btn_IncomeRemove.TabIndex = 16;
            this.btn_IncomeRemove.Text = "제거";
            this.btn_IncomeRemove.UseVisualStyleBackColor = true;
            this.btn_IncomeRemove.Click += new System.EventHandler(this.btn_IncomeRemove_Click);
            // 
            // btn_IncomeEnroll
            // 
            this.btn_IncomeEnroll.Location = new System.Drawing.Point(627, 280);
            this.btn_IncomeEnroll.Name = "btn_IncomeEnroll";
            this.btn_IncomeEnroll.Size = new System.Drawing.Size(75, 28);
            this.btn_IncomeEnroll.TabIndex = 15;
            this.btn_IncomeEnroll.Text = "등록";
            this.btn_IncomeEnroll.UseVisualStyleBackColor = true;
            this.btn_IncomeEnroll.Click += new System.EventHandler(this.btn_IncomeEnroll_Click);
            // 
            // lbl_AllExpenditure
            // 
            this.lbl_AllExpenditure.AutoSize = true;
            this.lbl_AllExpenditure.Font = new System.Drawing.Font("굴림", 10.8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(129)));
            this.lbl_AllExpenditure.Location = new System.Drawing.Point(41, 368);
            this.lbl_AllExpenditure.Name = "lbl_AllExpenditure";
            this.lbl_AllExpenditure.Size = new System.Drawing.Size(119, 19);
            this.lbl_AllExpenditure.TabIndex = 17;
            this.lbl_AllExpenditure.Text = "총 지출 : 0원";
            // 
            // lbl_AllIncome
            // 
            this.lbl_AllIncome.AutoSize = true;
            this.lbl_AllIncome.Font = new System.Drawing.Font("굴림", 10.8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(129)));
            this.lbl_AllIncome.Location = new System.Drawing.Point(384, 368);
            this.lbl_AllIncome.Name = "lbl_AllIncome";
            this.lbl_AllIncome.Size = new System.Drawing.Size(119, 19);
            this.lbl_AllIncome.TabIndex = 18;
            this.lbl_AllIncome.Text = "총 수입 : 0원";
            // 
            // lbl_TotalMoney
            // 
            this.lbl_TotalMoney.AutoSize = true;
            this.lbl_TotalMoney.Font = new System.Drawing.Font("굴림", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(129)));
            this.lbl_TotalMoney.Location = new System.Drawing.Point(299, 423);
            this.lbl_TotalMoney.Name = "lbl_TotalMoney";
            this.lbl_TotalMoney.Size = new System.Drawing.Size(128, 20);
            this.lbl_TotalMoney.TabIndex = 19;
            this.lbl_TotalMoney.Text = "총 자산 : 0원";
            // 
            // btn_Save
            // 
            this.btn_Save.Location = new System.Drawing.Point(313, 455);
            this.btn_Save.Name = "btn_Save";
            this.btn_Save.Size = new System.Drawing.Size(114, 49);
            this.btn_Save.TabIndex = 20;
            this.btn_Save.Text = "이 달 가계부 저장";
            this.btn_Save.UseVisualStyleBackColor = true;
            this.btn_Save.Click += new System.EventHandler(this.btn_Save_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(735, 523);
            this.Controls.Add(this.btn_Save);
            this.Controls.Add(this.lbl_TotalMoney);
            this.Controls.Add(this.lbl_AllIncome);
            this.Controls.Add(this.lbl_AllExpenditure);
            this.Controls.Add(this.btn_IncomeRemove);
            this.Controls.Add(this.btn_IncomeEnroll);
            this.Controls.Add(this.btn_ExpenditureRemove);
            this.Controls.Add(this.btn_ExpenditureEnroll);
            this.Controls.Add(this.txt_IncomeMoney);
            this.Controls.Add(this.txt_IncomeContent);
            this.Controls.Add(this.txt_ExpenditureMoney);
            this.Controls.Add(this.txt_ExpenditureContent);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.lvwIncome);
            this.Controls.Add(this.lvwExpenditure);
            this.Controls.Add(this.lbl_month);
            this.Controls.Add(this.btn_NextMonth);
            this.Controls.Add(this.btn_PreviousMonth);
            this.Name = "Form1";
            this.Text = "Household Ledger Calculator";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Form1_FormClosing);
            this.Load += new System.EventHandler(this.Form1_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private System.Windows.Forms.Button btn_NextMonth;
        private System.Windows.Forms.Button btn_PreviousMonth;
        private System.Windows.Forms.Label lbl_month;
        private System.Windows.Forms.ListView lvwExpenditure;
        private System.Windows.Forms.ListView lvwIncome;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.TextBox txt_ExpenditureContent;
        private System.Windows.Forms.TextBox txt_ExpenditureMoney;
        private System.Windows.Forms.TextBox txt_IncomeContent;
        private System.Windows.Forms.TextBox txt_IncomeMoney;
        private System.Windows.Forms.Button btn_ExpenditureEnroll;
        private System.Windows.Forms.Button btn_ExpenditureRemove;
        private System.Windows.Forms.Button btn_IncomeRemove;
        private System.Windows.Forms.Button btn_IncomeEnroll;
        private System.Windows.Forms.Label lbl_AllExpenditure;
        private System.Windows.Forms.Label lbl_AllIncome;
        private System.Windows.Forms.Label lbl_TotalMoney;
        private System.Windows.Forms.Button btn_Save;
    }
}

