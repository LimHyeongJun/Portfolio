package command.ex3;

public class Elevator {
	private Command[] commands;
	
	public Elevator() {
		commands = new Command[3];
		
		Command noCommand = new NoCommand();
		for(int i = 0; i < 3; i++)
			commands[i] = noCommand;
	}
	
	public void setCommand(int slot, Command command) {
		commands[slot - 1] = command;
	}
	
	public void buttonPush(int slot) {
		commands[slot - 1].execute();
	}
	
	public String toString() {
		StringBuffer stringBuff = new StringBuffer();
		stringBuff.append("\n------ Elevator Button -------\n");
		for (int i = 0; i < commands.length; i++) {
			stringBuff.append("[button " + (i + 1) + "] " + commands[i].getClass().getName() + "\n");
		}
		return stringBuff.toString();
	}
}
