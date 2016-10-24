#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <cstring>
#include "TCPConnection.h"

namespace SnakeServer {
namespace Network {

TCPConnection::TCPConnection(IOHandler &t_ioHandler) : m_ioHandler(t_ioHandler) {}

TCPConnection::~TCPConnection() {}

void TCPConnection::init() {
    if (m_listening) {
        return;
    }

    // Vytvoření nového socketu
    m_lsd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (m_lsd < 0) {
        throw std::runtime_error("Socket() error");
    }

    int optval = 1;
    if (ioctl(m_lsd, FIONBIO, (char *) &optval) < 0) {
        close(m_lsd);
        throw std::runtime_error("ioctl() error");
    }

    optval = 1;
    // Možnost permanentního znovupoužití stejného portu
    setsockopt(m_lsd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));

    struct ::sockaddr_in address;
    memset(&address, 0, sizeof(address));
    address.sin_family = PF_INET;
    address.sin_port = htons(m_port);
    address.sin_addr.s_addr = htonl(INADDR_ANY); // Poslouchám na jekémkoliv interfacu

    // Nabindování socketu na port
    if (bind(m_lsd, (struct sockaddr *) &address, sizeof(address)) < 0) {
        throw std::runtime_error("bind() error");
    }

    // Otevření socketu pro poslouchání
    if (listen(m_lsd, BACKLOG) < 0) {
        throw std::runtime_error("listen() error");
    }

    // Nastavení FD_Setu pro server socket
    FD_SET(m_lsd, &m_master_read_fds);
    m_fdMax = m_lsd;
    m_fdMin = m_lsd;

    // Vytvoření pipy pro interní komunikaci
    if (pipe(m_pipefd) == -1) {
        throw std::runtime_error("pipe() error");
    }

    // Začlenění pipy do FD setu
    FD_SET(m_pipefd[0], &m_master_read_fds);
    m_fdMax = m_pipefd[0];

    m_listening = true;
}

void TCPConnection::start() {
    if (m_interupt || !m_listening) {
        return;
    }

    m_interupt = false;
    m_thread = std::thread(&TCPConnection::run, this);
}

void TCPConnection::run() {
    while(!m_interupt) {
        // Zkopírování seznamů se sockety
        memcpy(&m_read_fds, &m_master_read_fds, sizeof(m_master_read_fds));
        memcpy(&m_write_fds, &m_master_write_fds, sizeof(m_master_write_fds));

        if (select(m_fdMax + 1, &m_read_fds, &m_write_fds, NULL, NULL) == -1) {
            close(m_lsd);
            // Zavolad obslužný handler, který se postará o úklid
            m_interupt = true;
            m_listening = false;
            break;
        }

        for(int i = m_fdMin; i < m_fdMax; ++i) {
            if (FD_ISSET(i, &m_read_fds)) { // Pokud je socket[i] čtecího typu
                if (i == m_pipefd[0]) {break;};
                if (i == m_lsd) { // Pokud je socket[i] můj hlavní server socket
                    // Jsem připraven přijmout nového klienta
                    try {
                        accept();
                    } catch (std::exception ex) {
                        std::cout << "Vyskytla se chyba s připojením uživatele" << std::endl;
                    }
                } else {
                    try {
                        // Přijímám data od klienta
                        m_clients[i]->receive();
                    } catch (std::exception ex) {
                        std::cout << "Chyba při přijímání dat od klienta" << std::endl;
                    }
                }
            }
            if (FD_ISSET(i, &m_write_fds)) {
                // Posílám data klientovi
                unsigned long sended = m_clients[i]->send();
                // TODO odebrat socket z FD_SETu pro zápis pouze, pokud už není více věcí k zápisu
            }
        }
    }
}

void TCPConnection::accept() {
    if (!m_listening) {
        return;
    }

    struct sockaddr_in address;
    socklen_t len = sizeof(address);

    memset(&address, 0, sizeof(address));
    int sd = ::accept(m_lsd, (struct sockaddr *) &address, &len);
    if (sd < 0) {
        throw std::runtime_error("accepf() error");
    }

    // Přidání nového klienta do mapy
    m_clients[sd] = std::make_unique<TCPStream>(sd, &address, *this);

    // Přidání socket descriptoru do hlavní seznamu descriptorů
    FD_SET(sd, &m_master_read_fds);
    if (sd > m_fdMax) m_fdMax = sd;
    if (sd < m_fdMin) m_fdMin = sd;
}

void TCPConnection::stop() {
    // Nastavení příznaku interupt
    m_interupt = true;
    // Zápis do interní pipy pro případné probuzení selectu
    write(m_pipefd[1], "x", 1);
}

void TCPConnection::disconnectClient(int socketID) {
    if (m_clients.find(socketID) != m_clients.end()) {
        m_clients[socketID]->closeStream();
        m_clients.erase(socketID);
    }
}

void TCPConnection::onDataReceived(int socketID, std::list<std::string> data) {
    // TODO implementovat handler onDataReceived
    m_ioHandler.onDataReceived(socketID, data);
}

void TCPConnection::onLostConnection(int socketID) {
    // TODO implementovat handler onLostConection
}

void TCPConnection::onDisconnect(int socketID) {
    // TODO implementovat handler onDisconnect
    FD_CLR(socketID, &m_master_read_fds);
    FD_CLR(socketID, &m_master_write_fds);
    m_ioHandler.onDisconnect(socketID);
}

void TCPConnection::onRestoreConnection(int socketID) {
    // TODO implementovat handler onRestoreConnection
}

void TCPConnection::sendData(int socketID, std::string data) {
    m_clients[socketID]->prepareDataToSend(data);
    FD_SET(socketID, &m_master_write_fds);
    // TODO inkerementovat ve své struktuře counter představující počet dat k odeslání
}

}
}