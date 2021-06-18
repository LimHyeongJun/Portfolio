package proxy.ex2;

public class ATMMachine {
	private State noCardState;
	private State hasCardState;
	private State noCashState;
	private State state;
	private String location;
	private int currentMoney;
	
	public ATMMachine(String location, int money) {
		noCardState = new NoCardState(this);
		hasCardState = new HasCardState(this);
		noCashState = new NoCashState(this);
		this.location = location;
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
	
	String getLocation() {
		return location;
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
}
