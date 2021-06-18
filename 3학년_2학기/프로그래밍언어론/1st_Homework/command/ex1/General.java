package command.ex1;

public class General {
	private Command attackCommand;
	private Command retreatCommand;
	
	public void setCommand(Command attackCommand, Command retreatCommand) {
		this.attackCommand = attackCommand;
		this.retreatCommand = retreatCommand;
	}
	
	public void attackControl() {
		attackCommand.execute();
	}
	
	public void retreatControl() {
		retreatCommand.execute();
	}
}
