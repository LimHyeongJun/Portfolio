package proxy.ex2;

public class NoCashState implements State {
	ATMMachine atmMachine;
	
	public NoCashState(ATMMachine atmMachine) {
		this.atmMachine = atmMachine;
	}
	
	public void insertCard() {
		System.out.println("You can't insert a card, the machine has no cash");
	}


	public void ejectCard() {
		System.out.println("You can't eject, you haven't inserted a card yet");
	}


	public void withdrawCash(int money) {
		System.out.println("Machine has no cash");
	}
	
	public String toString() {
		return "no cash";
	}
}
