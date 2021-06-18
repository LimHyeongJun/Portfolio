package abstractFactory.ex3;

public class StrawberryTaste implements Taste {
	int level;
	
	public StrawberryTaste(int level) {
		this.level = level;
	}
	
	public String toString() {
		if(level == 1) {
			return "Strawberry Taste ¡¿ 1";
		} else if (level == 2) {
			return "Strawberry Taste ¡¿ 2";
		} else if (level == 3) {
			return "Strawberry Taste ¡¿ 3";
		}
		
		return null;
	}

}
