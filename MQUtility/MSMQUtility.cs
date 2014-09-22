using System;
using System.Drawing;
using System.Collections;
using System.Collections.Specialized;
using System.ComponentModel;
using System.Windows.Forms;
using System.Data;
using System.Messaging;
using System.IO;
using System.Text;

namespace MSMQUtil2006
{
	/// <summary>
	/// Summary description for Form1.
	/// </summary>
	public class MSMQUtility : System.Windows.Forms.Form
	{
        private System.Windows.Forms.ComboBox queueName;
        private System.Windows.Forms.ComboBox mqServerName;
        private System.Windows.Forms.Button peekButton;
        private System.Windows.Forms.Button popButton;
        private System.Windows.Forms.TextBox peekText;
        private System.Windows.Forms.Label msmqServerLabel;
        private System.Windows.Forms.Label queueNameLabel;
        private System.Windows.Forms.CheckBox ipCheckBox;
        private System.Windows.Forms.TextBox SendBox;
        private System.Windows.Forms.Button sendButton;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label targetMQServLabel;
        private System.Windows.Forms.ComboBox targetServerCombo;
        private System.Windows.Forms.ComboBox targetQueueCombo;
        private System.Windows.Forms.Button transferButton;
        private System.Windows.Forms.CheckBox targetIPCheckbox;

        private TimeSpan peekPopSpan= new TimeSpan(0,0,5);
        private System.Windows.Forms.Button Queues;
        private System.Windows.Forms.MainMenu mainMenu1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.ComboBox targetQueue2;
        private System.Windows.Forms.Button doubleCopy;
        private IContainer components;

        private StringFormatter formatter = new StringFormatter();

        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main() 
        {
            Application.Run(new MSMQUtility());
        }

