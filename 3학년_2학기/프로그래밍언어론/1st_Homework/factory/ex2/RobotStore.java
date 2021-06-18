package factory.ex2;

public class RobotStore {
	SimpleRobotFactory factory;
	
	public RobotStore(SimpleRobotFactory factory) {
		this.factory = factory;
	}
	
	public Robot orderRobot(String type) {
		Robot robot = null;
		
		robot = factory.createRobot(type);
		
		return robot;
	}
}
