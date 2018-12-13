#include <stdio.h>
#include <string.h>
#include <semaphore.h>
#include "chat.h"
#include "se_juneday_JChat.h"
#include "se_juneday_JChat_MessageListener.h"

#define DEBUG
#ifdef DEBUG
#define LOG(a) fprintf(stderr, "[%s:%d] %s\n", __FILE__, __LINE__, a);
#define FUNC_IN() fprintf(stderr,  "[%s:%d] ---> %s()\n", __FILE__, __LINE__, __func__);
#define FUNC_OUT() fprintf(stderr, "[%s:%d] <--- %s()\n", __FILE__, __LINE__, __func__);
#else
#define LOG(a) 
#define FUNC_IN() 
#define FUNC_OUT()
#endif


#define CHECK_JNI(stat, ge, gvm) \
  if (stat == JNI_EDETACHED) {                                   \
    if (gvm->AttachCurrentThread((void **) &ge, NULL) != 0) {    \
      printf("Failed to attach\n");                              \
    }                                                            \
  } else if (stat == JNI_OK) {                                   \
      ;                                                          \
  } else if (stat == JNI_EVERSION) {                             \
      printf("GetEnv: version not supported\n");                 \
  }


JavaVM * g_vm;

#define MAX_ALLOWED_CHAT_CLIENTS 10

#define GET_GLOBAL_ID() (0)

typedef struct jchat_client_ {
  chat_client cc;
  jmethodID onInput;
  jobject g_obj;
} jchat_client;

typedef struct jchat_clients_ {
  unsigned int nr_jclients;
  jchat_client jclients[MAX_ALLOWED_CHAT_CLIENTS];
} jchat_clients;

static jchat_clients clients;

#define GET_CC_PTR(idx) &(clients.jclients[idx].cc)
#define GET_CLIENT_PTR(idx) &(clients.jclients[idx])
#define GET_NEXT_IDX() (clients.nr_jclients)

#define CHECK_JNI(stat, ge, gvm) \
  if (stat == JNI_EDETACHED) {                                   \
    if (gvm->AttachCurrentThread((void **) &ge, NULL) != 0) {    \
      printf("Failed to attach\n");                              \
    }                                                            \
  } else if (stat == JNI_OK) {                                   \
      ;                                                          \
  } else if (stat == JNI_EVERSION) {                             \
      printf("GetEnv: version not supported\n");                 \
  }

static void init_next_client(void)
{
  unsigned int next = GET_NEXT_IDX();
  if (next>=MAX_ALLOWED_CHAT_CLIENTS)
    {
      return;
    }
  jchat_client* client = &(clients.jclients[next]);

  client->onInput=0;
  client->g_obj=0;
}

JNIEXPORT jint JNI_OnLoad(JavaVM* vm, void* reserved)
{
  JNIEnv* env = NULL;
  FUNC_IN();
  g_vm=vm;
  jint result;

  clients.nr_jclients = 0;
  init_next_client();
  
  result = g_vm->GetEnv((void**) &env, JNI_VERSION_1_4);
  if ( result != JNI_OK) {
    return -1;
  }

  FUNC_OUT();
  return JNI_VERSION_1_4;
}

