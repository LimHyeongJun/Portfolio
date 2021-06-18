package command.ex3;

public class ThirdFloorStopCommand implements Command {
	Floor floor;
	
	public ThirdFloorStopCommand() {
		this.floor = new ThirdFloor();
	}
	
	public void execute() {
		floor.stop();
	}

}