		///<summary>
		///</summary>
		public MSMQUtility()
		{
            //
			// Required for Windows Form Designer support
			//
			InitializeComponent();

            // Source Queues
            mqServerName.Items.Clear();
            queueName.Items.Clear();

            // Target Queues
            targetServerCombo.Items.Clear();
            targetQueueCombo.Items.Clear();
            targetQueue2.Items.Clear();

            // Source Machine Names
            StringCollection sc = new StringCollection ();
            sc.Add ("localhost");

            foreach (string s in sc)
            {
                mqServerName.Items.Add (s);
                targetServerCombo.Items.Add (s);
            }
        }

		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		protected override void Dispose( bool disposing )
		{
			if( disposing )
			{
				if (components != null) 
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
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(MSMQUtility));
            this.peekButton = new System.Windows.Forms.Button();
            this.popButton = new System.Windows.Forms.Button();
            this.peekText = new System.Windows.Forms.TextBox();
            this.queueName = new System.Windows.Forms.ComboBox();
            this.mqServerName = new System.Windows.Forms.ComboBox();
            this.msmqServerLabel = new System.Windows.Forms.Label();
            this.queueNameLabel = new System.Windows.Forms.Label();
            this.ipCheckBox = new System.Windows.Forms.CheckBox();
            this.SendBox = new System.Windows.Forms.TextBox();
            this.sendButton = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.targetMQServLabel = new System.Windows.Forms.Label();
            this.targetServerCombo = new System.Windows.Forms.ComboBox();
            this.targetQueueCombo = new System.Windows.Forms.ComboBox();
            this.transferButton = new System.Windows.Forms.Button();
            this.targetIPCheckbox = new System.Windows.Forms.CheckBox();
            this.Queues = new System.Windows.Forms.Button();
            this.mainMenu1 = new System.Windows.Forms.MainMenu(this.components);
            this.label2 = new System.Windows.Forms.Label();
            this.targetQueue2 = new System.Windows.Forms.ComboBox();
            this.doubleCopy = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // peekButton
            // 
            this.peekButton.Location = new System.Drawing.Point(16, 96);
            this.peekButton.Name = "peekButton";
            this.peekButton.Size = new System.Drawing.Size(75, 23);
            this.peekButton.TabIndex = 0;
            this.peekButton.Text = "Peek";
            this.peekButton.Click += new System.EventHandler(this.peekButton_Click);
            // 
            // popButton
            // 
            this.popButton.Location = new System.Drawing.Point(224, 96);
            this.popButton.Name = "popButton";
            this.popButton.Size = new System.Drawing.Size(96, 23);
            this.popButton.TabIndex = 1;
            this.popButton.Text = "Pop (Receive)";
            this.popButton.Click += new System.EventHandler(this.popButton_Click);
            // 
            // peekText
            // 
            this.peekText.Location = new System.Drawing.Point(16, 128);
            this.peekText.Multiline = true;
            this.peekText.Name = "peekText";
            this.peekText.ReadOnly = true;
            this.peekText.Size = new System.Drawing.Size(304, 128);
            this.peekText.TabIndex = 3;
            // 
            // queueName
            // 
            this.queueName.Location = new System.Drawing.Point(16, 64);
            this.queueName.Name = "queueName";
            this.queueName.Size = new System.Drawing.Size(304, 21);
            this.queueName.TabIndex = 4;
            // 
            // mqServerName
            // 
            this.mqServerName.Location = new System.Drawing.Point(16, 24);
            this.mqServerName.Name = "mqServerName";
            this.mqServerName.Size = new System.Drawing.Size(304, 21);
            this.mqServerName.TabIndex = 5;
            this.mqServerName.SelectedIndexChanged += new System.EventHandler(this.sourceQueueChanged);
            // 
            // msmqServerLabel
            // 
            this.msmqServerLabel.Location = new System.Drawing.Point(8, 8);
            this.msmqServerLabel.Name = "msmqServerLabel";
            this.msmqServerLabel.Size = new System.Drawing.Size(104, 16);
            this.msmqServerLabel.TabIndex = 6;
            this.msmqServerLabel.Text = "Source MQ Server:";
            // 
            // queueNameLabel
            // 
            this.queueNameLabel.Location = new System.Drawing.Point(8, 48);
            this.queueNameLabel.Name = "queueNameLabel";
            this.queueNameLabel.Size = new System.Drawing.Size(80, 16);
            this.queueNameLabel.TabIndex = 7;
            this.queueNameLabel.Text = "Queue Name:";
            // 
            // ipCheckBox
            // 
            this.ipCheckBox.Location = new System.Drawing.Point(144, 8);
            this.ipCheckBox.Name = "ipCheckBox";
            this.ipCheckBox.Size = new System.Drawing.Size(88, 16);
            this.ipCheckBox.TabIndex = 8;
            this.ipCheckBox.Text = "IP Address?";
            // 
            // SendBox
            // 
            this.SendBox.Location = new System.Drawing.Point(16, 264);
            this.SendBox.Multiline = true;
            this.SendBox.Name = "SendBox";
            this.SendBox.Size = new System.Drawing.Size(304, 120);
            this.SendBox.TabIndex = 9;
            // 
            // sendButton
            // 
            this.sendButton.Location = new System.Drawing.Point(16, 392);
            this.sendButton.Name = "sendButton";
            this.sendButton.Size = new System.Drawing.Size(75, 23);
            this.sendButton.TabIndex = 10;
            this.sendButton.Text = "Send";
            this.sendButton.Click += new System.EventHandler(this.sendButton_Click);
            // 
            // label1
            // 
            this.label1.Location = new System.Drawing.Point(16, 464);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(88, 16);
            this.label1.TabIndex = 14;
            this.label1.Text = "Queue Name 1:";
            // 
            // targetMQServLabel
            // 
            this.targetMQServLabel.Location = new System.Drawing.Point(16, 424);
            this.targetMQServLabel.Name = "targetMQServLabel";
            this.targetMQServLabel.Size = new System.Drawing.Size(120, 16);
            this.targetMQServLabel.TabIndex = 13;
            this.targetMQServLabel.Text = "Target MQ Server:";
            // 
            // targetServerCombo
            // 
            this.targetServerCombo.Location = new System.Drawing.Point(16, 440);
            this.targetServerCombo.Name = "targetServerCombo";
            this.targetServerCombo.Size = new System.Drawing.Size(304, 21);
            this.targetServerCombo.TabIndex = 12;
            this.targetServerCombo.SelectedIndexChanged += new System.EventHandler(this.targetQueueChanged);
            // 
            // targetQueueCombo
            // 
            this.targetQueueCombo.Location = new System.Drawing.Point(16, 480);
            this.targetQueueCombo.Name = "targetQueueCombo";
            this.targetQueueCombo.Size = new System.Drawing.Size(304, 21);
            this.targetQueueCombo.TabIndex = 11;
            // 
            // transferButton
            // 
            this.transferButton.Location = new System.Drawing.Point(240, 392);
            this.transferButton.Name = "transferButton";
            this.transferButton.Size = new System.Drawing.Size(75, 23);
            this.transferButton.TabIndex = 15;
            this.transferButton.Text = "Transfer";
            this.transferButton.Click += new System.EventHandler(this.transferButton_Click);
            // 
            // targetIPCheckbox
            // 
            this.targetIPCheckbox.Location = new System.Drawing.Point(232, 424);
            this.targetIPCheckbox.Name = "targetIPCheckbox";
            this.targetIPCheckbox.Size = new System.Drawing.Size(88, 16);
            this.targetIPCheckbox.TabIndex = 16;
            this.targetIPCheckbox.Text = "IP Address?";
            // 
            // Queues
            // 
            this.Queues.Location = new System.Drawing.Point(240, 0);
            this.Queues.Name = "Queues";
            this.Queues.Size = new System.Drawing.Size(112, 23);
            this.Queues.TabIndex = 17;
            this.Queues.Text = "Add Machine Name";
            this.Queues.Click += new System.EventHandler(this.queuesButton_Click);
            // 
            // label2
            // 
            this.label2.Location = new System.Drawing.Point(16, 504);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(88, 16);
            this.label2.TabIndex = 19;
            this.label2.Text = "Queue Name 2:";
            // 
            // targetQueue2
            // 
            this.targetQueue2.Location = new System.Drawing.Point(16, 520);
            this.targetQueue2.Name = "targetQueue2";
            this.targetQueue2.Size = new System.Drawing.Size(304, 21);
            this.targetQueue2.TabIndex = 18;
            // 
            // doubleCopy
            // 
            this.doubleCopy.Location = new System.Drawing.Point(128, 392);
            this.doubleCopy.Name = "doubleCopy";
            this.doubleCopy.Size = new System.Drawing.Size(75, 23);
            this.doubleCopy.TabIndex = 20;
            this.doubleCopy.Text = "Copy to 2";
            this.doubleCopy.Click += new System.EventHandler(this.doubleCopy_Click);
            // 
            // MSMQUtility
            // 
            this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
            this.ClientSize = new System.Drawing.Size(376, 553);
            this.Controls.Add(this.doubleCopy);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.targetQueue2);
            this.Controls.Add(this.Queues);
            this.Controls.Add(this.targetIPCheckbox);
            this.Controls.Add(this.transferButton);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.targetMQServLabel);
            this.Controls.Add(this.targetServerCombo);
            this.Controls.Add(this.targetQueueCombo);
            this.Controls.Add(this.sendButton);
            this.Controls.Add(this.SendBox);
            this.Controls.Add(this.ipCheckBox);
            this.Controls.Add(this.queueNameLabel);
            this.Controls.Add(this.msmqServerLabel);
            this.Controls.Add(this.mqServerName);
            this.Controls.Add(this.queueName);
            this.Controls.Add(this.peekText);
            this.Controls.Add(this.popButton);
            this.Controls.Add(this.peekButton);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Menu = this.mainMenu1;
            this.Name = "MSMQUtility";
            this.Text = "MSMQ Utility";
            this.ResumeLayout(false);
            this.PerformLayout();

        }
		#endregion



        private void queuesButton_Click(object sender, System.EventArgs e)
        {
            AddMachineDlg dlg = new AddMachineDlg ();

            if (dlg.ShowDialog () == DialogResult.OK)
            {
                mqServerName.Items.Add (dlg.newMachineText.Text);
                targetServerCombo.Items.Add (dlg.newMachineText.Text);
            }
        }

        private string GetQueueName (string queueInd)
        {
            string server = "";
            string queue  = "";
            bool ipCheck = false;

            if (queueInd == "target")
            {
                server=targetServerCombo.Text;
                queue=targetQueueCombo.Text;
                ipCheck = targetIPCheckbox.Checked;
            }
            else if (queueInd == "target2")
            {
                server=targetServerCombo.Text;
                queue=targetQueue2.Text;
                ipCheck = targetIPCheckbox.Checked;
            }
            else
            {
                server=mqServerName.Text;
                queue=queueName.Text;
                ipCheck = ipCheckBox.Checked;
            }
            string fullMQName = "";
            if (ipCheck)
            {
                fullMQName = "FormatName:DIRECT=TCP:" + server + queue;
            }
            else
            {
                fullMQName = "FormatName:DIRECT=OS:" + server + queue;
            }

            return fullMQName;
        }

        private void peekRPop (bool pop)
        {
            System.Messaging.Message msg = null;
            MessageQueue queue = null;
            try
            {
                string queueName = GetQueueName("source");
                queue = new MessageQueue(queueName);

                if (pop)
                    msg = queue.Receive(peekPopSpan);
                else
                    msg = queue.Peek(peekPopSpan);
            }
            catch (Exception e)
            {
                MessageBox.Show ("Couldn't Peek/Pop:" + e.Source + ":" + e.Message);
            }

            try
            {
                if (msg != null)
                {
                    StreamReader reader = new StreamReader(msg.BodyStream);
                    string msgBody = reader.ReadToEnd().Replace ("\0", ".");
                    
                    peekText.Text = msgBody;
                }
                else
                    MessageBox.Show ("No Message Found.");
                
            }
            catch (Exception excp)
            {
                MessageBox.Show ("Couldn't Translate Message:" + excp.Source + ":" + excp.Message);
            }
        }

        private void popButton_Click(object sender, System.EventArgs e)
        {
            if (   mqServerName.Text.Length > 0
                && queueName.Text.Length > 0)
            {
                peekRPop (true);
            }
            else
            {
                MessageBox.Show ("A required field for this operation is blank");
                return;
            }
        }

        private void peekButton_Click(object sender, System.EventArgs e)
        {
            if (   mqServerName.Text.Length > 0
                && queueName.Text.Length > 0)
            {
                peekRPop (false);
            }
            else
            {
                MessageBox.Show ("A required field for this operation is blank");
                return;
            }
        }

        private void sendButton_Click(object sender, System.EventArgs e)
        {
            if (   targetServerCombo.Text.Length < 1
                || targetQueueCombo.Text.Length < 1)
            {
                MessageBox.Show ("A required field for this operation is blank");
                return;
            }

            try
            {
                string queueName = GetQueueName("target");
                MessageQueue queue = new MessageQueue(queueName);

                var msg = new System.Messaging.Message(SendBox.Text, formatter);
                msg.BodyType = 8;
                queue.Send(msg);
                MessageBox.Show ("Message Sent!");
            }
            catch (Exception exc)
            {
                MessageBox.Show ("Couldn't Send Message:" + exc.Source + ":" + exc.Message);
            }
        }

        private void transferButton_Click(object sender, System.EventArgs e)
        {
            if (   mqServerName.Text.Length < 1
                || queueName.Text.Length    < 1
                || targetServerCombo.Text.Length < 1
                || targetQueueCombo.Text.Length  < 1)
            {
                MessageBox.Show ("A required field for this operation is blank");
                return;
            }

            try
            {
                string sourceQueueName = GetQueueName("source");
                string targetQueueName = GetQueueName("target");
                MessageQueue sourceQueue = new MessageQueue(sourceQueueName);
                MessageQueue targetQueue = new MessageQueue(targetQueueName);

                System.Messaging.Message msg;

                msg = sourceQueue.Peek(peekPopSpan);
                targetQueue.Send(msg);
                msg = sourceQueue.Receive(peekPopSpan);
                MessageBox.Show ("Message Trasnferred from " + sourceQueueName + " to " + targetQueueName);
            }
            catch (Exception ex)
            {
                MessageBox.Show ("Transfer failed:" + ex.Source + ":" + ex.Message);
            }
        }

        private void doubleCopy_Click(object sender, System.EventArgs e)
        {
            if (   mqServerName.Text.Length < 1
                || queueName.Text.Length    < 1
                || targetServerCombo.Text.Length < 1
                || targetQueueCombo.Text.Length  < 1
                || targetQueue2.Text.Length  < 1)
            {
                MessageBox.Show ("A required field for this operation is blank");
                return;
            }

            try
            {
                string sourceQueueName = GetQueueName("source");
                string targetQueueName = GetQueueName("target");
                string target2QueueName = GetQueueName("target2");
                MessageQueue sourceQueue = new MessageQueue(sourceQueueName);
                MessageQueue targetQueue = new MessageQueue(targetQueueName);
                MessageQueue target2Queue = new MessageQueue(target2QueueName);

                System.Messaging.Message msg;

                msg = sourceQueue.Peek(peekPopSpan);
                targetQueue.Send(msg);
                target2Queue.Send(msg);
                msg = sourceQueue.Receive(peekPopSpan);
                MessageBox.Show ("Message Trasnferred from " + sourceQueueName + " to " + targetQueueName);
            }
            catch (Exception ex)
            {
                MessageBox.Show ("Copy failed:" + ex.Source + ":" + ex.Message);
            }
        }


        private void sourceQueueChanged(object sender, System.EventArgs e)
        {
            if (mqServerName.Text.Length > 0)
            {
                queueName.Items.Clear();
                try
                {
                    MessageQueue[] QueueList = 
                        MessageQueue.GetPrivateQueuesByMachine (mqServerName.Text);

                    // Move to the next queue and read its path.
                    foreach(MessageQueue queueItem in QueueList)
                    {                   
                        // Increase the count if priority is Lowest.
                        queueName.Items.Add ("\\" + queueItem.QueueName);
                    }

                    MessageQueue[] QueueList2 = 
                        MessageQueue.GetPrivateQueuesByMachine (mqServerName.Text);

                    // Move to the next queue and read its path.
                    foreach(MessageQueue queueItem2 in QueueList2)
                    {                   
                        // Increase the count if priority is Lowest.
                        queueName.Items.Add ("\\" + queueItem2.QueueName);
                    }
                }
                catch (Exception ex)
                {
                    MessageBox.Show ("Error pulling Message Queues:" + ex.Source + ":" + ex.Message);
                }
            }
        }

        private void targetQueueChanged(object sender, System.EventArgs e)
        {
            if (targetServerCombo.Text.Length > 0)
            {
                targetQueueCombo.Items.Clear();
                targetQueue2.Items.Clear();
                try
                {
                    MessageQueue[] QueueList = 
                        MessageQueue.GetPrivateQueuesByMachine (targetServerCombo.Text);

                    // Move to the next queue and read its path.
                    foreach(MessageQueue queueItem in QueueList)
                    {                   
                        // Increase the count if priority is Lowest.
                        targetQueueCombo.Items.Add ("\\" + queueItem.QueueName);
                        targetQueue2.Items.Add ("\\" + queueItem.QueueName);
                    }

                    MessageQueue[] QueueList2 = 
                        MessageQueue.GetPrivateQueuesByMachine (targetServerCombo.Text);

                    // Move to the next queue and read its path.
                    foreach(MessageQueue queueItem2 in QueueList2)
                    {                   
                        // Increase the count if priority is Lowest.
                        targetQueueCombo.Items.Add ("\\" + queueItem2.QueueName);
                        targetQueue2.Items.Add ("\\" + queueItem2.QueueName);
                    }
                }
                catch (Exception ex)
                {
                    MessageBox.Show ("Error pulling Message Queues:" + ex.Source + ":" + ex.Message);
                }
            }
        }

	}

    public class StringFormatter : IMessageFormatter
    {

        public bool CanRead(System.Messaging.Message message)
        {
            return true;
        }

        public object Read(System.Messaging.Message msg)
        {
            //Obtain the BodyStream for the message.
            Stream stm = msg.BodyStream;

            //Create a StreamReader object used for reading from the stream.
            StreamReader reader = new StreamReader(stm);

            //Return the string read from the stream.
            //StreamReader.ReadToEnd returns a string.
            return reader.ReadToEnd();
        }
	

        public void Write(System.Messaging.Message msg, object obj)
        {
            //Declare a buffer.
            byte[] buff;

            if (obj is String) {
               buff = Encoding.Unicode.GetBytes(obj.ToString());
            }
            else
            {
                buff = new byte[0];
            }

            //Create a new MemoryStream object passing the buffer.
            Stream stm = new MemoryStream(buff);

            //Assign the stream to the message's BodyStream property.
            msg.BodyStream = stm;
        } 

        public object Clone()
        {
            return new StringFormatter();
        }
    }
}
