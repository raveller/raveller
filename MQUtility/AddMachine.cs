using System;
using System.Drawing;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;

namespace MSMQUtil2006
{
	/// <summary>
	/// Summary description for Form1.
	/// </summary>
	public class AddMachineDlg : System.Windows.Forms.Form
	{
        private System.Windows.Forms.Button addButton;
        private System.Windows.Forms.Button cancelButton;
        ///<summary>
        ///</summary>
        public  System.Windows.Forms.TextBox newMachineText;
		/// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.Container components = null;

		///<summary>
		///</summary>
		public AddMachineDlg()
		{
			//
			// Required for Windows Form Designer support
			//
			InitializeComponent();

			//
			// TODO: Add any constructor code after InitializeComponent call
			//
		}

		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		protected override void Dispose( bool disposing )
		{
			if( disposing )
			{
				if(components != null)
				{
					components.Dispose();
				}
			}
			base.Dispose( disposing );
		}

		#region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent()
		{
            this.newMachineText = new System.Windows.Forms.TextBox();
            this.addButton = new System.Windows.Forms.Button();
            this.cancelButton = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // newMachineText
            // 
            this.newMachineText.Location = new System.Drawing.Point(24, 16);
            this.newMachineText.Name = "newMachineText";
            this.newMachineText.Size = new System.Drawing.Size(224, 20);
            this.newMachineText.TabIndex = 0;
            this.newMachineText.Text = "";
            // 
            // addButton
            // 
            this.addButton.DialogResult = System.Windows.Forms.DialogResult.OK;
            this.addButton.Location = new System.Drawing.Point(16, 56);
            this.addButton.Name = "addButton";
            this.addButton.TabIndex = 1;
            this.addButton.Text = "Add";
            // 
            // cancelButton
            // 
            this.cancelButton.DialogResult = System.Windows.Forms.DialogResult.Cancel;
            this.cancelButton.Location = new System.Drawing.Point(176, 56);
            this.cancelButton.Name = "cancelButton";
            this.cancelButton.TabIndex = 2;
            this.cancelButton.Text = "Close";
            // 
            // AddMachineDlg
            // 
            this.AcceptButton = this.addButton;
            this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
            this.CancelButton = this.cancelButton;
            this.ClientSize = new System.Drawing.Size(272, 102);
            this.Controls.Add(this.cancelButton);
            this.Controls.Add(this.addButton);
            this.Controls.Add(this.newMachineText);
            this.Name = "AddMachineDlg";
            this.Text = "AddMachineName";
            this.ResumeLayout(false);

        }
		#endregion
	}
}
