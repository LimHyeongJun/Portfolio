package command.ex1;

public class Main {
	public static void main(String[] args) {
		System.out.println("--------Command pattern example 1--------");
		
		General general = new General();
		SwordAttack sa = new SwordAttack();
		AttackCommand attackCommand = new AttackCommand(sa);
		Retreat r = new Retreat();
		RetreatCommand retreatCommand = new RetreatCommand(r);
		
		general.setCommand(attackCommand, retreatCommand);
		general.attackControl();
		general.retreatControl();
	}
}
