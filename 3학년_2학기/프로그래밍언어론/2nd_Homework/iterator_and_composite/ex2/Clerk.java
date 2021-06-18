package iterator_and_composite.ex2;

public class Clerk {
	Cartoon cartoon;
	Workbook workbook;
	
	public Clerk(Cartoon cartoon, Workbook workbook) {
		this.cartoon = cartoon;
		this.workbook = workbook;
	}
	
	public void printBook() {
		Iterator cartoonIterator = cartoon.createIterator();
		Iterator workbookIterator = workbook.createIterator();
		
		System.out.println("BOOK\n----\nCARTOON");
		printBook(cartoonIterator);
		System.out.println("\nWORKBOOK");
		printBook(workbookIterator);
	}
	
	private void printBook(Iterator iterator) {
		while(iterator.hasNext() ) {
			BookItem bookItem = (BookItem)iterator.next();
			System.out.print(bookItem.getName() + ", $");
			System.out.println(bookItem.getPrice());
		}
	}
}