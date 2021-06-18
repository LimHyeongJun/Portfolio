package state.ex1;

public class Main {
	public static void main(String[] args) {
		Light light = new Light();
		
		System.out.print(light);
		System.out.println("-------");
		light.off();
		light.on();
		light.on();
		light.off();
		System.out.println("-------");
		System.out.print(light);
	}
}
