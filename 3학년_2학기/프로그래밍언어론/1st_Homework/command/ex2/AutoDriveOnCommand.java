package command.ex2;

public class AutoDriveOnCommand implements Command {
	AutoDriveMode autoDriveMode;
	
	public AutoDriveOnCommand(AutoDriveMode autoDriveMode) {
		this.autoDriveMode = autoDriveMode;
	}
	
	public void execute() {
		autoDriveMode.on();
	}
}
