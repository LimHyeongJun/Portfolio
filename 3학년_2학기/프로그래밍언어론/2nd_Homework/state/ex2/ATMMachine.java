package state.ex2;

public class ATMMachine {
	private State noCardState;
	private State hasCardState;
	private State noCashState;
	private State state;
	private int currentMoney;
	
	public ATMMachine(int money) {
		noCardState = new NoCardState(this);
		hasCardState = new HasCardState(this);
		noCashState = new NoCashState(this);
		
		this.currentMoney = money;
		state = noCardState;
	}
	
	public void insertCard() {
		state.insertCard();
	}
	
	public void ejectCard() {
		state.ejectCard();
	}
	
	public void withdrawCash(int money) {
		state.withdrawCash(money);
	}
	
	void setState(State state) {
		this.state = state;
	}
	
	void refill(int money) {
		this.currentMoney += money;
		
		if(state == noCashState) {
			state = hasCardState;
		}
		
		System.out.println("ATM Machine refill " + money 
				+ "won, current money is " + currentMoney + "won");
	}
	
	int getCurrentCash() {
		return currentMoney;
	}
	
	void setCurrentCash(int money) {
		this.currentMoney = money;
	}
	
	public State getState() {
		return state;
	}
	
	public State getNoCardState() {
		return noCardState;
	}
	
	public State getHasCardState() {
		return hasCardState;
	}
	
	public State getNoCashState() {
		return noCashState;
	}
	
	public String toString() {
		StringBuffer result = new StringBuffer();
		
		result.append("State is \'" + state + "\'\n");
		result.append("Machine has " + currentMoney + "won right now\n");
		
		return result.toString();
	}
}
