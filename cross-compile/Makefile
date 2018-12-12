
DEST_DIR=bin
ARM_PROG=$(DEST_DIR)/hello-arm
X86_PROG=$(DEST_DIR)/hello-x86_64
AARCH_PROG=$(DEST_DIR)/hello-aarch
RPI_PROG=$(DEST_DIR)/hello-armv7

all: $(ARM_PROG) $(RPI_PROG)

$(ARM_PROG): c/hello.c
	avr-gcc $< -o $@

$(AARCH_PROG): c/hello.c
	aarch64-linux-gnu-g++  $< -o $@

$(RPI_PROG):  c/hello.c
	arm-linux-gnu-gcc $< -o $@


clean:
	-find . -name "*~" | xargs rm -f
	-find . -name "*.o" | xargs rm -f
	-rm -fr bin/*
