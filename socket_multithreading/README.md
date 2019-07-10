
# Sockets and Threads in C/C++ language

This is a basic implementation of sockets and threads in C/C++ language.

To compile project, in command line (linux environment), run the following commands:

Create build path:

```
cd <project_path>
mkdir build && cd build
```

Run cmake to generate makefiles annd make to compile:

```
cmake ..
make
```

There are three tests in the main file:

Step 1: Simple thread example;

Step 2: Simple socket server example, you should connect using netcat on localhost port 8888;

Step 3: Socket multithreading server, you should connect using netcat on localhost port 9999 (can accept many client connections).

Run main file:

```
cd <project_path>
./bin/<bin_file>
```

Use netcat to receive/send data to socket test (run main file before to start socket listening, you can adjust socket timeout in main file):

```
nc localhost <port>
```
