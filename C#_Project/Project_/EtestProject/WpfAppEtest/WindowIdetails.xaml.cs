using System;
using System.Collections.Generic;
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
using System.Windows.Shapes;

namespace WpfAppEtest
{
    /// <summary>
    /// Interaction logic for WindowIdetails.xaml
    /// </summary>
    /// 
    /*
     * this window to take the detailes about the stuednt 
     * and start the exam 
     * should put the name of the student and the id
     * */
    public partial class WindowIdetails : Window
    {
        private string nameExam;
        public WindowIdetails(string nameExam)
        {
            this.nameExam = nameExam;
            InitializeComponent();
        }

        private void nameExam_Copy_TextChanged(object sender, TextChangedEventArgs e)
        {

        }

       
        // start if the name and the id are not empty
        private void Button_Click_Exam_start(object sender, RoutedEventArgs e)
        {
            
            if (NameStudent.Text!="" && IdStudent.Text != "")
            {
                ExamWindow win2 = new ExamWindow(NameStudent.Text, IdStudent.Text,this.nameExam);
                win2.Show();
                this.Close();
            }
            else
            {
                erorrExamDetal.Text = "Inputs can not be Empty.";
            }
            
        }
    }
}
