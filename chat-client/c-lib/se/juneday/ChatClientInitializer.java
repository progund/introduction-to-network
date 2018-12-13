package org.henrikard.chat.client;

import org.henrikard.chat.client.ChatGUI;

import java.io.*;
import java.net.Socket;
/**
 * @author Rikard
 * <p>
 * Simple chat client with a Swing GUI and a
 * thread (instance of Runnable) that listens on
 * server messages and updates the textarea of the
 * chat client.
 * </p>
 * <p>
 * This class represents the chat client network functionality.
 * When instantiated, the client connects to the server
 * and creates and launches the GUI. The GUI will have
 * a reference to this chat client network object.
 * </p>
 */

public class ChatClientInitializer{
    
  /*
   * Hard coded server and port values.
   * These could optionally be passed as arguments to main
   * and forwarded here via the constructor.
   */
  private static final String SERVER="127.0.0.1";
  private static final int PORT=1066;
  private Socket socket;
  public Socket getSocket(){
    return socket;
  }
  private void connect() throws IOException{
    try{
      socket=new Socket(SERVER,PORT);
    }catch(IOException e){
      System.err.println("Error connecting: " +e);
      throw new IOException("Couldn't connect to the server", e);
    }
  }
  /**
   * This constructor creates the initializer for the
   * chat client and sets up the connection to the server.
   * @throws IOException if the connection to the server fails
   */
  public ChatClientInitializer() throws IOException{
    connect();
    new Thread(new ChatGUI(this)).start();
  }    
}
