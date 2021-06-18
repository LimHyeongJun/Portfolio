package command.ex3;

public class Main {
	public static void main(String[] args) {
		System.out.println("--------Command pattern example 3--------");
		
		Elevator elevator = new Elevator();
		
		FirstFloorStopCommand firstFloorStopCommand = new FirstFloorStopCommand();
		SecondFloorStopCommand secondFloorStopCommand = new SecondFloorStopCommand();
		ThirdFloorStopCommand thirdFloorStopCommand = new ThirdFloorStopCommand();
		
		elevator.setCommand(1, firstFloorStopCommand);		//1�� ���ߴ� ��ư ����
		elevator.setCommand(2, secondFloorStopCommand);		//2�� ���ߴ� ��ư ����
		elevator.setCommand(3, thirdFloorStopCommand);		//3�� ���ߴ� ��ư ����
		
		System.out.println(elevator);
		
		elevator.buttonPush(1);
		elevator.buttonPush(2);
		elevator.buttonPush(3);
	}
}
