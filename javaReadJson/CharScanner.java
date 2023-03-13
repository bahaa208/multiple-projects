/**
 * @author Ronny Sivan (ronny.sivan@gmail.com)
 *
 * @date Nov 26, 2017
 * 
 */
package Work;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;

/**
 * ReadInput
 *
 */
public class CharScanner
{
   private char    c;
   private boolean h;
   private InputStream is;

   public CharScanner( InputStream is )
   {
	  this.is = is;
	  
      read();
   }

   public CharScanner( File name ) throws FileNotFoundException
   {
	  is = new FileInputStream( name );
	  
      read();
   }

  

private void read()
   {
      int c;
      do
      {
         try
         {
            c = is.read();
         }
         catch( IOException e )
         {
            e.printStackTrace();
            c = -1;
         }
      }
      while( ( c != -1 ) && 
    		 ( ( c == '\n' ) || 
    		   ( c == '\r' ) || 
    		   ( c == '\t' ) || 
    		   ( c == ' ' ) ) );

      this.h = ( c != -1 );
      this.c = (char) c;
   }

   public boolean hasNext()
   {
      return( h );
   }

   public char next()
   {
      char n = c;
//      System.out.print(c);
      read();
      return( n );
   }

   public char peek()
   {
      return( c );
   }

   public boolean read( char e )
   {
      boolean result = this.c == e;
      read();
      return( result );
   }

   /**
    * main
    *
    * @param args
    */
   public static void main( String[] args )
   {
      CharScanner cs = new CharScanner( System.in );

      while( cs.hasNext() )
      {
         System.out.print( cs.peek() );
         System.out.print( "+" );
         System.out.println( cs.next() );
      }

   }

}
