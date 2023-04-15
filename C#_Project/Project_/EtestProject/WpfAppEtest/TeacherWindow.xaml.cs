using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using EtestProject.Models;
using System.Net.Http;
using System.Net.Http.Headers;
using System.IO;
using Path = System.IO.Path;
using File = System.IO.File;

using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using Xceed.Wpf.Toolkit.Primitives;

namespace WpfAppEtest
{
    /// <summary>
    /// Interaction logic for TeacherWindow.xaml
    /// </summary>
    /// 


    /*
     * THIS IS TEACHER WINDOW 
     * her the techer can add exam or edite ,remove ,add question...
     * and check the grade of the student by read from the data base
     * after adding exam the exam is exist in json file not in the data base 
     * should press load to data base to edite and add question and,,.
     * 
     * */
    public partial class TeacherWindow : Window
    {
        private List<Test> tests;
        private HttpClient client;
        public TeacherWindow()
        {
            // using list of tist to save after edite an data base to make the operation more fast
            tests = new List<Test>();
            //client var to make conection to the server 
            client = new HttpClient();
            client.BaseAddress = new Uri("https://localhost:7218/"); // Replace with your API base URL
            client.DefaultRequestHeaders.Accept.Clear();
            client.DefaultRequestHeaders.Accept.Add(new MediaTypeWithQualityHeaderValue("application/json"));
            


            InitializeComponent();

        }
        // search for the exam by name 
        private void OnSearchBoxTextChanged(object sender, TextChangedEventArgs e)
        {
            string filter = "";
            filter = SearchBox.Text;
            try
            {
                MyListBox.Items.Clear();

            }
            catch { }


            var response = client.GetAsync($"api/Tests").Result;

            if (!response.IsSuccessStatusCode)
            {
                // Handle error
                Console.WriteLine($"Error retrieving test from server: {response.StatusCode}");
                 
            }
            try
            {
                var responseContent = response.Content.ReadAsStringAsync().Result;
                List<Test> test = JsonConvert.DeserializeObject<List<Test>>(responseContent);
                tests = test;

                for (int i = 0; i < tests.Count; i++)
                    
                {
                    // if we press all  we well  see al the exams in the data base
                    if (filter == "all")
                    {
                        var name = tests[i].getName();
                        MyListBox.Items.Add(name);

                    }

                    if (filter != "" && tests[i].getName().StartsWith(filter)   )
                    {
                        var name = tests[i].getName();
                        MyListBox.Items.Add(name);
                    }
                }

            }
            catch { }
            
            



        }


        // this function to put the exam in the screen question, section ..
        private void Edit(object sender, RoutedEventArgs e)
        {
            if (MyListBox.SelectedItem != null)
            {
                var name = MyListBox.SelectedItem.ToString();
                for (int i = 0; i < tests.Count; i++)
                {
                    if (tests[i].getName() == name)
                    {
                        screen.Text = tests[i].ToString();
                        return;
                    }
                }
                screen.Text = "";
            }

        }
        // to read and put the section info list 
        public List<Answer> getNewStringSection()
        {
            List<Answer> sections = new List<Answer>();
            for (int i = 0; i < MyListSection.Items.Count; i++)
            {
                sections.Add(new Answer(MyListSection.Items[i].ToString()));
            }
            return sections;
        }

