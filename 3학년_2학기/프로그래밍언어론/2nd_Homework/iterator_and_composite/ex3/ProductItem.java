package iterator_and_composite.ex3;

public class ProductItem {
	String name;
	String description;
	boolean onSale;
	double price;
	
	public ProductItem(String name, String description, boolean onSale, double price) {
		this.name = name;
		this.description = description;
		this.onSale = onSale;
		this.price = price;
	}
	
	public String getName() {
		return name;
	}
  
	public String getDescription() {
		return description;
	}
  
	public double getPrice() {
		return price;
	}
	
	public boolean isOnSale() {
		return onSale;
	}
}
