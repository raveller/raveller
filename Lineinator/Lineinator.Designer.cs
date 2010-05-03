namespace NewLine
{
    partial class Lineinator
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Lineinator));
            this.SourceTxtBox = new System.Windows.Forms.TextBox();
            this.sourceBrowseBtn = new System.Windows.Forms.Button();
            this.targetBrowseBtn = new System.Windows.Forms.Button();
            this.targetTxtBox = new System.Windows.Forms.TextBox();
            this.lineInAteBtn = new System.Windows.Forms.Button();
            this.delimTxtBox = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.copySourcePlusTgtBtn = new System.Windows.Forms.Button();
            this.extTextBox = new System.Windows.Forms.TextBox();
            this.label4 = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // SourceTxtBox
            // 
            this.SourceTxtBox.Location = new System.Drawing.Point(12, 36);
            this.SourceTxtBox.Name = "SourceTxtBox";
            this.SourceTxtBox.ReadOnly = true;
            this.SourceTxtBox.Size = new System.Drawing.Size(281, 20);
            this.SourceTxtBox.TabIndex = 0;
            // 
            // sourceBrowseBtn
            // 
            this.sourceBrowseBtn.Location = new System.Drawing.Point(299, 36);
            this.sourceBrowseBtn.Name = "sourceBrowseBtn";
            this.sourceBrowseBtn.Size = new System.Drawing.Size(30, 20);
            this.sourceBrowseBtn.TabIndex = 1;
            this.sourceBrowseBtn.Text = "...";
            this.sourceBrowseBtn.UseVisualStyleBackColor = true;
            this.sourceBrowseBtn.Click += new System.EventHandler(this.sourceBrowseBtn_Click);
            // 
            // targetBrowseBtn
            // 
            this.targetBrowseBtn.Location = new System.Drawing.Point(299, 131);
            this.targetBrowseBtn.Name = "targetBrowseBtn";
            this.targetBrowseBtn.Size = new System.Drawing.Size(30, 20);
            this.targetBrowseBtn.TabIndex = 3;
            this.targetBrowseBtn.Text = "...";
            this.targetBrowseBtn.UseVisualStyleBackColor = true;
            this.targetBrowseBtn.Click += new System.EventHandler(this.targetBrowseBtn_Click);
            // 
            // targetTxtBox
            // 
            this.targetTxtBox.Location = new System.Drawing.Point(12, 131);
            this.targetTxtBox.Name = "targetTxtBox";
            this.targetTxtBox.ReadOnly = true;
            this.targetTxtBox.Size = new System.Drawing.Size(281, 20);
            this.targetTxtBox.TabIndex = 2;
            // 
            // lineInAteBtn
            // 
            this.lineInAteBtn.Location = new System.Drawing.Point(218, 162);
            this.lineInAteBtn.Name = "lineInAteBtn";
            this.lineInAteBtn.Size = new System.Drawing.Size(111, 42);
            this.lineInAteBtn.TabIndex = 4;
            this.lineInAteBtn.Text = "New Line it!";
            this.lineInAteBtn.UseVisualStyleBackColor = true;
            this.lineInAteBtn.Click += new System.EventHandler(this.lineInAteBtn_Click);
            // 
            // delimTxtBox
            // 
            this.delimTxtBox.Location = new System.Drawing.Point(97, 165);
            this.delimTxtBox.Name = "delimTxtBox";
            this.delimTxtBox.Size = new System.Drawing.Size(102, 20);
            this.delimTxtBox.TabIndex = 5;
            this.delimTxtBox.Text = "~";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(9, 168);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(47, 13);
            this.label1.TabIndex = 6;
            this.label1.Text = "Delimiter";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(12, 104);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(57, 13);
            this.label2.TabIndex = 7;
            this.label2.Text = "Target File";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(12, 9);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(60, 13);
            this.label3.TabIndex = 8;
            this.label3.Text = "Source File";
            // 
            // copySourcePlusTgtBtn
            // 
            this.copySourcePlusTgtBtn.Location = new System.Drawing.Point(204, 70);
            this.copySourcePlusTgtBtn.Name = "copySourcePlusTgtBtn";
            this.copySourcePlusTgtBtn.Size = new System.Drawing.Size(125, 20);
            this.copySourcePlusTgtBtn.TabIndex = 9;
            this.copySourcePlusTgtBtn.Text = "target = source + ext";
            this.copySourcePlusTgtBtn.UseVisualStyleBackColor = true;
            this.copySourcePlusTgtBtn.Click += new System.EventHandler(this.copySourcePlusTgtBtn_Click);
            // 
            // extTextBox
            // 
            this.extTextBox.Location = new System.Drawing.Point(42, 70);
            this.extTextBox.Name = "extTextBox";
            this.extTextBox.Size = new System.Drawing.Size(132, 20);
            this.extTextBox.TabIndex = 10;
            this.extTextBox.Text = ".tgt";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(9, 74);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(21, 13);
            this.label4.TabIndex = 11;
            this.label4.Text = "ext";
            // 
            // Lineinator
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(341, 220);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.extTextBox);
            this.Controls.Add(this.copySourcePlusTgtBtn);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.delimTxtBox);
            this.Controls.Add(this.lineInAteBtn);
            this.Controls.Add(this.targetBrowseBtn);
            this.Controls.Add(this.targetTxtBox);
            this.Controls.Add(this.sourceBrowseBtn);
            this.Controls.Add(this.SourceTxtBox);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "Lineinator";
            this.Text = "Lineinator - The New Line Inserter";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox SourceTxtBox;
        private System.Windows.Forms.Button sourceBrowseBtn;
        private System.Windows.Forms.Button targetBrowseBtn;
        private System.Windows.Forms.TextBox targetTxtBox;
        private System.Windows.Forms.Button lineInAteBtn;
        private System.Windows.Forms.TextBox delimTxtBox;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Button copySourcePlusTgtBtn;
        private System.Windows.Forms.TextBox extTextBox;
        private System.Windows.Forms.Label label4;
    }
}