        // make update for the question
        private void UpdateQ(object sender, RoutedEventArgs e)
        {

            

                // if no section are selected that mean maybe we have to add section or update the text or true section index
                if (MyListBox.SelectedItem != null)
                {
                if (MyListSection.SelectedIndex >= 0)
                    
                {
                    var sected_inde = MyListSection.SelectedIndex;
                    // if the are selected item and no section in the section box that mean delete sectino
                    if (newSection.Text == "")
                    {
                        MyListSection.Items.RemoveAt(MyListSection.SelectedIndex);





                    }
                    else
                    {
                        MyListSection.Items[MyListSection.SelectedIndex] = newSection.Text;

                    }
                    var name = MyListBox.SelectedItem.ToString();
                    for (int i = 0; i < tests.Count; i++)
                    {
                        if (tests[i].getName() == name)
                        {
                            try
                            {
                                int index = int.Parse(numberQuestion.Text);
                                string Ques = HeadOfQuestion.Text;
                                var lis = getNewStringSection();
                                int tr = int.Parse(trueSection.Text);
                                // should update this to real
                                string url = "null";
                                // somthing errro
                                if (index < 1 || index > tests[i].numberQ() || tr+1 < 1 )
                                {
                                    TextBlock.Text = "out of range Error .*";
                                    return;
                                }
                                var qu = tests[i].GetQuestion(index-1);
                                if (tr > qu.numberSec())
                                {
                                    TextBlock.Text = "out of range Error ";
                                    return;
                                }
                                TextBlock.Text = "";
                                tests[i].changeQuestion(index - 1, Ques, lis, tr - 1, url);
                                


                                if (newSection.Text == "")
                                {

                                    // we have to delete the section



                                    //get test from server
                                    var response1 = client.GetAsync($"api/Tests/{tests[i].Name}").Result;

                                    if (!response1.IsSuccessStatusCode)
                                    {
                                        // Handle error
                                        Console.WriteLine($"Error retrieving test from server: {response1.StatusCode}");

                                    }
                                    ///update out Tests
                                    var responseContent = response1.Content.ReadAsStringAsync().Result;
                                    Test theTest = JsonConvert.DeserializeObject<Test>(responseContent);
                                     






                                    var qu2 = theTest.GetQuestion(index - 1);
                                    var ansswer = qu2.getAllSection()[sected_inde];
                                     
                                    
                                    // we delete the section
                                    var response2 = client.DeleteAsync($"api/Answers/{ansswer.Id}");
                                    var z = qu2.getAllSection();
                                    z.RemoveAt(sected_inde);
                                    tests[i].changeQuestion(index - 1, qu2.questionText,z , qu2.correctAnswer);

                                }
                                else
                                {

                                    //get the test from server;
                                    var response1 = client.GetAsync($"api/Tests/{tests[i].getName()}").Result;

                                    if (!response1.IsSuccessStatusCode)
                                    {
                                        // Handle error
                                        Console.WriteLine($"Error retrieving test from server: {response1.StatusCode}");

                                    }
                                    ///update out Tests
                                    var responseContent = response1.Content.ReadAsStringAsync().Result;
                                    Test theTest = JsonConvert.DeserializeObject<Test>(responseContent);


 
                                    // here we have to update the section 
                                    var qu2 = theTest.GetQuestion(index - 1);
                                    var ansswer = qu2.getAllSection()[sected_inde];
                                    ansswer.Text = newSection.Text;
                                    TextBlock.Text = "D" + ansswer.Id + ansswer.Text;
                                    var json1 = JsonConvert.SerializeObject(ansswer);
                                    var content1 = new StringContent(json1, Encoding.UTF8, "application/json");
                                    var response11 = client.PutAsync($"api/Answers/{ansswer.Id}", content1);
                                    TextBlock.Text = "changed section ";

                                }

                              
                                var json = JsonConvert.SerializeObject(tests[i]);
                                var content = new StringContent(json, Encoding.UTF8, "application/json");
                                var response = client.PutAsync($"api/Tests/{tests[i].Id}", content);

                                newSection.Text = "";



                            }
                            catch { }

                        }
                    }

                }
                else
                {
                    
                    var name = MyListBox.SelectedItem.ToString();
                    for (int i = 0; i < tests.Count; i++)
                    {
                        if (tests[i].getName() == name)
                        {
                            try
                            {
                                int index = int.Parse(numberQuestion.Text);
                                string Ques = HeadOfQuestion.Text;
                                if (!(newSection.Text == "new" || newSection.Text == ""))
                                {
                                    MyListSection.Items.Add(newSection.Text);




                                    //// to add section
                                    var answer = new Answer(newSection.Text, 0);
                                    answer.QuestionId = tests[i].GetQuestion(index - 1).Id;
                                    var json1 = JsonConvert.SerializeObject(answer);
                                    var content1 = new StringContent(json1, Encoding.UTF8, "application/json");
                                    var response1 = client.PostAsync($"api/Answers", content1);

                                }


                                var lis = tests[i].GetQuestion(index - 1).getAllSection();
                                if (newSection.Text != ""){
                                    lis.Add(new Answer(newSection.Text));
                                }
                                
                                int tr = int.Parse(trueSection.Text);
                                // should update this to real
                                string url = "null";
                                if (index < 1 || index-1 > tests[i].numberQ() || tr+1 < 1)
                                {
                                    TextBlock.Text = "out of range Error ..";
                                    return;
                                }
                                else
                                {
                                    TextBlock.Text = "";
                                }

                                
                                 
                                tests[i].changeQuestion(index - 1, Ques, lis, tr - 1, url);
                                TextBlock.Text = "==>" + tests[i].GetQuestion(index-1).getAllSection().Count;
                                newSection.Text = "";

                                var ques11 = tests[i].GetQuestion(index - 1);


                                //update Question
                                var json = JsonConvert.SerializeObject(ques11);
                                var content = new StringContent(json, Encoding.UTF8, "application/json");
                                var response = client.PutAsync($"api/Questions/{ques11.Id}", content);

                            }
                            catch { }

                        }
                    }
                }

            }
            Edit(sender, e);


             



        }




         



