package iterator_and_composite.ex3;

import java.util.Iterator;

public class BeverageIterator implements Iterator {
	ProductItem[] list;
	int position = 0;
	
	public BeverageIterator(ProductItem[] list) {
		this.list = list;
	}
	
	public Object next() {
		ProductItem productItem = list[position];
		position++;
		return productItem;
	}

	public boolean hasNext() {
		if(position >= list.length || list[position] == null)
			return false;
		else
			return true;
	}
	
	public void remove() {
		if (position <= 0) {
			throw new IllegalStateException
				("You can't remove an item until you've done at least one next()");
		}
		if (list[position-1] != null) {
			for (int i = position-1; i < (list.length-1); i++) {
				list[i] = list[i+1];
			}
			list[list.length-1] = null;
		}
	}
}
