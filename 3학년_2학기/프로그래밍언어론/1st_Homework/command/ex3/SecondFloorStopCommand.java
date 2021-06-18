package command.ex3;

public class SecondFloorStopCommand implements Command {
	Floor floor;
	
	public SecondFloorStopCommand() {
		this.floor = new SecondFloor();
	}
	
	public void execute() {
		floor.stop();
	}

}
