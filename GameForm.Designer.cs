namespace Tamagochi_Project
{
    partial class GameForm
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
            this.TamagochiLiveTimer = new System.Windows.Forms.Timer(this.components);
            this.TamagochiLevelImage = new System.Windows.Forms.PictureBox();
            this.LifeStatusLabel1 = new System.Windows.Forms.Label();
            this.LifeStateLabel = new System.Windows.Forms.Label();
            this.ExitBtn = new System.Windows.Forms.Button();
            this.TamagochiLiveProgressBar = new System.Windows.Forms.ProgressBar();
            this.FeedingProgressBar = new System.Windows.Forms.ProgressBar();
            this.FeedingLabel = new System.Windows.Forms.Label();
            this.DrinkingLabel = new System.Windows.Forms.Label();
            this.DrinkingProgressBar = new System.Windows.Forms.ProgressBar();
            this.FeedingBtn = new System.Windows.Forms.Button();
            this.DrinkingBtn = new System.Windows.Forms.Button();
            this.FeedingTimer = new System.Windows.Forms.Timer(this.components);
            this.DrinkingTimer = new System.Windows.Forms.Timer(this.components);
            ((System.ComponentModel.ISupportInitialize)(this.TamagochiLevelImage)).BeginInit();
            this.SuspendLayout();
            // 
            // TamagochiLiveTimer
            // 
            this.TamagochiLiveTimer.Enabled = true;
            this.TamagochiLiveTimer.Interval = 1000;
            this.TamagochiLiveTimer.Tick += new System.EventHandler(this.TamagochiLiveTimer_Tick);
            // 
            // TamagochiLevelImage
            // 
            this.TamagochiLevelImage.Image = global::Tamagochi_Project.Properties.Resources._1lvl;
            this.TamagochiLevelImage.Location = new System.Drawing.Point(64, 147);
            this.TamagochiLevelImage.Name = "TamagochiLevelImage";
            this.TamagochiLevelImage.Size = new System.Drawing.Size(77, 86);
            this.TamagochiLevelImage.SizeMode = System.Windows.Forms.PictureBoxSizeMode.AutoSize;
            this.TamagochiLevelImage.TabIndex = 0;
            this.TamagochiLevelImage.TabStop = false;
            // 
            // LifeStatusLabel1
            // 
            this.LifeStatusLabel1.AutoSize = true;
            this.LifeStatusLabel1.Location = new System.Drawing.Point(38, 112);
            this.LifeStatusLabel1.Name = "LifeStatusLabel1";
            this.LifeStatusLabel1.Size = new System.Drawing.Size(166, 16);
            this.LifeStatusLabel1.TabIndex = 1;
            this.LifeStatusLabel1.Text = "Стадия жизни тамагочи:";
            // 
            // LifeStateLabel
            // 
            this.LifeStateLabel.AutoSize = true;
            this.LifeStateLabel.Location = new System.Drawing.Point(98, 128);
            this.LifeStateLabel.Name = "LifeStateLabel";
            this.LifeStateLabel.Size = new System.Drawing.Size(43, 16);
            this.LifeStateLabel.TabIndex = 2;
            this.LifeStateLabel.Text = "1 из 5";
            // 
            // ExitBtn
            // 
            this.ExitBtn.Location = new System.Drawing.Point(678, 385);
            this.ExitBtn.Name = "ExitBtn";
            this.ExitBtn.Size = new System.Drawing.Size(91, 35);
            this.ExitBtn.TabIndex = 3;
            this.ExitBtn.Text = "Выход";
            this.ExitBtn.UseVisualStyleBackColor = true;
            this.ExitBtn.Click += new System.EventHandler(this.ExitBtn_Click);
            // 
            // TamagochiLiveProgressBar
            // 
            this.TamagochiLiveProgressBar.ForeColor = System.Drawing.Color.Black;
            this.TamagochiLiveProgressBar.Location = new System.Drawing.Point(41, 254);
            this.TamagochiLiveProgressBar.Name = "TamagochiLiveProgressBar";
            this.TamagochiLiveProgressBar.Size = new System.Drawing.Size(163, 23);
            this.TamagochiLiveProgressBar.Step = 5;
            this.TamagochiLiveProgressBar.Style = System.Windows.Forms.ProgressBarStyle.Continuous;
            this.TamagochiLiveProgressBar.TabIndex = 4;
            // 
            // FeedingProgressBar
            // 
            this.FeedingProgressBar.ForeColor = System.Drawing.Color.Black;
            this.FeedingProgressBar.Location = new System.Drawing.Point(326, 147);
            this.FeedingProgressBar.Name = "FeedingProgressBar";
            this.FeedingProgressBar.Size = new System.Drawing.Size(254, 23);
            this.FeedingProgressBar.Step = -5;
            this.FeedingProgressBar.Style = System.Windows.Forms.ProgressBarStyle.Continuous;
            this.FeedingProgressBar.TabIndex = 5;
            this.FeedingProgressBar.Value = 100;
            // 
            // FeedingLabel
            // 
            this.FeedingLabel.AutoSize = true;
            this.FeedingLabel.Location = new System.Drawing.Point(323, 112);
            this.FeedingLabel.Name = "FeedingLabel";
            this.FeedingLabel.Size = new System.Drawing.Size(46, 16);
            this.FeedingLabel.TabIndex = 6;
            this.FeedingLabel.Text = "Голод";
            // 
            // DrinkingLabel
            // 
            this.DrinkingLabel.AutoSize = true;
            this.DrinkingLabel.Location = new System.Drawing.Point(323, 219);
            this.DrinkingLabel.Name = "DrinkingLabel";
            this.DrinkingLabel.Size = new System.Drawing.Size(53, 16);
            this.DrinkingLabel.TabIndex = 8;
            this.DrinkingLabel.Text = "Жажда";
            // 
            // DrinkingProgressBar
            // 
            this.DrinkingProgressBar.ForeColor = System.Drawing.Color.Black;
            this.DrinkingProgressBar.Location = new System.Drawing.Point(326, 254);
            this.DrinkingProgressBar.Name = "DrinkingProgressBar";
            this.DrinkingProgressBar.Size = new System.Drawing.Size(254, 23);
            this.DrinkingProgressBar.Step = -5;
            this.DrinkingProgressBar.Style = System.Windows.Forms.ProgressBarStyle.Continuous;
            this.DrinkingProgressBar.TabIndex = 7;
            this.DrinkingProgressBar.Value = 100;
            // 
            // FeedingBtn
            // 
            this.FeedingBtn.Location = new System.Drawing.Point(624, 135);
            this.FeedingBtn.Name = "FeedingBtn";
            this.FeedingBtn.Size = new System.Drawing.Size(125, 35);
            this.FeedingBtn.TabIndex = 9;
            this.FeedingBtn.Text = "Покормить";
            this.FeedingBtn.UseVisualStyleBackColor = true;
            this.FeedingBtn.Click += new System.EventHandler(this.FeedingBtn_Click);
            // 
            // DrinkingBtn
            // 
            this.DrinkingBtn.Location = new System.Drawing.Point(624, 242);
            this.DrinkingBtn.Name = "DrinkingBtn";
            this.DrinkingBtn.Size = new System.Drawing.Size(91, 35);
            this.DrinkingBtn.TabIndex = 10;
            this.DrinkingBtn.Text = "Напоить";
            this.DrinkingBtn.UseVisualStyleBackColor = true;
            this.DrinkingBtn.Click += new System.EventHandler(this.DrinkingBtn_Click);
            // 
            // FeedingTimer
            // 
            this.FeedingTimer.Enabled = true;
            this.FeedingTimer.Interval = 1000;
            this.FeedingTimer.Tick += new System.EventHandler(this.FeedingTimer_Tick);
            // 
            // DrinkingTimer
            // 
            this.DrinkingTimer.Enabled = true;
            this.DrinkingTimer.Interval = 1000;
            this.DrinkingTimer.Tick += new System.EventHandler(this.DrinkingTimer_Tick);
            // 
            // GameForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this.DrinkingBtn);
            this.Controls.Add(this.FeedingBtn);
            this.Controls.Add(this.DrinkingLabel);
            this.Controls.Add(this.DrinkingProgressBar);
            this.Controls.Add(this.FeedingLabel);
            this.Controls.Add(this.FeedingProgressBar);
            this.Controls.Add(this.TamagochiLiveProgressBar);
            this.Controls.Add(this.ExitBtn);
            this.Controls.Add(this.LifeStateLabel);
            this.Controls.Add(this.LifeStatusLabel1);
            this.Controls.Add(this.TamagochiLevelImage);
            this.Name = "GameForm";
            this.Text = "GameForm";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.GameForm_FormClosing);
            ((System.ComponentModel.ISupportInitialize)(this.TamagochiLevelImage)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Timer TamagochiLiveTimer;
        private System.Windows.Forms.PictureBox TamagochiLevelImage;
        private System.Windows.Forms.Label LifeStatusLabel1;
        private System.Windows.Forms.Label LifeStateLabel;
        private System.Windows.Forms.Button ExitBtn;
        private System.Windows.Forms.ProgressBar TamagochiLiveProgressBar;
        private System.Windows.Forms.ProgressBar FeedingProgressBar;
        private System.Windows.Forms.Label FeedingLabel;
        private System.Windows.Forms.Label DrinkingLabel;
        private System.Windows.Forms.ProgressBar DrinkingProgressBar;
        private System.Windows.Forms.Button FeedingBtn;
        private System.Windows.Forms.Button DrinkingBtn;
        private System.Windows.Forms.Timer FeedingTimer;
        private System.Windows.Forms.Timer DrinkingTimer;
    }
}