package factory.ex2;

public class Main {
	public static void main(String[] args) {
		System.out.println("--------Factory pattern example 2--------");
		
		SimpleRobotFactory factory = new SimpleRobotFactory();
		RobotStore store = new RobotStore(factory);
		
		Robot robot1 = store.orderRobot("transformer");
		System.out.println("Robot 1 is a " + robot1.getName());
		
		Robot robot2 = store.orderRobot("powerrobot");
		System.out.println("Robot 2 is a " + robot2.getName());
		
		Robot robot3 = store.orderRobot("superrobot");
		System.out.println("Robot 3 is a " + robot3.getName());
	}
}
