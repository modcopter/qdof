package is.hw.qdof.ModuleServer;

import java.io.IOException;
import java.io.InputStreamReader;
import java.io.BufferedReader;
import java.util.NoSuchElementException;
import java.util.StringTokenizer;
import java.util.logging.Logger;

import org.webbitserver.WebSocketConnection;

public class CommandListenerThread extends Thread {

	private static BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
	private final Logger log = Logger.getLogger(this.getClass().getName());
	private JSONWebSockets sockets;
	
	public CommandListenerThread(Controller c, JSONWebSockets sockets) {
		setDaemon(true);
		this.sockets = (JSONWebSockets) sockets;
	}
	
	@Override
	public void run() {
		String line;
		String commandTerm;
		String paramTerm = null;
		StringTokenizer stk;
		
		while(true) {
			line = "";
			commandTerm = "";
			
			try {
				line = in.readLine();
			} catch (IOException e) {
				e.printStackTrace();
			}
			
			if(!line.equals("")) {
				stk = new StringTokenizer(line, " ");
				
				commandTerm = stk.nextToken();
				
				try {
					paramTerm = stk.nextToken();
				} catch(NoSuchElementException ex) {
					
				}
				
				switch(commandTerm) {
					case "stop":
						log.info("'stop' wird ausgeführt.");
						log.info("ModuleServer done. thank you.");
						System.exit(0);
						
					case "list":
						listClients();
					break;
						
					case "kick":
						if(paramTerm == null) break;
						kickClient(Integer.valueOf(paramTerm));
					break;
					
					default:
						log.info("Kommando nicht erkannt");
					break;
				}
				
			}
		}
	}
	
	public void listClients() {
		for(WebSocketConnection wsc : sockets.connections) {
			log.info("Client "+String.valueOf(sockets.connections.indexOf(wsc)) + ": " + wsc.httpRequest().remoteAddress().toString());
		}
	}
	
	public void kickClient(int clientId) {
		if(sockets.kickClient(clientId)) {
			log.info("Kicking client #"+String.valueOf(clientId));
		} else {
			log.info("Client #"+String.valueOf(clientId) + "does not exist.");
		}
	}
}
