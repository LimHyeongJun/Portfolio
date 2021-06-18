package iterator_and_composite.ex3;

import java.util.ArrayList;
import java.util.Iterator;

public class Snack implements Product {
	ArrayList<ProductItem> productItems;
	
	public Snack() {
		productItems = new ArrayList<ProductItem>();
		
		addItem("양파링", "양파 맛 나는 원형 과자", false, 1.99);
		addItem("포카칩", "감자 맛 나는 칩 과자", true, 1.49);
		addItem("허니버터칩", "달콤한 꿀 맛이 나는 칩 과자", true, 1.39);
	}
	
	public void addItem(String name, String description, boolean onSale, double price) {
		ProductItem productItem = new ProductItem(name, description, onSale, price);
		productItems.add(productItem);
	}
	
	public ArrayList<ProductItem> getProductItems() {
		return productItems;
	}
	
	public Iterator createIterator() {
		return productItems.iterator();
	}
}
