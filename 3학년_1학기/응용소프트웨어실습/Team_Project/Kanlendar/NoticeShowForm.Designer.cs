namespace Kanlendar {
    partial class NoticeShowForm {
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
            this.txt_notice = new System.Windows.Forms.TextBox();
            this.SuspendLayout();
            // 
            // txt_notice
            // 
            this.txt_notice.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.txt_notice.Location = new System.Drawing.Point(14, 19);
            this.txt_notice.Multiline = true;
            this.txt_notice.Name = "txt_notice";
            this.txt_notice.ReadOnly = true;
            this.txt_notice.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.txt_notice.Size = new System.Drawing.Size(523, 237);
            this.txt_notice.TabIndex = 2;
            this.txt_notice.TabStop = false;
            // 
            // NoticeShowForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(551, 275);
            this.Controls.Add(this.txt_notice);
            this.Name = "NoticeShowForm";
            this.Text = "NoticeShowForm";
            this.Load += new System.EventHandler(this.Form3_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox txt_notice;
    }
}