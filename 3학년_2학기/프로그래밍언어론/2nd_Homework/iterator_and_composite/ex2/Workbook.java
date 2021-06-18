package iterator_and_composite.ex2;

import java.util.ArrayList;

public class Workbook implements Book {
	ArrayList<BookItem> bookItems;

	public Workbook() {
		bookItems = new ArrayList<BookItem>();
		
		addItem("���� ������", 12.99);
		addItem("���� ������", 13.99);
		addItem("���� ������", 13.49);
		addItem("���� ������", 12.49);
	}
	
	public void addItem(String name, double price) {
		BookItem bookItem = new BookItem(name, price);
		bookItems.add(bookItem);
	}
	
	public ArrayList<BookItem> getBookItems() {
		return bookItems;
	}
	
	public Iterator createIterator() {
		return new WorkbookIterator(bookItems);
	}
}
