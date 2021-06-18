package proxy.ex2;

public class Main {
	public static void main(String[] args) {
		ATMMachine machine = new ATMMachine("seoul", 300000);
		ATMMachineMonitor monitor = new ATMMachineMonitor(machine);
		
		monitor.report();
		System.out.println("----------");
		machine.insertCard();
		machine.withdrawCash(10000);
		System.out.println("----------");
		monitor.report();
	}
}
