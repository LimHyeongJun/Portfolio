package abstractFactory.ex3;

public class SeoulStyleBottle implements Bottle {
	int level;
	
	public SeoulStyleBottle(int level) {
		this.level = level;
	}
	
	public String toString() {
		if(level == 1) {
			return "Seoul Style Small Bottle";
		} else if (level == 2) {
			return "Seoul Style Medium Bottle";
		} else if (level == 3) {
			return "Seoul Style Big Bottle";
		}
		
		return null;
	}
}
