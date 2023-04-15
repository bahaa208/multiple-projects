using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using EtestProject.Data;
using EtestProject.Models;

namespace EtestProject.Controllers
{
    /*
      * controller for the Answer/section to get all Answer/section in data base 
      * or 
      * delete Answer/section 
      * or
      * post Answer/section
      * or 
      * put update Answer/section
      * 
      * 
      */
    [Route("api/[controller]")]
    [ApiController]
    public class AnswersController : ControllerBase
    {
        private readonly TestContext _context;

        public AnswersController(TestContext context)
        {
            _context = context;
        }

        // GET: api/Answers
        [HttpGet]
        public async Task<ActionResult<IEnumerable<Answer>>> GetAnswerDatabase()
        {
          if (_context.AnswerDatabase == null)
          {
              return NotFound();
          }
            return await _context.AnswerDatabase.ToListAsync();
        }

        // GET: api/Answers/5
        [HttpGet("{id}")]
        public async Task<ActionResult<Answer>> GetAnswer(int id)
        {
          if (_context.AnswerDatabase == null)
          {
              return NotFound();
          }
            var answer = await _context.AnswerDatabase.FindAsync(id);

            if (answer == null)
            {
                return NotFound();
            }

            return answer;
        }

        // PUT: api/Answers/5
        // To protect from overposting attacks, see https://go.microsoft.com/fwlink/?linkid=2123754
        [HttpPut("{id}")]
        public async Task<IActionResult> PutAnswer(int id, Answer answer)
        {
            if (id != answer.Id)
            {
                return BadRequest();
            }

            _context.Entry(answer).State = EntityState.Modified;

            try
            {
                await _context.SaveChangesAsync();
            }
            catch (DbUpdateConcurrencyException)
            {
                if (!AnswerExists(id))
                {
                    return NotFound();
                }
                else
                {
                    throw;
                }
            }

            return NoContent();
        }

        // POST: api/Answers
        // To protect from overposting attacks, see https://go.microsoft.com/fwlink/?linkid=2123754
        [HttpPost]
        public async Task<ActionResult<Answer>> PostAnswer(Answer answer)
        {

          if (_context.AnswerDatabase == null)
          {
              return Problem("Entity set 'TestContext.AnswerDatabase'  is null.");
          }
            

              _context.AnswerDatabase.Add(answer);
            
            await _context.SaveChangesAsync();

            return CreatedAtAction("GetAnswer", new { id = answer.Id }, answer);
        }

        // DELETE: api/Answers/5
        [HttpDelete("{id}")]
        public async Task<IActionResult> DeleteAnswer(int id)
        {
            if (_context.AnswerDatabase == null)
            {
                return NotFound();
            }
            var answer = await _context.AnswerDatabase.FindAsync(id);
            if (answer == null)
            {
                return NotFound();
            }

            _context.AnswerDatabase.Remove(answer);
            await _context.SaveChangesAsync();

            return NoContent();
        }

        private bool AnswerExists(int id)
        {
            return (_context.AnswerDatabase?.Any(e => e.Id == id)).GetValueOrDefault();
        }
    }
}
