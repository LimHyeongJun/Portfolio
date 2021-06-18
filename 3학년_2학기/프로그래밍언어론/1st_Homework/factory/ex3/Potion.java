package factory.ex3;

public abstract class Potion {
	String name;
	int price;
	int healing;
	
	public void use() {
		System.out.println("Use " + name + " and healing " + healing);
	}
	
	public String toString() {
		StringBuffer display = new StringBuffer();
		display.append("---- " + name + " ----\n");
		display.append("price : " + price + "\n");
		display.append("healing amount: " + healing + "\n");
		return display.toString();
	}
}
