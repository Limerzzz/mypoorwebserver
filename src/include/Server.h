/*
 * @Author: Limer
 * @Date: 2022-04-03 15:49:40
 * @LastEditors: Limer
 * @LastEditTime: 2022-05-16 13:24:41
 * @Description:
 */
#ifndef __SERVER_H__
#define __SERVER_H__
#include <functional>
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
    std::function<void(Connection*)> on_connect_callback_;

   public:
    explicit Server(Eventloop*);
    ~Server();

    void newConnection(Socket*);
    void deleteConnection(Socket*);
    void OnConnect(std::function<void(Connection*)> cb);
};
#endif