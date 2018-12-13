package se.juneday;

public class JChatTest{

  public static void main(String[] args) {
    JChatMessageListener listener = new JChatMessageListener() {

        @Override
        public void onInput(String message) {
          System.out.println("\n****Received: " + message);
        }
        
      };

    
    JChat jchat = new JChat("localhost", 1066);
    System.out.println("--- JChat start");

    jchat.startChat();
    jchat.setMessageListener(listener);
    System.out.println("--- JChat started");

    try        
      {
        Thread.sleep(1000*10);
      } 
    catch(InterruptedException ex) 
      {
        Thread.currentThread().interrupt();
      }

    System.out.println("--- JChat stopping");
    jchat.stopChat();
    System.out.println("--- JChat stopped");
    System.exit(0);
  }
}
