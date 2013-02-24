package is.hw.qdof.MAVServer;

import is.hw.qdof.MAVServer.Messages.Attitude;

import java.io.IOException;
import java.lang.reflect.InvocationTargetException;
import java.util.HashMap;
import java.util.Map;

import com.google.gson.Gson;
import com.google.gson.TypeAdapter;
import com.google.gson.TypeAdapterFactory;
import com.google.gson.reflect.TypeToken;
import com.google.gson.stream.JsonReader;
import com.google.gson.stream.JsonWriter;
import com.google.protobuf.Descriptors.Descriptor;
import com.google.protobuf.Descriptors.FieldDescriptor;
import com.google.protobuf.GeneratedMessage.Builder;
import com.google.protobuf.GeneratedMessage;

public class MessageTypeFactory implements TypeAdapterFactory {
	@Override
	public <T> TypeAdapter<T> create(final Gson gson, TypeToken<T> type) {
		@SuppressWarnings("unchecked")
		Class<T> rawType = (Class<T>) type.getRawType();

		if (rawType.getSuperclass() != GeneratedMessage.class)
			return null;


		return new TypeAdapter<T>() {
			public void write(JsonWriter out, T value) throws IOException {
				GeneratedMessage msg = (GeneratedMessage) value;
				out.beginObject();
				//
				out.name("msgId");
				out.value(msg.getClass().getSimpleName());
				//
				for (Map.Entry<FieldDescriptor, Object> entry : msg.getAllFields().entrySet()) {
					out.name(entry.getKey().getName());
					out.value(gson.toJson(entry.getValue()));
				}
				//
				out.endObject();
			}

			@SuppressWarnings("unchecked")
			public T read(JsonReader reader) throws IOException {
				Object finalMessage;
				Class<?> messageClass;
				Object builder;
				Map<String, Object> jsonFields = new HashMap<>();
				//
				reader.beginObject();
				while (reader.hasNext()) {
					jsonFields.put(reader.nextName(), reader.nextString());
				}
				reader.endObject();
				// Now for the real parsing....
				// Get the message class and instanciate it!
				String msgId = jsonFields.get("msgId").toString();
				String pack = this.getClass().getPackage().getName();
				String messageClassName = pack + ".Messages$" + msgId;
				//
				try {
					messageClass = Class.forName(messageClassName);
					builder = messageClass.getMethod("newBuilder").invoke(null);
				} catch (Exception e) {
					return null;
				}
				//
				try {
					Class<?> builderClass = builder.getClass();
					//
					Descriptor msgDesc = (Descriptor) messageClass.getMethod("getDescriptor").invoke(null);
					
					for (FieldDescriptor field : msgDesc.getFields()) {
						if (jsonFields.containsKey(field.getName())) {
							Object val = jsonFields.get(field.getName());
							Class<?> castClass = (Class<?>) builderClass.getMethod("getField", FieldDescriptor.class)
																		.invoke(builder, field).getClass();
							builderClass.getMethod("setField", FieldDescriptor.class, Object.class)
										.invoke(builder, field, castClass.cast(val));
						}
					}
				} catch (Exception e) {
					e.printStackTrace();
				}
				//
				return null;
			}
		};
	}
}
