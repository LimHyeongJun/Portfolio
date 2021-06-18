package iterator_and_composite.ex3;

import java.util.ArrayList;
import java.util.Iterator;

public class Snack implements Product {
	ArrayList<ProductItem> productItems;
	
	public Snack() {
		productItems = new ArrayList<ProductItem>();
		
		addItem("���ĸ�", "���� �� ���� ���� ����", false, 1.99);
		addItem("��īĨ", "���� �� ���� Ĩ ����", true, 1.49);
		addItem("��Ϲ���Ĩ", "������ �� ���� ���� Ĩ ����", true, 1.39);
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
