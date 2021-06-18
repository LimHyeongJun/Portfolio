package state.ex3;

public class Phone {
	private State powerOnState;
	private State powerOffState;
	private State displayOnState;
	private State displayOffState;
	
	private State state;
	
	public Phone() {
		powerOnState = new PowerOnState(this);
		powerOffState = new PowerOffState(this);
		displayOnState = new DisplayOnState(this);
		displayOffState = new DisplayOffState(this);
		state = powerOffState;
	}
	
	public void powerOn() {
		state.powerOn();
	}
	
	public void powerOff() {
		state.powerOff();
	}
	
	public void displayOn() {
		state.displayOn();
	}
	
	public void displayOff() {
		state.displayOff();
	}
	
	void setState(State state) {
		this.state = state;
	}
	
	public State getState() {
		return state;
	}
	
	public State getPowerOnState() {
		return powerOnState;
	}
	
	public State getPowerOffState() {
		return powerOffState;
	}
	
	public State getDisplayOnState() {
		return displayOnState;
	}
	
	public State getDisplayOffState() {
		return displayOffState;
	}
	
	public String toString() {
		StringBuffer result = new StringBuffer();
		
		result.append("Phone is \'" + state + "\'\n");
		
		return result.toString();
	}
}
