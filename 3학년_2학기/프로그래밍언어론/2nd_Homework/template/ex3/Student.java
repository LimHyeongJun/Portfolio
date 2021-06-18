package template.ex3;

public class Student implements Comparable {
	String name;
	int score;
	
	public Student(String name, int score) {
		this.name = name;
		this.score = score;
	}
	
	public String toString() {
		return name + "\'s score: " + score;
	}
	
	public int compareTo(Object object) {
		Student otherStudent = (Student)object;
		
		if(this.score > otherStudent.score)
			return -1;
		else if(this.score == otherStudent.score)
			return 0;
		else
			return 1;
	}
}
