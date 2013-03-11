package is.hw.qdof.MAVServer;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.net.Socket;

import com.google.gson.Gson;
import com.google.gson.GsonBuilder;
import com.google.gson.protobuf.ProtoTypeAdapter;
import com.google.protobuf.GeneratedMessage;
import com.google.protobuf.Message;

public class ClientThread implements Runnable {
	private Socket sock;
	private TcpServer server;
	private PrintWriter writer;
	private BufferedReader reader;
	private Gson gson;
	private SerialConnection serCon;

	public ClientThread(Socket sock, TcpServer server, SerialConnection serCon) {
		this.sock = sock;
		this.server = server;
		
		gson = new GsonBuilder().registerTypeHierarchyAdapter(
			      GeneratedMessage.class, new ProtoTypeAdapter()).create();
		
		try {
			writer = new PrintWriter(sock.getOutputStream(), true);
			reader = new BufferedReader(new InputStreamReader(sock.getInputStream()));
		} catch (IOException e) {
			e.printStackTrace();
		}
		
		this.serCon = serCon;
	}
	
	@Override
	public void run() {
		while (!writer.checkError()) {
			try {
				String inJson = reader.readLine();
				//
				ProtoJsonObject pjson = gson.fromJson(inJson, ProtoJsonObject.class);
				//
				Class<?> msgClass = Class.forName(this.getClass().getPackage().getName() + ".Messages$" + pjson.msgId);
				Object message = (Message) gson.fromJson(pjson.content, msgClass);
				//
				msgClass.getMethod("writeDelimitedTo", OutputStream.class).invoke(message, serCon.getOutputStream());
				//message.writeDelimitedTo(serCon.getOutputStream());
				//
			} catch (Exception e) {
				//e.printStackTrace();
			}
		}
		//
		System.out.println("Client discon");
		server.removeThread(this);
	}
	
	public void send(String data) throws IOException {
		writer.println(data);
	}
}