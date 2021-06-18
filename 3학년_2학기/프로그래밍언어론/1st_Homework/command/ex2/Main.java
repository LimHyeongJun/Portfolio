package command.ex2;

public class Main {
	public static void main(String[] args) {
		System.out.println("--------Command pattern example 2--------");
		
		Driver driver = new Driver();
		
		AutoDriveMode autoDriveMode = new AutoDriveMode();
		AutoParkingMode autoParkingMode = new AutoParkingMode();
		
		AutoDriveOnCommand autoDriveOnCommand = new AutoDriveOnCommand(autoDriveMode);
		AutoDriveOffCommand autoDriveOffCommand = new AutoDriveOffCommand(autoDriveMode);
		
		AutoParkingOnCommand autoParkingOnCommand = new AutoParkingOnCommand(autoParkingMode);
		AutoParkingOffCommand autoParkingOffCommand = new AutoParkingOffCommand(autoParkingMode);
		
		driver.setCommand(0, autoDriveOnCommand, autoDriveOffCommand);
		driver.setCommand(1, autoParkingOnCommand, autoParkingOffCommand);
		
		System.out.println(driver);
		
		driver.onButtonPush(0);
		driver.offButtonPush(0);
		driver.onButtonPush(1);
		driver.offButtonPush(1);
	}
}
