package factory.ex2;

public class SimpleRobotFactory {
	Robot robot;
	
	public SimpleRobotFactory() {
		robot = null;
	}
	
	public Robot createRobot(String type) {
		if(type.equalsIgnoreCase("powerrobot")) {
			robot = new PowerRobot();
		} else if(type.equalsIgnoreCase("superrobot")) {
			robot = new SuperRobot();
		} else if(type.equalsIgnoreCase("transformer")) {
			robot = new Transformer();
		}
		
		return robot;
	}
}