int jchat_print_msg(const char *msg, void *ptr)
{
  JNIEnv * g_env;
  int getEnvStat = g_vm->GetEnv((void **)&g_env, JNI_VERSION_1_4);
  jchat_client* jc ;
  chat_client* cc = (chat_client*) ptr;
  int i;
  CHECK_JNI(getEnvStat, g_env, g_vm);
  FUNC_IN();

  cc = GET_CC_PTR(GET_GLOBAL_ID());

  // Associated array anyone? :)
  for (i=0; i<MAX_ALLOWED_CHAT_CLIENTS; i++)
    {
      if ( &(clients.jclients[i].cc) == cc)
        {
          fprintf(stderr, "==== FOUND AT %d\n", i);
          jc = &clients.jclients[i];
        }
    }
  void print_chat_client_info(chat_client *cc);
  print_chat_client_info(cc);

  if ( (g_env!=NULL) && (msg!=NULL) && (strlen(msg)!=0))
    {
      jstring jstrBuf = g_env->NewStringUTF(msg);
      LOG(" ---== PRINTING ==---  -------------------------");
      LOG(msg);
      fprintf (stderr, "jpm -----------------------: %d | %p | %p\n",
               0, cc, jc);
      fprintf(stderr, "onInput: %p\n", jc->onInput);
      fprintf(stderr, "g_obj:   %p\n", jc->g_obj);
      LOG("PRINTING, invoke now ----> ");
      g_env->CallVoidMethod(jc->g_obj, jc->onInput, jstrBuf);
      LOG("PRINTING, delete now ");
      g_env->DeleteLocalRef(jstrBuf); 
      LOG(" ---== PRINTING ==--- ");
    }
  else
    {
      LOG("NOT PRINTING");
    }



  FUNC_OUT();
}


JNIEXPORT void JNICALL
Java_se_juneday_JChat_setMessageListenerNative (JNIEnv *env,
                                                jobject obj,
                                                jint jid,
                                                jobject interface){
  FUNC_IN();
  int id = (int) jid;
  chat_client* cc = GET_CC_PTR(id);
  jchat_client* jc = GET_CLIENT_PTR(id);

  fprintf (stderr, "smln -----------------------: %d | %p | %p\n",
           id, cc, jc);
  fprintf (stderr, "smln -----------------------: %d | %p | %p\n",
           id, jc->onInput, jc->g_obj);

  jclass cls = env->GetObjectClass(interface);
  jc->onInput = env->GetMethodID (cls, "onInput", "(Ljava/lang/String;)V");
  jc->g_obj = obj;

  jchat_print_msg("FROM jchat.c", cc);

  fprintf (stderr, "smln -----------------------: %d | %p | %p\n",
           id, cc, jc);
  fprintf (stderr, "smln -----------------------: %d | %p | %p\n",
           id, jc->onInput, jc->g_obj);

  
  
           //  onInputEnv = env;
  //  onInputObj = obj;
  //  g_obj = obj;

  chat_set_feedback_fun(cc,
                        (input_handler)jchat_print_msg);
  
  FUNC_OUT();
  return;
}

JNIEXPORT jint JNICALL
Java_se_juneday_JChat_startChat(JNIEnv *env,
                                jobject obj,
                                jstring j_host,
                                jint j_port)
{
  jobject g_obj;
  JNIEnv * g_env;
  const char *host_name ;

  int getEnvStat;
  char tmp[10];
  int next = GET_NEXT_IDX();
  FUNC_IN();

  host_name= env->GetStringUTFChars(j_host, NULL);

  chat_client* cc = GET_CC_PTR(next);

  fprintf (stderr,"start chat %s:%d\n",
           host_name, (int)j_port);
  
  chat_init(cc,
            (char*)host_name,
            (int)j_port);
  //  chat_set_feedback_fun(&cc, jchat_print_msg);

  chat_loop(cc);
  
  if (host_name==NULL)
    {
      return -1;
    }
  LOG(host_name);

  sprintf(tmp, "%d", j_port);
  LOG(tmp);


  jint jidx = clients.nr_jclients;
  clients.nr_jclients++;

  FUNC_OUT();
  return jidx;
}

JNIEXPORT void JNICALL
Java_se_juneday_JChat_stopChatNative (JNIEnv *env,
                                      jobject obj,
                                      jint id)
{
  FUNC_IN();
  chat_client *cc = GET_CC_PTR((int)id);
  chat_close(cc);
  FUNC_OUT();
}


JNIEXPORT void JNICALL Java_se_juneday_JChat_send
(JNIEnv *, jobject, jstring) {
  fprintf(stderr, "  in c: send()");

  chat_client *cc = GET_CC_PTR((int)0);
  chat_handle_input(cc, (const char*)"from C with love");
  fprintf(stderr, "  in c: sent ... over and out");
  
}
