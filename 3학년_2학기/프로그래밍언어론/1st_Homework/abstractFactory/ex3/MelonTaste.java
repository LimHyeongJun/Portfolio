package abstractFactory.ex3;

public class MelonTaste implements Taste {
	int level;
	
	public MelonTaste(int level) {
		this.level = level;
	}
	
	public String toString() {
		if(level == 1) {
			return "Melon Taste ¡¿ 1";
		} else if (level == 2) {
			return "Melon Taste ¡¿ 2";
		} else if (level == 3) {
			return "Melon Taste ¡¿ 3";
		}
		
		return null;
	}
}
