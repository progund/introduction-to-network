#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "chat.h"

int feedback(const char *msg)
{
  return fprintf(stdout, "\r[CHAT] %s\n", msg);
}

int main(int argc, char **argv) {
  chat_client cc;
  unsigned int port;
  int ret;

  /*
   * 
   * Rudimentary parser
   *
   */ 
  if (argc < 3)
    {
      fprintf(stderr,"Usage:\n");
      fprintf(stderr,"  %s <hostname> <port>\n", argv[0]);
      return 1;
    }
  /* turn port number into an (unsigned) int */
  if (sscanf(argv[2], "%ud", &port)!=1)
    {
      fprintf(stderr,"invalid port: %s\n", argv[2]);
      return 2;
    }

  /*
   * Init chat client values
   */
  ret = chat_init(&cc, argv[1], port);
  if (ret!=CHAT_CLIENT_OK)
    {
      fprintf(stderr, "Failed initialising the client\n");
      return 1;
    }
  
  /*
   * Use our own feedback function
   */
  chat_set_feedback_fun(&cc, feedback);
  
  /*
   * Enter chat - loop until bye or quit
   */
  chat_loop(&cc);
  if (ret!=CHAT_CLIENT_OK)
    {
      fprintf(stderr, "Failed initialising the client\n");
      return 1;
    }

  /*
   * Close the chat client
   */
  chat_close(&cc);
  
  return 0;
}
