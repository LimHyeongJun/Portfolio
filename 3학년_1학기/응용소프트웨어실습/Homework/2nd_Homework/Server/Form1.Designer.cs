namespace Server {
    partial class ServerForm {
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
            this.btn_Send = new System.Windows.Forms.Button();
            this.txt_PortNumber = new System.Windows.Forms.TextBox();
            this.lbl_PortNumber = new System.Windows.Forms.Label();
            this.txt_IPAddress = new System.Windows.Forms.TextBox();
            this.lbl_IPAddress = new System.Windows.Forms.Label();
            this.txt_send = new System.Windows.Forms.TextBox();
            this.txt_all = new System.Windows.Forms.TextBox();
            this.btn_ServerStart = new System.Windows.Forms.Button();
            this.btn_exit = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // btn_Send
            // 
            this.btn_Send.Location = new System.Drawing.Point(419, 332);
            this.btn_Send.Name = "btn_Send";
            this.btn_Send.Size = new System.Drawing.Size(75, 26);
            this.btn_Send.TabIndex = 16;
            this.btn_Send.Text = "보내기";
            this.btn_Send.UseVisualStyleBackColor = true;
            this.btn_Send.Click += new System.EventHandler(this.btn_Send_Click);
            // 
            // txt_PortNumber
            // 
            this.txt_PortNumber.Location = new System.Drawing.Point(419, 99);
            this.txt_PortNumber.Name = "txt_PortNumber";
            this.txt_PortNumber.Size = new System.Drawing.Size(147, 25);
            this.txt_PortNumber.TabIndex = 15;
            this.txt_PortNumber.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.OnlyDigit);
            // 
            // lbl_PortNumber
            // 
            this.lbl_PortNumber.AutoSize = true;
            this.lbl_PortNumber.Location = new System.Drawing.Point(416, 81);
            this.lbl_PortNumber.Name = "lbl_PortNumber";
            this.lbl_PortNumber.Size = new System.Drawing.Size(102, 15);
            this.lbl_PortNumber.TabIndex = 14;
            this.lbl_PortNumber.Text = "Port Number : ";
            // 
            // txt_IPAddress
            // 
            this.txt_IPAddress.Location = new System.Drawing.Point(419, 41);
            this.txt_IPAddress.Name = "txt_IPAddress";
            this.txt_IPAddress.Size = new System.Drawing.Size(147, 25);
            this.txt_IPAddress.TabIndex = 13;
            // 
            // lbl_IPAddress
            // 
            this.lbl_IPAddress.AutoSize = true;
            this.lbl_IPAddress.Location = new System.Drawing.Point(416, 23);
            this.lbl_IPAddress.Name = "lbl_IPAddress";
            this.lbl_IPAddress.Size = new System.Drawing.Size(88, 15);
            this.lbl_IPAddress.TabIndex = 12;
            this.lbl_IPAddress.Text = "IP Address :";
            // 
            // txt_send
            // 
            this.txt_send.Location = new System.Drawing.Point(31, 333);
            this.txt_send.Name = "txt_send";
            this.txt_send.Size = new System.Drawing.Size(363, 25);
            this.txt_send.TabIndex = 11;
            this.txt_send.KeyDown += new System.Windows.Forms.KeyEventHandler(this.txt_send_KeyDown);
            // 
            // txt_all
            // 
            this.txt_all.Location = new System.Drawing.Point(31, 26);
            this.txt_all.Multiline = true;
            this.txt_all.Name = "txt_all";
            this.txt_all.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.txt_all.Size = new System.Drawing.Size(363, 278);
            this.txt_all.TabIndex = 10;
            // 
            // btn_ServerStart
            // 
            this.btn_ServerStart.Location = new System.Drawing.Point(419, 152);
            this.btn_ServerStart.Name = "btn_ServerStart";
            this.btn_ServerStart.Size = new System.Drawing.Size(147, 27);
            this.btn_ServerStart.TabIndex = 17;
            this.btn_ServerStart.Text = "서버 시작";
            this.btn_ServerStart.UseVisualStyleBackColor = true;
            this.btn_ServerStart.Click += new System.EventHandler(this.btn_ServerStart_Click);
            // 
            // btn_exit
            // 
            this.btn_exit.ForeColor = System.Drawing.Color.Red;
            this.btn_exit.Location = new System.Drawing.Point(509, 332);
            this.btn_exit.Name = "btn_exit";
            this.btn_exit.Size = new System.Drawing.Size(75, 26);
            this.btn_exit.TabIndex = 18;
            this.btn_exit.Text = "종료";
            this.btn_exit.UseVisualStyleBackColor = true;
            this.btn_exit.Click += new System.EventHandler(this.btn_exit_Click);
            // 
            // ServerForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(596, 381);
            this.Controls.Add(this.btn_exit);
            this.Controls.Add(this.btn_ServerStart);
            this.Controls.Add(this.btn_Send);
            this.Controls.Add(this.txt_PortNumber);
            this.Controls.Add(this.lbl_PortNumber);
            this.Controls.Add(this.txt_IPAddress);
            this.Controls.Add(this.lbl_IPAddress);
            this.Controls.Add(this.txt_send);
            this.Controls.Add(this.txt_all);
            this.Name = "ServerForm";
            this.Text = "Server";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.ServerForm_FormClosing);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button btn_Send;
        private System.Windows.Forms.TextBox txt_PortNumber;
        private System.Windows.Forms.Label lbl_PortNumber;
        private System.Windows.Forms.TextBox txt_IPAddress;
        private System.Windows.Forms.Label lbl_IPAddress;
        private System.Windows.Forms.TextBox txt_send;
        private System.Windows.Forms.TextBox txt_all;
        private System.Windows.Forms.Button btn_ServerStart;
        private System.Windows.Forms.Button btn_exit;
    }
}

