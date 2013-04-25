package is.hw.qdof.ModuleServer;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.logging.Logger;

import org.webbitserver.BaseWebSocketHandler;
import org.webbitserver.WebSocketConnection;

import com.google.gson.Gson;
import com.google.gson.JsonObject;
import com.google.gson.JsonParser;
import com.google.gson.JsonSyntaxException;
import com.google.gson.reflect.TypeToken;

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
    	//JsonMessage msg = gson.fromJson(message, JsonMessage.class);
    	JsonParser parser = new JsonParser();
    	JsonObject msg = parser.parse(message).getAsJsonObject();

    	boolean isSub = msg.get("id").getAsString().equals("sub");
		boolean isUnsub = msg.get("id").getAsString().equals("unsub");
		
		if(isSub||isUnsub && msg.get("content").isJsonArray()) {
			ArrayList<String> msgIds = (new Gson()).fromJson(msg.get("content").getAsJsonArray(), new TypeToken<List<String>>(){}.getType());
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
    	//
    	try {
    		//msg = gson.fromJson(json, JsonMessage.class);
    		JsonParser parser = new JsonParser();
    		JsonObject o = (JsonObject) parser.parse(json);
    		//
    		msgId = o.get("id").getAsString();
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