package se.juneday;


public class JChat{

  private String hostname;
  private int port;
  private int id;
  private JChatMessageListener listener;
  
  static {
    System.loadLibrary("chat");
  }

  public JChat (String hostname, int port) {
    this.hostname = hostname;
    this.port = port;
  }

  public void setMessageListener(JChatMessageListener listener) {
    setMessageListenerNative(this.id, listener);
  }
    
  public native void
    setMessageListenerNative(int id, JChatMessageListener listener);
    
  private native int
    startChat(String hostname,
              int port);
  
  public void startChat() {
    id = startChat(hostname, port);
  }

  public void stopChat() {
    stopChatNative(id);
  }

  public native void send(String msg);

  public native void stopChatNative(int id) ;
  
}
