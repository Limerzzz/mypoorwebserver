/*
 * @Author: Limer
 * @Date: 2022-04-03 15:49:40
 * @LastEditors: Limer
 * @LastEditTime: 2022-04-28 22:24:39
 * @Description:
 */
#ifndef __SERVER_H__
#define __SERVER_H__
#include <unordered_map>
#include <vector>
class Eventloop;
class Socket;
class Acceptor;
class Connection;
class ThreadPool;

class Server {
   private:
    Eventloop* mainReactor;
    Acceptor* acpt;
    std::unordered_map<int, Connection*> conns;
    std::vector<Eventloop*> subReactors;
    ThreadPool* thpool;

   public:
    Server(Eventloop*);
    ~Server();

    void newConnection(Socket*);
    void deleteConnection(Socket*);
};
#endif