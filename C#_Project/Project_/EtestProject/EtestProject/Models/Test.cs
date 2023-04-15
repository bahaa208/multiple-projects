using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.Serialization;

using System.Text.Json.Serialization;

namespace EtestProject.Models
{
    [Serializable]
    public class Test
    {
        public int Id { get; set; }
        public string Name { get; set; }
        public string _id { get; set; }
        public DateTime Date { get; set; }
        public string NameOfTeacher { get; set; }
        public int Time { get; set; }
        public bool Random { get; set; }
        public List<Question> AllQuestionInTest { get; set; }


        /*
         * Test class that performance exam
         * we have neme Id for table in database
         * name of the teacher .........
         * get set..
        }*/
        public Test(string n, string i, DateTime d, string nt, int t, bool ran)
         {
            Name = n;
            _id = i;
            Date = d;
            NameOfTeacher = nt;
            Time = t;
            Random = ran;

            AllQuestionInTest = new List<Question>();
         }
        public Test()
        {
            Name = "";
            _id = "";
            Date = DateTime.Now;
            NameOfTeacher = "";
            Time = 0;
            Random = false;

            AllQuestionInTest = new List<Question>();
        }
        public void CopyTest(Test t)
        {
            Name = t.Name;
            _id = t._id;
            Date = t.Date;
            NameOfTeacher = t.NameOfTeacher;
            Time = t.Time;
            Random = t.Random;
            AllQuestionInTest.Clear();
            AllQuestionInTest = t.AllQuestionInTest;



        }
        public string getName()
        {
            return Name;
        }
        public string getId()
        {
            return _id;
        }
        //head_text is the text in top of Question
        //ls list of the section
        //tr the true section
        //head_imge
        public Question GetQuestion(int index)
        {
            if (index >= 0 && index < AllQuestionInTest.Count)
            {
                Question key = AllQuestionInTest[index];
                return key;
            }
            var q= new Question();
        
            return q;
        }
        public DateTime getDate()
        {
            return Date;
        }
        public int numberQ()
        {
            return AllQuestionInTest.Count;
        }
        public void CleanAllAnswer()
        {
            for(int i = 0; i < AllQuestionInTest.Count; i++)
            {
                for(int j=0;j< AllQuestionInTest[i].listAnswer.Count; j++)
                {
                    AllQuestionInTest[i].listAnswer.RemoveAt(j);
                }
            }
            
        }
        public bool setQuestion(Question q,int index)
        {
            if (index <= AllQuestionInTest.Count)
            {
                Question key = AllQuestionInTest[index];
                changeQuestion(index, q.GetQuestionText(), q.getAllSection(), q.getCorrect(),q.getImage());

                return true;
            }
            return false;
        }
        // to add question
        public void AddQ(string head_text, List<string> ls ,int tr, string head_imge = "null")
        {
            Question q = new Question(head_text, head_imge);
            for (int i = 0; i < ls.Count; i++)
            {
                q.AddSection(ls[i]);
            }
            q.setCorrect(tr);
             
            AllQuestionInTest.Add(q);
        }
        public void AddQuestion(Question q)
        {
             
            AllQuestionInTest.Add(q);
        }
        // to know how much solved
        public string answered()
        {
            int c = 0;
            for (int i = 0; i < AllQuestionInTest.Count; i++)
            {
                Question key = AllQuestionInTest[i];
                int value = AllQuestionInTest[i].studentChoose;
                if (value >= 0)
                {
                    c++;
                }
            }
            string c_string = ""+c;
            string All = AllQuestionInTest.Count.ToString();
            return c_string + " / " + All;

        }
        // put answer in Question
        public void putAnswer(int indexOfQuestion,int index_section)
        {
            if(indexOfQuestion <= AllQuestionInTest.Count)
            {
                
                AllQuestionInTest[indexOfQuestion].studentChoose = index_section;
            }
            
        }
        // get the grade of the test
        public double grade()
        {
            double All = AllQuestionInTest.Count;
            int trueAnswer=0;
            for (int i = 0; i < AllQuestionInTest.Count; i++)
            {
                Question key = AllQuestionInTest[i];
                int value = AllQuestionInTest[i].studentChoose;
                if (key.CheckAnswer(value))
                {
                    trueAnswer++;
                }
            }
            double g = trueAnswer / All;
            return g * 100;

        }
        // check if we  can start the exam
        public bool canOpenTheTest()
        {
            var otherDate = DateTime.Now;


            bool isSameMonthAndTime = Date.Month == otherDate.Month &&
                          Date.Hour == otherDate.Hour &&
                          Date.Minute == otherDate.Minute;
            return isSameMonthAndTime;

        }
        // get list od error
        public List<string> listOfError()
        {
            List<string> result = new List<string>();
            for (int i = 0; i < AllQuestionInTest.Count; i++)
            {
                Question key = AllQuestionInTest[i];
                int value = AllQuestionInTest[i].studentChoose;
                if (!key.CheckAnswer(value))
                {
                    int ind_ofQ = i + 1;
                    int ind_ofSection = value + 1;
                    int ind_ofTrueSection = key.getCorrect() + 1;
                    var s = "Q" + ind_ofQ + " :" + "wrong answer :" + ind_ofSection + " ;true answer :" + ind_ofTrueSection;
                    result.Add(s);

                }
            }
            return result;  
            
        }
        public void changeQuestion(int indexOfQuestion, string head_text, List<Answer> ls, int tr, string head_imge = "null")
        {

            if (indexOfQuestion <= AllQuestionInTest.Count)
            {
                AllQuestionInTest[indexOfQuestion].setQuestionText(head_text);

                AllQuestionInTest[indexOfQuestion].setQuestionText(head_imge,1);
                AllQuestionInTest[indexOfQuestion].setCorrect(tr);
                AllQuestionInTest[indexOfQuestion].listAnswer = ls;


            }

        }
        
        public override string ToString()
        {
            string str = "";

            for (int i = 0; i < AllQuestionInTest.Count; i++)
            {
                Question key = AllQuestionInTest[i];
                int value = AllQuestionInTest[i].studentChoose;
                var ii= i+1;
                str += "=>index: "+ii+")\n";
                str += "=>"+key.GetQuestionText()+" :\n";
                str+=key.ToString();
                str += "\n";

            }
            return str;


        }

    }
}



 