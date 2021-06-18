package iterator_and_composite.ex1;

public class Gamer {
	ChampionComponent allChampions;
	
	public Gamer(ChampionComponent allChampions) {
		this.allChampions = allChampions;
	}
	
	public void printChampion() {
		allChampions.print();
	}
}
