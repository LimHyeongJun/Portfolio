package state.ex3;

public class Main {
	public static void main(String[] args) {
		Phone phone = new Phone();
		
		System.out.println(phone + "---------");
		phone.displayOff();
		phone.powerOff();
		phone.powerOn();
		phone.displayOff();
		phone.displayOn();
		phone.displayOff();
		phone.displayOn();
		phone.powerOff();
		phone.displayOn();
		phone.powerOn();
		phone.displayOn();
		
		System.out.println("---------\n" + phone);
	}
}
