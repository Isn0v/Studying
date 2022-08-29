using Microsoft.Win32;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace TextEditor
{
    /// <summary>
    /// Логика взаимодействия для MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
            cmbFontFamily.ItemsSource = Fonts.SystemFontFamilies.OrderBy(f => f.Source);
            cmbFontSize.ItemsSource = new List<double>() { 8, 9, 10, 11, 12, 14, 16, 18, 20, 22, 24, 26, 28, 36, 48, 72 };
        }

        private void Open_Executed(object sender, ExecutedRoutedEventArgs e)
        {
            OpenFileDialog dlg = new OpenFileDialog();
            dlg.Filter = "Rich Text Format (*.rtf)|*.rtf|All files (*.*)|*.*";
            if (dlg.ShowDialog() == true)
            {
                using (FileStream fileStream = new FileStream(dlg.FileName, FileMode.Open))
                {
                    TextRange range = new TextRange(rbtEditor.Document.ContentStart, rbtEditor.Document.ContentEnd);
                    range.Load(fileStream, DataFormats.Rtf);
                }
            }
        }

        private void Save_Executed(object sender, ExecutedRoutedEventArgs e)
        {
            SaveFileDialog dlg = new SaveFileDialog();
            dlg.Filter = "Rich Text Format (*.rtf)|*.rtf|All files (*.*)|*.*";
            if (dlg.ShowDialog() == true)
            {
                using (FileStream fileStream = new FileStream(dlg.FileName, FileMode.Create))
                {
                    TextRange range = new TextRange(rbtEditor.Document.ContentStart, rbtEditor.Document.ContentEnd);
                    range.Save(fileStream, DataFormats.Rtf);
                }
            }
        }

        private void rbtEditor_SelectionChanged(object sender, RoutedEventArgs e)
        {
            object tmp = rbtEditor.Selection.GetPropertyValue(FontWeightProperty);
            btnBold.IsChecked = tmp != DependencyProperty.UnsetValue && tmp.Equals(FontWeights.Bold);

            tmp = rbtEditor.Selection.GetPropertyValue(FontStyleProperty);
            btnItalic.IsChecked = tmp != DependencyProperty.UnsetValue && tmp.Equals(FontStyles.Italic);

            tmp = rbtEditor.Selection.GetPropertyValue(Inline.TextDecorationsProperty);
            btnItalic.IsChecked = tmp != DependencyProperty.UnsetValue && tmp.Equals(TextDecorations.Underline);

            tmp = rbtEditor.Selection.GetPropertyValue(FontFamilyProperty);
            cmbFontFamily.SelectedItem = tmp;

            tmp = rbtEditor.Selection.GetPropertyValue(Inline.FontSizeProperty);
            cmbFontSize.Text = tmp.ToString();
        }

        private void cmbFontSize_TextChanged(object sender, TextChangedEventArgs e)
        {
            rbtEditor.Selection.ApplyPropertyValue(FontSizeProperty, cmbFontSize.Text);
        }

        private void cmbFontFamily_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            if(cmbFontFamily.SelectedItem != null)
            {
                rbtEditor.Selection.ApplyPropertyValue(FontFamilyProperty, cmbFontFamily.SelectedItem);
            }
        }

        private void Window_Closing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            SaveFileDialog dlg = new SaveFileDialog();
            dlg.Filter = "Rich Text Format (*.rtf)|*.rtf|All files (*.*)|*.*";
            if (dlg.ShowDialog() == true)
            {
                using (FileStream fileStream = new FileStream(dlg.FileName, FileMode.Create))
                {
                    TextRange range = new TextRange(rbtEditor.Document.ContentStart, rbtEditor.Document.ContentEnd);
                    range.Save(fileStream, DataFormats.Rtf);
                }
            }
        }
    }
}
