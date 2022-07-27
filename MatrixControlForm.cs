using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace MatrixGUI
{
    public partial class MatrixControlForm : Form
    {
        private int rows;
        private int cols;

        public int Rows { get => rows; }
        public int Cols { get => cols; }
        public MatrixControlForm()
        {
            InitializeComponent();
        }

        private void AddBtn_Click(object sender, EventArgs e)
        {
            if (!int.TryParse(RowTextBox.Text, out rows) || !int.TryParse(ColumnTextBox.Text, out cols))
            {
                MessageBox.Show("Неверный ввод\nПопробуйте еще раз", "Ошибка!", MessageBoxButtons.OK);
                RowTextBox.Clear();
                ColumnTextBox.Clear();
            }
            else
            {
                this.Close();
            }
        }
    }
}
