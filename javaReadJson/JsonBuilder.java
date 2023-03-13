package Work;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;

public class JsonBuilder {

    private CharScanner cs;
    private JsonValue v;

    public JsonBuilder(FileInputStream fileInputStream) throws FileNotFoundException, JsonSyntaxException {  // done
    	cs = new CharScanner(fileInputStream);
        v=parseValue();

    }


    public JsonValue parseValue() throws JsonSyntaxException {  // done
    	if (cs.peek() == '{') {
    		 
            cs.next();
            v = parseObject();
            

        } else {

            throw new JsonSyntaxException();
        }

        return v;
    	


    }
    public String readGivString() {// done
    	StringBuilder sbu = new StringBuilder();
    	while(cs.peek()!='"') {
    		sbu.append(cs.next());
    		
    	}
    	 
    	return sbu.toString();
    }


    public JsonArray parseArray() {  // done
    	JsonArray aray = new JsonArray();
    	 
    	while(cs.peek()!=']') {
    		if(cs.peek()=='"') {
    			cs.next();
    			aray.add(parseString());
    			
    			
    			
    			
    		}
    		if(cs.peek() >= '0' && cs.peek() <= '9') { 
    			aray.add(parseNumber());
    			
    			
    		}
    		cs.next();
    		if(cs.peek()==',') {
    			cs.next();
    		}
    		 
    		
    		
    	}
    	 
    	
		cs.next();
		 
    	return aray;

    }
    @SuppressWarnings("deprecation")
	public JsonNumber parseNumber() {   // done
    	StringBuilder stringBuilder = new StringBuilder();

        Number number;

        while (cs.peek() != ',') {
            stringBuilder.append(cs.next());
        }

        String value = stringBuilder.toString();
        if (value.contains(".")) {
            number = new Double(value);
        } else {
            number = new Integer(value);
        }
        

        return new JsonNumber(number);

    }

    public JsonString parseString() { // done

        StringBuilder s = new StringBuilder();
        while (cs.peek()!= '"') {
        	
            s.append(cs.peek());
            cs.next();
        }
        
        
        return new JsonString(s.toString());
    }

    public JsonObject parseObject() {
    	JsonObject oob = new JsonObject();
    	
    
    	
    	while(cs.peek()!='}' && cs.hasNext()) {
    		String key = null ;
        	JsonValue jsv = null;
        	
    		
    		if(cs.peek()=='"') {
    			cs.next();
    			

    			key = readGivString();
    			
    			
    			 
    			
    		}
    		
			 
    		cs.next();
    		
    		if(cs.peek()==':') {
    			cs.next();
    			
    			if(cs.peek()=='"' && jsv==null && valueKey(key)) {
        			cs.next();
        			jsv = parseString();
      
        			oob.put(key, jsv);// 00
        			cs.next();
        			 
        			
        			
        			
        		}
    			 
    			if(cs.peek()=='[' && jsv==null && valueKey(key)) {
    				cs.next();
    				
    				jsv = parseArray();
    				
    				
    				oob.put(key, jsv);
    				
    				  
    			}
    			// : array
    			
    			if(cs.peek() >= '0' && cs.peek() <= '9' && jsv==null && valueKey(key)) {
    				jsv = parseNumber();
    				
    				oob.put(key, jsv);
    				
    				
    				 
    				
    			}
    			 
    			if(cs.peek()=='{' && jsv==null && valueKey(key)) {
    				cs.next();
    				
    				jsv = parseObject();
    				
    				 
    				
    				oob.put(key, jsv);
    				
    			}
    			 
    		}
    	 
		cs.next();
		
   		
    		
    	}
    	return oob;

    }
    
    public boolean valueKey(String s) {
    	if(s==null) {
    		return false;
    	}
    	if(s.contains(";")) {
    		return false;
    	}
    	if(s.contains(":")) {
    		return false;
    	}
    	if(s.contains("[")) {
    		return false;
    	}
    	if(s.contains("]")) {
    		return false;
    	}
    	if(s.contains("{")) {
    		return false;
    	}
    	if(s.contains("}")) {
    		return false;
    	}
    	return true;
    }

    public JsonValue get(int i) throws JsonQueryException {
        return (JsonValue) v.get(i);
    }
    public JsonValue get(String s) {
        return (JsonValue) v.get(s);
    }
    public String toString() {
        return v+"";
    }


}
