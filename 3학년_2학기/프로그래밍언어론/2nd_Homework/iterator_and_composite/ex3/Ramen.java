package iterator_and_composite.ex3;

import java.util.*;

public class Ramen implements Product {
	Hashtable productItems = new Hashtable();
	
	public Ramen() {
		addItem("신라면", "매운 국물 라면", false, 3.39);
		addItem("불닭볶음면", "매운 국물없는 라면", true, 2.99);
		addItem("사리곰탕", "하얀 국물 라면", true, 3.19);
	}
	
	public void addItem(String name, String description, boolean onSale, double price) {
		ProductItem productItem = new ProductItem(name, description, onSale, price);
		productItems.put(productItem.getName(), productItem);
	}
	
	public Hashtable getItems() {
		return productItems;
	}
	
	public Iterator createIterator() {
		return productItems.values().iterator();
	}
}
