package state.ex3;

public class PowerOffState implements State {
	Phone phone;

	public PowerOffState(Phone phone) {
		this.phone = phone;
	}
	
	public void powerOn() {
		System.out.println("You power on the phone");
		phone.setState(phone.getPowerOnState());
	}


	public void powerOff() {
		System.out.println("Power is already off");
	}

	public void displayOn() {
		System.out.println("If you want display on the phone, power on first");
	}

	public void displayOff() {
		System.out.println("If you want display off the phone, power on first");
	}
	

	public String toString() {
		return "power off state";
	}
}
