package adapter.ex1;

public class MP3 implements MediaPlayer {
	public void play(String filename) {
		System.out.println("Playing MP3 file " + filename + ".mp3");
	}
}
