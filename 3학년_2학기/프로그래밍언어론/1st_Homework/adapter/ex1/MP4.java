package adapter.ex1;

public class MP4 implements MediaPackage{
	public void playFile(String filename) {
		System.out.println("Playing MP4 file " + filename + ".mp4");
	}
}
