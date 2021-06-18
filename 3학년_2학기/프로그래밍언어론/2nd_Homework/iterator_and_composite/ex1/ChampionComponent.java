package iterator_and_composite.ex1;

import java.util.*;

public abstract class ChampionComponent {
	public void add(ChampionComponent championComponent) {
		throw new UnsupportedOperationException();
	}
	
	public void remove(ChampionComponent championComponent) {
		throw new UnsupportedOperationException();
	}
	
	public ChampionComponent getChild(int i) {
		throw new UnsupportedOperationException();
	}
	
	public String getName() {
		throw new UnsupportedOperationException();
	}
	
	public String getDescription() {
		throw new UnsupportedOperationException();
	}
	
	public void print() {
		throw new UnsupportedOperationException();
	}
}
