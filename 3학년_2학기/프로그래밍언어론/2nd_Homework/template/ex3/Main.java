package template.ex3;

import java.util.Arrays;

public class Main {
	public static void main(String[] args) {
		Student students[] = {
				new Student("John", 90),
				new Student("Tom", 91),
				new Student("Emily", 87),
				new Student("Juliet", 95),
				new Student("Frodo", 85),
		};
		
		System.out.println("Before sorting:");
		display(students);
		
		Arrays.sort(students);
		
		System.out.println("\nAfter sorting:");
		display(students);
	}
	
	public static void display(Student[] students) {
		for (int i = 0; i < students.length; i++) {
			System.out.println(students[i]);
		}
	}
}
