package abstractFactory.ex3;

public class AppleTaste implements Taste {
	int level;
	
	public AppleTaste(int level) {
		this.level = level;
	}
	
	public String toString() {
		if(level == 1) {
			return "Apple Taste ¡¿ 1";
		} else if (level == 2) {
			return "Apple Taste ¡¿ 2";
		} else if (level == 3) {
			return "Apple Taste ¡¿ 3";
		}
		
		return null;
	}
}
