package adapter.ex1;

public class MKV implements MediaPackage{
	public void playFile(String filename) {
		System.out.println("Playing MKV file" + filename + ".mkv");
	}
}
