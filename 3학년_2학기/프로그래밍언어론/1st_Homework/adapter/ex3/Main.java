package adapter.ex3;

public class Main {
	public static void main(String[] args) {
		System.out.println("--------Adapter pattern example 3--------");
		
		UsbType cType = new CType();
		cType.charging();
		
		UsbAdapterImpl usbAdapter = new UsbAdapterImpl(cType);
		usbAdapter.plug();
	}
}
