package abstractFactory.ex3;

public class BusanAmount implements Amount {
	int level;
	
	public BusanAmount(int level) {
		this.level = level;
	}
	
	public String toString() {
		if(level == 1) {
			return "Amount: 150";
		} else if(level == 2) {
			return "Amount: 300";
		} else if(level == 3) {
			return "Amount: 500";
		}
		
		return null;
	}
}
