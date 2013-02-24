package is.hw.qdof.MAVServer;

import gnu.io.CommPortIdentifier;
import gnu.io.PortInUseException;
import gnu.io.SerialPort;
import gnu.io.SerialPortEvent;
import gnu.io.SerialPortEventListener;
import gnu.io.UnsupportedCommOperationException;
import is.hw.qdof.MAVServer.Messages.Attitude;
import is.hw.qdof.MAVServer.Messages.AttitudeOrBuilder;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.ArrayList;
import java.util.Enumeration;
import java.util.List;
import java.util.TooManyListenersException;

import com.google.gson.Gson;
import com.google.gson.GsonBuilder;
import com.google.protobuf.GeneratedMessage;
import com.google.protobuf.MessageOrBuilder;

public class SerialConnection {
	private CommPortIdentifier _basePortID;
	private SerialPort _basePort;
	private int _baud;
	
	public static List<String> getPorts() {
		List<String> retval = new ArrayList<>();
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
		List<CommPortIdentifier> retval = new ArrayList<>();
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
	
	public SerialConnection(String portname) throws IOException {
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
			try {
				Attitude att = Attitude.parseDelimitedFrom(_istream);
				//
				Gson gson = new GsonBuilder()
								.registerTypeAdapterFactory(new MessageTypeFactory())
								.create();
				//
				//System.out.println(gson.toJson(att));
				//
				gson.fromJson(gson.toJson(att), Attitude.class);
			} catch (Exception e1) {
				e1.printStackTrace();
			}
		}
	}
}
