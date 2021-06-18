package factory.ex1;

public abstract class Computer {
	String name;
	String hdd;
	String cpu;
	String graphicCard;
	
	public String toString() {
		StringBuffer display = new StringBuffer();
		display.append("---- " + name + " ----\n");
		display.append(hdd + "\n");
		display.append(cpu + "\n");
		display.append(graphicCard + "\n");
		return display.toString();
	}
}
