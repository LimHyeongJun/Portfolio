package facade.ex2;

public class Singer {
	private Diet diet;
	private DancePractice dancePractice;
	private SingingPractice singingPractice;
	private SongRecording songRecording;
	private String name;
	
	public Singer(String name) {
		diet = new Diet();
		dancePractice = new DancePractice();
		singingPractice = new SingingPractice();
		songRecording = new SongRecording();
		this.name = name;
	}
	
	public void releaseAlbum(String title) {
		diet.act();
		singingPractice.act();
		songRecording.act();
		dancePractice.act();
		System.out.println(name + " releases an album " + title);
	}
}
