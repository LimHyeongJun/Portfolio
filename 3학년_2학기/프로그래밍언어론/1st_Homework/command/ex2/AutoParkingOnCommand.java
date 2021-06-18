package command.ex2;

public class AutoParkingOnCommand implements Command {
	AutoParkingMode autoParkingMode;
	
	public AutoParkingOnCommand(AutoParkingMode autoParkingMode) {
		this.autoParkingMode = autoParkingMode;
	}
	
	public void execute() {
		autoParkingMode.on();
	}
}
