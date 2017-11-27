# Chat client written in C

## Server

We have written a chat server in Java. You can find it here: [https://github.com/progund/java-extra-lectures/tree/master/networking/chat](https://github.com/progund/java-extra-lectures/tree/master/networking/chat)

## Client

The client consists of a c file, `chat.c`, and a coresponding header
file, `chat.h` which implements most of the chat client stuff. See the
API below. The file `chat_main.c` is, as is suggested by the name, a c
file with a main function using the chat API.

### Chat API

See the header file `chat.h` for a description of the API.

## Build instructions

`gcc chat.c chat_main.c -o chat`

or

`make` - if you have make installed

## Execute instruction

`./chat localhost 1066 `

or

`make run` - if you have make installed




