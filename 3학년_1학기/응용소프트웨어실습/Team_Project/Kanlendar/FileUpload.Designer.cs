namespace Kanlendar
{
    partial class FileUpload
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.cmbDate = new System.Windows.Forms.ComboBox();
            this.cmbAssign = new System.Windows.Forms.ComboBox();
            this.txtAssign = new System.Windows.Forms.TextBox();
            this.btnSubmit = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // cmbDate
            // 
            this.cmbDate.FormattingEnabled = true;
            this.cmbDate.Location = new System.Drawing.Point(49, 90);
            this.cmbDate.Name = "cmbDate";
            this.cmbDate.Size = new System.Drawing.Size(271, 23);
            this.cmbDate.TabIndex = 0;
            this.cmbDate.SelectedIndexChanged += new System.EventHandler(this.cmbDate_SelectedIndexChanged);
            // 
            // cmbAssign
            // 
            this.cmbAssign.FormattingEnabled = true;
            this.cmbAssign.Location = new System.Drawing.Point(49, 119);
            this.cmbAssign.Name = "cmbAssign";
            this.cmbAssign.Size = new System.Drawing.Size(271, 23);
            this.cmbAssign.TabIndex = 1;
            // 
            // txtAssign
            // 
            this.txtAssign.AllowDrop = true;
            this.txtAssign.Location = new System.Drawing.Point(49, 12);
            this.txtAssign.Multiline = true;
            this.txtAssign.Name = "txtAssign";
            this.txtAssign.ReadOnly = true;
            this.txtAssign.Size = new System.Drawing.Size(271, 72);
            this.txtAssign.TabIndex = 2;
            this.txtAssign.DragDrop += new System.Windows.Forms.DragEventHandler(this.assign_DragDrop);
            this.txtAssign.DragEnter += new System.Windows.Forms.DragEventHandler(this.assign_DragEnter);
            // 
            // btnSubmit
            // 
            this.btnSubmit.Location = new System.Drawing.Point(147, 148);
            this.btnSubmit.Name = "btnSubmit";
            this.btnSubmit.Size = new System.Drawing.Size(75, 23);
            this.btnSubmit.TabIndex = 3;
            this.btnSubmit.Text = "제출";
            this.btnSubmit.UseVisualStyleBackColor = true;
            this.btnSubmit.Click += new System.EventHandler(this.btnSubmit_Click);
            // 
            // FileUpload
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(369, 183);
            this.Controls.Add(this.btnSubmit);
            this.Controls.Add(this.txtAssign);
            this.Controls.Add(this.cmbAssign);
            this.Controls.Add(this.cmbDate);
            this.Name = "FileUpload";
            this.Text = "FileUpload";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ComboBox cmbDate;
        private System.Windows.Forms.ComboBox cmbAssign;
        private System.Windows.Forms.TextBox txtAssign;
        private System.Windows.Forms.Button btnSubmit;
    }
}