namespace Kanlendar {
    partial class LoginForm {
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
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.chb_autoLogin = new System.Windows.Forms.CheckBox();
            this.txt_pw = new System.Windows.Forms.TextBox();
            this.txt_id = new System.Windows.Forms.TextBox();
            this.btn_login = new System.Windows.Forms.Button();
            this.label2 = new System.Windows.Forms.Label();
            this.chb_headless = new System.Windows.Forms.CheckBox();
            this.label1 = new System.Windows.Forms.Label();
            this.groupBox1.SuspendLayout();
            this.SuspendLayout();
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.chb_autoLogin);
            this.groupBox1.Controls.Add(this.txt_pw);
            this.groupBox1.Controls.Add(this.txt_id);
            this.groupBox1.Controls.Add(this.btn_login);
            this.groupBox1.Controls.Add(this.label2);
            this.groupBox1.Controls.Add(this.chb_headless);
            this.groupBox1.Controls.Add(this.label1);
            this.groupBox1.Location = new System.Drawing.Point(23, 21);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(302, 186);
            this.groupBox1.TabIndex = 1;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "klas 로그인 정보";
            // 
            // chb_autoLogin
            // 
            this.chb_autoLogin.AutoSize = true;
            this.chb_autoLogin.Location = new System.Drawing.Point(22, 152);
            this.chb_autoLogin.Name = "chb_autoLogin";
            this.chb_autoLogin.Size = new System.Drawing.Size(109, 19);
            this.chb_autoLogin.TabIndex = 5;
            this.chb_autoLogin.Text = "자동 로그인";
            this.chb_autoLogin.UseVisualStyleBackColor = true;
            // 
            // txt_pw
            // 
            this.txt_pw.Location = new System.Drawing.Point(87, 79);
            this.txt_pw.Name = "txt_pw";
            this.txt_pw.PasswordChar = '*';
            this.txt_pw.Size = new System.Drawing.Size(162, 25);
            this.txt_pw.TabIndex = 3;
            this.txt_pw.UseSystemPasswordChar = true;
            // 
            // txt_id
            // 
            this.txt_id.Location = new System.Drawing.Point(87, 44);
            this.txt_id.Name = "txt_id";
            this.txt_id.Size = new System.Drawing.Size(162, 25);
            this.txt_id.TabIndex = 2;
            // 
            // btn_login
            // 
            this.btn_login.Location = new System.Drawing.Point(174, 127);
            this.btn_login.Name = "btn_login";
            this.btn_login.Size = new System.Drawing.Size(75, 28);
            this.btn_login.TabIndex = 4;
            this.btn_login.Text = "로그인";
            this.btn_login.UseVisualStyleBackColor = true;
            this.btn_login.Click += new System.EventHandler(this.btn_login_Click);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(19, 82);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(67, 15);
            this.label2.TabIndex = 1;
            this.label2.Text = "비밀번호";
            // 
            // chb_headless
            // 
            this.chb_headless.AutoSize = true;
            this.chb_headless.Location = new System.Drawing.Point(22, 127);
            this.chb_headless.Name = "chb_headless";
            this.chb_headless.Size = new System.Drawing.Size(94, 19);
            this.chb_headless.TabIndex = 1;
            this.chb_headless.Text = "창 보이기";
            this.chb_headless.UseVisualStyleBackColor = true;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(19, 44);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(52, 15);
            this.label1.TabIndex = 0;
            this.label1.Text = "아이디";
            // 
            // LoginForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(353, 232);
            this.Controls.Add(this.groupBox1);
            this.Name = "LoginForm";
            this.Text = "LoginForm";
            this.Load += new System.EventHandler(this.LoginForm_Load);
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.CheckBox chb_autoLogin;
        private System.Windows.Forms.TextBox txt_pw;
        private System.Windows.Forms.TextBox txt_id;
        private System.Windows.Forms.Button btn_login;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.CheckBox chb_headless;
    }
}