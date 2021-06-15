namespace 지뢰찾기 {
    partial class Difficulty {
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
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.rdoAdvanced = new System.Windows.Forms.RadioButton();
            this.rdoMiddle = new System.Windows.Forms.RadioButton();
            this.rdoBeginner = new System.Windows.Forms.RadioButton();
            this.btn_OK = new System.Windows.Forms.Button();
            this.groupBox1.SuspendLayout();
            this.SuspendLayout();
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.rdoAdvanced);
            this.groupBox1.Controls.Add(this.rdoMiddle);
            this.groupBox1.Controls.Add(this.rdoBeginner);
            this.groupBox1.Location = new System.Drawing.Point(27, 23);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(208, 193);
            this.groupBox1.TabIndex = 0;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "난이도 선택";
            // 
            // rdoAdvanced
            // 
            this.rdoAdvanced.AutoSize = true;
            this.rdoAdvanced.Location = new System.Drawing.Point(31, 138);
            this.rdoAdvanced.Name = "rdoAdvanced";
            this.rdoAdvanced.Size = new System.Drawing.Size(114, 19);
            this.rdoAdvanced.TabIndex = 2;
            this.rdoAdvanced.Text = "고급 : 30x16";
            this.rdoAdvanced.UseVisualStyleBackColor = true;
            // 
            // rdoMiddle
            // 
            this.rdoMiddle.AutoSize = true;
            this.rdoMiddle.Location = new System.Drawing.Point(31, 87);
            this.rdoMiddle.Name = "rdoMiddle";
            this.rdoMiddle.Size = new System.Drawing.Size(114, 19);
            this.rdoMiddle.TabIndex = 1;
            this.rdoMiddle.Text = "중급 : 16x16";
            this.rdoMiddle.UseVisualStyleBackColor = true;
            // 
            // rdoBeginner
            // 
            this.rdoBeginner.AutoSize = true;
            this.rdoBeginner.Location = new System.Drawing.Point(31, 39);
            this.rdoBeginner.Name = "rdoBeginner";
            this.rdoBeginner.Size = new System.Drawing.Size(98, 19);
            this.rdoBeginner.TabIndex = 0;
            this.rdoBeginner.Text = "초급 : 9x9";
            this.rdoBeginner.UseVisualStyleBackColor = true;
            // 
            // btn_OK
            // 
            this.btn_OK.Location = new System.Drawing.Point(90, 234);
            this.btn_OK.Name = "btn_OK";
            this.btn_OK.Size = new System.Drawing.Size(82, 30);
            this.btn_OK.TabIndex = 1;
            this.btn_OK.Text = "확인";
            this.btn_OK.UseVisualStyleBackColor = true;
            this.btn_OK.Click += new System.EventHandler(this.btn_OK_Click);
            // 
            // Difficulty
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(262, 290);
            this.Controls.Add(this.btn_OK);
            this.Controls.Add(this.groupBox1);
            this.Name = "Difficulty";
            this.Text = "Set Difficulty";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Difficulty_FormClosing);
            this.Load += new System.EventHandler(this.Difficulty_Load);
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.RadioButton rdoAdvanced;
        private System.Windows.Forms.RadioButton rdoMiddle;
        private System.Windows.Forms.RadioButton rdoBeginner;
        private System.Windows.Forms.Button btn_OK;
    }
}

