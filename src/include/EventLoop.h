/*
 * @Author: Limer
 * @Date: 2022-04-03 15:11:52
 * @LastEditors: Limer
 * @LastEditTime: 2022-05-18 12:56:19
 * @Description:
 */
#ifndef __EVENTLOOP_H__
#define __EVENTLOOP_H__
#include <functional>

class Epoll;
class Channel;
class ThreadPool;

class Eventloop {
   private:
    Epoll* ep;
    bool quit;

   public:
    Eventloop();
    ~Eventloop();

    void loop();
    void updateChannel(Channel*);
};
#endif