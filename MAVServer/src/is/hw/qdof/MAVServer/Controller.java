package is.hw.qdof.MAVServer;

import java.io.IOException;
import java.util.logging.Logger;


public class Controller {
	private SerialConnection serCon;
	private TcpServer tcpServ = new TcpServer(58147);
	
	public Logger log = Logger.getLogger(this.getClass().getName());
	
	public static void main(String args[]) {
		new Controller(args);
	}
	
	public Controller(String args[]) {
		if (args.length < 1) {
			log.severe("Too few arguments!");
			log.severe("Expected at least 1, none was given!");
			log.severe("Terminating.");
			System.exit(-1);
		}
		
		try {
			serCon = new SerialConnection(args[0], tcpServ);
		} catch (IOException e) {
			log.severe("Serial port " + args[0] + " not found.");
			log.severe("Terminating.");
			System.exit(-1);
		}
		//
		serCon.setBaudRate(19200);
		//
		log.info("Opening port....");
		try {
			serCon.open();
		} catch (Exception e) {
			e.printStackTrace();
		}
		log.info("Port open!");
		//
		log.info("Starting server...");
		tcpServ.setSerialConnection(serCon);
		try {
			tcpServ.startServer();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
}
