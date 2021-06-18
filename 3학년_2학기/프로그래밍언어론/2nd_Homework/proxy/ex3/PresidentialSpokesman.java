package proxy.ex3;

public class PresidentialSpokesman implements NationalPosition {
	private President president;
	
	public PresidentialSpokesman() {
		president = new President();
	}
	
	public void announce(String message) {
		System.out.print("President say: ");
		president.announce(message);
	}
}
