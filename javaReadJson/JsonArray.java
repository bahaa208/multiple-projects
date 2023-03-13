package Work;

import java.util.ArrayList;
import java.util.List;

public class JsonArray implements JsonValue {

    private List<JsonValue> list;
    
    public JsonArray() {
    	list = new ArrayList<JsonValue>();
    }

    
    public JsonValue get(int i) throws JsonQueryException {
    	if(i>=list.size() || i<0) {
    		throw new JsonQueryException("   you putted a wrong number in get()");
    	}
        return list.get(i);
    }

    @Override
    public JsonValue get(String s) {
        return null;
    }
    public void add(JsonValue i) {
       list.add(i);
    }
    


    @Override
    public String toString() {
    	if(list.size()==0) {
    		return "";
    	}
    	String ss ="[ ";
    	//StringBuilder s = new StringBuilder();
    	//s.append("[ ");
    	int i;
    	for(i=0;i<=list.size()-2;i++) {
    		
    		ss+=(list.get(i)+" ,");
    		
    		
    		}
    		
    		
    	
    	ss+=(list.get(i));
    	//System.out.println(list.get(i+1)+"placcec "+i);
    	 
    	ss+=(" ]");
    	 
    	
		return ss.toString();
          
    }
}
