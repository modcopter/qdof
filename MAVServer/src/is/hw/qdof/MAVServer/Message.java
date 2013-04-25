package is.hw.qdof.MAVServer;

import java.io.FileNotFoundException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.lang.reflect.Type;
import java.nio.ByteBuffer;
import java.nio.charset.Charset;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Map;
import java.util.logging.Logger;

import com.google.gson.Gson;
import com.google.gson.JsonArray;
import com.google.gson.JsonElement;
import com.google.gson.JsonObject;
import com.google.gson.JsonParser;
import com.google.gson.JsonPrimitive;
import com.google.gson.JsonSerializationContext;
import com.google.gson.JsonSerializer;

public class Message {
	private int flags;
	private int id;
	private byte[] data;

	private enum States {
		STX,
		FLAG,
		ID,
		LEN,
		DATA
	}

	/**
	 * Parses a single message from an InputStream and returns it on success.
	 * 
	 * @param istream Where to read the message from
	 * @return a complete Message
	 * @throws Exception
	 */
	public static Message parse(InputStream istream) throws Exception {
		boolean cancel = false;
		States state = States.STX;
		Message currentMessage = new Message();
		int dataCounter = 0;
		//
		while (!cancel) {
			int b = istream.read();
			if (b == -1) {
				throw new Exception("End of stream reached!");
			}
			//
			switch (state) {
			case STX:
				// Parse STX
				if (b == 0x02) {
					currentMessage = new Message();
					state = States.FLAG;
					break;
				} else {
					break;
				}
			case FLAG:
				currentMessage.flags = b;
				state = States.ID;
				break;
			case ID:
				currentMessage.id = b;
				state = States.LEN;
				break;
			case LEN:
				if (b == 0) {
					currentMessage.data = null;
					return currentMessage;
				} else {
					currentMessage.data = new byte[b];
					dataCounter = 0;
				}
				//
				state = States.DATA;
				break;
			case DATA:
				currentMessage.data[dataCounter] = (byte) b;
				//
				if (dataCounter < currentMessage.data.length - 1) {
					dataCounter++;
					state = States.DATA;
					break;
				} else {
					return currentMessage;
				}
			}
		}
		//
		return null;
	}

	/**
	 * Send one message over the specified OutputStream.
	 * 
	 * @param ostream Where to send the message over
	 */
	public void send(OutputStream ostream) throws Exception {
		ostream.write(0x02);
		ostream.write(this.flags);
		ostream.write(this.id);
		//
		if (this.data == null) {
			ostream.write(0);
		} else {
			ostream.write(this.data.length);
			for (int b : this.data) {
				ostream.write(b);
			}
		}
	}
	
	public int getFlags() {
		return flags;
	}
	public void setFlags(int flags) {
		this.flags = flags;
	}
	public int getId() {
		return id;
	}
	public void setId(int id) {
		this.id = id;
	}
	public byte[] getData() {
		return data;
	}
	public void setData(byte[] data) {
		this.data = data;
	}
	
	
	
	public static class MessageDefinitionFile {	
		public Map<String, MessageDefinition> messages;
		
		public static MessageDefinitionFile load(String name) throws FileNotFoundException {
			Gson gson = new Gson();
			InputStream is = MessageDefinitionFile.class.getResourceAsStream(name);
			InputStreamReader isr = new InputStreamReader(is);
			return gson.fromJson(isr, MessageDefinitionFile.class);
		}
	}
	
	public class MessageDefinition {
		public String name;
		public ArrayList<MessageField> fields;
		
		@Override
		public String toString() {
			return "id: " + id + "; " + (fields.toString());
		}
	}
	
	public class MessageField {
		public String name;
		public String type;
	}
	
	public class MessageJsonConverter implements JsonSerializer<Message> {
		private MessageDefinitionFile definitions;
		
		public MessageJsonConverter(MessageDefinitionFile definitions) {
			this.definitions = definitions;
		}
		
		@Override
		public JsonElement serialize(Message src, Type typeOfSrc, JsonSerializationContext context) {
			JsonObject retval = new JsonObject();
			String msgId = String.valueOf(src.getId());
			ByteBuffer bb = ByteBuffer.wrap(src.getData());
			//
			retval.add("id", new JsonPrimitive(src.getId()));
			retval.add("flags", new JsonPrimitive(src.getFlags()));
			// Check if message is in current definitions file
			if ( this.definitions.messages.containsKey(msgId) ) {
				MessageDefinition msgDef = this.definitions.messages.get(msgId);
				JsonObject fields = new JsonObject();
				
				retval.add("fields", fields);
				for (MessageField field : this.definitions.messages.get(msgId).fields) {
					switch (field.type) {
					case "byte":
						int bytey = bb.get() & 0xff;							// "& 0xff" weil bytes unsigned sind. Deswegen in int speichern und maskieren
						fields.add(field.name, new JsonPrimitive(bytey));
						break;
					case "short":
						int shorty = bb.getShort() & 0xffff;					// Short sind 2 Byte, a.k.a. 4 Nibbles
						fields.add(field.name, new JsonPrimitive(shorty));
						break;
					case "int":
						long inty = bb.getInt() & 0xffffffffL;					// int sind 4 Byte
						fields.add(field.name, new JsonPrimitive(inty));
						break;
					case "string":
						// Ein String muss erst zusammengebaut werden aus den einzelnen
						// Bytes, und zwar bis ein \0 gefunden wurde.
						StringBuilder stringy = new StringBuilder();
						int b;
						while ((b = bb.get() & 0xff) != 0) {
							stringy.append((char) b);
						}
						fields.add(field.name, new JsonPrimitive(stringy.toString()));
						break;
					default:
						Logger.getLogger(this.getClass().getName()).info("Invalid field type: " + 
								field.type + " for message " +
								this.definitions.messages.get(msgId).name +
								"(" + src.getId() + ")");
					}
				}
			} else {
				JsonElement data = new Gson().toJsonTree(src.getData());
				retval.add("data", data);
			}
			//
			return retval;
		}
	}
}
