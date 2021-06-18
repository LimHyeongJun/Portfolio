package proxy.ex3;

public class Main {
	public static void main(String[] args) {
		NationalPosition spokesman = new PresidentialSpokesman();
		spokesman.announce("코로나 확진자가 급격히 늘어나고 있습니다\n"
				+ "국민 여러분들께서는 최대한 외출을 자제해주시기 바랍니다");
	}
}

