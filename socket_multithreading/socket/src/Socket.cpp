#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "Debug.h"
#include "Socket.h"

// Open socket server.
Socket::Socket(string host, uint16_t port)
{
	struct sockaddr_in server_addr;
	int sockfd;
	int ret;

	this->host = host;
	this->port = port;
	this->sockfd = -1;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0)
	{
		Debug::print(Debug::CL_RED, "%s: socket error\n", __FUNCTION__);
		return;
	}

	memset(&server_addr, 0, sizeof(server_addr));

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(this->port);
	server_addr.sin_addr.s_addr = INADDR_ANY;

	ret = bind(sockfd, (const struct sockaddr *) &server_addr, sizeof(server_addr));
	if(ret < 0)
	{
		Debug::print(Debug::CL_RED, "%s: bind error\n", __FUNCTION__);
		close(sockfd);
		return;
	}

	this->sockfd = sockfd;

	// Only one connection as default.
	this->connections = 1;
}

// Close socket server.
Socket::~Socket()
{
	if(isOpened())
	{
		close(this->sockfd);
	}
}

// Returns the informed host.
string Socket::getHost()
{
	return this->host;
}

// Returns the informed port.
uint16_t Socket::getPort()
{
	return this->port;
}

// Set the client connections limit.
void Socket::setConnections(unsigned int connections)
{
	this->connections = connections;
}

// Check if the socket was opened successfully.
bool Socket::isOpened()
{
	return (this->sockfd > 0);
}

// Start a listening for new client connections.
// When a new client connect it will return a client file descriptor.
int Socket::listenConnections(size_t timeout)
{
	struct sockaddr_in client_addr;
	fd_set readfds;
	struct timeval tv;
	unsigned int client_addr_len = sizeof(client_addr);
	int ret = -1;
	int clientfd = -1;

	memset(&client_addr, 0, client_addr_len);
	memset(&tv, 0, sizeof(tv));

	tv.tv_sec = timeout;
	tv.tv_usec = 0;

	while(true)
	{
		ret = listen(this->sockfd, this->connections);
		if(ret < 0)
		{
			Debug::print(Debug::CL_RED, "%s: listen error\n", __FUNCTION__);
			break;
		}

		FD_ZERO(&readfds);
		FD_SET(this->sockfd, &readfds);

		ret = select(this->sockfd + 1, &readfds, NULL, NULL, &tv);
		if(ret < 0)
		{
			Debug::print(Debug::CL_RED, "%s: select error\n", __FUNCTION__);
			break;
		}
		else if(ret == 0)
		{
			Debug::print(Debug::CL_YELLOW, "%s: select timeout\n", __FUNCTION__);
			break;
		}

		if(FD_ISSET(this->sockfd, &readfds))
		{
			clientfd = accept(this->sockfd, (struct sockaddr *) &client_addr, &client_addr_len);
			if(clientfd < 0)
			{
				Debug::print(Debug::CL_RED, "%s: accept error\n", __FUNCTION__);
				break;
			}

			return clientfd;
		}
	}

	return ret;
}

// Closes a client connection previously opened by Socket::listenConnections().
bool Socket::closeClientConnection(int clientfd)
{
	if(clientfd > 0)
	{
		close(clientfd);
		return true;
	}

	return false;
}

// Send data to socket.
bool Socket::sendData(int clientfd, const unsigned char *data, size_t len)
{
	size_t sent = 0;
	int ret = 0;

	while(sent < len)
	{
		ret = (int) send(clientfd, (const void *) data, len, 0);
		if(ret == -1)
		{
			Debug::print(Debug::CL_RED, "%s: send error\n", __FUNCTION__);
			return false;
		}
		sent += (size_t) ret;
	}

	return (sent == len);
}

// Send data from socket.
bool Socket::receiveData(int clientfd, unsigned char *data, size_t len, size_t timeout, bool removeNewLineAtEnd)
{
	struct timeval tv;
	fd_set readclifd;
	size_t received = 0;
	int ret = 0;

	while(received < len)
	{
		FD_ZERO(&readclifd);
		FD_SET(clientfd, &readclifd);

		memset(&tv, 0, sizeof(tv));

		tv.tv_sec = timeout;
		tv.tv_usec = 0;

		ret = select(clientfd + 1, &readclifd, NULL, NULL, &tv);
		if(ret < 0)
		{
			Debug::print(Debug::CL_RED, "%s: select error\n", __FUNCTION__);
			return false;
		}
		else if(ret == 0)
		{
			Debug::print(Debug::CL_YELLOW, "%s: select timeout\n", __FUNCTION__);
			break;
		}

		ret = (int) recv(clientfd, data + received, len - received, 0);
		if(ret < 0)
		{
			Debug::print(Debug::CL_RED, "%s: recv error\n", __FUNCTION__);
			return false;
		}
		else if(ret == 0)
		{
			Debug::print(Debug::CL_YELLOW, "%s: client connnection closed\n", __FUNCTION__);
			break;
		}
		received += (size_t) ret;
	}

	// If the lasts characters are '\n' we will remove it.
	while(removeNewLineAtEnd && received && data[received - 1] == '\n')
	{
		data[received - 1] = '\0';
		received--;
	}

	return (received > 0);
}
