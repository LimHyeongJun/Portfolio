package state.ex2;

public class NoCardState implements State {
	ATMMachine atmMachine;
	
	public NoCardState(ATMMachine atmMachine) {
		this.atmMachine = atmMachine;
	}

	public void insertCard() {
		System.out.println("You inserted a card");
		atmMachine.setState(atmMachine.getHasCardState());
	}


	public void ejectCard() {
		System.out.println("ATM machine has no card!");
	}


	public void withdrawCash(int money) {
		System.out.println("You haven't inserted a card");
	}
	
	public String toString() {
		return "no card state";
	}
}