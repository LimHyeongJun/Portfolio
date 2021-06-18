package iterator_and_composite.ex2;

public class Cartoon implements Book {
	static final int MAX_ITEMS = 6;
	int numberOfItems = 0;
	BookItem[] bookItems;
	
	public Cartoon() {
		bookItems = new BookItem[MAX_ITEMS];
		
		addItem("�����ý��丮", 8.99);
		addItem("�׷���ü�̽�", 7.99);
		addItem("����õ�ڹ�", 8.49);
		addItem("��Ÿũ����Ʈ �־���", 7.79);
	}
	
	public void addItem(String name, double price) {
		BookItem bookItem = new BookItem(name, price);
		if(numberOfItems >= MAX_ITEMS) {
			System.err.println("Sorry, menu is full! Can't add item to menu");
		} else {
			bookItems[numberOfItems] = bookItem;
			numberOfItems++;
		}
	}
	
	public BookItem[] getBookItem() {
		return bookItems;
	}
	
	public Iterator createIterator() {
		return new CartoonIterator(bookItems);
	}
}
