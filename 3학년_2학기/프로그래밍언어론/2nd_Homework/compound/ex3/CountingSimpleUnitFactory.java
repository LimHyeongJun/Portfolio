package compound.ex3;

public class CountingSimpleUnitFactory extends AbstractSimpleUnitFactory{
	public SimpleUnit createArcher() {
		return new AttackCounter(new Archer());
	}

	public SimpleUnit createWarrior() {
		return new AttackCounter(new Warrior());
	}

	public SimpleUnit createWizard() {
		return new AttackCounter(new Wizard());
	}
}
