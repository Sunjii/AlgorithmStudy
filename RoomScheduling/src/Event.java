
public class Event {
	int time;
	boolean start;
	Activity activity;
	
	Event(int time1, Activity act, boolean tf){
		this.time = time;
		this.activity = act;
		start = tf;
	}
	
	public String toString() {
		StringBuilder str = new StringBuilder();
		str.append(this.time);
		return str.toString();
	}

}
