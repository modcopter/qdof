package is.hw.qdof.MAVServer;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.ArrayList;
import java.util.List;
import java.util.logging.Logger;

public class TcpServer {
	private ServerSocket serverSock;
	private volatile List<ClientThread> clientList = new ArrayList<ClientThread>();
	
	private SerialConnection serCon;
	
	public TcpServer(int port) {
		try {
			serverSock = new ServerSocket(port);
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	
	public void startServer() throws IOException {
		while (true) {
			Socket clientSock = serverSock.accept();
			Logger.getLogger(this.getClass().getName()).info("Client " + clientSock.getRemoteSocketAddress().toString() + " connected!");
			ClientThread thread = new ClientThread(clientSock, this, serCon);
			clientList.add(thread);
			thread.run();
		}
	}
	
	public void sendData(String data) {
		for (ClientThread thr : clientList) {
			try {
				thr.send(data);
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
	}
	
	public void setSerialConnection(SerialConnection sercon) {
		this.serCon = sercon;
	}
	
	protected void removeThread(ClientThread thr) {
		clientList.remove(thr);
	}
}
