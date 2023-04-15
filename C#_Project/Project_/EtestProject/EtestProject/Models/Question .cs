using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.Serialization;
using System.Text.Json.Serialization;

namespace EtestProject.Models
{
     public class Question
    {
        // Fields (attributes)
        
        public int Id { get; set; }
        public string questionText { get; set; }
        public int correctAnswer { get; set; }
        public string questionURLImageText { get; set; }
        public List<Answer> listAnswer { get; set; }
        public int count { get; set; }
        public int TestId { get; set; }
        public int studentChoose { get; set; }


        // Constructor
        /*
         * question class that performance Question
         * we have neme Id for table in database
         * Text ,correctAnswer ,count of the question .........
         * get set..
        }*/
        public Question(string questionText, string questionURLImageText="null")
        {
            this.questionText = questionText;
            this.correctAnswer = -1;
            this.questionURLImageText = questionURLImageText;
            this.listAnswer = new List<Answer>();
            this.count = 0;
            this.studentChoose = -1;
        }
        public Question()
        {
             
            this.questionText = "";
            this.correctAnswer = -1;
            this.questionURLImageText = null;
            this.listAnswer = new List<Answer>();
            this.count = 0;
            this.studentChoose = -1;

        }
         
        public Question( string text, int correct, string imageURL, List<Answer> answers, int count)
        {
             
            this.questionText = text;
            this.correctAnswer = correct;
            this.questionURLImageText = imageURL;
            this.listAnswer = answers;
            this.count = count;
            this.studentChoose = -1;
        }
        public string getImage()
        {
            return questionURLImageText;
        }
        public void AddSection(string s)
        {
            listAnswer.Add(new Answer(s));
            count++;    
        }
        public int numberSec()
        {
            return listAnswer.Count;
        }
        public void setCorrect(int t)
        {
            if (t < listAnswer.Count)
            {
                correctAnswer = t;
            }
            
        }
        public int getCorrect()
        {
            return correctAnswer;
        }
        // Methods
        public bool CheckAnswer(int answer)
        {
            return answer==correctAnswer;
        }
        // i=0 then we have text else we have image
        public void setQuestionText(string s,int i = 0)
        {
            if (i==0)
            {
                questionText = s;
            }
            else { questionURLImageText = s; }
        }
        public List<Answer> getAllSection()
        {
            return listAnswer;
            
        }
        public void setAllSection(List<Answer> ll)
        {
            if(listAnswer == null) { return;  }
            for(int i = 0; i < ll.Count; i++)
            {
                Answer answer = ll[i];
                listAnswer.Add(answer);
            }

        }
        public string GetQuestionText()
        {
            if (questionURLImageText != "null" && questionURLImageText != "string")
            {
                return questionURLImageText;
            }
            return questionText;
        }
        public string getChooseAnswerString()
        {
            if (studentChoose == -1)
            {
                return "";
            }
            var s = listAnswer[studentChoose];
            return s.Text;
        }
        public string getCorrectAnswerString()
        {
            if (correctAnswer == -1)
            {
                return "*";
            }
            var s = listAnswer[correctAnswer];
            return s.Text;
        }
        public override string ToString()
        {
            string str = "";

            for (int i = 0; i < listAnswer.Count; i++)
            {
                str += 1 + i + " : " + listAnswer[i].ToString() + "\n";


            }
            var aa = 1 + correctAnswer;
            str +="correct Answer is index :"+ aa + "\n";

            return str;
        }

    }

}
