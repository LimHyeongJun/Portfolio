package command.ex3;

public class Main {
	public static void main(String[] args) {
		System.out.println("--------Command pattern example 3--------");
		
		Elevator elevator = new Elevator();
		
		FirstFloorStopCommand firstFloorStopCommand = new FirstFloorStopCommand();
		SecondFloorStopCommand secondFloorStopCommand = new SecondFloorStopCommand();
		ThirdFloorStopCommand thirdFloorStopCommand = new ThirdFloorStopCommand();
		
		elevator.setCommand(1, firstFloorStopCommand);		//1Ãþ ¸ØÃß´Â ¹öÆ° ¼³Á¤
		elevator.setCommand(2, secondFloorStopCommand);		//2Ãþ ¸ØÃß´Â ¹öÆ° ¼³Á¤
		elevator.setCommand(3, thirdFloorStopCommand);		//3Ãþ ¸ØÃß´Â ¹öÆ° ¼³Á¤
		
		System.out.println(elevator);
		
		elevator.buttonPush(1);
		elevator.buttonPush(2);
		elevator.buttonPush(3);
	}
}
