using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Tamagochi_Project
{
    public partial class WelcomeForm : Form
    {
        public WelcomeForm()
        {
            InitializeComponent();
        }

        

        private void StartBtn_Click(object sender, EventArgs e)
        {

            GameForm gameForm = new GameForm(LifeLVLStatus.LVL_1);
            gameForm.Show();
            this.Hide();
            SingleTon.SendObject(this);

        }

        private void ExitBtn_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void WelcomeForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            DialogResult exit = MessageBox.Show("Вы уверены, что хотите выйти?",
                "Вопрос", MessageBoxButtons.YesNo,
                MessageBoxIcon.Question, MessageBoxDefaultButton.Button1);
            if (exit == DialogResult.No)
            {
                e.Cancel = true;
            }
        }
    }
}
