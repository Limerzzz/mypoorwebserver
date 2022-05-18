/*
 * @Author: Limer
 * @Date: 2022-04-08 13:12:07
 * @LastEditors: Limer
 * @LastEditTime: 2022-05-18 12:36:44
 * @Description:
 */
#include "Connection.h"
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cassert>
#include "Buffer.h"
#include "Channel.h"
#include "EventLoop.h"
#include "Socket.h"

#define READ_BUF_SIZE 1024
Connection::Connection(Eventloop* _loop, Socket* _sock)
    : loop(_loop), sock(_sock) {
    if (_loop != nullptr) {
        connChl = new Channel(loop, sock->get_fd());
        connChl->enableReading();
        connChl->useET();
    }
    readBuf = new Buffer();
    sendBuf = new Buffer();
    sta = State::Connected;
}

Connection::~Connection() {
    if (loop != nullptr) delete connChl;
    delete sock;
    delete readBuf;
    delete sendBuf;
}

void Connection::Read() {
    assert(sta == State::Connected);
    readBuf->clear();
    if (sock->isNonblocking())
        readNonBlocking();
    else
        readBlocking();
}
void Connection::Write() {
    assert(sta == State::Connected);
    if (sock->isNonblocking())
        writeNonBlocking();
    else
        writeBlocking();
    sendBuf->clear();
}

void Connection::readNonBlocking() {
    int sockfd = sock->get_fd();
    char buf[1024];  // 这个buf大小无所谓
    while (
        true) {  // 使用非阻塞IO，读取客户端buffer，一次读取buf大小数据，直到全部读取完毕
        memset(buf, 0, sizeof(buf));
        ssize_t bytes_read = read(sockfd, buf, sizeof(buf));
        if (bytes_read > 0) {
            readBuf->append(buf, bytes_read);
        } else if (bytes_read == -1 &&
                   errno == EINTR) {  // 程序正常中断、继续读取
            printf("continue reading\n");
            continue;
        } else if (bytes_read == -1 &&
                   ((errno == EAGAIN) ||
                    (errno ==
                     EWOULDBLOCK))) {  // 非阻塞IO，这个条件表示数据全部读取完毕
            break;
        } else if (bytes_read == 0) {  // EOF，客户端断开连接
            printf("read EOF, client fd %d disconnected\n", sockfd);
            sta = State::Closed;
            break;
        } else {
            printf("Other error on client fd %d\n", sockfd);
            sta = State::Closed;
            break;
        }
    }
}

void Connection::writeNonBlocking() {
    int sockfd = sock->get_fd();
    char buf[sendBuf->size()];
    memcpy(buf, sendBuf->c_str(), sendBuf->size());
    int dataSize = sendBuf->size();
    int dataLeft = dataSize;
    while (dataLeft > 0) {
        ssize_t bytesWrite = write(sockfd, buf + dataSize - dataLeft, dataLeft);
        if (bytesWrite == -1 && errno == EINTR) {
            ::printf("continue writing \n");
            continue;
        }
        if (bytesWrite == -1 && errno == EAGAIN) {
            break;
        }
        if (bytesWrite == -1) {
            ::printf("Other error on client fd %d\n", sockfd);
            sta = State::Closed;
            break;
        }
        dataLeft -= bytesWrite;
    }
}
void Connection::readBlocking() {
    int sockfd = sock->get_fd();
    ssize_t rcvSize = 0;
    socklen_t len = sizeof(rcvSize);
    getsockopt(sockfd, SOL_SOCKET, SO_RCVBUF, &rcvSize, &len);
    char buf[rcvSize];
    ssize_t byteRead = read(sockfd, buf, sizeof(buf));
    if (byteRead > 0) {
        readBuf->append(buf, byteRead);
    } else if (byteRead == 0) {
        printf("read EOF, blocking client  fd %d disconnected.\n", sockfd);
        sta = State::Closed;
    } else if (byteRead == -1) {
        printf("Other error on blocking client fd %d\n", sockfd);
        sta = State::Closed;
    }
}

void Connection::writeBlocking() {
    // ! there could be a bug here, if the size of 'sendBuf' outweight size of
    // ! buffer of TCP.
    int sockfd = sock->get_fd();
    ssize_t bytewrite = write(sockfd, sendBuf->c_str(), sendBuf->size());
    if (bytewrite == -1) {
        printf("Other error on blocking client fd %d\n", sockfd);
        sta = State::Closed;
    }
}

void Connection::Close() { deleteConnectionCallback(sock); }
void Connection::setDeleteConnectionCallback(std::function<void(Socket*)> _cb) {
    deleteConnectionCallback = _cb;
}
void Connection::setOnConnectCallback(std::function<void(Connection*)> cb) {
    on_conn_cb_ = cb;
    connChl->setReadCallback([this]() { on_conn_cb_(this); });
}

Connection::State Connection::getState() { return sta; }
void Connection::setSendBuf(const char* str) { sendBuf->setBuf(str); }
Buffer* Connection::getReadBuf() { return readBuf; }
const char* Connection::ReadBuf() { return readBuf->c_str(); }
Buffer* Connection::getSendBuf() { return sendBuf; }
const char* Connection::SendBuf() { return sendBuf->c_str(); }
void Connection::getLienSendBuf() { sendBuf->getline(); }
Socket* Connection::getSocket() { return sock; }