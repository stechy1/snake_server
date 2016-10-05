#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include "TCPAcceptor.h"

namespace SnakeServer::Network {

	TCPAcceptor::TCPAcceptor(int port, const char* address) 
    : m_lsd(0), m_port(port), m_address(address), m_listening(false) {}

	TCPAcceptor::~TCPAcceptor() {
	    if (m_lsd > 0) {
	        close(m_lsd);
	    }
	}

	int TCPAcceptor::start() {
		// Pokud už poslouchám, tak nic provádět nebudu
		if (m_listening) {
			return 0;
		}

		// Vytvoření nového socketu
		m_lsd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (m_lsd < 0) err("Socket()");

		struct sockaddr_in address;
		memset(&address, 0, sizeof(address));
		address.sin_family = PF_INET;
		address.sin_port = htons(m_port);
		address.sin_addr.s_addr = htonl(INADDR_ANY); // Poslouchám na jekémkoliv interfacu

		int optval = 1;
		// Možnost permanentního znovupoužití stejného serveru
    	setsockopt(m_lsd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof optval);

    	// Propojení adresy a socket descriptoru
    	int result = bind(m_lsd, (struct sockaddr*) &address, sizeof(address));
    	if (result < 0) {
    		perror("bind() failed");
    		return result;
    	}

    	result = listen(m_lsd, BACKLOG);
    	if (result < 0) {
    		perror("listen() failed");
    		return result;
    	}

    	m_listening = true;
    	return result;
	}

	TCPStream* TCPAcceptor::accept() {
	    if (m_listening == false) {
	        return NULL;
	    }
	 
	    struct sockaddr_in address;
	    socklen_t len = sizeof(address);
	    memset(&address, 0, sizeof(address));
	    int sd = ::accept(m_lsd, (struct sockaddr*)&address, &len);
	    if (sd < 0) {
	        perror("accept() failed");
	        return NULL;
	    }
	    
	    return new TCPStream(sd, &address);
	}
} // end namespace