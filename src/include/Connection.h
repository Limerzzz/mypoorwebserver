/*
 * @Author: Limer
 * @Date: 2022-04-07 21:49:36
 * @LastEditors: Limer
 * @LastEditTime: 2022-04-11 13:32:22
 * @Description:
 */
#ifndef __CONNECTION_H__
#define __CONNECTION_H__

#include <functional>
class Eventloop;
class InetAddress;
class Socket;
class Channel;
class Buffer;
class Connection {
   private:
    Eventloop* loop;
    Socket* sock;
    Channel* connChl;
    Buffer* readbuf;
    std::function<void(Socket*)> deleteConnectionCallback;

   public:
    Connection(Eventloop*, Socket*);
    ~Connection();
    void echo(int);
    void setDeleteConnectionCallback(std::function<void(Socket*)>);
};
#endif