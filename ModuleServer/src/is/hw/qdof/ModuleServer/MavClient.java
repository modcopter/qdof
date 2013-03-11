package is.hw.qdof.ModuleServer;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.ConnectException;
import java.net.InetAddress;
import java.net.Socket;
import java.net.UnknownHostException;
import java.util.logging.Logger;

import com.google.gson.Gson;
import com.google.gson.GsonBuilder;
import com.google.gson.JsonElement;
import com.google.gson.JsonParser;

public class MavClient extends Thread {
    private String m_serverName;
    private int m_serverPort;
    private Socket m_clientSocket;
    private JSONWebSockets m_sockets;
    //
    private final Logger log = Logger.getLogger(this.getClass().getName());

    private Controller c;
    
    /**
     * Konstruktor der MavClient-Klasse
     * 
     * @param sockets
     *            Ein JSONWebSockets Objekt das benachrichtigt wird, wenn eine
     *            Nachricht einkommt und andersherum
     * @param serverName
     *            Der Hostname oder die IP des MAVServers
     * @param serverPort
     *            Der Port des MAVServers
     * 
     * @throws UnknownHostException
     *             Wird geworfen, wenn der Server nicht gefunden werden konnte
     * @throws IOException
     *             Wird geworfen, wenn ein I/O Fehler auftritt
     */
    public MavClient(JSONWebSockets sockets, String serverName, int serverPort, Controller c) throws UnknownHostException, IOException {
		m_serverName = serverName;
		m_serverPort = serverPort;
		this.c = c;
		
		try {
			m_clientSocket = new Socket(InetAddress.getByName(m_serverName), m_serverPort);
		} catch(ConnectException ex) {
			log.severe("Verbindung zu MavServer fehlgeschlagen. Bitte die Adresse des Servers überprüfen.");
			c.forceShutdown();
		}
		m_sockets = sockets;
		m_sockets.registerMAVClient((MavClient)this);
		
		log.info("Der MavClient läuft!");
    }

    /**
     * Sendet eine Nachricht an den MAVServer, damit er sie an das MAV
     * weiterleitet
     * 
     * @param json
     *            Eine JSON-Encodierte MAVLink Nachricht
     */
    public void sendMessage(String json) {
		try {
			PrintWriter printer = new PrintWriter(m_clientSocket.getOutputStream(), true);
			Gson formatter = new Gson();
			JsonParser p = new JsonParser();
			
			printer.println(formatter.toJson(p.parse(json)));
		} catch (IOException e) {
		    log.severe("Fehler beim Senden einer Nachricht!");
		    c.forceShutdown();
		}
    }

    public void breakSocket() {
    	try {
			m_clientSocket.close();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
    	m_clientSocket = null;
    }
    
    /**
     * Hauptmethode des Threads
     */
    @Override
    public void run() {
    	
    	BufferedReader reader = null;
		try {
			reader = new BufferedReader(new InputStreamReader(m_clientSocket.getInputStream()));
		} catch (IOException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
			c.forceShutdown();
		}
		
		while (!isInterrupted()) {
		    String inJson;
		    try {
				inJson = reader.readLine();										// Convention: Eine Nachricht steht immer in einer Zeile!
				
				m_sockets.mavMessageReceived(inJson);							// Den JSONWebSockets informieren, damit er die Nachricht weiterleitet
		    } catch (IOException e) {
		    	log.severe("Konnte nicht von MavServer lesen.");
		    	log.warning("ModuleServer wird beendet.");
		    	System.exit(1);
		    }
		}
		
		try {
			m_clientSocket.close();
			log.info("Verbindung zu MavServer getrennt.");
		} catch (IOException e) {
			// TODO Auto-generated catch block
			log.warning("Socket konnte nicht geschlossen werden.");
		}

		return;
    }
}