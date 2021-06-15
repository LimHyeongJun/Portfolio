namespace Client {
    partial class ClientForm {
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
            this.txt_all = new System.Windows.Forms.TextBox();
            this.txt_send = new System.Windows.Forms.TextBox();
            this.lbl_IPAddress = new System.Windows.Forms.Label();
            this.txt_IPAddress = new System.Windows.Forms.TextBox();
            this.lbl_PortNumber = new System.Windows.Forms.Label();
            this.lbl_NickName = new System.Windows.Forms.Label();
            this.txt_PortNumber = new System.Windows.Forms.TextBox();
            this.txt_NickName = new System.Windows.Forms.TextBox();
            this.btn_ConnectServer = new System.Windows.Forms.Button();
            this.btn_Send = new System.Windows.Forms.Button();
            this.btn_exit = new System.Windows.Forms.Button();
            this.btn_ReleaseConnect = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // txt_all
            // 
            this.txt_all.Location = new System.Drawing.Point(28, 25);
            this.txt_all.Multiline = true;
            this.txt_all.Name = "txt_all";
            this.txt_all.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.txt_all.Size = new System.Drawing.Size(363, 278);
            this.txt_all.TabIndex = 0;
            // 
            // txt_send
            // 
            this.txt_send.Location = new System.Drawing.Point(28, 332);
            this.txt_send.Name = "txt_send";
            this.txt_send.Size = new System.Drawing.Size(363, 25);
            this.txt_send.TabIndex = 1;
            this.txt_send.KeyDown += new System.Windows.Forms.KeyEventHandler(this.txt_send_KeyDown);
            // 
            // lbl_IPAddress
            // 
            this.lbl_IPAddress.AutoSize = true;
            this.lbl_IPAddress.Location = new System.Drawing.Point(413, 22);
            this.lbl_IPAddress.Name = "lbl_IPAddress";
            this.lbl_IPAddress.Size = new System.Drawing.Size(88, 15);
            this.lbl_IPAddress.TabIndex = 2;
            this.lbl_IPAddress.Text = "IP Address :";
            // 
            // txt_IPAddress
            // 
            this.txt_IPAddress.Location = new System.Drawing.Point(416, 40);
            this.txt_IPAddress.Name = "txt_IPAddress";
            this.txt_IPAddress.Size = new System.Drawing.Size(147, 25);
            this.txt_IPAddress.TabIndex = 3;
            // 
            // lbl_PortNumber
            // 
            this.lbl_PortNumber.AutoSize = true;
            this.lbl_PortNumber.Location = new System.Drawing.Point(413, 80);
            this.lbl_PortNumber.Name = "lbl_PortNumber";
            this.lbl_PortNumber.Size = new System.Drawing.Size(102, 15);
            this.lbl_PortNumber.TabIndex = 4;
            this.lbl_PortNumber.Text = "Port Number : ";
            // 
            // lbl_NickName
            // 
            this.lbl_NickName.AutoSize = true;
            this.lbl_NickName.Location = new System.Drawing.Point(413, 137);
            this.lbl_NickName.Name = "lbl_NickName";
            this.lbl_NickName.Size = new System.Drawing.Size(85, 15);
            this.lbl_NickName.TabIndex = 5;
            this.lbl_NickName.Text = "NickName : ";
            // 
            // txt_PortNumber
            // 
            this.txt_PortNumber.Location = new System.Drawing.Point(416, 98);
            this.txt_PortNumber.Name = "txt_PortNumber";
            this.txt_PortNumber.Size = new System.Drawing.Size(147, 25);
            this.txt_PortNumber.TabIndex = 6;
            this.txt_PortNumber.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.OnlyDigit);
            // 
            // txt_NickName
            // 
            this.txt_NickName.Location = new System.Drawing.Point(416, 155);
            this.txt_NickName.Name = "txt_NickName";
            this.txt_NickName.Size = new System.Drawing.Size(147, 25);
            this.txt_NickName.TabIndex = 7;
            // 
            // btn_ConnectServer
            // 
            this.btn_ConnectServer.Location = new System.Drawing.Point(416, 213);
            this.btn_ConnectServer.Name = "btn_ConnectServer";
            this.btn_ConnectServer.Size = new System.Drawing.Size(147, 28);
            this.btn_ConnectServer.TabIndex = 8;
            this.btn_ConnectServer.Text = "서버 연결";
            this.btn_ConnectServer.UseVisualStyleBackColor = true;
            this.btn_ConnectServer.Click += new System.EventHandler(this.btn_ConnectServer_Click);
            // 
            // btn_Send
            // 
            this.btn_Send.Location = new System.Drawing.Point(416, 331);
            this.btn_Send.Name = "btn_Send";
            this.btn_Send.Size = new System.Drawing.Size(75, 26);
            this.btn_Send.TabIndex = 9;
            this.btn_Send.Text = "보내기";
            this.btn_Send.UseVisualStyleBackColor = true;
            this.btn_Send.Click += new System.EventHandler(this.btn_Send_Click);
            // 
            // btn_exit
            // 
            this.btn_exit.ForeColor = System.Drawing.Color.Red;
            this.btn_exit.Location = new System.Drawing.Point(507, 331);
            this.btn_exit.Name = "btn_exit";
            this.btn_exit.Size = new System.Drawing.Size(75, 26);
            this.btn_exit.TabIndex = 10;
            this.btn_exit.Text = "종료";
            this.btn_exit.UseVisualStyleBackColor = true;
            this.btn_exit.Click += new System.EventHandler(this.btn_exit_Click);
            // 
            // btn_ReleaseConnect
            // 
            this.btn_ReleaseConnect.ForeColor = System.Drawing.Color.Red;
            this.btn_ReleaseConnect.Location = new System.Drawing.Point(416, 259);
            this.btn_ReleaseConnect.Name = "btn_ReleaseConnect";
            this.btn_ReleaseConnect.Size = new System.Drawing.Size(147, 28);
            this.btn_ReleaseConnect.TabIndex = 11;
            this.btn_ReleaseConnect.Text = "연결 해제";
            this.btn_ReleaseConnect.UseVisualStyleBackColor = true;
            this.btn_ReleaseConnect.Click += new System.EventHandler(this.btn_ReleaseConnect_Click);
            // 
            // ClientForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(596, 381);
            this.Controls.Add(this.btn_ReleaseConnect);
            this.Controls.Add(this.btn_exit);
            this.Controls.Add(this.btn_Send);
            this.Controls.Add(this.btn_ConnectServer);
            this.Controls.Add(this.txt_NickName);
            this.Controls.Add(this.txt_PortNumber);
            this.Controls.Add(this.lbl_NickName);
            this.Controls.Add(this.lbl_PortNumber);
            this.Controls.Add(this.txt_IPAddress);
            this.Controls.Add(this.lbl_IPAddress);
            this.Controls.Add(this.txt_send);
            this.Controls.Add(this.txt_all);
            this.Name = "ClientForm";
            this.Text = "Client";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.ClientForm_FormClosing);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox txt_all;
        private System.Windows.Forms.TextBox txt_send;
        private System.Windows.Forms.Label lbl_IPAddress;
        private System.Windows.Forms.TextBox txt_IPAddress;
        private System.Windows.Forms.Label lbl_PortNumber;
        private System.Windows.Forms.Label lbl_NickName;
        private System.Windows.Forms.TextBox txt_PortNumber;
        private System.Windows.Forms.TextBox txt_NickName;
        private System.Windows.Forms.Button btn_ConnectServer;
        private System.Windows.Forms.Button btn_Send;
        private System.Windows.Forms.Button btn_exit;
        private System.Windows.Forms.Button btn_ReleaseConnect;
    }
}

