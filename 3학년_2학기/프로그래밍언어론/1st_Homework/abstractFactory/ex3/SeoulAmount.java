package abstractFactory.ex3;

public class SeoulAmount implements Amount {
	int level;
	
	public SeoulAmount(int level) {
		this.level = level;
	}
	
	public String toString() {
		if(level == 1) {
			return "Amount: 100";
		} else if(level == 2) {
			return "Amount: 200";
		} else if(level == 3) {
			return "Amount: 300";
		}
		
		return null;
	}
}
