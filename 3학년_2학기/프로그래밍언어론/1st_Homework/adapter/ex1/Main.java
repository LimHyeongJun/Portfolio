package adapter.ex1;

public class Main {
	public static void main(String[] args) {
		System.out.println("--------Adapter pattern example 1--------");
		
		MediaPlayer mp3 = new MP3();
		mp3.play("I can\'t stop me");
		
		mp3 = new FormatAdapter(new MP4());
		mp3.play("I can\'t stop me");
		
		mp3 = new FormatAdapter(new MKV());
		mp3.play("I can\'t stop me");
	}
}
