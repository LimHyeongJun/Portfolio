package state.ex1;

public class Light {
	private State onState;
	private State offState;
	
	private State state;
	
	public Light() {
		onState = new OnState(this);
		offState = new OffState(this);
		
		state = offState;
	}
	
	public void on() {
		state.on();
	}
	
	public void off() {
		state.off();
	}
	
	public void setState(State state) {
		this.state = state;
	}
	
	public State getState() {
		return state;
	}
	
	public State getOnState() {
		return onState;
	}
	
	public State getOffState() {
		return offState;
	}
	
	public String toString() {
		StringBuffer result = new StringBuffer();
		
		result.append("Light is " + state + "\n");
		
		return result.toString();
	}
}
