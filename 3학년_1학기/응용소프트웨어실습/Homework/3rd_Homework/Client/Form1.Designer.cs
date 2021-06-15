namespace Client {
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
            this.btn_ServerConnect = new System.Windows.Forms.Button();
            this.txt_Port = new System.Windows.Forms.TextBox();
            this.txt_IP = new System.Windows.Forms.TextBox();
            this.lbl_Port = new System.Windows.Forms.Label();
            this.lbl_IP = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // btn_ServerConnect
            // 
            this.btn_ServerConnect.Location = new System.Drawing.Point(100, 128);
            this.btn_ServerConnect.Name = "btn_ServerConnect";
            this.btn_ServerConnect.Size = new System.Drawing.Size(132, 33);
            this.btn_ServerConnect.TabIndex = 19;
            this.btn_ServerConnect.Text = "서버 접속";
            this.btn_ServerConnect.UseVisualStyleBackColor = true;
            this.btn_ServerConnect.Click += new System.EventHandler(this.btn_ServerConnect_Click);
            // 
            // txt_Port
            // 
            this.txt_Port.Location = new System.Drawing.Point(100, 82);
            this.txt_Port.Name = "txt_Port";
            this.txt_Port.Size = new System.Drawing.Size(132, 25);
            this.txt_Port.TabIndex = 18;
            this.txt_Port.KeyDown += new System.Windows.Forms.KeyEventHandler(this.txt_Port_KeyDown);
            // 
            // txt_IP
            // 
            this.txt_IP.Location = new System.Drawing.Point(100, 39);
            this.txt_IP.Name = "txt_IP";
            this.txt_IP.Size = new System.Drawing.Size(132, 25);
            this.txt_IP.TabIndex = 17;
            // 
            // lbl_Port
            // 
            this.lbl_Port.AutoSize = true;
            this.lbl_Port.Location = new System.Drawing.Point(45, 85);
            this.lbl_Port.Name = "lbl_Port";
            this.lbl_Port.Size = new System.Drawing.Size(49, 15);
            this.lbl_Port.TabIndex = 16;
            this.lbl_Port.Text = "Port : ";
            // 
            // lbl_IP
            // 
            this.lbl_IP.AutoSize = true;
            this.lbl_IP.Location = new System.Drawing.Point(59, 42);
            this.lbl_IP.Name = "lbl_IP";
            this.lbl_IP.Size = new System.Drawing.Size(35, 15);
            this.lbl_IP.TabIndex = 15;
            this.lbl_IP.Text = "IP : ";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(310, 199);
            this.Controls.Add(this.btn_ServerConnect);
            this.Controls.Add(this.txt_Port);
            this.Controls.Add(this.txt_IP);
            this.Controls.Add(this.lbl_Port);
            this.Controls.Add(this.lbl_IP);
            this.Name = "Form1";
            this.Text = "Form1";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Form1_FormClosing);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button btn_ServerConnect;
        private System.Windows.Forms.TextBox txt_Port;
        private System.Windows.Forms.TextBox txt_IP;
        private System.Windows.Forms.Label lbl_Port;
        private System.Windows.Forms.Label lbl_IP;
    }
}

