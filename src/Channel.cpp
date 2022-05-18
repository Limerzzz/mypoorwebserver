/*
 * @Author: Limer
 * @Date: 2022-03-31 16:30:04
 * @LastEditors: Limer
 * @LastEditTime: 2022-05-17 12:59:19
 * @Description:
 */
#include "Channel.h"
#include <unistd.h>
#include "EventLoop.h"

Channel::Channel(Eventloop* lp, int _fd)
    : _loop(lp), fd(_fd), events(0), revents(0), inEpoll(false) {}

Channel::~Channel() {
    if (fd != -1) {
        close(fd);
        fd = -1;
    }
}

void Channel::enableReading() {
    events |= EPOLLIN | EPOLLPRI;
    _loop->updateChannel(this);
}
void Channel::useET() {
    events |= EPOLLET;
    _loop->updateChannel(this);
}

int Channel::getFd() { return fd; }

uint32_t Channel::getEvents() { return events; }
uint32_t Channel::getRevents() { return revents; }
void Channel::setEvents(uint32_t evnts) { events = evnts; }
void Channel::setRevents(uint32_t revnts) { revents = revnts; }
bool Channel::getInEpoll() { return inEpoll; }
void Channel::setInEpoll(bool inep) { inEpoll = inep; }

void Channel::setReadCallback(std::function<void()> _cb) {
    read_callback = _cb;
}

void Channel::handleEvent() {
    if (revents & (EPOLLIN | EPOLLPRI)) {
        read_callback();
    }
    if (revents & EPOLLOUT) {
        write_callback();
    }
}