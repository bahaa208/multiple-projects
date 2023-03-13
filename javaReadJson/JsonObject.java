package Work;


import java.util.LinkedHashMap;
import java.util.Map;
 

public class JsonObject implements JsonValue {

    private Map<String, JsonValue> map;
    
    public JsonObject() {
    	map =  new LinkedHashMap<String, JsonValue>();
    }


    @Override
    public JsonValue get(int i) {

        int counter = 0;
        for (String s : map.keySet()) {
            if (counter == i)
                return map.get(s);
            counter++;
        }

        return null;
    }

    @Override
    public JsonValue get(String s) {
        return map.get(s);
    }


    public void put(String key, JsonValue value) {

        map.put(key, value);
    }
    @Override
    public String toString() {
    	String ss ="{ ";
    	
    	for (String keys : map.keySet()) {
    		 ss+=keys+ " : " + map.get(keys)+" ,";
    		 
    		}
    	String strCopy1 = String.valueOf(ss.toCharArray(), 0, ss.length()-1);
    	strCopy1+=" }";
    	return strCopy1;
    	   
    	}
}	
          
 