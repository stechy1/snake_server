#ifndef SNAKE_TCPSTREAM
#define SNAKE_TCPSTREAM

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string>

namespace SnakeServer {

    namespace Network {

        unsigned int const BUFFER_SIZE = 2048;

        class TCPStream {
            int m_sd;        // Socket file discriptor
            std::string m_peerIP;    // IP adresa peeru
            int m_peerPort;  // Port peeru

        public:
            friend class TCPConnection;  // Přiřazení "přátelské" třídy pro přístup k privátnímu konstruktoru

            // sd - Socket descriptor; address - reference na strukturu sockaddr_in
            TCPStream(const int t_sd, const struct sockaddr_in *t_address); // Jediný používaný konstruktor

            virtual ~TCPStream();

            // Odešle zadaný buffer do internetu
            ssize_t send();

            // Přijme data z internetu
            std::string receive();

            // Ukončí spojení s klientem
            void closeStream();

            // Getter pro IP adresu peeru
            std::string getPeerIP();

            // Getter pro Port peeru
            int getPeerPort();

        private:
            TCPStream(); // Prázdný konstruktor
            TCPStream(const TCPStream &stream); // Copy konstructor
        }; // end class

    } // end namespace Network

} // end namespace SnakeServer

#endif