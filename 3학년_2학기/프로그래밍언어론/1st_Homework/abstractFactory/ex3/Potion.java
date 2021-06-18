package abstractFactory.ex3;

public abstract class Potion {
	String name;
	int level;
	
	Taste taste;
	Amount amount;
	Bottle bottle;
	
	abstract void prepare();
	
	public String toString() {
		StringBuffer result = new StringBuffer();
		result.append("---- " + name + " ----\n");
		
		if(taste != null)
			result.append(taste + "\n");
		if(bottle != null)
			result.append(bottle + "\n");
		if(amount != null)
			result.append(amount + "\n");
		
		return result.toString();
	}
	
	public String getName() {
		return name;
	}
	
	public void setName(String name) {
		this.name = name;
	}
}
