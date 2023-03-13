package Work;


public class JsonNumber implements JsonValue {


    private Number k;
    
    public JsonNumber(Number k) {
    	this.k = k;
    }

    @Override
    public JsonValue get(int i) {
        return  (JsonValue) k;
    }

    @Override
    public JsonValue get(String s) {
    	return (JsonValue) k;

    }


    @Override
    public String toString() {
        return k +"";
    }
}
