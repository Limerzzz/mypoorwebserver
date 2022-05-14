/*
 * @Author: Limer
 * @Date: 2022-03-27 16:27:28
 * @LastEditors: Limer
 * @LastEditTime: 2022-04-25 22:06:50
 * @Description:
 */
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cerrno>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "Buffer.h"
#include "InetAddress.h"
#include "Socket.h"
#include "util.h"

int main(int argc, char** argv) {
    int ret = -1;
    Socket* sock = new Socket();
    InetAddress* serv_addr = new InetAddress("127.0.0.1", 8888);
    sock->connect(serv_addr);
    int sockfd = sock->get_fd();
    setnonblocking(sockfd);
    Buffer* writebuf = new Buffer();
    Buffer* readbuf = new Buffer();
    while (1) {
        writebuf->getline();
        ssize_t writebytes = write(sockfd, writebuf->c_str(), writebuf->size());
        if (writebytes == -1) {
            printf("socket already disconnected, can't write any more!\n");
            break;
        }
        int count = 0;
        char buf[1024];  //这个buf大小无所谓
        fflush(stdout);
        while (true) {
            bzero(&buf, sizeof(buf));
            ssize_t read_bytes = read(sockfd, buf, sizeof(buf));
            if (read_bytes > 0) {
                readbuf->append(buf, read_bytes);
            } else if (read_bytes == 0) {  // EOF
                printf("server disconnected!\n");
                exit(EXIT_SUCCESS);
            } else if (read_bytes == -1 && errno == EAGAIN) {
                printf("count: %d, message from server: %s\n", readbuf->size(),
                       readbuf->c_str());
                break;
            }
        }
        readbuf->clear();
        writebuf->clear();
    }
    delete sock;
    delete serv_addr;
    delete writebuf;
    delete readbuf;
    return 0;
}
