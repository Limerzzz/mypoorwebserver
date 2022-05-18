/*
 * @Author: Limer
 * @Date: 2022-04-03 15:53:26
 * @LastEditors: Limer
 * @LastEditTime: 2022-05-18 13:03:26
 * @Description:
 */
#include "Server.h"
#include <strings.h>
#include <unistd.h>
#include <cerrno>
#include <cstdio>
#include <functional>
#include <thread>
#include "Acceptor.h"
#include "Channel.h"
#include "Connection.h"
#include "EventLoop.h"
#include "Socket.h"
#include "ThreadPool.h"
#include "util.h"

#define READ_BUFF_SIZE 1024

Server::Server(Eventloop* lp) : mainReactor(lp), acpt(nullptr) {
    acpt = new Acceptor(mainReactor);
    std::function<void(Socket*)> cb =
        std::bind(&Server::newConnection, this, std::placeholders::_1);
    acpt->setNewConnCallback(cb);

    int size = std::thread::hardware_concurrency();
    thpool = new ThreadPool(size);
    for (int i = 0; i < size; ++i) {
        subReactors.push_back(new Eventloop());
    }

    for (int i = 0; i < size; ++i) {
        std::function<void()> sub_loop =
            // ? why is there a '&';
            std::bind(&Eventloop::loop, subReactors[i]);
        thpool->add(sub_loop);
    }
}

Server::~Server() {
    delete acpt;
    delete thpool;
}

void Server::newConnection(Socket* sock) {
    errif(sock->get_fd() == -1, "new connection error!");
    uint64_t random = sock->get_fd() % subReactors.size();
    Connection* conn = new Connection(subReactors[random], sock);
    std::function<void(Socket*)> cb =
        std::bind(&Server::deleteConnection, this, std::placeholders::_1);
    conn->setDeleteConnectionCallback(cb);
    conn->setOnConnectCallback(on_connect_callback_);
    conns[sock->get_fd()] = conn;
}

void Server::deleteConnection(Socket* sock) {
    int sockfd = sock->get_fd();
    auto it = conns.find(sockfd);
    if (it != conns.end()) {
        Connection* conn = conns[sock->get_fd()];
        conns.erase(sock->get_fd());
        delete conn;
        conn = nullptr;
    }
}

void Server::OnConnect(std::function<void(Connection*)> cb) {
    on_connect_callback_ = cb;
}