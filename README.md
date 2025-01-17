# Requirements

This program requires ncurses and gcc.
Please ensure these two are installed before attempting to build.

# Building

Run `make` in the root project directory.

# Running

Run `./cchat <address> <port> <username>` to start the chat client.
You *CANNOT* resize the terminal window while the chat client is running -
doing so will cause the connection to be lost.
To exit the chat, send it an interrupt signal with ctrl+c.
If the chat exits any other way
(i.e. because the terminal was resized or the connection was lost),
it may leave your terminal in an unusable state.

