package compound.ex3;

public class BattleCruiserAdapter extends SimpleUnit {
	BattleCruiser battleCruiser;
	
	public BattleCruiserAdapter(BattleCruiser battleCruiser) {
		this.battleCruiser = battleCruiser;
		setMovable(new MoveSky());
	}
	
	public void performAttack() {
		battleCruiser.fire();
	}
	
	public void display() {
		System.out.println("Battle Cruiser pretending to be a simple unit");
	}
}
