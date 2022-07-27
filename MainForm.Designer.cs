namespace MatrixGUI
{
    partial class MainForm
    {
        /// <summary>
        /// Обязательная переменная конструктора.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Освободить все используемые ресурсы.
        /// </summary>
        /// <param name="disposing">истинно, если управляемый ресурс должен быть удален; иначе ложно.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Код, автоматически созданный конструктором форм Windows

        /// <summary>
        /// Требуемый метод для поддержки конструктора — не изменяйте 
        /// содержимое этого метода с помощью редактора кода.
        /// </summary>
        private void InitializeComponent()
        {
            this.matrixMenuStrip = new System.Windows.Forms.MenuStrip();
            this.Matrix1ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.Add1ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.Delete1ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.Matrix2ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.Add2ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.Delete2ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.matrixMenuStrip.SuspendLayout();
            this.SuspendLayout();
            // 
            // matrixMenuStrip
            // 
            this.matrixMenuStrip.ImageScalingSize = new System.Drawing.Size(20, 20);
            this.matrixMenuStrip.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.Matrix1ToolStripMenuItem,
            this.Matrix2ToolStripMenuItem});
            this.matrixMenuStrip.Location = new System.Drawing.Point(0, 0);
            this.matrixMenuStrip.Name = "matrixMenuStrip";
            this.matrixMenuStrip.Size = new System.Drawing.Size(800, 28);
            this.matrixMenuStrip.TabIndex = 0;
            this.matrixMenuStrip.Text = "matrixMenuStrip";
            // 
            // Matrix1ToolStripMenuItem
            // 
            this.Matrix1ToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.Add1ToolStripMenuItem,
            this.Delete1ToolStripMenuItem});
            this.Matrix1ToolStripMenuItem.Name = "Matrix1ToolStripMenuItem";
            this.Matrix1ToolStripMenuItem.Size = new System.Drawing.Size(93, 24);
            this.Matrix1ToolStripMenuItem.Text = "Матрица1";
            // 
            // Add1ToolStripMenuItem
            // 
            this.Add1ToolStripMenuItem.Name = "Add1ToolStripMenuItem";
            this.Add1ToolStripMenuItem.Size = new System.Drawing.Size(224, 26);
            this.Add1ToolStripMenuItem.Text = "Добавить";
            this.Add1ToolStripMenuItem.Click += new System.EventHandler(this.Add1ToolStripMenuItem_Click);
            // 
            // Delete1ToolStripMenuItem
            // 
            this.Delete1ToolStripMenuItem.Name = "Delete1ToolStripMenuItem";
            this.Delete1ToolStripMenuItem.Size = new System.Drawing.Size(224, 26);
            this.Delete1ToolStripMenuItem.Text = "Удалить";
            this.Delete1ToolStripMenuItem.Click += new System.EventHandler(this.Delete1ToolStripMenuItem_Click);
            // 
            // Matrix2ToolStripMenuItem
            // 
            this.Matrix2ToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.Add2ToolStripMenuItem,
            this.Delete2ToolStripMenuItem});
            this.Matrix2ToolStripMenuItem.Name = "Matrix2ToolStripMenuItem";
            this.Matrix2ToolStripMenuItem.Size = new System.Drawing.Size(97, 24);
            this.Matrix2ToolStripMenuItem.Text = "Матрица 2";
            // 
            // Add2ToolStripMenuItem
            // 
            this.Add2ToolStripMenuItem.Name = "Add2ToolStripMenuItem";
            this.Add2ToolStripMenuItem.Size = new System.Drawing.Size(224, 26);
            this.Add2ToolStripMenuItem.Text = "Добавить";
            this.Add2ToolStripMenuItem.Click += new System.EventHandler(this.Add2ToolStripMenuItem_Click);
            // 
            // Delete2ToolStripMenuItem
            // 
            this.Delete2ToolStripMenuItem.Name = "Delete2ToolStripMenuItem";
            this.Delete2ToolStripMenuItem.Size = new System.Drawing.Size(224, 26);
            this.Delete2ToolStripMenuItem.Text = "Удалить";
            this.Delete2ToolStripMenuItem.Click += new System.EventHandler(this.Delete2ToolStripMenuItem_Click);
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this.matrixMenuStrip);
            this.MainMenuStrip = this.matrixMenuStrip;
            this.Name = "MainForm";
            this.Text = "MainForm";
            this.matrixMenuStrip.ResumeLayout(false);
            this.matrixMenuStrip.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.MenuStrip matrixMenuStrip;
        private System.Windows.Forms.ToolStripMenuItem Matrix1ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem Add1ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem Delete1ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem Matrix2ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem Add2ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem Delete2ToolStripMenuItem;
    }
}

