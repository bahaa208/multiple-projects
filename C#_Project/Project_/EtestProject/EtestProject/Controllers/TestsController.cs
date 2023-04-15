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
     * controller for the test to get all test in data base 
     * or 
     * delete exam 
     * or
     * post exam
     * or 
     * put update exam
     * 
     * */
    [Route("api/[controller]")]
    [ApiController]
    public class TestsController : ControllerBase
    {
        private readonly TestContext _context;

        public TestsController(TestContext context)
        {
            _context = context;
        }

        // GET: api/Tests
        [HttpGet]
        public async Task<ActionResult<IEnumerable<Test>>> GetTestDatabase()
        {
          if (_context.TestDatabase == null)
          {
              return NotFound();
          }
            return await _context.TestDatabase.Include(t => t.AllQuestionInTest).ThenInclude(q => q.listAnswer).ToListAsync();
        }

        /*
         *
         *GetTestDatabase()
         *GetTest(string name)
         *PutTest(int id, Test test)
         *PostTest(Test test)
         **/

        // GET: api/Tests/5
        [HttpGet("{name}")]
        public async Task<ActionResult<Test>> GetTest(string name)
        {
            if (_context.TestDatabase == null)
            {
                return NotFound();
            }

            var test = await _context.TestDatabase.Include(e => e.AllQuestionInTest)
                                           .ThenInclude(q => q.listAnswer)
                                           .FirstOrDefaultAsync(e => e.Name == name);

            if (test == null)
            {
                return NotFound();
            }

            return test;
        }

        // PUT: api/Tests/5
        // To protect from overposting attacks, see https://go.microsoft.com/fwlink/?linkid=2123754
        [HttpPut("{id}")]
        public async Task<IActionResult> PutTest(int id, Test test)
        {
            if (id != test.Id)
            {
                return BadRequest();
            }

            _context.Entry(test).State = EntityState.Modified;
            


            try
            {
                await _context.SaveChangesAsync();
            }
            catch (DbUpdateConcurrencyException)
            {
                if (!TestExists(id))
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

        // POST: api/Tests
        // To protect from overposting attacks, see https://go.microsoft.com/fwlink/?linkid=2123754
        [HttpPost]
        public async Task<ActionResult<Test>> PostTest(Test test)
        {
          if (_context.TestDatabase == null)
          {
              return Problem("Entity set 'TestContext.TestDatabase'  is null.");
          }
            _context.TestDatabase.Add(test);
            await _context.SaveChangesAsync();

            return CreatedAtAction("GetTest", new { id = test.Id }, test);
        }

        // DELETE: api/Tests/5
        [HttpDelete("{id}")]
        public async Task<IActionResult> DeleteTest(int id)
        {
            if (_context.TestDatabase == null)
            {
                return NotFound();
            }
            var test = await _context.TestDatabase.FindAsync(id);
            if (test == null)
            {
                return NotFound();
            }

            _context.TestDatabase.Remove(test);
            await _context.SaveChangesAsync();

            return NoContent();
        }

        
        
        private bool TestExists(int id)
        {
            return _context.TestDatabase.Any(e => e.Id == id);
        }
    }
}
    