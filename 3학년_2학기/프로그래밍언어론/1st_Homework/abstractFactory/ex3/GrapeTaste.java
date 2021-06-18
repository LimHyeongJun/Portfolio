package abstractFactory.ex3;

public class GrapeTaste implements Taste {
	int level;
	
	public GrapeTaste(int level) {
		this.level = level;
	}
	
	public String toString() {
		if(level == 1) {
			return "Grape Taste ¡¿ 1";
		} else if (level == 2) {
			return "Grape Taste ¡¿ 2";
		} else if (level == 3) {
			return "Grape Taste ¡¿ 3";
		}
		
		return null;
	}
}
