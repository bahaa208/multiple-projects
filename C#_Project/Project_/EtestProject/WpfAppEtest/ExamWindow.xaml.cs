using EtestProject.Models;
using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Http.Headers;
using System.Net.Http;
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
    /// Interaction logic for ExamWindow.xaml
    /// </summary>
    /// 
    /*
     * 
     * this window is display the exam 
     * we start from the first question and can go next and prev 
     * button to finsh the exam 
     * after finish the exam the grade and the false question are saved in teh data base including the name of teh exam id name student ...
     * */
    public partial class ExamWindow : Window
    {
        private Test theTest;
        private string nameStudent;
        private string IdStudent;
        private HttpClient client;

        private int numberOfQuestion;

        private int currentQuestionIndex;

        private List<int> _listIndex;



        public ExamWindow(string name,string id,string nameExam)
        {
            // conection to the server for checking 
            currentQuestionIndex = 0;
            this.nameStudent = name;
            this.IdStudent = id;
            client = new HttpClient();
            client.BaseAddress = new Uri("https://localhost:7218/"); // Replace with your API base URL
            client.DefaultRequestHeaders.Accept.Clear();
            client.DefaultRequestHeaders.Accept.Add(new MediaTypeWithQualityHeaderValue("application/json"));
            //get the test from server;
            var response1 = client.GetAsync($"api/Tests/{nameExam}").Result;
            if (!response1.IsSuccessStatusCode)
            {
                // Handle error
                 
                return;

            }






            //-------------------------------------------------------------------------
            var responseContent = response1.Content.ReadAsStringAsync().Result;
             this.theTest = JsonConvert.DeserializeObject<Test>(responseContent);
            if (theTest == null)
            {
                this.Close();
            }

            this.numberOfQuestion = theTest.numberQ();
            /*
             * check if  the exam is random question 
             * we build a list that work like hash table to make the question randomly display
             * */
            if (theTest.Random)
            {
                _listIndex = getListIndex(1);
            }
            else
            {
                _listIndex = getListIndex(0);
            }

            
            InitializeComponent();
            // to save the choosing section after preesing in it
            Sections.SelectionChanged += Sections_SelectedIndexChanged;
            showQuestion();
        }


        // put the answer in the exam 
        private void Sections_SelectedIndexChanged(object sender, EventArgs e)
        {
            // Check if an item is selected
            if (Sections.SelectedIndex != -1)
            {
                int answerIndex = Sections.SelectedIndex;
                theTest.putAnswer(getIndexOfQuestion(), answerIndex);
                NumberOfQuestionAnswered.Text = "" + theTest.answered();
                Question currentQuestion = theTest.GetQuestion(getIndexOfQuestion());

                Sections.SelectedIndex = currentQuestion.studentChoose;

                // Call your function with the selected item as a parameter

            }
        }

        // the index of the question
        public int getIndexOfQuestion()
        {
            return _listIndex.IndexOf(currentQuestionIndex);
        }
        public List<int> getListIndex(int i)
        {// return list of 0-number question and change the place randomly if the exam is random
            List<int> myList = new List<int>();
            for (int j = 0; j < numberOfQuestion; j++)
            {
                myList.Add(j);
            }


            if (i == 0)
            {
                return myList;
            }
            else
            {
                
                Random rng = new Random();

                int n = myList.Count;
                while (n > 1)
                {
                    n--;
                    int k = rng.Next(n + 1);
                    int value = myList[k];
                    myList[k] = myList[n];
                    myList[n] = value;
                }
                return myList;

            }
        }

         public void showQuestion()
         {// to display the question 
            Question currentQuestion = theTest.GetQuestion(getIndexOfQuestion());
            NumberOfQuestionAnswered.Text =""+ theTest.answered();
            QuestionLabel.Text = currentQuestionIndex+1 +
                " ) " +
                currentQuestion.questionText;
            Sections.SelectionChanged -= Sections_SelectedIndexChanged;

            Sections.Items.Clear();

            Sections.SelectionChanged += Sections_SelectedIndexChanged;

            var lis = currentQuestion.getAllSection();
            for (int j = 0; j < lis.Count; j++)
            {
                Sections.Items.Add(lis[j]);
            }
            Sections.SelectedIndex = currentQuestion.studentChoose;

        }

        // to move to the next question
        private void Button_Click_next(object sender, RoutedEventArgs e)
        {
            if(currentQuestionIndex < numberOfQuestion - 1)
            {
                currentQuestionIndex++;
                showQuestion();

            }

        }

        // to move to the prev question
        private void Button_Click_prev(object sender, RoutedEventArgs e)
        {
            if (currentQuestionIndex > 0)
            {
                currentQuestionIndex--;
                showQuestion();
            }
        }

        // to finish the exam and save all in the data base
        private void Button_Click_Finish(object sender, RoutedEventArgs e)
        {





            double grade = theTest.grade();
            string idTest = theTest._id;

            Grade _grade = new Grade();

            _grade.gradeStudent = (int)grade;
            _grade.NameStudent = nameStudent;
            _grade.IdTest = idTest;
            _grade.IdStudent = IdStudent;

            List<Errors> list = new List<Errors>();
            for (int i = 0; i < theTest.AllQuestionInTest.Count; i++)
            {
                Question key = theTest.AllQuestionInTest[i];
                int value = theTest.AllQuestionInTest[i].studentChoose;
                if (!key.CheckAnswer(value))
                {
                    Errors error = new Errors();
                    error.QuestionName = key.questionText;
                    error.ErrorAnswer = key.getChooseAnswerString();
                    error.TrueAnswer = key.getCorrectAnswerString();
                    list.Add(error);

                     

                }
            }

            _grade.listOfErrors = list;

            // add the grade to data base
            var json1 = JsonConvert.SerializeObject(_grade);
            var content1 = new StringContent(json1, Encoding.UTF8, "application/json");
            var response1 = client.PostAsync($"api/Grades", content1);

            this.Close();
            // close the window
        }

        
    }
}
