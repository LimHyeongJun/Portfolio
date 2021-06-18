package iterator_and_composite.ex3;

import java.util.Iterator;

public class Beverage implements Product {
	static final int MAX_ITEMS = 5;
	int numberOfItems = 0;
	ProductItem[] productItems;
	
	public Beverage() {
		productItems = new ProductItem[MAX_ITEMS];
		
		addItem("환타", "오렌지맛 탄산 음료수", true, 1.11);
		addItem("비락식혜", "식혜 음료수", false, 0.79);
		addItem("갈아만든 배", "배 맛이 나는 음료수", false, 0.99);
		addItem("포카리스웨트", "이온 음료", true, 1.59);
	}
	
	public void addItem(String name, String description, boolean onSale, double price) 
	{
		ProductItem productItem = new ProductItem(name, description, onSale, price);
		if (numberOfItems >= MAX_ITEMS) {
			System.err.println("Sorry, menu is full!  Can't add item to menu");
		} else {
			productItems[numberOfItems] = productItem;
			numberOfItems = numberOfItems + 1;
		}
	}
	
	public ProductItem[] getProductItems() {
		return productItems;
	}
	
	public Iterator createIterator() {
		return new BeverageIterator(productItems);
	}
}