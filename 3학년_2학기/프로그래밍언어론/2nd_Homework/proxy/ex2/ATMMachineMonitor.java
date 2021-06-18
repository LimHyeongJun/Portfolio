package proxy.ex2;

public class ATMMachineMonitor {
	ATMMachine machine;
	
	public ATMMachineMonitor(ATMMachine machine) {
		this.machine = machine;
	}
	
	public void report() {
		System.out.println("ATM Machine's location: " + machine.getLocation());
		System.out.println("Current money in ATM machine: " + machine.getCurrentCash() + "won");
		System.out.println("Current state: " + machine.getState());
	}
}
