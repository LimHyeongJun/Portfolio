package abstractFactory.ex3;

public class BusanStyleBottle implements Bottle {
	int level;
	
	public BusanStyleBottle(int level) {
		this.level = level;
	}
	
	public String toString() {
		if(level == 1) {
			return "Busan Style Small Bottle";
		} else if (level == 2) {
			return "Busan Style Medium Bottle";
		} else if (level == 3) {
			return "Busan Style Big Bottle";
		}
		
		return null;
	}

}
