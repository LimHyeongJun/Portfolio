package iterator_and_composite.ex3;

import java.util.*;

public class Ramen implements Product {
	Hashtable productItems = new Hashtable();
	
	public Ramen() {
		addItem("�Ŷ��", "�ſ� ���� ���", false, 3.39);
		addItem("�Ҵߺ�����", "�ſ� �������� ���", true, 2.99);
		addItem("�縮����", "�Ͼ� ���� ���", true, 3.19);
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
