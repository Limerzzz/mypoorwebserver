/*
 * @Author: Limer
 * @Date: 2022-03-29 22:02:54
 * @LastEditors: Limer
 * @LastEditTime: 2022-05-17 22:09:18
 * @Description:
 */
#include "Server.h"
#include <iostream>
#include "Acceptor.h"
#include "Channel.h"
#include "Connection.h"
#include "EventLoop.h"
#include "InetAddress.h"
#include "Socket.h"

int main() {
    Eventloop* loop = new Eventloop();
    Server* server = new Server(loop);
    server->OnConnect([](Connection* conn) {
        conn->Read();
        if (conn->getState() == Connection::State::Closed) {
            conn->Close();
            return;
        }
        std::cout << "Message from client" << conn->getSocket() << std::endl;
        conn->setSendBuf(conn->ReadBuf());
        conn->Write();
    });
    loop->loop();
    delete server;
    delete loop;
    return 0;
}