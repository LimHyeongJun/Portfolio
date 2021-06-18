package strategy.ex3;

public class BattleCruiserAdapter extends Unit {
	BattleCruiser battleCruiser;
	
	public BattleCruiserAdapter(BattleCruiser battleCruiser) {
		this.battleCruiser = battleCruiser;
	}
	
	public void performAttack() {
		battleCruiser.fire();
	}

	public void display() {
		System.out.println("Battle Cruiser pretending to be a simple unit");
	}
}
