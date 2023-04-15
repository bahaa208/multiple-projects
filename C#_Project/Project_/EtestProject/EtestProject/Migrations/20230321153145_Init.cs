using System;
using Microsoft.EntityFrameworkCore.Migrations;

#nullable disable

namespace EtestProject.Migrations
{
    /// <inheritdoc />
    public partial class Init : Migration
    {
        /// <inheritdoc />
        protected override void Up(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.CreateTable(
                name: "GradeDatabase",
                columns: table => new
                {
                    Id = table.Column<int>(type: "int", nullable: false)
                        .Annotation("SqlServer:Identity", "1, 1"),
                    NameStudent = table.Column<string>(type: "nvarchar(max)", nullable: false),
                    gradeStudent = table.Column<int>(type: "int", nullable: false),
                    IdStudent = table.Column<string>(type: "nvarchar(max)", nullable: false),
                    IdTest = table.Column<string>(type: "nvarchar(max)", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_GradeDatabase", x => x.Id);
                });

            migrationBuilder.CreateTable(
                name: "TestDatabase",
                columns: table => new
                {
                    Id = table.Column<int>(type: "int", nullable: false)
                        .Annotation("SqlServer:Identity", "1, 1"),
                    Name = table.Column<string>(type: "nvarchar(max)", nullable: false),
                    _id = table.Column<string>(type: "nvarchar(max)", nullable: false),
                    Date = table.Column<DateTime>(type: "datetime2", nullable: false),
                    NameOfTeacher = table.Column<string>(type: "nvarchar(max)", nullable: false),
                    Time = table.Column<int>(type: "int", nullable: false),
                    Random = table.Column<bool>(type: "bit", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_TestDatabase", x => x.Id);
                });

            migrationBuilder.CreateTable(
                name: "ErrorsDatabase",
                columns: table => new
                {
                    Id = table.Column<int>(type: "int", nullable: false)
                        .Annotation("SqlServer:Identity", "1, 1"),
                    QuestionName = table.Column<string>(type: "nvarchar(max)", nullable: false),
                    GradeId = table.Column<int>(type: "int", nullable: false),
                    ErrorAnswer = table.Column<string>(type: "nvarchar(max)", nullable: false),
                    TrueAnswer = table.Column<string>(type: "nvarchar(max)", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_ErrorsDatabase", x => x.Id);
                    table.ForeignKey(
                        name: "FK_ErrorsDatabase_GradeDatabase_GradeId",
                        column: x => x.GradeId,
                        principalTable: "GradeDatabase",
                        principalColumn: "Id",
                        onDelete: ReferentialAction.Cascade);
                });

            migrationBuilder.CreateTable(
                name: "QuestionDatabase",
                columns: table => new
                {
                    Id = table.Column<int>(type: "int", nullable: false)
                        .Annotation("SqlServer:Identity", "1, 1"),
                    questionText = table.Column<string>(type: "nvarchar(max)", nullable: false),
                    correctAnswer = table.Column<int>(type: "int", nullable: false),
                    questionURLImageText = table.Column<string>(type: "nvarchar(max)", nullable: false),
                    count = table.Column<int>(type: "int", nullable: false),
                    TestId = table.Column<int>(type: "int", nullable: false),
                    studentChoose = table.Column<int>(type: "int", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_QuestionDatabase", x => x.Id);
                    table.ForeignKey(
                        name: "FK_QuestionDatabase_TestDatabase_TestId",
                        column: x => x.TestId,
                        principalTable: "TestDatabase",
                        principalColumn: "Id",
                        onDelete: ReferentialAction.Cascade);
                });

            migrationBuilder.CreateTable(
                name: "AnswerDatabase",
                columns: table => new
                {
                    Id = table.Column<int>(type: "int", nullable: false)
                        .Annotation("SqlServer:Identity", "1, 1"),
                    Text = table.Column<string>(type: "nvarchar(max)", nullable: false),
                    QuestionId = table.Column<int>(type: "int", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_AnswerDatabase", x => x.Id);
                    table.ForeignKey(
                        name: "FK_AnswerDatabase_QuestionDatabase_QuestionId",
                        column: x => x.QuestionId,
                        principalTable: "QuestionDatabase",
                        principalColumn: "Id",
                        onDelete: ReferentialAction.Cascade);
                });

            migrationBuilder.CreateIndex(
                name: "IX_AnswerDatabase_QuestionId",
                table: "AnswerDatabase",
                column: "QuestionId");

            migrationBuilder.CreateIndex(
                name: "IX_ErrorsDatabase_GradeId",
                table: "ErrorsDatabase",
                column: "GradeId");

            migrationBuilder.CreateIndex(
                name: "IX_QuestionDatabase_TestId",
                table: "QuestionDatabase",
                column: "TestId");
        }

        /// <inheritdoc />
        protected override void Down(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropTable(
                name: "AnswerDatabase");

            migrationBuilder.DropTable(
                name: "ErrorsDatabase");

            migrationBuilder.DropTable(
                name: "QuestionDatabase");

            migrationBuilder.DropTable(
                name: "GradeDatabase");

            migrationBuilder.DropTable(
                name: "TestDatabase");
        }
    }
}
