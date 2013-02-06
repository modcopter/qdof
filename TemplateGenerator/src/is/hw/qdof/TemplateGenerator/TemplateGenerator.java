package is.hw.qdof.TemplateGenerator;

import java.util.Formatter;
import java.util.HashMap;
import java.util.Map;

import org.jdom2.*;
import org.jdom2.input.SAXBuilder;

import java.io.*;

public class TemplateGenerator {
	//Der StringBuilder
	StringBuilder sb = new StringBuilder();
	
	File inputFile;
	File outputFile;
	Document xmlDoc;
	Element xmlMsgs;
	
	//Debugzähler
	int messageNum = 0;
	int fieldNum = 0;
	int arrayFieldNum = 0;
	
	HashMap<Integer, String> idName = new HashMap<Integer, String>();
	
	public static void main(String[] args) {
		new TemplateGenerator(args);
	}
	
	public TemplateGenerator(String[] fileNames) {
		
		if(fileNames.length < 1) {
			debug("Usage: <input file>");
			System.exit(1);
		}
		
		try {
			inputFile = new File(fileNames[0]);
		} catch(Exception e) {
			debug("Keine gültige MAV-Link Definition gefunden.");
			System.exit(1);
		}
		
		parseInput();
		
		makeMessageNames();
		sb.append("\r\n");
		makeMessageParams();
		
		debug(messageNum + " Nachrichten mit " + fieldNum + " Feldern verarbeitet.");
		debug(arrayFieldNum + " Array-Felder verarbeitet.");
		System.out.println(sb.toString());
	}
	
	public static void debug(String msg) {
		System.err.println(msg);
	}
	
	private void parseInput() {
		SAXBuilder b = new SAXBuilder();
		
		try {
			xmlDoc = b.build(inputFile);
		} catch (JDOMException | IOException e) {
			debug("Fehler beim Einlesen der Datei: "+e.getMessage());
			debug("Beendet.");
			System.exit(1);
		}
		
		xmlMsgs = xmlDoc.getRootElement().getChild("messages");
		
		if(xmlMsgs == null) {
			debug("Kein messages Element gefunden. Programm beendet.");
			System.exit(1);
		}
	}
	
	public void makeMessageNames() {
		Formatter f = new Formatter(sb);
		
		for(Element e: xmlMsgs.getChildren()) {
			idName.put(Integer.parseInt(e.getAttributeValue("id")), e.getAttributeValue("name"));
		}
		
		//Funktionssignatur
		f.format("std::string getMavlinkMessageName(mavlink_message_t msg) { \r\n")
		 .format("\tswitch (msg.msgid) {\r\n");
		
		for(Map.Entry<Integer, String> entry : idName.entrySet()) {
			f.format("\tcase %1$s: \r\n", entry.getKey())
			 .format("\t\treturn \"%1$s\";\r\n",entry.getValue());
		}
		
		//Schliessende Klammern
		f.format("\tdefault: \r\n\t\treturn \"UNDEFINED\";\r\n\r\n")
		 .format("\t}\r\n")
		 .format("}\r\n");
	}
	
	public void makeMessageParams() {
		Formatter f = new Formatter(sb);
		
		//Funktionssignatur, Beginn der Funktion
		f.format("Json::Value getMavlinkParams(mavlink_message_t msg) { \r\n")
		 .format("\tJson::Value content;\r\n")
		 .format("\tswitch (msg.msgid) {\r\n");
		
		//Lokale Variablen
		String msgID;
		String msgName;
		
		String fieldType;
		String fieldName;
		
		int arraySize;
		String arrayType;
		
		for(Element e: xmlMsgs.getChildren()) {
			msgID = e.getAttributeValue("id");
			msgName = e.getAttributeValue("name").toLowerCase();
			
			//Zähler hochzählen
			messageNum++;
			
			//Beginn des Case-Statements
			f.format("\tcase %1$s: {\t//%2$s\r\n", msgID, msgName);
			
			
			for(Element field: e.getChildren("field")) {
				fieldType = field.getAttributeValue("type");
				fieldName = field.getAttributeValue("name");
				
				fieldNum++;
				
				if(fieldType.endsWith("]")) { //Falls Feld ein Array ist
					arraySize = Integer.parseInt(fieldType.substring(fieldType.indexOf("[")+1).replace("]", "")); //ArrayGrösse speichern
					arrayType = fieldType.substring(0,fieldType.indexOf("[")); //Array-Typ speichern
					
					arrayFieldNum++;
					
					if(arrayType.equals("char")) { //Sonderfall für char
						f.format("\r\n\t\tchar arr_%2$s[%1$s]; ", arraySize, fieldName)
						 .format("mavlink_msg_%1$s_get_%2$s(&msg, arr_%2$s); \r\n", msgName, fieldName)
						 .format("\t\tcontent[\"%1$s\"] = std::string(arr_%1$s, %2$s);\r\n\r\n", fieldName, arraySize);
						
					} else { //Ansonsten generische Schleife
						f.format("\r\n\t\t%3$s arr_%2$s[%1$s]; ", arraySize, fieldName, arrayType)
						 .format("mavlink_msg_%1$s_get_%2$s(&msg, arr_%2$s); \r\n", msgName, fieldName)
						 .format("\t\tcontent[\"%1$s\"] = Json::Value(Json::arrayValue);\r\n\r\n", fieldName, arraySize)
						 .format("\t\tfor(%2$s i : arr_%1$s) {\r\n", fieldName, arrayType)
						 .format("\t\t\tcontent[\"%1$s\"].append(i);\r\n", fieldName)
						 .format("\t\t}\r\n");	
					}
					
				} else { //Einfache Felder
					f.format("\t\tcontent[\"%1$s\"] = mavlink_msg_%2$s_get_%1$s(&msg);\r\n", fieldName, msgName);
				}
			}
			//Ende des case-statements
			f.format("\t\tbreak;\r\n\t\t}\r\n\r\n");
		}
		
		//Ende der Funktion
		f.format("\t}\r\n");
		f.format("\treturn content;\r\n");
		f.format("}\r\n");
	}

}
