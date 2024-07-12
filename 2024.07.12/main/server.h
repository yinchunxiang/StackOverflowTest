//
// Created by Chunxiang Yin on 12/7/24.
//

#ifndef STACKOVERFLOWTEST_SERVER_H
#define STACKOVERFLOWTEST_SERVER_H
#include <iostream>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string>

class Server {
public:
    Server();
    Server(std::string ip_address,int port);
    ~Server();

    void startListen();
private:
    int m_socket;
    int port;
    std::string ip_address;
    long message_in;
    unsigned int m_socket_address_len;
    void acceptConnection(int &new_socket);
    std::string buildResponse();
    void sendResponse();
    int m_new_socket;
    std::string server_message;
    int server_start();
    void close_server();
    struct sockaddr_in m_socketAddress;
};


#endif //STACKOVERFLOWTEST_SERVER_H
