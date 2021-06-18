package command.ex3;

public class FirstFloorStopCommand implements Command {
	Floor floor;
	
	public FirstFloorStopCommand() {
		this.floor = new FirstFloor();
	}
	
	public void execute() {
		floor.stop();
	}
}
