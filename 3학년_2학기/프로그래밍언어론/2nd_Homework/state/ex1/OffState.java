package state.ex1;

public class OffState implements State {
	Light light;
	
	public OffState(Light light) {
		this.light = light;
	}
	
	public void on() {
		System.out.println("Light on!");
		light.setState(light.getOnState());
	}

	public void off() {
		System.out.println("Alreay Light off, so No response");
	}
	
	public String toString() {
		return "Off state";
	}
}
