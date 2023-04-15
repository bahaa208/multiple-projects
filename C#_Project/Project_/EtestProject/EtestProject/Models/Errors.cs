namespace EtestProject.Models
{
    public class Errors
    {
        public int Id { get; set; }
        public string QuestionName { get; set; }
        public int GradeId { get; set; }
        public string ErrorAnswer { get; set; }
        public string TrueAnswer { get; set; }


        /*
        * grade class that Presenting the errors question
        * 
        * 
        * */
        public Errors()
        {
            Id = 0;
            QuestionName = "";
            ErrorAnswer = "";
            TrueAnswer = "";

        }
    }
}
