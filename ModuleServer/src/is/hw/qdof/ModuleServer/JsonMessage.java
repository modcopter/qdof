package is.hw.qdof.ModuleServer;

public class JsonMessage {
    /**
     * Die ID der Nachricht um die es geht
     */
    String msgId;

    /**
     * Der Inhalt der Nachricht. Kann verschiedene Typen annehmen: Bei "sub" und
     * "unsub" ist es eine ArrayList\<String\>, sonst ist es eine Map<String, Object>
     */
    Object content;
}
