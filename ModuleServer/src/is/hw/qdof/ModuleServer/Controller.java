package is.hw.qdof.ModuleServer;

import java.io.IOException;
import java.util.concurrent.ExecutionException;
import java.util.logging.FileHandler;
import java.util.logging.Formatter;
import java.util.logging.ConsoleHandler;
import java.util.logging.Handler;
import java.util.logging.Level;
import java.util.logging.LogRecord;
import java.util.logging.Logger;

import org.webbitserver.WebServer;
import org.webbitserver.WebServers;

public class Controller {
	private final Logger log = Logger.getLogger("is.hw.qdof"); //Logger f�r ganzes Paket
	private int webSocketPort = 8080; //Standardport 8080
	private String mavServerAdress; //Keine Standardadresse
	private int mavServerPort = 58147; //
	
	//Dateilogging
    FileHandler fh;
    
	private WebServer ws;
	private MavClient mvcl;
	
	public Controller(String[] args) {
		configLogger();
		
		if(args.length < 1) {
			showUsage(true);
		}
		
		if(args[0] == "") {
			log.warning("Adresse des MavServers nicht angegeben.");
			showUsage(true);
		} else {
			mavServerAdress = args[0];
		}
		
		if(args.length > 2) {
			if(args[1] == null) {
				log.warning("Kein WebSocket Port angegeben, benutze Port 8080.");
				showUsage(false);
			} else {
				webSocketPort = Integer.parseInt(args[1]);
			}
		}
		if(args.length > 3) {
			if(args[2] != null) {
				log.info("MavServerPort angegeben: " + args[2]);
				mavServerPort = Integer.parseInt(args[2]);
			}
		}
		
		log.info("ModuleServer startet.");
		
		JSONWebSockets webSockets = new JSONWebSockets();
		
		ws = WebServers.createWebServer(webSocketPort)
				.add("/", webSockets);
		
		mvcl = null;
		
		try {
			mvcl = new MavClient(webSockets, mavServerAdress, mavServerPort, this);
			
			mvcl.start();
			ws.start();
		} catch (Exception e) {
			e.printStackTrace();
			this.forceShutdown();
		}
		
		CommandListenerThread c = new CommandListenerThread(this, webSockets);
		
		c.start();
		
		try {
			c.join();
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		System.exit(0);
	}
	
	public static void main(String[] args) {
		new Controller(args);
		
	}
	
	private void showUsage(boolean exit) {
		log.info("Argumente: <MavServer Adresse> <WebSocketPort> <MavServerPort>");
		if(exit) System.exit(1);
	}
	
	private void configLogger() {
		//Konsolenlogging
		log.setUseParentHandlers(false);
	    Handler conHdlr = new ConsoleHandler();
	    conHdlr.setFormatter(new Formatter() {
	      public String format(LogRecord record) {
	        return record.getLevel() + ": " + record.getMessage() + "\n";
	      }
	    });
	    log.addHandler(conHdlr);
	    
	    try {
			fh = new FileHandler("moduleServerLog.xml");
			fh.setLevel(Level.WARNING);
			log.addHandler(fh);
		} catch (SecurityException | IOException e) {
			e.printStackTrace();
		}
	    
	    
	}
	
	public void forceShutdown() {
		try {
			ws.stop().get();			
		} catch (InterruptedException e) {
			e.printStackTrace();
		} catch (ExecutionException e) {
			e.printStackTrace();
		}
		
		if(mvcl != null) { //Falls MavClient instanziert ist
			try {
				mvcl.breakSocket();
				mvcl.join(); //Auf Beendigung des Threads warten
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}
		
		log.info("ModuleServer done. thank you.");
		System.exit(1);
	}

	
	@Override
	public void finalize() {
		fh.flush();
		fh.close();
	}
	
}