        // when we put the number of the question should get all the information of the ques
        private void select_number_ofQ(object sender, TextChangedEventArgs e)
        {
            TextBlock.Text = "";
          
            string filter = ""+ MyListBox.SelectedItem.ToString();


            if (numberQuestion.Text == "")
            {
                HeadOfQuestion.Text = "";
                trueSection.Text = "";
                MyListSection.Items.Clear();
                return;

            }

            for (int i = 0; i < tests.Count; i++)
            {

                if (tests[i].getName()==filter && filter != "")
                {// find and show the question in the screen
                    try
                    {
                        int num = int.Parse(numberQuestion.Text) - 1;
                        Question q = tests[i].GetQuestion(num);

                        if (q != null)
                        {
                            MyListSection.Items.Clear();
                            var lis = q.getAllSection();
                            for (int j = 0; j < lis.Count; j++)
                            {
                                MyListSection.Items.Add(lis[j]);
                            }
                            HeadOfQuestion.Text = q.GetQuestionText();
                            trueSection.Text = "" + (1 + q.getCorrect());

                        }
                         
                    }
                    catch { }


                }
            }
        }
        // when we choose section should apear in the new section box
        private void MyListSection_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            if (MyListSection.SelectedItem != null)
            {
                var s = MyListSection.SelectedItem.ToString();

                newSection.Text = s;
            }



        }

        // to add new question

        private void ButtonAddQusetion(object sender, RoutedEventArgs e)
        {
            if (MyListBox.SelectedItem != null)
            {
                 
                     
                    var name = MyListBox.SelectedItem.ToString();
                    for (int i = 0; i < tests.Count; i++)
                    {
                        if (tests[i].getName() == name)
                        {
                            try
                            {
                                  
                                TextBlock.Text = "";
                                var ind = tests[i].numberQ();
                                tests[i].AddQ("new question", new List<string>(),0);
                                screen.Text = tests[i].ToString();
                                Question q = tests[i].GetQuestion(ind);
                                q.TestId = tests[i].Id;
                                MyListSection.Items.Clear();
                                var lis = q.getAllSection();
                                for (int j = 0; j < lis.Count; j++)
                                {
                                    MyListSection.Items.Add(lis[j]);
                                }
                                HeadOfQuestion.Text = q.GetQuestionText();
                                
                                numberQuestion.Text =""+ (ind+1);
                                trueSection.Text = "1";

                                
                                //// to add new Question to the data base
                                 
                                var json1 = JsonConvert.SerializeObject(q);
                                var content1 = new StringContent(json1, Encoding.UTF8, "application/json");
                                var response1 = client.PostAsync($"api/Questions", content1);
                                


                                var response = client.GetAsync($"api/Tests").Result;

                                if (!response.IsSuccessStatusCode)
                                {
                                    // Handle error
                                    Console.WriteLine($"Error retrieving test from server: {response.StatusCode}");

                                } 
                                ///update out Tests
                                var responseContent = response.Content.ReadAsStringAsync().Result;
                                List<Test> test = JsonConvert.DeserializeObject<List<Test>>(responseContent);
                                tests[i] = test[i];

                        }
                            catch { }

                        }
                    }

                
                 
            }
        }

        
        // to add new exam to the json file 
        private void Button_AddExam(object sender, RoutedEventArgs e)
        {
            BuildExamWindow win2 = new BuildExamWindow(tests);
            win2.ShowDialog();
            var date = win2.SelectedDateTime;
            if (date > DateTime.Now)
            {
                screen.Text = " " + win2.getNameExam();
                //List<string> ls2 = new List<string>();
                var a = new Test(win2.getNameExam(), win2.id_Exam, win2.SelectedDateTime, win2.name_Teacher, win2.time_Exam, win2.is_random);




                string destinationFile = "Json-File/dataJson.json";
                destinationFile = Path.GetFullPath(destinationFile);

                if (!File.Exists(destinationFile))
                {
                    // Create the directory if it doesn't exist
                    Directory.CreateDirectory(Path.GetDirectoryName(destinationFile));

                    // Create the file
                    using (File.Create(destinationFile)) { }
                }
                //Open the File

                string json = File.ReadAllText(destinationFile);

                // Deserialize the JSON string into a List<Test> object
                List<Test> testsData = JsonConvert.DeserializeObject<List<Test>>(json);
                if(testsData == null)
                {
                    testsData = new List<Test>();
                }
                testsData.Add(a);
                string json2 = JsonConvert.SerializeObject(testsData);
                File.WriteAllText(destinationFile, json2);

                screen.Text = "                                                                       " +
                              "                                                                       " +
                              "                   Add Successfully To JsonFile.json                   " +
                              "                   press loadData to save in Database.                 ";


                
            }

            
        }

