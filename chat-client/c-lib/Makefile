UNAME := $(shell uname -s)
MK_FILE=missing
ifeq ($(UNAME), Linux)
  MK_FILE=mk/linux.mk
endif
ifeq ($(UNAME), Darwin)
  MK_FILE=mk/macos.mk
endif
ifeq ($(UNAME), CYGWIN_NT_5.1)
  MK_FILE=mk/linux.cygwin
endif
ifeq ($(UNAME), CYGWIN_NT-10.0)
  MK_FILE=mk/cygwin.mk
endif
ifeq ($(MK_FILE), missing)
  $(error OS "$(UNAME)" not supported, we are sorry)
else
  include $(MK_FILE)
endif

CHAT_LIB=c/libchat.so
CHAT_TEST_PROG=c/chat_main
JNI_PATH=$(JDK_INC_DIR)/..

JCHAT_CLASS=se/juneday/JChat.class 
JCHAT_SOURCE=${JCHAT_CLASS:%.class=%.java}

JCHAT_GUI_CLASS=se/juneday/JChatGui
JCHAT_TEST=se/juneday/JChatTest

CFLAGS=-pedantic -Wconversion -Wall -Werror -Wextra 

info:
	echo $(JDKS_DIR)
	echo $(JDK_JNI_H)
	echo $(JDK_INC_DIR)

all: java $(CHAT_LIB)

java: $(JCHAT_CLASS)

java-test: $(JCHAT_CLASS) $(JCHAT_TEST).class
	java -Djava.library.path=c $(JCHAT_TEST)

gui: $(JCHAT_CLASS) $(JCHAT_GUI_CLASS).class
	@echo Starting gui
	java -Djava.library.path=c $(JCHAT_GUI_CLASS)

jni:
	javah -cp . -d c se.juneday.JChat
	javah -cp . -d c se.juneday.JChatMessageListener

$(CHAT_LIB): c/jchat.c
	g++ -DDEBUG -shared -fPIC -I$(JNI_PATH)/include -I$(JNI_PATH)/include/linux c/chat.c c/jchat.c -o $(CHAT_LIB)

lib: $(CHAT_LIB)

%.class:%.java
	javac $<

clean:
	-rm *.o *.so c/*.so c/*.o $(CLASSES)
	-find . -name "*~" | xargs rm
	-rm se/juneday/*.class

$(CHAT_TEST_PROG): $(CHAT_LIB) 
	gcc $(CFLAGS) -L./c/ -lchat c/chat_main.c -o $(CHAT_TEST_PROG) -lpthread -lchat

