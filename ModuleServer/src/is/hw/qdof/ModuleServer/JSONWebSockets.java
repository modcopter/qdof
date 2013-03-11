package is.hw.qdof.ModuleServer;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;
import java.util.logging.Logger;

import org.webbitserver.BaseWebSocketHandler;
import org.webbitserver.WebSocketConnection;

import com.google.gson.Gson;
import com.google.gson.JsonSyntaxException;

public class JSONWebSockets extends BaseWebSocketHandler {
	protected ArrayList<WebSocketConnection> connections = new ArrayList<WebSocketConnection>();
	private HashMap<WebSocketConnection, ArrayList<String>> hm = new HashMap<WebSocketConnection, ArrayList<String>>();
	private MavClient mClient;
	private final Logger log = Logger.getLogger(this.getClass().getName());
	private Gson gson = new Gson();
	
	public void onOpen(WebSocketConnection connection) {
		connections.add(connection);
		hm.put(connection, new ArrayList<String>());
		statusUpdate();
    }

    public void onClose(WebSocketConnection connection) {
    	connections.remove(connection);
    	hm.remove(connection);
    	statusUpdate();
    }

    public void onMessage(WebSocketConnection connection, String message) {
    	JsonMessage msg = gson.fromJson(message, JsonMessage.class);

    	boolean isSub = msg.msgId.equals("sub");
		boolean isUnsub = msg.msgId.equals("unsub");
		
		if(isSub||isUnsub && msg.content instanceof ArrayList<?>) {
			@SuppressWarnings("unchecked")
			ArrayList<String> msgIds = (ArrayList<String>) msg.content;
			//
    		for(String s: msgIds) {
    			if(isSub) {
    				addSub(connection, s);
    			} else if(isUnsub) {
    				remSub(connection, s);
    			}
    		}
    	} else {
    		mClient.sendMessage(message);
    	}
    }
    
    public void registerMAVClient(MavClient newMClient) {
    	if(mClient != null) {
    		log.warning("MAVClient war schon registriert und wird ueberschrieben.");
    	}
    	mClient = newMClient;
    	log.info("MAVClient ist registriert: "+ mClient.toString());
    }
    
    public void mavMessageReceived(String json) {
    	String msgId = null;
    	JsonMessage msg;
    	//
    	try {
    		msg = gson.fromJson(json, JsonMessage.class);
    		msgId = msg.msgId;
    	} catch(JsonSyntaxException ex) {
    		log.warning("JSON-Syntax ist fehlerhaft. "+ex.getMessage());
    		return;
    	}
    	
    	for(Map.Entry<WebSocketConnection, ArrayList<String>> entry: hm.entrySet()) {
    		WebSocketConnection currentConn = entry.getKey();
    		for(String s: entry.getValue()) {
    			if(s.equals(msgId)) {
    				currentConn.send(json);
    			}
    		}
    	}
    }
    
    public void sendToAll(String message) {
    	log.info("Nachrichten an " + connections.size() + " Clients senden.");
    	for(WebSocketConnection wsConn: connections) {
    		wsConn.send(message);
    	}
    }
    
    private void statusUpdate() {
    	log.info(connections.size()+" clients sind verbunden.");
    }
    
    private void addSub(WebSocketConnection conn, String msgName) {
    	ArrayList<String> ar = hm.get(conn);
    	if(ar != null) {
    		ar.add(msgName);
    		log.info("Client #"+connections.indexOf(conn)+" abonniert Message '"+msgName+"'.");
    	} else {
    		log.warning("Subscribe fehlgeschlagen. Der angegebene Client existiert nicht.");
    	}
    }
    
    private void remSub(WebSocketConnection conn, String msgName) {
    	ArrayList<String> ar = hm.get(conn);
    	if(ar != null) {
    		if(ar.remove(msgName)) {
    			log.info("Client #"+connections.indexOf(conn)+" bestellt Message '"+msgName+"' ab.");
    		} else {
    			log.warning("Client #"+connections.indexOf(conn)+" hatte Message '"+ msgName +"' nicht abonniert.");
    		}
    	} else {
    		log.warning("Unsubscribe fehlgeschlagen. Client existierte nicht.");
    	}
    }
    
    public boolean kickClient(int id) {
    	WebSocketConnection client = connections.get(id);
    	
    	if(client==null) return false;
    	
    	client.close();
    	return true;
    }
}