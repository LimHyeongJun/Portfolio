namespace Kanlendar {
    partial class MemoPlan {
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
            this.txt_plan = new System.Windows.Forms.TextBox();
            this.lbl_date = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.btn_red = new System.Windows.Forms.Button();
            this.btn_yellow = new System.Windows.Forms.Button();
            this.btn_green = new System.Windows.Forms.Button();
            this.btn_blue = new System.Windows.Forms.Button();
            this.btn_white = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // txt_plan
            // 
            this.txt_plan.Location = new System.Drawing.Point(17, 83);
            this.txt_plan.Multiline = true;
            this.txt_plan.Name = "txt_plan";
            this.txt_plan.Size = new System.Drawing.Size(318, 254);
            this.txt_plan.TabIndex = 0;
            // 
            // lbl_date
            // 
            this.lbl_date.AutoSize = true;
            this.lbl_date.Font = new System.Drawing.Font("굴림", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(129)));
            this.lbl_date.Location = new System.Drawing.Point(13, 34);
            this.lbl_date.Name = "lbl_date";
            this.lbl_date.Size = new System.Drawing.Size(49, 20);
            this.lbl_date.TabIndex = 1;
            this.lbl_date.Text = "Date";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("굴림", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(129)));
            this.label2.Location = new System.Drawing.Point(21, 370);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(53, 20);
            this.label2.TabIndex = 2;
            this.label2.Text = "Save";
            // 
            // btn_red
            // 
            this.btn_red.BackColor = System.Drawing.Color.Red;
            this.btn_red.Location = new System.Drawing.Point(83, 365);
            this.btn_red.Name = "btn_red";
            this.btn_red.Size = new System.Drawing.Size(34, 32);
            this.btn_red.TabIndex = 4;
            this.btn_red.Text = " ";
            this.btn_red.UseVisualStyleBackColor = false;
            this.btn_red.Click += new System.EventHandler(this.btn_red_Click);
            // 
            // btn_yellow
            // 
            this.btn_yellow.Location = new System.Drawing.Point(123, 365);
            this.btn_yellow.Name = "btn_yellow";
            this.btn_yellow.Size = new System.Drawing.Size(34, 32);
            this.btn_yellow.TabIndex = 5;
            this.btn_yellow.Text = " ";
            this.btn_yellow.UseVisualStyleBackColor = true;
            this.btn_yellow.Click += new System.EventHandler(this.btn_yellow_Click);
            // 
            // btn_green
            // 
            this.btn_green.Location = new System.Drawing.Point(163, 365);
            this.btn_green.Name = "btn_green";
            this.btn_green.Size = new System.Drawing.Size(34, 32);
            this.btn_green.TabIndex = 6;
            this.btn_green.Text = " ";
            this.btn_green.UseVisualStyleBackColor = true;
            this.btn_green.Click += new System.EventHandler(this.btn_green_Click);
            // 
            // btn_blue
            // 
            this.btn_blue.Location = new System.Drawing.Point(203, 365);
            this.btn_blue.Name = "btn_blue";
            this.btn_blue.Size = new System.Drawing.Size(34, 32);
            this.btn_blue.TabIndex = 7;
            this.btn_blue.Text = " ";
            this.btn_blue.UseVisualStyleBackColor = true;
            this.btn_blue.Click += new System.EventHandler(this.btn_blue_Click);
            // 
            // btn_white
            // 
            this.btn_white.Location = new System.Drawing.Point(243, 365);
            this.btn_white.Name = "btn_white";
            this.btn_white.Size = new System.Drawing.Size(34, 32);
            this.btn_white.TabIndex = 8;
            this.btn_white.Text = " ";
            this.btn_white.UseVisualStyleBackColor = true;
            this.btn_white.Click += new System.EventHandler(this.btn_white_Click);
            // 
            // MemoPlan
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(355, 450);
            this.ControlBox = false;
            this.Controls.Add(this.btn_white);
            this.Controls.Add(this.btn_blue);
            this.Controls.Add(this.btn_green);
            this.Controls.Add(this.btn_yellow);
            this.Controls.Add(this.btn_red);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.lbl_date);
            this.Controls.Add(this.txt_plan);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.None;
            this.Name = "MemoPlan";
            this.Text = "MemoPlan";
            this.Load += new System.EventHandler(this.MemoPlan_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox txt_plan;
        private System.Windows.Forms.Label lbl_date;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Button btn_red;
        private System.Windows.Forms.Button btn_yellow;
        private System.Windows.Forms.Button btn_green;
        private System.Windows.Forms.Button btn_blue;
        private System.Windows.Forms.Button btn_white;
    }
}