#include "TCPStream.h"

namespace SnakeServer::Network {
	TCPStream::TCPStream() {}
	TCPStream::TCPStream() {}

	TCPStream::TCPStream(int sd, struct sockaddr_in* address) : msd(sd) {
	    char ip[50];
	    inet_ntop(PF_INET, (struct in_addr*)&(address->sin_addr.s_addr), 
	              ip, sizeof(ip)-1);
	    m_peerIP = ip;
	    m_peerPort = ntohs(address->sin_port);
	}

	TCPStream::~TCPStream() {
	    close(m_sd);
	}

	string TCPStream::getPeerIP( void ) {
		return m_peerIP;
	}

	int TCPStream::getPeerPort( void ) {
		return m_peerPort;
	}
} // end namespace