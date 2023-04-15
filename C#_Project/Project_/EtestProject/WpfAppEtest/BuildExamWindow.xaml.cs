using EtestProject.Models;
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
using System.Xml.Linq;

namespace WpfAppEtest
{
    /// <summary>
    /// Interaction logic for BuildExamWindow.xaml
    /// </summary>
    /// 
    /*
     * this window for adding new empty exam 
     * press the date time name id period ..
     * check if the is onther exam in the same date 
     * or
     * the date in weekend
     * or the date is in the past 
     * if there is some of them we got error massege
     * 
     * */
    public partial class BuildExamWindow : Window
    {
        private List<Test> tests;
        public BuildExamWindow(List<Test> tests)
        {
            this.tests = tests;
            InitializeComponent();
        }
        public DateTime SelectedDateTime;
        private string name_Exam;
        public string id_Exam;
        public string name_Teacher;
        public bool is_random;
        public int time_Exam;

        public string getNameExam()
        {
            return name_Exam;
        }
        //check if there is confilct by date
        public bool conflictByDate(DateTime a)
        {
            for (int i = 0; i < tests.Count; i++)
            {
                bool sameDay = a.Year == tests[i].getDate().Year &&
               a.Month == tests[i].getDate().Month &&
               a.Day == tests[i].getDate().Day;
                if (sameDay)
                {
                    return true;
                }
            }
            return false;

        }
        // confli by id
        public bool conflictById(string a)
        {
            for (int i = 0; i < tests.Count; i++)
            {
                
                if (tests[i].getId()==a)
                {
                    return true;
                }
            }
            return false;

        }
        //by name
        public bool conflictByNameExam(string a)
        {
            for (int i = 0; i < tests.Count; i++)
            {
                 
                if (tests[i].getName()==a)
                {
                    return true;
                }
            }
            return false;

        }

        //button to add the exam if there is error we got massege
        private void ScheduleExamButton_Click(object sender, RoutedEventArgs e)
        {
            erorrExam.Text = "";
            // Get the selected date and time from the DatePicker controls
            DateTime examDateTime = examDatePicker.SelectedDate.GetValueOrDefault();
            try
            {
                if(timeString.Text.Contains(":") && timeString.Text.Length == 5)
                {
                    TimeSpan time = TimeSpan.Parse(timeString.Text);

                    examDateTime = examDateTime + time;
                }
                else
                {
                    throw new Exception();
                }
                
                
            }
            catch(Exception ex)
            {
                erorrExam.Text = "Error Exam Hour , change the hour";
                return;
            }
            examDatePicker.SelectedDate=examDateTime;
            DateTime yesterday = DateTime.Today.AddDays(-1);
            // Perform validation to ensure the selected date and time is valid for scheduling an exam
            if (examDateTime < DateTime.Now)
            {
                MessageBox.Show("You cannot schedule an exam for a past date and time.");
                SelectedDateTime = yesterday;
            }
            /*else if (examDateTime.DayOfWeek == DayOfWeek.Saturday )
            {
                MessageBox.Show("Exams cannot be scheduled on weekends.");
                SelectedDateTime = yesterday;
            }*/
            else
            {   //examDateTime
                string nameexam = nameExam.Text;
                string idexam = idExam.Text;
                bool random = (bool)radioRandom.IsChecked;
                string nameteacter = nameTeacher.Text;
                if(conflictByDate(examDateTime))
                {
                    erorrExam.Text = "Error conflict by date change date.";
                    return;
                }
                if (conflictById(idexam) )
                {
                    erorrExam.Text = "Error conflict by id change id of the exam.";
                    return;
                }
                if (conflictByNameExam(nameexam))
                {
                    erorrExam.Text = "Error conflict by name of exam change the name";
                    return;
                }
                 
                 
                int num2;
                bool success = int.TryParse(timeOfExame.Text, out num2); // Using int.TryParse()
                if (!success || num2<1)
                {
                    erorrExam.Text = "Erorr with period of exam change the period";
                    return;
                }
                
                this.name_Exam = nameexam;

                this.id_Exam = idexam;
                this.is_random = random;
                this.name_Teacher = nameteacter;
                this.time_Exam = num2;
                MessageBox.Show("Your exam has been scheduled to " + examDateTime.ToString("g") + "."+ name_Exam);
                this.SelectedDateTime = examDateTime;
                this.Close();




                // Schedule the exam for the selected date and time
                
            }
        }

        private void TextBox_TextChanged(object sender, TextChangedEventArgs e)
        {

        }
    }
}
