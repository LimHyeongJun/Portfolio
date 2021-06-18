package adapter.ex2;

public class Txt implements FilenameExtension {
	public void storeFile(String filename) {
		System.out.println("Store " + filename + ".txt");
	}
}
