package command.ex2;

public class AutoDriveOffCommand implements Command {
	AutoDriveMode autoDriveMode;
	
	public AutoDriveOffCommand(AutoDriveMode autoDriveMode) {
		this.autoDriveMode = autoDriveMode;
	}
	
	public void execute() {
		autoDriveMode.off();
	}

}
