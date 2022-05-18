/*
 * @Author: Limer
 * @Date: 2022-04-04 15:08:19
 * @LastEditors: Limer
 * @LastEditTime: 2022-05-17 13:20:43
 * @Description:
 */
#include "Socket.h"
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include "InetAddress.h"
#include "util.h"

Socket::Socket() {
    sockfd = ::socket(AF_INET, SOCK_STREAM, 0);
    errif(sockfd == -1, "fail to create a sockfd!");
}
Socket::Socket(int fd) : sockfd(fd) {}
Socket::~Socket() { ::close(sockfd); }

void Socket::bind(InetAddress* addr) {
    int ret = ::bind(sockfd, (sockaddr*)&addr->_addr, addr->_addr_len);
    errif(ret == -1, "fail to bind sockaddr!\n");
}

void Socket::listen() {
    int ret = ::listen(sockfd, SOMAXCONN);
    errif(ret == -1, "fail to listen socketfd!\n");
}

int Socket::accept(InetAddress* clnt_addr) {
    int new_fd =
        ::accept(sockfd, (sockaddr*)&clnt_addr->_addr, &clnt_addr->_addr_len);
    errif(new_fd == -1, "fail to accept new sockfd");
    return new_fd;
}

void Socket::connect(InetAddress* serv_addr) {
    int ret =
        ::connect(sockfd, (sockaddr*)&serv_addr->_addr, serv_addr->_addr_len);
    errif(ret == -1, "fail to connect the server!");
}

int Socket::get_fd() { return sockfd; }

bool Socket::isNonblocking() {
    int oldOpt = fcntl(sockfd, F_GETFL);
    return (oldOpt & O_NONBLOCK) > 0;
}