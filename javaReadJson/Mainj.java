package Work;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.InputStream;
import java.util.Scanner;

public class Mainj {

	public static void main( String[] args ) throws JsonQueryException {
		JsonBuilder avraham = null;
		try
		 {
			 avraham = new JsonBuilder( new FileInputStream("C:\\JAVA.WORK\\HomeWorkjava3\\src\\Work\\Avraham"));
			 System.out.println( avraham );
			 System.out.println( ( avraham.get( "issue" ).get("Ketura").get(2) ));
		 }
		 catch( JsonSyntaxException e )
		 {
			 e.printStackTrace();
		 }
		 catch (FileNotFoundException e) 
		 {
			 e.printStackTrace();
		 }
		}
	}
	 