        private void HeadOfQuestion_TextChanged(object sender, TextChangedEventArgs e)
        {

        }

        
        // delete the exam from data base and the json file if the exam exist 
        private void Button_Click_delete_exam(object sender, RoutedEventArgs e)
        {
            if (MyListBox.SelectedItem != null)
            {
                var nameToDelete = MyListBox.SelectedItem.ToString();
                int idToDelete = -1;
                Test tdelet = null;
                for (int i = 0; i < tests.Count; i++)
                {
                    if (tests[i].getName() == nameToDelete)
                    {
                        idToDelete = tests[i].Id;
                        tdelet = tests[i];
                    }
                }
                if(idToDelete != -1)
                {
                    // we delete the Exam
                    var response2 = client.DeleteAsync($"api/Tests/{idToDelete}");
                    screen.Text = "";
                    SearchBox.Text = "";
                    
                    MyListBox.Items.Clear();
                    HeadOfQuestion.Text = "";
                    trueSection.Text = "";
                    MyListSection.Items.Clear();






                    string destinationFile = "Json-File/dataJson.json";
                    destinationFile = Path.GetFullPath(destinationFile);

                    if (!File.Exists(destinationFile))
                    {
                        // Create the directory if it doesn't exist
                        Directory.CreateDirectory(Path.GetDirectoryName(destinationFile));

                        // Create the file
                        using (File.Create(destinationFile)) { }
                    }
                    //Open the File

                    string json = File.ReadAllText(destinationFile);

                    // Deserialize the JSON string into a List<Test> object
                    List<Test> testsData = JsonConvert.DeserializeObject<List<Test>>(json);
                    if (tdelet != null)
                    {
                        int count = -1;
                        int deleteIndex = -1;
                        foreach (var test in testsData)
                        {
                            count++;
                            if (test.Name == tdelet.Name) { deleteIndex = count; }


                        }
                        if (deleteIndex != -1)
                        {
                            testsData.RemoveAt(deleteIndex);
                            screen.Text = "                                      " +
                                          "                                      " +
                                          "                                Deleted Successfully          ";
                        }
                        string json2 = JsonConvert.SerializeObject(testsData);
                        File.WriteAllText(destinationFile, json2);
                    }

                    





                }
                

            }

        }

         

         
        // load the exam info the data base using server 
        private void Button_Click_LoadData(object sender, RoutedEventArgs e)
        { 


            string destinationFile = "Json-File/dataJson.json";
            destinationFile = Path.GetFullPath(destinationFile);


            try
            {
                if (!File.Exists(destinationFile))
                {
                    // Create the directory if it doesn't exist
                    Directory.CreateDirectory(Path.GetDirectoryName(destinationFile));

                    // Create the file
                    using (File.Create(destinationFile)) { }
                }
                //Open the File

                string json = File.ReadAllText(destinationFile);

                // Deserialize the JSON string into a List<Test> object
                List<Test> testsData = JsonConvert.DeserializeObject<List<Test>>(json);
                foreach (var test in testsData)
                {

                    var response1 = client.GetAsync($"api/Tests/{test.Name}").Result;

                    if (!response1.IsSuccessStatusCode)
                    {
                         //success
                        test.Id = 0;
                        var json1 = JsonConvert.SerializeObject(test);
                        var content1 = new StringContent(json1, Encoding.UTF8, "application/json");
                        var response2 = client.PostAsync($"api/Tests", content1);
                        screen.Text = "                             " +
                            "                                        " +
                            "                    Loaded Successfully       ";


                    }
                     

                }
            }
            catch (Exception ee)
            {
                Console.WriteLine("Exception: " + ee.Message);
            }
            finally
            {
                Console.WriteLine("Executing finally block.");
            }
            

        }


     
    // to show the exam grade after the student solve it read from the server and show
    private void Button_Click_ShowGrade(object sender, RoutedEventArgs e)
        {
            string nameofExam = "";
            string idOfTest = "";
            if (MyListBox.SelectedItem != null)
            {
                nameofExam = MyListBox.SelectedItem.ToString();

                //get the test from server;
                var response1 = client.GetAsync($"api/Tests/{nameofExam}").Result;

                if (!response1.IsSuccessStatusCode)
                {
                    // Handle error
                    Console.WriteLine($"Error retrieving test from server: {response1.StatusCode}");

                }
                ///update out Tests
                var responseContent = response1.Content.ReadAsStringAsync().Result;
                Test theTest = JsonConvert.DeserializeObject<Test>(responseContent);
                idOfTest = theTest._id;


            }
            else { return; }
            var response = client.GetAsync($"api/Grades").Result;

            if (!response.IsSuccessStatusCode)
            {
                // Handle error
                Console.WriteLine($"Error retrieving test from server: {response.StatusCode}");

            }
            try
            {
                var responseContent = response.Content.ReadAsStringAsync().Result;
                List<Grade> AllGrade = JsonConvert.DeserializeObject<List<Grade>>(responseContent);
                List<Grade> toShow = new List<Grade>();
                List<double> gradedouble = new List<double>();
                for (int i = 0; i < AllGrade.Count; i++)
                {
                    if (AllGrade[i].IdTest == idOfTest)
                    {
                        toShow.Add(AllGrade[i]);
                        gradedouble.Add(AllGrade[i].gradeStudent);
                    }
                    
                }
                screen.Text = "";
                for (int j = 0; j < toShow.Count; j++)
                {
                    screen.Text+=toShow[j].ToString();
                }
                // display the average of all student grade
                double average = gradedouble.Average();
                screen.Text += "\n" + "Average Grade: " + average.ToString("0.00");
            }
            catch {
                screen.Text += "\n" + "      No grade for this exam .";
            }
            

        }

        // to delete question 
        private void DeleteQuestion(object sender, RoutedEventArgs e)
        {



            var name = MyListBox.SelectedItem.ToString();
            for (int i = 0; i < tests.Count; i++)
            {
                if (tests[i].getName() == name)
                {
                    try
                    {
                        int _index = int.Parse(numberQuestion.Text);


                        var ques11 = tests[i].GetQuestion(_index - 1);


                        //delete Question
                        var response2 = client.DeleteAsync($"api/Questions/{ques11.Id}");


                        tests[i].AllQuestionInTest.RemoveAt(_index - 1);
                        screen.Text = tests[i].ToString();
                    }
                    catch { }

                }
            }

            try
            {
                int index = int.Parse(numberQuestion.Text);
                if (index > 1)
                {
                    numberQuestion.Text = (index - 1) + "";
                }
                else
                {
                    numberQuestion.Text = "";
                }
            }
            catch
            {
                screen.Text = "select index for Question .";
            }
        }
    }
}
