package state.ex1;

public class OnState implements State {
	Light light;
	
	public OnState(Light light) {
		this.light = light;
	}
	
	public void on() {
		System.out.println("Alreay Light on, so No response");
	}

	public void off() {
		System.out.println("Light off!");
		light.setState(light.getOnState());
	}
	
	public String toString() {
		return "On state";
	}
}
