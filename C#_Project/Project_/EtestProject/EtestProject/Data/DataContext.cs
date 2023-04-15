
using EtestProject.Models;

using Microsoft.EntityFrameworkCore;
 

namespace EtestProject.Data
{
    public class TestContext : DbContext
    {
        public TestContext(DbContextOptions<TestContext> options) : base(options)
        {
        }
       /*
        * to build data base for Exam, Question ,Grade Answer Errors
        * */

        public DbSet<Test> TestDatabase { get; set; }
        public DbSet<Question> QuestionDatabase { get; set; }
        public DbSet<Answer> AnswerDatabase { get; set; }
        public DbSet<Grade> GradeDatabase { get; set; }
        public DbSet<Errors> ErrorsDatabase { get; set; }

       /*
        Exam has many question and question has many answers
       grade has many Errors
       to build the table
        */

        protected override void OnModelCreating(ModelBuilder modelBuilder)
        {
            modelBuilder.Entity<Test>()
                .HasMany(t => t.AllQuestionInTest)
                .WithOne()
                .OnDelete(DeleteBehavior.Cascade);

            modelBuilder.Entity<Question>()
                .HasMany(t => t.listAnswer)
                .WithOne()
                .OnDelete(DeleteBehavior.Cascade);

            modelBuilder.Entity<Grade>()
                .HasMany(t => t.listOfErrors)
                .WithOne()
                .OnDelete(DeleteBehavior.Cascade);

        }
    }
}
