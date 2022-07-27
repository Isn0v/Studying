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
    public partial class MainForm : Form
    {
        private Matrix matrix;
        public MainForm()
        {
            InitializeComponent();
        }

        private void MatrixControlForm1_FormClosed(object sender, FormClosedEventArgs e)
        {
            MatrixControlForm form = (MatrixControlForm)sender;

            Random r = new Random();

            matrix = new Matrix(form.Rows, form.Cols);
            matrix.fillWithRandom(1, 10, r);

            Element[][] elems = new Element[matrix.Columns][];

            for (int i = 0; i < matrix.Columns; i++)
            {
                elems[i] = new Element[matrix.Columns];
                for (int j = 0; j < matrix.Rows; j++)
                {
                    elems[i][j] = new Element(matrix, j, i);
                    Controls.Add(elems[i][j]);
                }
            }
        }

        private void Add1ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            MatrixControlForm form = new MatrixControlForm();
            form.Show();
            form.FormClosed += MatrixControlForm1_FormClosed;
        }

        private void Delete1ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            foreach(TextBox tb in Controls.OfType<TextBox>())
            {
                string tbName = tb.Name;
                if (tbName.Substring(9) == "TextBoxFirst")
                {
                    Controls.Remove(tb);
                }
            }
        }

        private void Add2ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            MatrixControlForm form = new MatrixControlForm();
            form.Show();
            form.FormClosed += MatrixControlForm2_FormClosed;
        }

        private void MatrixControlForm2_FormClosed(object sender, FormClosedEventArgs e)
        {
            MatrixControlForm form = (MatrixControlForm)sender;

            Random r = new Random();

            matrix = new Matrix(form.Rows, form.Cols);
            matrix.fillWithRandom(1, 10, r);

            Element[][] elems = new Element[matrix.Columns][];

            for (int i = 0; i < matrix.Columns; i++)
            {
                elems[i] = new Element[matrix.Columns];
                for (int j = 0; j < matrix.Rows; j++)
                {
                    elems[i][j] = new Element(matrix, j, i, true);
                    Controls.Add(elems[i][j]);
                }
            }
        }

        private void Delete2ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            foreach (TextBox tb in Controls.OfType<TextBox>())
            {
                string tbName = tb.Name;
                if (tbName.Substring(9) == "TextBoxSecond")
                {
                    Controls.Remove(tb);
                }
            }
        }
    }
}
