#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

#include "Thread.h"
#include "Mutex.h"
#include "Socket.h"
#include "Debug.h"

#include <vector>

using namespace std;

// Signal finish action.
static bool glbToFinish = false;

// ---------------------------
// Threads test...
// ---------------------------

// Thread callback variable counter.
static unsigned int glbCounter = 0;

// Thread callback args.
struct thread_args
{
	unsigned int id;
	unsigned int font_color;
	unsigned int counter_limit;
};

// Generetes a randomic number between two integers.
int rand_interval(int min, int max)
{
	return ((rand() % (max - min + 1)) + min);
}

// Thread callback function.
void *task(void *arg)
{
	struct thread_args *ta = (struct thread_args *) arg;
	bool loop_continue = true;
	unsigned int rand_num = 0;

	Debug::print((Debug::Colors) ta->font_color, "Printing msg from %s function running on thread id %u...\n", __FUNCTION__, ta->id);

	while(loop_continue)
	{
		rand_num = rand_interval(100000, 900000);
		usleep(rand_num);

		if(glbToFinish)
		{
			Debug::print((Debug::Colors) ta->font_color, "Finish request received, stopping thread id %u...\n", ta->id);
			return (void *) strdup("Finish request received, stopping and returnning from task.");
		}

		Mutex::lock();

		if(glbCounter <= ta->counter_limit)
		{
			Debug::print((Debug::Colors) ta->font_color, "Thread id: %u -> counter %04u -> rand: %06u\n", ta->id, glbCounter, rand_num);
			glbCounter++;
		}
		else
		{
			Debug::print((Debug::Colors) ta->font_color, "Stopping thread id %u...\n", ta->id);
			loop_continue = false;
		}

		Mutex::unlock();
	}

	return (void *) strdup("Returning msg from task.");
}

void threadTest()
{
	Thread *task1;
	Thread *task2;
	Thread *task3;
	struct thread_args ta1;
	struct thread_args ta2;
	struct thread_args ta3;
	bool start1;
	bool start2;
	bool start3;

	Debug::print(Debug::CL_NORMAL, "Starting thread tests...\n");

	ta1 = {1, (unsigned int) Debug::CL_MAGENTA, 10};
	ta2 = {2, (unsigned int) Debug::CL_BLUE,    15};
	ta3 = {3, (unsigned int) Debug::CL_GREEN,   15};

	task1 = new Thread();
	task2 = new Thread();
	task3 = new Thread();

	if(!Mutex::init())
	{
		Debug::print(Debug::CL_NORMAL, "Mutex init error!\n");
	}

	start1 = task1->create(task, (void *) &ta1);
	start2 = task2->create(task, (void *) &ta2);
	start3 = task3->create(task, (void *) &ta3);

	Debug::print(Debug::CL_NORMAL, "Thread id %u %s%s\n", ta1.id, start1 ? "started" : "error", "!");
	Debug::print(Debug::CL_NORMAL, "Thread id %u %s%s\n", ta2.id, start2 ? "started" : "error", "!");
	Debug::print(Debug::CL_NORMAL, "Thread id %u %s%s\n", ta3.id, start3 ? "started" : "error", "!");

	if(start1 && task1->join() && !task1->wasCanceled())
	{
		Debug::print(Debug::CL_NORMAL, "Thread id %u joined -> retval %s\n", ta1.id, (const char *) task1->getRetval());
		free(task1->getRetval());
	}
	else
	{
		Debug::print(Debug::CL_NORMAL, "Thread id %u join error", ta1.id);
	}

	if(start2 && task2->join() && !task2->wasCanceled())
	{
		Debug::print(Debug::CL_NORMAL, "Thread id %u joined -> retval %s\n", ta2.id, (const char *) task2->getRetval());
		free(task2->getRetval());
	}
	else
	{
		Debug::print(Debug::CL_NORMAL, "Thread id %u join error", ta2.id);
	}

	if(start3 && task3->join() && !task3->wasCanceled())
	{
		Debug::print(Debug::CL_NORMAL, "Thread id %u joined -> retval %s\n", ta3.id, (const char *) task3->getRetval());
		free(task3->getRetval());
	}
	else
	{
		Debug::print(Debug::CL_NORMAL, "Thread id %u join error", ta3.id);
	}

	if(!Mutex::destroy())
	{
		Debug::print(Debug::CL_NORMAL, "Mutex destroy error!\n");
	}

	Debug::print(Debug::CL_NORMAL, "Done!\n");

	if(task1)
	{
		delete task1;
	}

	if(task2)
	{
		delete task2;
	}

	if(task3)
	{
		delete task3;
	}
}

// ---------------------------
// Socket test...
// ---------------------------

#define HOST "127.0.0.1"
#define PORT 8888

