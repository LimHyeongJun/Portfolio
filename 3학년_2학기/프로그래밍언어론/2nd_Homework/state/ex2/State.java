package state.ex2;

public interface State {
	public void insertCard();
	public void ejectCard();
	public void withdrawCash(int money);
}
