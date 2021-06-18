package decorator.ex1;

public abstract class Car {
	String description = "Unknown Car";
	
	public String getDescription() {
		return description;
	}
	
	public abstract int cost();
}
