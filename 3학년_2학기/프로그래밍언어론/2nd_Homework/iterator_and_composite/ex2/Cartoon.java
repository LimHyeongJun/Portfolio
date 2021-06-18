package iterator_and_composite.ex2;

public class Cartoon implements Book {
	static final int MAX_ITEMS = 6;
	int numberOfItems = 0;
	BookItem[] bookItems;
	
	public Cartoon() {
		bookItems = new BookItem[MAX_ITEMS];
		
		addItem("메이플스토리", 8.99);
		addItem("그랜드체이스", 7.99);
		addItem("마법천자문", 8.49);
		addItem("스타크래프트 애쒸비", 7.79);
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
