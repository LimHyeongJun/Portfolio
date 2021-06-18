package facade.ex3;

public class Soldier {
	private BeforeGunCare beforeGunCare;
	private Move move;
	private CartridgeCase cartridgeCase;
	private AfterGunCare afterGunCare;
	
	public Soldier() {
		beforeGunCare = new BeforeGunCare();
		move = new Move();
		cartridgeCase = new CartridgeCase();
		afterGunCare = new AfterGunCare();
	}
	
	public void shootingPratice() {
		beforeGunCare.execute();
		move.execute("사격장");
		System.out.println("사격 연습을 한다");
		cartridgeCase.take();
		move.execute("부대");
		afterGunCare.execute();
	}
}
