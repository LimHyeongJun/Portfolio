namespace 지뢰찾기 {
    partial class ReplayForm {
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
            this.lbl_result = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.btn_Yes = new System.Windows.Forms.Button();
            this.btn_No = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // lbl_result
            // 
            this.lbl_result.AutoSize = true;
            this.lbl_result.Location = new System.Drawing.Point(136, 23);
            this.lbl_result.Name = "lbl_result";
            this.lbl_result.Size = new System.Drawing.Size(0, 15);
            this.lbl_result.TabIndex = 0;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(41, 52);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(272, 15);
            this.label2.TabIndex = 1;
            this.label2.Text = "The Game is Over!  You want to replay?";
            // 
            // btn_Yes
            // 
            this.btn_Yes.Location = new System.Drawing.Point(44, 92);
            this.btn_Yes.Name = "btn_Yes";
            this.btn_Yes.Size = new System.Drawing.Size(81, 32);
            this.btn_Yes.TabIndex = 2;
            this.btn_Yes.Text = "Yes!";
            this.btn_Yes.UseVisualStyleBackColor = true;
            this.btn_Yes.Click += new System.EventHandler(this.btn_Yes_Click);
            // 
            // btn_No
            // 
            this.btn_No.Location = new System.Drawing.Point(221, 92);
            this.btn_No.Name = "btn_No";
            this.btn_No.Size = new System.Drawing.Size(92, 32);
            this.btn_No.TabIndex = 3;
            this.btn_No.Text = "No!";
            this.btn_No.UseVisualStyleBackColor = true;
            this.btn_No.Click += new System.EventHandler(this.btn_No_Click);
            // 
            // ReplayForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(352, 145);
            this.Controls.Add(this.btn_No);
            this.Controls.Add(this.btn_Yes);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.lbl_result);
            this.Name = "ReplayForm";
            this.Text = "Replay";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.ReplayForm_FormClosing);
            this.Load += new System.EventHandler(this.ReplayForm_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label lbl_result;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Button btn_Yes;
        private System.Windows.Forms.Button btn_No;
    }
}