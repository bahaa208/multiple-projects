using EtestProject.Models;
using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Http;
using System.Net.Http.Headers;
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
    /// Interaction logic for StudentWindow.xaml
    /// </summary>
    /// 

    /*
     * this window for making exam <start the exam>
     * press the name 
     * every thing is ok start to indefication
     * 
     * */
    public partial class StudentWindow : Window
    {
        private HttpClient client;

        public StudentWindow()
        {
            // to get the exam from the server
            client = new HttpClient();
            client.BaseAddress = new Uri("https://localhost:7218/"); // Replace with your API base URL
            client.DefaultRequestHeaders.Accept.Clear();
            client.DefaultRequestHeaders.Accept.Add(new MediaTypeWithQualityHeaderValue("application/json"));
            InitializeComponent();
        }

        /* this button for checking the exam name and date if evrey rhing is ok and the exam was found 
         * check the time if the diffrent between the  time now and exam time is at least 10 min before or max 5 min after 
         * the exam open else got error massege
         * */
        private void Button_Click(object sender, RoutedEventArgs e)
        {
            string _nameExam = nameExam.Text;
            bool youCanGet = false;

            //get the test from server;
            var response1 = client.GetAsync($"api/Tests/{_nameExam}").Result;
            if (!response1.IsSuccessStatusCode)
            {
                // Handle error
                erorrExamTime.Text = "Exam Not found ! " +
                    "No Exam with this Name .";
                return;

            }
             
            var responseContent = response1.Content.ReadAsStringAsync().Result;
            Test theTest = JsonConvert.DeserializeObject<Test>(responseContent);
            DateTime dateExam = theTest.Date;
            /*WindowIdetails win = new WindowIdetails(_nameExam);
            win.Show();
            return;*/
            if (DateTime.Now < dateExam)
            {// check the diffrent before the exame
                if (still10Minutes(dateExam))
                {
                    youCanGet = true;

                }
                else
                {
                    TimeSpan diff = dateExam.Subtract(DateTime.Now);
                    erorrExamTime.Text = "only if still 10 min you can git in ." +
                        "wait "+ Math.Abs(diff.Minutes).ToString() + " minutes .";
                    

                }

            }
            else
            {// check the diffrent after the exame
                if (after5Minutes(dateExam))
                {
                    youCanGet = true;

                }
                else
                {
                    TimeSpan diff = dateExam.Subtract(DateTime.Now);
                    erorrExamTime.Text = "you Missed the Exam ." +
                        "\nlate time " + Math.Abs(diff.Minutes).ToString() + " minutes .";


                }
            }
            if (youCanGet)
            {// you can start

                WindowIdetails win1 = new WindowIdetails(_nameExam);
                win1.Show();

            }
            else
            {
                return;
            }
        }


        //  function check time before
        public bool still10Minutes(DateTime t)
        {
            DateTime now = DateTime.Now;
            if (t > now)
            {
                TimeSpan diff = t.Subtract(now);
                return (diff.TotalMinutes <= 10);
            }
            else
            {
                return false;
            }
        }
        // function check after
        public bool after5Minutes(DateTime t)
        {
            DateTime now = DateTime.Now;
            if (t < now)
            {
                TimeSpan diff = t.Subtract(now);
             
                return (Math.Abs(diff.TotalMinutes) <= 5);
            }
            else
            {
                return false;
            }
        }

         
    }
}
