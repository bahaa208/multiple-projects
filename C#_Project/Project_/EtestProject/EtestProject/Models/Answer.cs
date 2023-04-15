namespace EtestProject.Models
{

    /*
        * grade class that Presenting the section or the answer
        * 
        * 
        * */
    public class Answer
    {
        public int Id { get; set; }
        public string Text { get; set; }
        public int QuestionId { get; set; }
        public Answer(string i,int id=0)
        {
            this.Text = i;
            Id = id;
        }
        public Answer()
        {
            this.Text = "";
        }
        public override string ToString()
        {
            return Text;
        }
    }
}
