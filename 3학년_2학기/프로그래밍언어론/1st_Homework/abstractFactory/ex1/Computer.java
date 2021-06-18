package abstractFactory.ex1;

public abstract class Computer {
	protected String name;
	protected Keyboard keyboard;
	protected Monitor monitor;
	protected Mouse mouse;
	
	abstract void assemble();
	
	public String toString() {
		StringBuffer result = new StringBuffer();
		result.append("----" + name + "----\n");
		if(keyboard != null)
			result.append(keyboard + "\n");
		
		if(monitor != null)
			result.append(monitor + "\n");
		
		if(mouse != null)
			result.append(mouse + "\n");
		
		return result.toString();
	}
}
