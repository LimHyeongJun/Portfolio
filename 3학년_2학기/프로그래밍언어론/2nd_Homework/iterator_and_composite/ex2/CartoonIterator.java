package iterator_and_composite.ex2;

public class CartoonIterator implements Iterator{
	BookItem[] bookItems;
	int position = 0;
	
	public CartoonIterator(BookItem[] bookItems) {
		this.bookItems = bookItems;
	}
	
	public Object next() {
		BookItem bookItem = bookItems[position];
		position++;
		return bookItem;
	}
	
	public boolean hasNext() {
		if(position >= bookItems.length || bookItems[position] == null) {
			return false;
		} else {
			return true;
		}
	}
}
