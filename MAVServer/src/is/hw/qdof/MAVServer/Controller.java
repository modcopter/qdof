package is.hw.qdof.MAVServer;

import java.io.IOException;


public class Controller {
	private SerialConnection serCon;
	
	public static void main(String args[]) {
		new Controller(args);
	}
	
	public Controller(String args[]) {
		if (args.length < 1) {
			System.out.println("Too few arguments!");
			System.out.println("<COM-Port>");
			System.exit(-1);
		}
		
		try {
			serCon = new SerialConnection(args[0]);
		} catch (IOException e) {
			System.out.println("Port " + args[0] + " not found!");
			System.exit(-1);
		}
		//
		serCon.setBaudRate(19200);
		//
		System.out.println("Opening port...");
		try {
			serCon.open();
		} catch (Exception e) {
			e.printStackTrace();
		}
		System.out.println("Port open!");
	}
}
