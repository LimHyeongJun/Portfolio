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
		move.execute("�����");
		System.out.println("��� ������ �Ѵ�");
		cartridgeCase.take();
		move.execute("�δ�");
		afterGunCare.execute();
	}
}
