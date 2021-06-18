package adapter.ex2;

public class Off implements FilenameExtension {
	public void storeFile(String filename) {
		System.out.println("Store " + filename + ".off");
	}
}
