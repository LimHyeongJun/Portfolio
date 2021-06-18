package state.ex3;

public class DisplayOnState implements State {
	Phone phone;

	public DisplayOnState(Phone phone) {
		this.phone = phone;
	}
	
	public void powerOn() {
		System.out.println("Power is already on");
	}


	public void powerOff() {
		System.out.println("You power off the phone");
		phone.setState(phone.getPowerOffState());
	}

	public void displayOn() {
		System.out.println("Display is already on");
	}

	public void displayOff() {
		System.out.println("You display off the phone");
		phone.setState(phone.getDisplayOffState());
	}
	

	public String toString() {
		return "display on state";
	}
}
