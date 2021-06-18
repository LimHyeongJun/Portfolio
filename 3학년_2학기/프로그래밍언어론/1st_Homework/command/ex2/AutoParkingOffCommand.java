package command.ex2;

public class AutoParkingOffCommand implements Command {
	AutoParkingMode autoParkingMode;
	
	public AutoParkingOffCommand(AutoParkingMode autoParkingMode) {
		this.autoParkingMode = autoParkingMode;
	}
	
	public void execute() {
		autoParkingMode.off();
	}

}
