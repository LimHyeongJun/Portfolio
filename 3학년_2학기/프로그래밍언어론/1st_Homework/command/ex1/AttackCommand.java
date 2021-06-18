package command.ex1;

public class AttackCommand implements Command {
	private SwordAttack swordAttack;
	
	public AttackCommand(SwordAttack swordAttack) {
		this.swordAttack = swordAttack;
	}
	public void execute() {
		swordAttack.attack();
	}
}
