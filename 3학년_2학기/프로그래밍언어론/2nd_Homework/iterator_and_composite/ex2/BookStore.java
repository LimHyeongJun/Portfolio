package iterator_and_composite.ex2;

public class BookStore {
	public static void main(String args[]) {
		Cartoon cartoon = new Cartoon();
		Workbook workbook = new Workbook();
		
		Clerk clerk = new Clerk(cartoon, workbook);
		
		clerk.printBook();
	}
}
