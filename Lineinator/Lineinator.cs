using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Text;
using System.Windows.Forms;

namespace NewLine
{
    ///<summary>
    ///</summary>
    public partial class Lineinator : Form
    {
        ///<summary>
        ///</summary>
        public Lineinator()
        {
            InitializeComponent();
        }

        private void sourceBrowseBtn_Click(object sender, EventArgs e)
        {
            System.Windows.Forms.OpenFileDialog fd = new OpenFileDialog();

            fd.ShowDialog();

            this.SourceTxtBox.Text = fd.FileName;
        }

        private void targetBrowseBtn_Click(object sender, EventArgs e)
        {
            System.Windows.Forms.OpenFileDialog fd = new OpenFileDialog();

            fd.ShowDialog();

            this.targetTxtBox.Text = fd.FileName;

        }

        private void lineInAteBtn_Click(object sender, EventArgs e)
        {
            // Create the file.
            using (System.IO.FileStream tgtFs = System.IO.File.Create(targetTxtBox.Text))
            {
                // Open the stream and read it back.
                using (System.IO.FileStream srcFs = System.IO.File.Open(SourceTxtBox.Text, FileMode.Open, FileAccess.Read, FileShare.None))
                {
                    byte[] b = new byte[1024];
                    UTF8Encoding temp = new UTF8Encoding(true);

                    while (srcFs.Read(b, 0, b.Length) > 0)
                    {
                        string lineinated = temp.GetString(b).Replace(delimTxtBox.Text, delimTxtBox.Text + "\n");

                        Byte[] info = new UTF8Encoding(true).GetBytes(lineinated);
                        // Add some information to the file.
                        tgtFs.Write(info, 0, info.Length);
                    }
                }
            }
        }

        private void copySourcePlusTgtBtn_Click(object sender, EventArgs e)
        {
            this.targetTxtBox.Text = this.SourceTxtBox.Text + extTextBox.Text;
        }
    }
}