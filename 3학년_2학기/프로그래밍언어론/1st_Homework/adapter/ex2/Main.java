package adapter.ex2;

public class Main {
	public static void main(String[] args) {
		System.out.println("--------Adapter pattern example 2--------");
		
		Viewer hwp = new Hwp();
		hwp.store("2016726082_HW1");
		
		hwp = new FilenameExtensionAdapter(new Txt());
		hwp.store("2016726082_HW1");
		
		System.out.println();
		
		Viewer word = new Word();
		word.store("capture");
		
		word = new FilenameExtensionAdapter(new Off());
		word.store("capture");
	}
}
