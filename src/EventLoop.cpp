/*
 * @Author: Limer
 * @Date: 2022-04-03 15:35:16
 * @LastEditors: Limer
 * @LastEditTime: 2022-05-18 12:57:08
 * @Description:
 */
#include "EventLoop.h"
#include <vector>
#include "Channel.h"
#include "Epoll.h"
#include "ThreadPool.h"

Eventloop::Eventloop() : ep(nullptr), quit(false) { ep = new Epoll(); }

Eventloop::~Eventloop() { delete ep; }

void Eventloop::loop() {
    while (!quit) {
        std::vector<Channel*> chs;
        chs = ep->poll(-1);
        for (auto it : chs) {
            it->handleEvent();
        }
    }
}

void Eventloop::updateChannel(Channel* ch) { ep->updateChannel(ch); }
