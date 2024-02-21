# Dash
Dash is an experimental and simple http server with focus on speed and the amount of queries served.

## Build
Once the project repository is cloned properly, make can be used to build the executable.

    $ cd DashServer
    $ make

An executable named ```./DashSever``` will be generated at top level of the project repository

## A basic todo :
1) Establish a connection using sockets
2) Listen to http requests
3) Parse the http request received
4) Serve the request appropriately and go back to state 2
