package is.hw.qdof.MAVServer;

import gnu.io.CommPortIdentifier;

import java.util.Enumeration;

public class Controller {
	public static void main(String args[]) {
		Enumeration<?> comPorts;
		CommPortIdentifier currentIdent;
		//
		comPorts = CommPortIdentifier.getPortIdentifiers();
		//
		while (comPorts.hasMoreElements()) {
			currentIdent = (CommPortIdentifier) comPorts.nextElement();
			//
			if(currentIdent.getPortType() == CommPortIdentifier.PORT_SERIAL) {
				System.out.println(currentIdent.getName());
	    	}
		}
	}
}
