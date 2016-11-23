#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <cstring>
#include <boost/uuid/uuid_io.hpp>
#include "Server.h"
#include "SimpleLogger.h"

namespace SnakeServer {
namespace Network {

Server::Server(const uint16_t t_port, const IOHandler &t_ioHandler, const uuid &t_seed)
        : m_port(t_port), m_ioHandler(t_ioHandler),
          m_streamHandler(*this, m_clients_reference), m_uuid_generator(t_seed) {
    FD_ZERO(&m_master_read_fds);
    FD_ZERO(&m_master_write_fds);
    FD_ZERO(&m_read_fds);
    FD_ZERO(&m_write_fds);

    LOG_INFO << "Server constructed.";

}

Server::~Server() {
    if (m_thread.joinable()) {
        m_thread.join();
    }

    FD_ZERO(&m_master_read_fds);

    for (auto &client : m_clients) {
        client.second->closeStream();
    }

    LOG_INFO << "Server destruct OK.";
}

void Server::init() {
    // Vytvoření nového socketu
    m_lsd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (m_lsd < 0) {
        LOG_ERROR << "Can not create new socket.";
        throw std::runtime_error("Socket() error");
    }

    int optval = 1;
    if (ioctl(m_lsd, FIONBIO, (char *) &optval) < 0) {
        close(m_lsd);
        LOG_ERROR << "Can not perform ioctl operation.";
        throw std::runtime_error("ioctl() error");
    }

    optval = 1;
    // Možnost permanentního znovupoužití stejného portu
    if (setsockopt(m_lsd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) < 0) {
        LOG_ERROR << "Can not perform setsockopt operation.";
        throw std::runtime_error("setsockopt() error");
    }

    struct ::sockaddr_in address;
    memset(&address, 0, sizeof(address));
    address.sin_family = PF_INET;
    address.sin_port = htons(m_port);
    address.sin_addr.s_addr = htonl(INADDR_ANY); // Poslouchám na jekémkoliv interfacu

    // Nabindování socketu na port
    if (bind(m_lsd, (struct sockaddr *) &address, sizeof(address)) < 0) {
        LOG_ERROR << "Can not bind socket.";
        throw std::runtime_error("bind() error");
    }

    // Otevření socketu pro poslouchání
    if (listen(m_lsd, BACKLOG) < 0) {
        LOG_ERROR << "Can not listen on socket.";
        throw std::runtime_error("listen() error");
    }

    // Nastavení FD_Setu pro server socket
    FD_SET(m_lsd, &m_master_read_fds);
    m_fdMax = m_lsd;
    m_fdMin = m_lsd;

    // Vytvoření pipy pro interní komunikaci
    if (pipe(m_pipefd) == -1) {
        LOG_ERROR << "Can not create internal pipe.";
        throw std::runtime_error("pipe() error");
    }

    // Začlenění pipy do FD setu
    FD_SET(m_pipefd[0], &m_master_read_fds);
    m_fdMax = m_pipefd[0];

    LOG_INFO << "Server initialized.";
}

void Server::start() {
    if (m_listening) {
        return;
    }
    init();

    LOG_INFO << "Starting server thread.";
    m_interupt = false;
    m_listening = true;
    m_thread = std::thread(&Server::run, this);
}

void Server::run() {
    LOG_INFO << "Server thread is running.";
    while (!m_interupt) {
        // Zkopírování seznamů se sockety
        memcpy(&m_read_fds, &m_master_read_fds, sizeof(m_master_read_fds));
        memcpy(&m_write_fds, &m_master_write_fds, sizeof(m_master_write_fds));

        if (select(m_fdMax + 1, &m_read_fds, &m_write_fds, NULL, NULL) == -1) {
            close(m_lsd);
            // Zavolat obslužný handler, který se postará o úklid
            LOG_FATAL << "Chyba v selektu";
            m_interupt = true;
            m_listening = false;
            break;
        }

        for (int i = m_fdMin; i <= m_fdMax; ++i) {
            if (FD_ISSET(i, &m_read_fds)) { // Pokud je socket[i] čtecího typu
                if (i == m_pipefd[0]) { break; };
                if (i == m_lsd) { // Pokud je socket[i] můj hlavní server socket
                    // Jsem připraven přijmout nového klienta
                    try {
                        accept();
                    } catch (std::exception ex) {
                        LOG_ERROR << "Vyskytla se chyba s připojením uživatele";
                        std::cout << ex.what() << std::endl;
                    }
                } else {
                    try {
                        // Přijímám data od klienta
                        m_clients[i]->receive();
                    } catch (std::exception ex) {
                        LOG_ERROR << "Chyba při přijímání dat od klienta";
                        std::cout << ex.what() << std::endl;
                    }
                }
            }
        }
    }
    LOG_INFO << "Server thread ended.";
}

void Server::accept() {
    if (!m_listening) {
        return;
    }

    struct sockaddr_in address;
    socklen_t len = sizeof(address);

    memset(&address, 0, sizeof(address));
    int sd = ::accept(m_lsd, (struct sockaddr *) &address, &len);
    if (sd < 0) {
        throw std::runtime_error("accept() error");
    }

    // Přidání nového klienta do mapy
    auto stream = std::make_unique<TCPStream>(sd, &address, m_streamHandler);
    auto src_uid = stream->m_peerIP + std::to_string(stream->m_peerPort);
    auto uuid = m_uuid_generator(src_uid);
    m_clients[sd] = std::move(stream);
    m_clients_reference[uuid] = sd;

    // Přidání socket descriptoru do hlavní seznamu descriptorů
    FD_SET(sd, &m_master_read_fds);
    if (sd > m_fdMax) m_fdMax = sd;
    if (sd < m_fdMin) m_fdMin = sd;
}

void Server::stop() {
    LOG_INFO << "Stoping server thread.";
    // Nastavení příznaku interupt
    m_interupt = true;
    // Zápis do interní pipy pro případné probuzení selectu
    write(m_pipefd[1], "x", 1);
}

void Server::disconnectClient(const uuid &clientID) {
    if (m_clients_reference.find(clientID) != m_clients_reference.end()) {
        auto socketID = m_clients_reference[clientID];
        m_clients[socketID]->closeStream();
        m_clients.erase(socketID);
        m_clients_reference[clientID] = -1;
        FD_CLR(socketID, &m_master_read_fds);
    }
}

void Server::sendData(const uuid &clientID, const std::string &data) {
    int uid = m_clients_reference[clientID];
    if (uid == -1)
        return;

    m_clients[uid]->send(data);
}

}
}