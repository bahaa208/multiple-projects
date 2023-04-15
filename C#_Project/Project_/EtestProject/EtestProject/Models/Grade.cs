namespace EtestProject.Models
{
    public class Grade
    {
        public int Id { get; set; }
        public string NameStudent { get; set; }
        public int gradeStudent { get; set; }

        public string IdStudent { get; set; }
        public string IdTest { get; set; }

         
        public List<Errors> listOfErrors { get; set; }
        /*
         * grade class that Presenting the grade
         * 
         * 
         * */
        public Grade()
        {
            listOfErrors = new List<Errors>();
            IdStudent = "";
            IdTest = "";
            gradeStudent = 0;
            NameStudent = "";
            Id = 0;

        }
        public override string ToString()
        {
            string str = "Student Name: ";
            str += NameStudent + " , ID: " +
                IdStudent+" , grade: "+gradeStudent+"\n";
            return str;


        }
    }
}
