CC=gcc
JDKS_DIR=$(shell find /usr/lib/jvm/* -prune -type d) 
JDK_JNI_H=$(shell find $(JDKS_DIR) -name "jni.h" | tail -1)
JDK_INC_DIR=$(shell dirname $(JDK_JNI_H) )
JDK_C_FLAGS="-I\"$JDK_INC_DIR\" -I\"$JDK_INC_DIR/linux\"  "
JDK_LD_FLAGS=" -shared -fPIC -o c/liblove.so"
JDK_LIB_DIR=$(shell dirname $(find $(JDK_INC_DIR)/../ -name "libjvm.so"))
