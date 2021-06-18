package abstractFactory.ex2;

public abstract class Car {
	protected String name;
	protected Wheel wheel;
	protected Navigation navigation;
	protected Seat seat;
	
	protected abstract void prepare();
	
	public String toString() {
		StringBuffer result = new StringBuffer();
		result.append("----" + name + "----\n");
		if(wheel != null)
			result.append(wheel + "\n");
		
		if(navigation != null)
			result.append(navigation + "\n");
		
		if(seat != null)
			result.append(seat + "\n");
		
		return result.toString();
	}
}
