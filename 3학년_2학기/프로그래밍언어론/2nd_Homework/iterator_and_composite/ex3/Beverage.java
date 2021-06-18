package iterator_and_composite.ex3;

import java.util.Iterator;

public class Beverage implements Product {
	static final int MAX_ITEMS = 5;
	int numberOfItems = 0;
	ProductItem[] productItems;
	
	public Beverage() {
		productItems = new ProductItem[MAX_ITEMS];
		
		addItem("ȯŸ", "�������� ź�� �����", true, 1.11);
		addItem("�������", "���� �����", false, 0.79);
		addItem("���Ƹ��� ��", "�� ���� ���� �����", false, 0.99);
		addItem("��ī������Ʈ", "�̿� ����", true, 1.59);
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