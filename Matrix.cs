using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MatrixGUI
{
    internal class Matrix //реализована только прямоугольная матрица
    {
        private int[][] matrix;

        private int rows;
        private int columns;

        public int Columns { get => columns; }
        public int Rows { get => rows; }
        private void initMatrix()
        {
            matrix = new int[Columns][];
            for (int i = 0; i < Columns; i++)
            {
                matrix[i] = new int[Rows];
            }
        }

        public Matrix(int rows = 0, int columns = 0)
        {
            this.columns = columns;
            this.rows = rows;
            this.initMatrix();
        }
        public Matrix(int[][] _matrix)
        {
            this.columns = _matrix.Length;
            this.rows = _matrix[0].Length;
            matrix = _matrix;
        }

        public void SetValue(int row, int column, int value)
        {
            matrix[column][row] = value;
        }
        public int GetValue(int row, int column)
        {
            if (row < 0 || column < 0 || row >= Rows || column >= Columns)
            {
                throw new MatrixException("Error: indexes of value are out of range");
            }
            return matrix[column][row];
        }
        public void fillWithRandom(int minValue, int maxValue, Random r)
        {
            //Random r = new Random();
            for (int i = 0; i < Columns; i++)
            {
                for (int j = 0; j < Rows; j++)
                {
                    matrix[i][j] = r.Next(minValue, maxValue);
                }
            }
        }

        public static Matrix matrixSum(Matrix matr1, Matrix matr2)
        {
            if (matr1 == null || matr2 == null)
            {
                throw new MatrixException("Error: The one of the matrixes or both of them aren't initialized!");
            }
            if (matr1.Rows != matr2.Rows || matr1.Columns != matr2.Columns)
            {
                throw new MatrixException("Error: Matrixes doesn't have the same same length!");
            }
            Matrix res = new Matrix(matr1.Rows, matr1.Columns);
            for (int i = 0; i < matr1.Columns; i++)
            {
                for (int j = 0; j < matr1.Rows; j++)
                {
                    res.SetValue(i, j, matr1.GetValue(i, j) + matr2.GetValue(i, j));
                }
            }
            return res;
        }
        public static Matrix matrixSubtraction(Matrix matr1, Matrix matr2)
        {
            if (matr1 == null || matr2 == null)
            {
                throw new MatrixException("Error: The one of the matrixes or both of them aren't initialized!");
            }
            if (matr1.Rows != matr2.Rows || matr1.Columns != matr2.Columns)
            {
                throw new MatrixException("Error: Matrixes doesn't have the same same length!");
            }
            Matrix res = new Matrix(matr1.Rows, matr1.Columns);
            for (int i = 0; i < matr1.Columns; i++)
            {
                for (int j = 0; j < matr1.Rows; j++)
                {
                    res.SetValue(i, j, matr1.GetValue(i, j) - matr2.GetValue(i, j));
                }
            }
            return res;
        }

        public override string ToString()
        {
            string res = "";
            if (matrix == null)
            {
                throw new MatrixException("Error: matrix isn't initialized!");
            }
            if (Rows == 0 || Columns == 0)
            {
                throw new MatrixException("Error: matrix doesn't contain anything!");
            }
            for (int i = 0; i < Rows; i++)
            {
                for (int j = 0; j < Columns; j++)
                {
                    res+=$"{matrix[i][j]} ";
                }
                res+="\n";
            }
            return res;
        }
    }
    class MatrixException : ApplicationException
    {
        public MatrixException(string message) : base(message) { }
    }
}
