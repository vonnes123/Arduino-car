
namespace Car_system
{
    partial class Form1
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
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
            this.bAlarm = new System.Windows.Forms.Button();
            this.lbxLog = new System.Windows.Forms.ListBox();
            this.lLog = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.tbxTemperature = new System.Windows.Forms.TextBox();
            this.tbxHeadlight = new System.Windows.Forms.TextBox();
            this.SuspendLayout();
            // 
            // bAlarm
            // 
            this.bAlarm.BackColor = System.Drawing.Color.Red;
            this.bAlarm.Location = new System.Drawing.Point(81, 310);
            this.bAlarm.Name = "bAlarm";
            this.bAlarm.Size = new System.Drawing.Size(127, 81);
            this.bAlarm.TabIndex = 0;
            this.bAlarm.Text = "ALARM";
            this.bAlarm.UseVisualStyleBackColor = false;
            this.bAlarm.Click += new System.EventHandler(this.bAlarm_Click);
            // 
            // lbxLog
            // 
            this.lbxLog.FormattingEnabled = true;
            this.lbxLog.ItemHeight = 16;
            this.lbxLog.Location = new System.Drawing.Point(478, 123);
            this.lbxLog.Name = "lbxLog";
            this.lbxLog.Size = new System.Drawing.Size(187, 292);
            this.lbxLog.TabIndex = 1;
            // 
            // lLog
            // 
            this.lLog.AutoSize = true;
            this.lLog.Location = new System.Drawing.Point(489, 96);
            this.lLog.Name = "lLog";
            this.lLog.Size = new System.Drawing.Size(32, 17);
            this.lLog.TabIndex = 2;
            this.lLog.Text = "Log";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(316, 160);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(90, 17);
            this.label1.TabIndex = 5;
            this.label1.Text = "Temperature";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(331, 310);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(75, 17);
            this.label2.TabIndex = 6;
            this.label2.Text = "Headlights";
            // 
            // timer1
            // 
            this.timer1.Enabled = true;
            this.timer1.Tick += new System.EventHandler(this.timer1_Tick);
            // 
            // tbxTemperature
            // 
            this.tbxTemperature.Location = new System.Drawing.Point(318, 180);
            this.tbxTemperature.Name = "tbxTemperature";
            this.tbxTemperature.Size = new System.Drawing.Size(102, 22);
            this.tbxTemperature.TabIndex = 7;
            // 
            // tbxHeadlight
            // 
            this.tbxHeadlight.Location = new System.Drawing.Point(319, 330);
            this.tbxHeadlight.Name = "tbxHeadlight";
            this.tbxHeadlight.Size = new System.Drawing.Size(101, 22);
            this.tbxHeadlight.TabIndex = 8;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("$this.BackgroundImage")));
            this.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.ClientSize = new System.Drawing.Size(738, 450);
            this.Controls.Add(this.tbxHeadlight);
            this.Controls.Add(this.tbxTemperature);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.lLog);
            this.Controls.Add(this.lbxLog);
            this.Controls.Add(this.bAlarm);
            this.DoubleBuffered = true;
            this.Name = "Form1";
            this.Text = "Form1";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button bAlarm;
        private System.Windows.Forms.ListBox lbxLog;
        private System.Windows.Forms.Label lLog;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Timer timer1;
        private System.Windows.Forms.TextBox tbxTemperature;
        private System.Windows.Forms.TextBox tbxHeadlight;
    }
}

