using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Tamagochi_Project
{
    public partial class GameForm : Form
    {
        private LifeLVLStatus current_state;
        private string current_path = Directory.GetParent(Environment.CurrentDirectory).Parent.FullName + @"\pics\";

        public GameForm(LifeLVLStatus state)
        {
            InitializeComponent();
            current_state = state;
        }

        private void DisableTimers()
        {
            TamagochiLiveTimer.Enabled = false;
            FeedingTimer.Enabled = false;
            DrinkingTimer.Enabled = false;
        } 
        private void GameVictory()
        {
            DisableTimers();
            MessageBox.Show("Вы победили!\nНажмите, чтобы перейти в меню", "Поздравляем!!!", MessageBoxButtons.OK, MessageBoxIcon.Information);
            this.Close();
        }

        private void GameLoss()
        {
            DisableTimers();
            MessageBox.Show("Вы проиграли\nНажмите, чтобы пперейти в меню", "Поражение", MessageBoxButtons.OK, MessageBoxIcon.Information);
            this.Close();
        }

        private void ChangeLifeLvlState(LifeLVLStatus lvlState)
        {
            TamagochiLiveProgressBar.Value = 0;
            current_state += 1;

            string lvlLabel_new = Convert.ToInt32(lvlState) + " из 5";
            LifeStateLabel.Text = lvlLabel_new;

            TamagochiLevelImage.Image = Image.FromFile(current_path + Convert.ToInt32(lvlState) + "lvl.jpg");
        }


        private void ExitBtn_Click(object sender, EventArgs e)
        {
            DialogResult exit = MessageBox.Show("Возврат в меню?\n(Ваш прогресс не сохранится)",
               "Вопрос", MessageBoxButtons.YesNo,
               MessageBoxIcon.Question, MessageBoxDefaultButton.Button1);
            if (exit == DialogResult.Yes)
            {
                this.Close();
            }
        }

        private void GameForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            
            WelcomeForm welcomeForm = (WelcomeForm)SingleTon.ReceiveObject();
            welcomeForm.Show();
        }

        private void TamagochiLiveTimer_Tick(object sender, EventArgs e)
        {
            TamagochiLiveProgressBar.PerformStep();
            if (TamagochiLiveProgressBar.Value == 100)
            {
                switch (current_state)
                {
                    case LifeLVLStatus.LVL_1:
                        {
                            ChangeLifeLvlState(LifeLVLStatus.LVL_2);
                        }
                        break;
                    case LifeLVLStatus.LVL_2:
                        {
                            ChangeLifeLvlState(LifeLVLStatus.LVL_3);
                        }
                        break;
                    case LifeLVLStatus.LVL_3:
                        {
                            ChangeLifeLvlState(LifeLVLStatus.LVL_4);
                        }
                        break;
                    case LifeLVLStatus.LVL_4:
                        {
                            ChangeLifeLvlState(LifeLVLStatus.LVL_5);
                        }
                        break;
                    case LifeLVLStatus.LVL_5:
                        {
                            GameVictory();
                        }
                        break;
                }
            }
        }

        private void FeedingTimer_Tick(object sender, EventArgs e)
        {
            FeedingProgressBar.PerformStep();
            if (FeedingProgressBar.Value <= 0)
            {
                GameLoss();
            }
        }
        private void FeedingBtn_Click(object sender, EventArgs e)
        {
            try
            {
                FeedingProgressBar.Value += 10;
            }
            catch { }
            finally { }
        }

        private void DrinkingTimer_Tick(object sender, EventArgs e)
        {
            DrinkingProgressBar.PerformStep();
            if (DrinkingProgressBar.Value <= 0)
            {
                GameLoss();
            }
        }

        private void DrinkingBtn_Click(object sender, EventArgs e)
        {
            try
            {
                DrinkingProgressBar.Value += 10;
            }
            catch { }
            finally { }
        }

    }
}
