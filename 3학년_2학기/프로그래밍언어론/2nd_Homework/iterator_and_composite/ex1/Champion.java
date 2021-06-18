package iterator_and_composite.ex1;

import java.util.Iterator;
import java.util.ArrayList;

public class Champion extends ChampionComponent {
	private String name;
	private String description;
	
	public Champion(String name, String description) {
		this.name = name;
		this.description = description;
	}
	
	public String getName() {
		return name;
	}
  
	public String getDescription() {
		return description;
	}
	
	public void print() {
		System.out.print("  " + getName());
		System.out.println("     -- " + getDescription());
	}
}
