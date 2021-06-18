package iterator_and_composite.ex2;

public class BookItem {
	String name;
	double price;
	
	public BookItem(String name, double price) {
		this.name = name;
		this.price = price;
	}
	
	public String getName() {
		return name;
	}
	
	public double getPrice() {
		return price;
	}
	
	public String toString() {
		return name + ", $" + price + "\n";
	}
}
