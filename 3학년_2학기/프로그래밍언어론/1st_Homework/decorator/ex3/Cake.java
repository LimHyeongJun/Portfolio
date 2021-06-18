package decorator.ex3;

public abstract class Cake {
	String description = "Unknown Cake";
	
	public String getDescription() {
		return description;
	}
	
	public abstract int cost();
}
