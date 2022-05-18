/*
 * @Author: Limer
 * @Date: 2022-03-31 15:56:04
 * @LastEditors: Limer
 * @LastEditTime: 2022-05-18 12:31:29
 * @Description:
 * Channel类作为一个中间层连接fd和Eventpoll，fd上有对应事件发生执行Channel设定的callback函数。
 */
#include <sys/epoll.h>
#include <functional>

class Eventloop;
class Channel {
   private:
    Eventloop* _loop;
    int fd;
    uint32_t events;
    uint32_t revents;
    bool inEpoll;
    std::function<void()> read_callback;
    std::function<void()> write_callback;

   public:
    Channel(Eventloop*, int);
    ~Channel();

    void enableReading();
    void handleEvent();

    int getFd();
    uint32_t getEvents();
    void setEvents(uint32_t);
    uint32_t getRevents();
    void setRevents(uint32_t);
    bool getInEpoll();
    void setInEpoll(bool);
    void setReadCallback(std::function<void()>);
    void useET();
};
