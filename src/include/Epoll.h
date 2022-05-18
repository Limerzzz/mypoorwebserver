/*
 * @Author: Limer
 * @Date: 2022-03-29 21:12:26
 * @LastEditors: Limer
 * @LastEditTime: 2022-05-18 12:40:48
 * @Description:
 */
#ifndef __EPOLL_H__
#define __EPOLL_H__
#include <string.h>
#include <sys/epoll.h>
#include <sys/types.h>
#include <unistd.h>
#include <vector>
#include "util.h"

class Channel;

enum def {
    MAX_EVENTS = 1024,
};
class Epoll {
    int epfd;
    struct epoll_event* events;

   public:
    Epoll();
    ~Epoll();
    std::vector<Channel*> poll(int);
    void updateChannel(Channel*);
    void DeleteChannel(Channel*);
};
#endif
