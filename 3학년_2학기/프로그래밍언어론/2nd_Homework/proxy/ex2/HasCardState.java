package proxy.ex2;

public class HasCardState implements State {
	ATMMachine atmMachine;
	
	public HasCardState(ATMMachine atmMachine) {
		this.atmMachine = atmMachine;
	}
	

	public void insertCard() {
		System.out.println("You already insert a card. You can't insert a card");
	}


	public void ejectCard() {
		System.out.println("Card returned");
		atmMachine.setState(atmMachine.getNoCardState());
	}


	public void withdrawCash(int money) {
		int currentCash = atmMachine.getCurrentCash();
		if(currentCash > money) {
			System.out.print("You withdraw " + money + "won");
			
			int remainCash = currentCash - money;
			atmMachine.setCurrentCash(remainCash);
			System.out.println(", and remain " + remainCash + "won in machine");
		} else if(currentCash == money) {
			System.out.println("You withdraw " + money + "won, and no cash in machine");
			atmMachine.setState(atmMachine.getNoCashState());
		} else {
			System.out.println("Machine doesn't have enough money to withdraw " + money + "won");
		}
	}
	
	public String toString() {
		return "has card";
	}
}
