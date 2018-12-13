package se.juneday;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.io.IOException;
import com.sun.java.swing.plaf.gtk.GTKLookAndFeel;

public class JChatGUI {

  /* GUI components */
  private JFrame frame;
  private JTextArea messages;
  private JTextField input;
  private JScrollPane sp;

  private JChat jchat;

  MessageListener listener;
  /* Send message to server */
  private void send(String msg){
    try{
      System.out.println(msg);
      input.setText("");
       }catch(IOException e){
      System.err.println("Error writing to server: " + e);
      messages.append("\nError sending to server: " + e.getMessage());
      messages.append("\n");
      input.setText("");
    }
  }
  private void initComponents(){
    frame=new JFrame("Chat client");
    frame.setSize(400,400);
    frame.setLayout(new BorderLayout());
    frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    messages=new JTextArea();
    messages.setEditable(false);
    sp = new JScrollPane(messages);
    sp.setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_ALWAYS);
    input=new JTextField();
    /* When user hits enter, send message to server */
    input.addActionListener(new ActionListener(){
        public void actionPerformed(ActionEvent ae){
          System.out.println("Sending (from Java): " + input.getText());
          send(input.getText());
        }
      });

    //new JChatTest().main(null);
    
    System.out.println("--- JChat start");
    System.out.println("--- JChat started");
  }
  
  private void layout(){
    frame.add(sp, BorderLayout.CENTER);
    frame.add(input, BorderLayout.SOUTH);
  }
  private void show(){
    frame.setVisible(true);
  }

  public JChatGUI(){
    System.out.println(" * Creating JChatGUI *");
    ddd

      zlistener = new MessageListener() {
        @Override
        public void onInput(String message) {
          System.out.println("\n\n\n******************************************************************Received: " + message + "*******************************************************************************************************************\n\n\n");
          System.err.println("\n\n\n******************************************************************Received: " + message + "*******************************************************************************************************************\n\n\n");
          messages.append(message);
          messages.append("\n");
        }
      };
    
    try{
      UIManager.setLookAndFeel(new GTKLookAndFeel());
    }catch(Exception e){}
    initComponents();
    layout();
    show();

  }

  public void go() {
      jchat = new JChat("localhost", 1066);
      jchat.startChat();
      listener.onInput("TEST FRA SELF");
      jchat.setMessageListener(listener);
      System.out.println("setting listener");
      try        
        {
          Thread.sleep(1000);
      } 
      catch(InterruptedException ex) 
        {
          ; //Thread.currentThread().interrupt();
      }
  }  
  public static void main(String[] args){
    try {
      JChatGUI gui = new JChatGUI();
      gui.go();
      
    } catch (Throwable t) {
      t.printStackTrace();
    }
  }
  
}
