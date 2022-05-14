/*
 * @Author: Limer
 * @Date: 2022-03-29 13:49:36
 * @LastEditors: Limer
 * @LastEditTime: 2022-03-29 21:40:15
 * @Description: 
 */
#ifndef __UTIL_H__
#define __UTIL_H__
#include <fcntl.h>
void errif(bool condition, const char*);
int setnonblocking(int fd);
#endif