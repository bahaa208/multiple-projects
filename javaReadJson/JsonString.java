package Work;
public class JsonString implements JsonValue {

    private String s;

    public JsonString(String value) {
        s = value;
    }

    @Override
    public JsonValue get(int i) {
        return null;
    } 

    @Override
    public String toString() {
        return s;
    }

	@Override
	public JsonValue get(String s) {
		// TODO Auto-generated method stub
		return null;
	}
}
