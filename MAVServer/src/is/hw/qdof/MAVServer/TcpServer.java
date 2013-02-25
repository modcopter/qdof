package is.hw.qdof.MAVServer;

import java.io.IOException;
import java.net.ServerSocket;

public class TcpServer {
	private ServerSocket serverSock;
	
	public TcpServer(int port) {
		try {
			serverSock = new ServerSocket(port);
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	
	public void run() {
		
	}
	
	private class MainListenThread implements Runnable {
		@Override
		public void run() {
			
		}
	}
}
