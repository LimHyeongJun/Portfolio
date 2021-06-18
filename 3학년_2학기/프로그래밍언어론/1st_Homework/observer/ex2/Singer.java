package observer.ex2;

import java.util.*;

public class Singer implements Talent {
	private ArrayList fanList;
	
	public Singer() {
		fanList = new ArrayList();
	}
	
	public void addFan(Fan o) {
		fanList.add(o);
	}
	
	public void deleteFan(Fan o) {
		int i = fanList.indexOf(o);
		if(i >= 0)
			fanList.remove(i);
	}
	
	public void speak(String talk) {
		for(int i = 0; i < fanList.size(); i++) {
			Fan o = (Fan)fanList.get(i);
			o.hear(talk);
		}
	}
}
