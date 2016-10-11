#include "TCPStream.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <iostream>

namespace SnakeServer {

	namespace Network {

		TCPStream::TCPStream() {}

		TCPStream::TCPStream(int sd, struct sockaddr_in* address) : _sd(sd) {
		    char ip[50];
		    inet_ntop(PF_INET, (struct in_addr*)&(address->sin_addr.s_addr), ip, sizeof(ip)-1);
		    _peerIP = ip;
		    _peerPort = ntohs(address->sin_port);
		}

		TCPStream::~TCPStream() {
		    close(_sd);
		}

		ssize_t TCPStream::receive(char* buffer, size_t len) {
			char tmp[2048];
		    ssize_t received = recv(_sd, tmp, 2048 - 1, 0);

		    if (received == -1) {
		    	printf("Ups on socket: %i\n", _sd);
		    	exit(1);
		    }

		    std::cout << "Received: " << tmp << std::endl;

		    return 0;
		}

		std::string TCPStream::getPeerIP() {
			return _peerIP;
		}

		int TCPStream::getPeerPort() {
			return _peerPort;
		}

	} // endnamespace Network

} // end namespace SnakeServer