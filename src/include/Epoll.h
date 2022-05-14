/*
 * @Author: Limer
 * @Date: 2022-03-29 21:12:26
 * @LastEditors: Limer
 * @LastEditTime: 2022-04-01 13:15:46
 * @Description:
 */
#ifndef __EPOLL_H__
#define __EPOLL_H__
#include "util.h"
#include <string.h>
#include <sys/epoll.h>
#include <sys/types.h>
#include <unistd.h>
#include <vector>

class Channel;

enum def {
  MAX_EVENTS = 1024,
};
class Epoll {
  int epfd;
  struct epoll_event *events;

public:
  Epoll();
  ~Epoll();
  void addFd(int, uint32_t);
  std::vector<Channel *> poll(int);
  void updateChannel(Channel *);
};
#endif
