/*
 * @Author: Limer
 * @Date: 2022-03-29 22:02:54
 * @LastEditors: Limer
 * @LastEditTime: 2022-04-06 21:48:41
 * @Description:
 */
#include "Server.h"
#include "Acceptor.h"
#include "Channel.h"
#include "EventLoop.h"
#include "InetAddress.h"
#include "Socket.h"

int main() {
    Eventloop* loop = new Eventloop();
    Server* server = new Server(loop);
    loop->loop();
    delete server;
    delete loop;
    return 0;
}