void socketTest()
{
	Socket *sock;
	int clientfd;
	const size_t timeout_sec = 10;
	string toSend;
	unsigned char toReceive[128];

	Debug::print(Debug::CL_NORMAL, "Starting socket tests...\n");

	sock = new Socket(HOST, (uint16_t) PORT);
	toSend = "Hello, I'm the socket server!";

	if(sock->isOpened())
	{
		Debug::print(Debug::CL_NORMAL, "Start listening...\n");
		clientfd = sock->listenConnections(timeout_sec);
		if(clientfd > 0)
		{
			Debug::print(Debug::CL_NORMAL, "New client connection...\n");

			// Sending data...
			if(Socket::sendData(clientfd, (const unsigned char *) toSend.c_str(), toSend.length()))
			{
				Debug::print(Debug::CL_NORMAL, "Data sent\n");
			}

			// Sending new line...
			if(Socket::sendData(clientfd, (const unsigned char *) "\n", 1))
			{
				Debug::print(Debug::CL_NORMAL, "Newline sent\n");
			}

			// Receiving response...
			if(Socket::receiveData(clientfd, toReceive, sizeof(toReceive), timeout_sec, true))
			{
				Debug::print(Debug::CL_NORMAL, "Socket client response: [%s]\n", toReceive);
			}

			Debug::print(Debug::CL_NORMAL, "Closing client connection...\n");
			Socket::closeClientConnection(clientfd);
		}
	}

	Debug::print(Debug::CL_NORMAL, "Done!\n");

	delete sock;
}

// ---------------------------
// Socket with threads test...
// ---------------------------

#define PORT_MT 9999

// Socket multithreading data sctructure.
struct socket_multithreading
{
	Thread *task;
	int client_id;
	int client_fd;
	string toSend;
	unsigned char toReceive[128];
	size_t timeoutSec;
	bool started;
	bool finished;
};

void *task_socket_multithreading(void *arg)
{
	struct socket_multithreading *conn = (struct socket_multithreading *) arg;

	Debug::print(Debug::CL_NORMAL, "New client connection | id [%d]...\n", conn->client_id);

	// Sending data...
	if(Socket::sendData(conn->client_fd, (const unsigned char *) conn->toSend.c_str(), conn->toSend.length()))
	{
		Debug::print(Debug::CL_NORMAL, "Data sent | id [%d]\n", conn->client_id);
	}

	// Sending new line...
	if(Socket::sendData(conn->client_fd, (const unsigned char *) "\n", 1))
	{
		Debug::print(Debug::CL_NORMAL, "Newline sent | id [%d]\n", conn->client_id);
	}

	// Receiving response...
	if(Socket::receiveData(conn->client_fd, conn->toReceive, sizeof(conn->toReceive), conn->timeoutSec, true))
	{
		Debug::print(Debug::CL_NORMAL, "Socket client response: [%s] | id [%d]\n", conn->toReceive, conn->client_id);
	}

	Debug::print(Debug::CL_NORMAL, "Closing client connection | id [%d]...\n", conn->client_id);
	Socket::closeClientConnection(conn->client_fd);

	conn->finished = true;

	return NULL;
}

void socketMultiThreadingTest()
{
	Socket *sock;
	int clientfd;
	const size_t timeout_sec = 5;
	int counter_cli_conn = 0;

	// Socket multithreading connections list.
	vector<struct socket_multithreading *> client_connections;

	Debug::print(Debug::CL_NORMAL, "Starting socket multithreading tests...\n");

	sock = new Socket(HOST, (uint16_t) PORT_MT);

	if(sock->isOpened())
	{
		Debug::print(Debug::CL_NORMAL, "Start socket multithreading listening...\n");
		sock->setConnections(5);
		while(true)
		{
			// We only go to listen connections when signal is not received.
			if(!glbToFinish)
			{
				clientfd = sock->listenConnections(timeout_sec);
				if(clientfd > 0)
				{
					struct socket_multithreading *newConn = new (struct socket_multithreading);

					newConn->task = new Thread();
					newConn->client_id = counter_cli_conn;
					newConn->client_fd = clientfd;
					newConn->toSend = "Hello, I'm the socket server!";
					newConn->toReceive[0] = '\0';
					newConn->timeoutSec = timeout_sec;
					newConn->started = false;
					newConn->finished = false;

					if(newConn->task->create(task_socket_multithreading, (void *) newConn))
					{
						Debug::print(Debug::CL_NORMAL, "New connection accepted and started!\n");

						newConn->started = true;
						client_connections.push_back(newConn);
						counter_cli_conn++;
					}
				}
			}

			for(unsigned int i = 0; i < client_connections.size(); i++)
			{
				struct socket_multithreading *conn = client_connections[i];
				bool toCleanMemory = false;

				if(conn->task)
				{
					if(!glbToFinish)
					{
						// Only join thread when it was terminated (to not block loop).
						if(conn->started && conn->finished && !conn->task->wasCanceled())
						{
							conn->task->join();
							toCleanMemory = true;
						}
					}
					else
					{
						// Waits for thread join (block loop until thread finish).
						if(conn->started)
						{
							conn->task->join();
							toCleanMemory = true;
						}
					}

					if(toCleanMemory)
					{
						delete conn->task;
						delete conn;
						client_connections.erase(client_connections.begin() + i);
					}
				}
				else
				{
					// Lets go to remove empty task from vector.
					client_connections.erase(client_connections.begin() + i);
				}
			}

			if(glbToFinish && client_connections.size() == 0)
			{
				break;
			}
		}
	}

	Debug::print(Debug::CL_NORMAL, "Done!\n");

	delete sock;
}

void handle_signal(int signal)
{
	if(signal == SIGINT)
	{
		Debug::print(Debug::CL_NORMAL, "\nInterrupt signal received, stopping app...\n");
		glbToFinish = true;
	}
}

int main(int argc, char *argv[])
{
	signal(SIGINT, handle_signal);

	if(!glbToFinish) threadTest();
	if(!glbToFinish) socketTest();
	if(!glbToFinish) socketMultiThreadingTest();

	return (int) (glbToFinish);
}
