/*
 * @Author: Limer
 * @Date: 2022-03-29 13:35:57
 * @LastEditors: Limer
 * @LastEditTime: 2022-04-15 16:57:00
 * @Description:
 */
#ifndef __SOCKET_H__
#define __SOCKET_H__
class InetAddress;
class Socket {
    int sockfd;

   public:
    Socket();
    Socket(int fd);
    ~Socket();
    void bind(InetAddress* addr);
    void listen();
    int accept(InetAddress* clnt_addr);
    void connect(InetAddress* serv_addr);
    int get_fd();
};

#endif