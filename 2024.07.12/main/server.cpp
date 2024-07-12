//
// Created by Chunxiang Yin on 12/7/24.
//

#include "server.h"

#include <sstream>
#include <unistd.h>

using namespace std;

const int BUFFER_SIZE = 30720;

Server::Server(std::string ip_address,int port)
{
    this->ip_address = ip_address;
    this->port = port;
    this->m_socket_address_len = sizeof(m_socketAddress);
    this->server_message = buildResponse();
    int x = server_start();
    if (1 == x) cout << "construct server failed";
}

Server::Server()
{
}

Server::~Server()
{
}

int Server::server_start()
{
    m_socket = socket(AF_INET, SOCK_STREAM, 0);
    if(m_socket < 0)
    {
        return 1;
    }
    m_socketAddress.sin_family = AF_INET;
    m_socketAddress.sin_port = htons(port);
    m_socketAddress.sin_addr.s_addr = inet_addr(ip_address.c_str());
    if (bind(m_socket,(sockaddr *)&m_socketAddress, m_socket_address_len) < 0)
    {
        return 1;
    }
    return 0;
}
void Server :: close_server()
{
    close(m_socket);
    exit(0);
}

void Server :: startListen()
{
    if(listen(m_socket,20)<0)
    {
        cout << "Connection Failed" << endl;
    }
    cout  << "\n*** Listening on ADDRESS: " << inet_ntoa(m_socketAddress.sin_addr) << " PORT: " << ntohs(m_socketAddress.sin_port) << " ***\n\n";
    int bytesReceived;

    while (true)
    {
        cout << " Waiting for a new connection " << endl;
        acceptConnection(m_new_socket);

        char buffer[BUFFER_SIZE] = {0};
        bytesReceived = read(m_new_socket, buffer, BUFFER_SIZE);
        if (bytesReceived < 0)
        {
            cout << "Failed to read bytes from client socket connection" << endl;
        }
        cout << " Received Request from client " << endl;
        sendResponse();
        close(m_new_socket);
    }
}

std::string Server :: buildResponse()
{
    std::string htmlFile = "<!DOCTYPE html><html lang=\"en\"><body><h1> HOME </h1><p> Hello from your Server :) </p></body></html>";
    std::ostringstream ss;
    ss << "HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: " << htmlFile.size() << "\n\n"
       << htmlFile;

    return ss.str();
}

void Server :: acceptConnection (int &new_socket)
{
    new_socket = accept(m_socket, (sockaddr *)&m_socketAddress, &m_socket_address_len);
}

void Server :: sendResponse()
{
    long bytesSent;

    bytesSent = write(m_new_socket, server_message.c_str(), server_message.size());
    if (bytesSent == server_message.size())
    {
        cout << "Server responded to client" << endl;
    }
}

int main()
{
    //http_server = Server();
    Server server = Server("127.0.0.1",80);
    //  bind(server.m_socket, server.ip_address, sizeof())
    server.startListen();
    return 0;
}
