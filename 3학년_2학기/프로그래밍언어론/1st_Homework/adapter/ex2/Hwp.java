package adapter.ex2;

public class Hwp implements Viewer {
	public void store(String filename) {
		System.out.println("Store " + filename + ".hwp");
	}
}
