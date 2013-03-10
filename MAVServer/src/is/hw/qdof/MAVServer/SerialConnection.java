package is.hw.qdof.MAVServer;

import gnu.io.CommPortIdentifier;
import gnu.io.PortInUseException;
import gnu.io.SerialPort;
import gnu.io.SerialPortEvent;
import gnu.io.SerialPortEventListener;
import gnu.io.UnsupportedCommOperationException;
import is.hw.qdof.MAVServer.Messages.Attitude;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.util.ArrayList;
import java.util.Enumeration;
import java.util.List;
import java.util.TooManyListenersException;
import java.util.logging.Logger;

import javax.xml.ws.spi.Invoker;

import com.google.gson.Gson;
import com.google.gson.GsonBuilder;
import com.google.gson.JsonObject;
import com.google.gson.protobuf.ProtoTypeAdapter;
import com.google.protobuf.DynamicMessage;
import com.google.protobuf.GeneratedMessage;

public class SerialConnection {
	private CommPortIdentifier _basePortID;
	private SerialPort _basePort;
	private int _baud;
	private TcpServer _server;
	
	public static List<String> getPorts() {
		List<String> retval = new ArrayList<String>();
		Enumeration<?> ports = CommPortIdentifier.getPortIdentifiers();
		//
		while (ports.hasMoreElements()) {
			CommPortIdentifier currentPort = (CommPortIdentifier) ports.nextElement();
			if (currentPort.getPortType() == CommPortIdentifier.PORT_SERIAL) {
				retval.add(currentPort.getName());
			}
		}
		//
		return retval;
	}
	
	public static List<CommPortIdentifier> getPortIDs() {
		List<CommPortIdentifier> retval = new ArrayList<CommPortIdentifier>();
		Enumeration<?> ports = CommPortIdentifier.getPortIdentifiers();
		//
		while (ports.hasMoreElements()) {
			CommPortIdentifier currentPort = (CommPortIdentifier) ports.nextElement();
			if (currentPort.getPortType() == CommPortIdentifier.PORT_SERIAL) {
				retval.add(currentPort);
			}
		}
		//
		return retval;
	}
	
	public SerialConnection(String portname, TcpServer server) throws IOException {
		List<CommPortIdentifier> ports = getPortIDs();
		//
		for (CommPortIdentifier id : ports) {
			if (id.getName().contentEquals(portname)) {
				_basePortID = id;
				break;
			}
		}
		//
		if (_basePortID == null)
			throw new IOException("Port " + portname + " not found!");
		//
		_server = server;
	}
	
	public void setBaudRate(int baud) throws NullPointerException {
		_baud = baud;
	}
	
	public void open() throws NullPointerException, PortInUseException, UnsupportedCommOperationException, TooManyListenersException {
		if (_basePortID == null)
			throw new NullPointerException("Port not created!");
		//
		_basePort = (SerialPort) _basePortID.open("MAVServer", 5000);
		_basePort.setSerialPortParams(_baud,
				SerialPort.DATABITS_8,
				SerialPort.STOPBITS_1,
				SerialPort.PARITY_NONE);
		//
		_basePort.setFlowControlMode(SerialPort.FLOWCONTROL_NONE);
		//
		_basePort.addEventListener(new SerialEventListener());
		_basePort.notifyOnDataAvailable(true);
	}
	
	public InputStream getInputStream() throws IOException {
		return _basePort.getInputStream();
	}
	
	public OutputStream getOutputStream() throws IOException {
		return _basePort.getOutputStream();
	}
	
	private class SerialEventListener implements SerialPortEventListener {
		private InputStream _istream;
				
		public SerialEventListener() {
			try {
				_istream = _basePort.getInputStream();
			} catch (Exception ex) {
				ex.printStackTrace();
				_basePort.removeEventListener();
				return;
			}
		}
		
		@Override
		public void serialEvent(SerialPortEvent e) {
			if (e.getEventType() != SerialPortEvent.DATA_AVAILABLE)
				return;
			//
			/*try {
				DynamicMessage msg = DynamicMessage.parseFrom(Attitude.getDescriptor(), _istream);
				//				
				Gson gson = new GsonBuilder().registerTypeHierarchyAdapter(
			      GeneratedMessage.class, new ProtoTypeAdapter()).create();
				
				JsonObject content = gson.toJsonTree(msg).getAsJsonObject();
				
				ProtoJsonObject pjo = new ProtoJsonObject();
				pjo.content = content;
				pjo.msgId = msg.getClass().getSimpleName();
				//
				String json = gson.toJson(pjo);
				_server.sendData(json);
			} catch (Exception e1) {
				e1.printStackTrace();
			}*/
			for (Class<?> subclass : Messages.class.getClasses()) {
				try {
					Method meth = subclass.getMethod("parseDelimitedFrom", InputStream.class);
					Object msg = meth.invoke(null, _istream);
					//
					if (msg == null) {
						continue;
					}
					//
					Gson gson = new GsonBuilder().registerTypeHierarchyAdapter(
							GeneratedMessage.class, new ProtoTypeAdapter()).create();
					
					JsonObject content = gson.toJsonTree(msg).getAsJsonObject();
					
					ProtoJsonObject pjo = new ProtoJsonObject();
					pjo.content = content;
					pjo.msgId = msg.getClass().getSimpleName();
					//
					String json = gson.toJson(pjo);
					_server.sendData(json);
					System.out.println(json);
				} catch (NoSuchMethodException ex) {
					// Die Klasse ist wahrscheinlich keine Message, hat kein "parseDelimitedFrom"
				} catch (IllegalAccessException | IllegalArgumentException | InvocationTargetException ex) {
					// Exceptions beim Parsen der Nachricht
				} catch (Exception ex) {
					// Etwas anderes = Unbekannt = Schlecht!
					ex.printStackTrace();
				}
			}
		}
	}
}
