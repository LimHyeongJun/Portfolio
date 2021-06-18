package state.ex3;

public class PowerOnState implements State {
	Phone phone;

	public PowerOnState(Phone phone) {
		this.phone = phone;
	}
	
	public void powerOn() {
		System.out.println("Power is already on");
	}


	public void powerOff() {
		System.out.println("If you want power off the phone, display on first");
	}

	public void displayOn() {
		System.out.println("You display on the phone");
		phone.setState(phone.getDisplayOnState());
	}

	public void displayOff() {
		System.out.println("If you want display off the phone, display on first");
	}
	

	public String toString() {
		return "power on state";
	}
}
