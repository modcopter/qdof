package is.hw.qdof.ModuleServer;

import java.io.IOException;
import java.io.InputStreamReader;
import java.io.BufferedReader;
import java.util.StringTokenizer;
import java.util.logging.Logger;

public class CommandListenerThread extends Thread {

	private static BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
	private final Logger log = Logger.getLogger(this.getClass().getName());
	
	public CommandListenerThread(Controller c) {
		setDaemon(true);
	}
	
	@Override
	public void run() {
		String line;
		String commandTerm;
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
				
				switch(commandTerm) {
					case "stop":
						log.info("'stop' wird ausgeführt.");
						log.info("ModuleServer done. thank you.");
						System.exit(0);
						
					default:
						log.info("Kommando nicht erkannt");
					break;
				}
				
			}
		}
	}
	
}
