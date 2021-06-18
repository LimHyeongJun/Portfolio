package command.ex1;

public class RetreatCommand implements Command {
	private Retreat retreat;
	
	public RetreatCommand(Retreat retreat) {
		this.retreat = retreat;
	}
	
	public void execute() {
		retreat.retreat();
	}
}
