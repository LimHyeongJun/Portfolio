package command.ex2;

import java.util.*;

public class Driver {
	private Command[] onCommands;
	private Command[] offCommands;
	
	public Driver() {
		onCommands = new Command[2];
		offCommands = new Command[2];
		
		Command noCommand = new NoCommand();
		for(int i = 0; i < 2; i++) {
			onCommands[i] = noCommand;
			onCommands[i] = noCommand;
		}
	}
	
	public void setCommand(int slot, Command onCommand, Command offCommand) {
		onCommands[slot] = onCommand;
		offCommands[slot] = offCommand;
	}
 
	public void onButtonPush(int slot) {
		onCommands[slot].execute();
	}
 
	public void offButtonPush(int slot) {
		offCommands[slot].execute();
	}
  
	public String toString() {
		StringBuffer stringBuff = new StringBuffer();
		stringBuff.append("\n------ Remote Control -------\n");
		for (int i = 0; i < onCommands.length; i++) {
			stringBuff.append("[slot " + i + "] " + onCommands[i].getClass().getName()
				+ "    " + offCommands[i].getClass().getName() + "\n");
		}
		return stringBuff.toString();
	}
}
