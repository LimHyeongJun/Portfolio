package adapter.ex3;

public class UsbAdapterImpl implements UsbAdapter{
	private UsbType usbType;
	
	public UsbAdapterImpl(UsbType usbType) {
		this.usbType = usbType;
	}
	
	public void plug() {
		System.out.print("Using Adapter : ");
		usbType.charging();
	}
}
