/*
 * @Author: Limer
 * @Date: 2022-04-06 13:46:57
 * @LastEditors: Limer
 * @LastEditTime: 2022-04-06 21:42:01
 * @Description:
 */
#ifndef __ACCEPTOR_H__
#define __ACCEPTOR_H__

#include <functional>
class Eventloop;
class InetAddress;
class Socket;
class Channel;
class Acceptor {
   private:
    Eventloop* loop;
    InetAddress* addr;
    Socket* sock;
    Channel* acptChl;
    std::function<void(Socket*)> newConnCallback;

   public:
    Acceptor(Eventloop*);
    ~Acceptor();
    void acptConn();
    void setNewConnCallback(std::function<void(Socket*)>);
};

#endif
