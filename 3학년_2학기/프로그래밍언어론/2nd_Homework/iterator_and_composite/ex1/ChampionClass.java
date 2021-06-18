package iterator_and_composite.ex1;

import java.util.Iterator;
import java.util.ArrayList;

public class ChampionClass extends ChampionComponent {
	ArrayList<ChampionComponent> championComponents = new ArrayList<ChampionComponent>();
	private String name;
	private String description;
	
	public ChampionClass(String name, String description) {
		this.name = name;
		this.description = description;
	}
	
	public void add(ChampionComponent championComponent) {
		championComponents.add(championComponent);
	}
	
	public void remove(ChampionComponent championComponent ) {
		championComponents.remove(championComponent);
	}
	
	public ChampionComponent getChild(int i) {
		return (ChampionComponent)championComponents.get(i);
	}
	
	public String getName() {
		return name;
	}
	
	public String getDescription() {
		return description;
	}
	
	public void print() {
		System.out.print("\n" + getName());
		System.out.println(", " + getDescription());
		System.out.println("---------------------");
		
		Iterator iterator = championComponents.iterator();
		while(iterator.hasNext()) {
			ChampionComponent championComponent = (ChampionComponent)iterator.next();
			championComponent.print();
		}
	}
}
