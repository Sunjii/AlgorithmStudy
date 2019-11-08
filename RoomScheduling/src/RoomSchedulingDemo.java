import java.util.Scanner;

public class RoomSchedulingDemo {

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int n;
		n = sc.nextInt();
		
		Event[] events = new Event[2*n];
		
		

		//ArrayList events = new ArrayList();
		for (int i = 0; i < n; i++) {
			int input_time = sc.nextInt();
			int input_time2 = sc.nextInt();
			Activity act = new Activity();
			events[i] = new Event(input_time, act, true);
			events[i+1] = new Event(input_time2, act, false);
		}

		// Collections.sort(events);
		//int size = events.size();
		for (int i = 0; i < 2*n; i++) {
//			System.out.println(events[i].time);
		}

		/*
		ArrayList freelist = new ArrayList();
		for (int i = 0; i < n; i++) {
			freelist.add(new Room(false));
		}
		*/
		Room[] freelist = new Room[n];
		for(int i=0; i<n; i++) {
			freelist[i] = new Room(false);
		}
		int c=n-1;
		int count = 0;
		
		
		for (int i = 0; i < 2 * n - 1; i++) {
			if(events[i].start == false) {
				Room room = events[i].activity.room;
				room.used = false;
				freelist[c] = room;
				c++;
				count--;
			} else {
				Room room = freelist[c];
				c--;
				room.used = true;
				events[i].activity.room = room;
				count++;
			}
		}
		
		System.out.println("필요한 룸의 수 : " + count);

	}

}
