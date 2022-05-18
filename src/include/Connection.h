/*
 * @Author: Limer
 * @Date: 2022-04-07 21:49:36
 * @LastEditors: Limer
 * @LastEditTime: 2022-05-17 13:38:10
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
   public:
    enum State { Invalid = 1, Handshaking, Connected, Closed, Failed };
    Connection(Eventloop*, Socket*);
    ~Connection();
    void Read();
    void Write();
    State getState();
    void Close();
    Socket* getSocket();

    // buffer
    void setSendBuf(const char*);
    Buffer* getReadBuf();
    const char* ReadBuf();
    Buffer* getSendBuf();
    const char* SendBuf();
    void getLienSendBuf();

    void echo(int);
    void setDeleteConnectionCallback(std::function<void(Socket*)>);
    void setOnConnectCallback(std::function<void(Connection*)>);

   private:
    Eventloop* loop;
    Socket* sock;
    Channel* connChl;
    Buffer* readBuf;
    Buffer* sendBuf;
    State sta;
    std::function<void(Socket*)> deleteConnectionCallback;
    std::function<void(Connection*)> on_conn_cb_;

    void readNonBlocking();
    void writeNonBlocking();
    void readBlocking();
    void writeBlocking();
};
#endif