/*
 * @Author: Limer
 * @Date: 2022-03-29 13:41:02
 * @LastEditors: Limer
 * @LastEditTime: 2022-03-29 20:57:23
 * @Description:
 */
#ifndef __INET_ADDRESS_H__
#define __INET_ADDRESS_H__
#include <arpa/inet.h>
class InetAddress {
public:
  struct sockaddr_in _addr;
  socklen_t _addr_len;

public:
  InetAddress();
  InetAddress(const char *IP, int port);
};
#endif