package facade.ex1;

public class Computer {
	private Cpu cpu;
	private Hdd hdd;
	private Ram ram;
	
	public Computer() {
		this.cpu = new Cpu();
		this.hdd = new Hdd();
		this.ram = new Ram();
	}
	
	public void start() {
		cpu.execute();
		hdd.execute();
		ram.execute();
	}
}
