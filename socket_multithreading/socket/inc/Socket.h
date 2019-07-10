#ifndef SOCKET_H_
#define SOCKET_H_

#include <string>
#include <stdint.h>

using namespace std;

class Socket
{
private:
	string host;
	uint16_t port;
	int sockfd;
	unsigned int connections;

public:
	Socket(string host, uint16_t port);
	~Socket();

	string getHost();
	uint16_t getPort();
	void setConnections(unsigned int connections);
	bool isOpened();
	int listenConnections(size_t timeout);
	static bool closeClientConnection(int clientfd);
	static bool sendData(int clientfd, const unsigned char *data, size_t len);
	static bool receiveData(int clientfd, unsigned char *data, size_t len, size_t timeout, bool removeNewLineAtEnd = false);
};

#endif
