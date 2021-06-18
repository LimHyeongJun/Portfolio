package observer.ex2;

public class SingerFan implements Fan {
	private String name;
	private Singer singer;
	
	public String getName() {
		return name;
	}
	
	public SingerFan(String name, Singer singer) {
		this.name = name;
		this.singer = singer;
		singer.addFan(this);
	}
	
	public void hear(String voice) {
		System.out.println(name + "이 \"" + voice + "\"를 들었습니다");
	}
}
