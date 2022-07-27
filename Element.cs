using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace MatrixGUI
{
    internal class Element : TextBox
    {
        public Element(Matrix matrix, int row, int col)
        {
            int ElementCount = col * matrix.Rows + row;
            this.Font = new System.Drawing.Font("Microsoft Sans Serif", 18F);
            this.Size = new System.Drawing.Size(60, 60);
            this.Location = new System.Drawing.Point(60 + row * this.Width, 60 + col * this.Height);
            this.Name = "Element" + Convert.ToString(col) + Convert.ToString(row) + "TextBoxFirst";
            this.Text = Convert.ToString(matrix.GetValue(row, col));
            this.TextAlign = HorizontalAlignment.Center;
            this.TabIndex = ElementCount;
        }

        public Element(Matrix matrix, int row, int col, bool isSecond): this(matrix, row, col)
        {
            this.Location = new System.Drawing.Point(350 + row * this.Width, 60 + col * this.Height);
            this.Name = "Element" + Convert.ToString(col) + Convert.ToString(row) + "TextBoxSecond";
        }
    }
}
