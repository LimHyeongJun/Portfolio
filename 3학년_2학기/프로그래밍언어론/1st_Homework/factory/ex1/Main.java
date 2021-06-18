package factory.ex1;

public class Main {
	public static void main(String[] args) {
		System.out.println("--------Factory pattern example 1--------");
		
		SimpleComputerFactory factory = new SimpleComputerFactory();
		ComputerStore store = new ComputerStore(factory);

		Computer computer1 = store.orderComputer("desktop");
		System.out.println("Computer 1 :\n" + computer1);
		
		
		Computer computer2 = store.orderComputer("laptop");
		System.out.println("Computer 2:\n" + computer2);
		
		Computer computer3 = store.orderComputer("tablet");
		System.out.println("Computer 3:\n" + computer3);
	}
}
