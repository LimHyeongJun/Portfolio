package adapter.ex2;

public class FilenameExtensionAdapter implements Viewer {
	private FilenameExtension filenameExtension;
	
	public FilenameExtensionAdapter(FilenameExtension f) {
		filenameExtension = f;
	}
	
	public void store(String filename) {
		System.out.print("Using Adapter --> ");
		filenameExtension.storeFile(filename);
	}
}
