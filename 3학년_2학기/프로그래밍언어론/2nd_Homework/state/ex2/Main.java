package state.ex2;

public class Main {
	public static void main(String[] args) {
		ATMMachine machine = new ATMMachine(100000);
		
		System.out.println(machine);
		machine.withdrawCash(1000);
		machine.insertCard();
		machine.ejectCard();
		machine.ejectCard();
		machine.insertCard();
		machine.withdrawCash(90000);
		machine.ejectCard();
		machine.withdrawCash(20000);
		machine.insertCard();
		machine.withdrawCash(10000);
		
		System.out.println("\n" + machine);
		
		machine.withdrawCash(10000);
		machine.refill(200000);
		machine.withdrawCash(20000);
		
		System.out.println("\n" + machine);
	}
}
