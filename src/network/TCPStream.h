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
            int _sd;        // Socket file discriptor
            std::string _peerIP;    // IP adresa peeru
            int _peerPort;  // Port peeru

        public:
            friend class TCPAcceptor;  // Přiřazení "přátelské" třídy pro přístup k privátnímu konstruktoru
            //friend class TCPConnector; // Přiřazení "přátelské" třídy pro přístup k privátnímu konstruktoru

            virtual ~TCPStream();

            // Odešle zadaný buffer do internetu
            //int send(char *buffer, size_t len);

            // Přijme data z internetu
            std::string receive();

            // Ukončí spojení s klientem
            void closeStream();

            // Getter pro IP adresu peeru
            std::string getPeerIP();

            // Getter pro Port peeru
            int getPeerPort();

        private:
            // sd - Socket descriptor; address - reference na strukturu sockaddr_in
            TCPStream(int t_sd, struct sockaddr_in *t_address); // Jediný používaný konstruktor
            TCPStream(); // Prázdný konstruktor
            TCPStream(const TCPStream &stream); // Copy konstructor
        }; // end class

    } // end namespace Network

} // end namespace SnakeServer

#endif