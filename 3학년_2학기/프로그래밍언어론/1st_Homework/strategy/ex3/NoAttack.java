package strategy.ex3;

public class NoAttack implements Attackable {
	public void attack() {
		System.out.println("Can not attack");
	}
}
