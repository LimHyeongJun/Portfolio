package iterator_and_composite.ex2;

import java.util.ArrayList;

public class WorkbookIterator implements Iterator{
	ArrayList<BookItem> bookItems;
	int position = 0;
	
	public WorkbookIterator(ArrayList<BookItem> bookItems) {
		this.bookItems = bookItems;
	}
	
	public Object next() {
		Object object = bookItems.get(position);
		position++;
		return object;
	}
	
	public boolean hasNext() {
		if(position >= bookItems.size()) {
			return false;
		} else {
			return true;
		}
	}
}
