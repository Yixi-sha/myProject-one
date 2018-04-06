#ifndef YIXIRTP_H
#define YIXIRTP_H

#include <iostream>
#include <cstdio>

/*for getpid*/
#include <sys/types.h>
#include <unistd.h>

/*for socket*/
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>

#include <strings.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <arpa/inet.h>

#include <sys/socket.h>
#include <netinet/in.h> 
#include <arpa/inet.h>   
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
          

/*using yixi lib*/
#include "../../DateStructure/Exception/Exception.h"


#define UDP_port 3333 

extern "C"
{
	pid_t getpid(void);  
	int socket(int domain, int type, int protocol);
   	void *memset(void *s, int c, size_t n);
    int close(int fd);
    int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
    uint16_t htons(uint16_t hostshort);
    int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
    ssize_t recvfrom(int sockfd, void *buf, size_t len, int flags,struct sockaddr *src_addr, \
      socklen_t *addrlen);
    ssize_t sendto(int sockfd, const void *buf, size_t len, int flags, \
      const struct sockaddr *dest_addr, socklen_t addrlen);
    ssize_t recvfrom(int sockfd, void *buf, size_t len, int flags,\
      struct sockaddr *src_addr, socklen_t *addrlen);

}

using namespace std;

namespace yixi
{
class yixiRtp : public  Object
{
private:
    /*define send socket type*/
    int i_send_socket_fd;
    struct sockaddr_in i_send_UDP_stuct;
    in_addr_t i_send_addr;

    /*define reicev socket type*/
    int i_receive_socket_fd;
    struct sockaddr_in i_receive_UDP_stuct;
    
    /*RTP head*/
    char *i_RTPhead;

public:
    yixiRtp(void)
    {
        int ret = 0;
        i_receive_socket_fd = socket(AF_INET, SOCK_DGRAM, 0);
        if(i_receive_socket_fd == -1)
        {
            THROW_EXCEPTION(InvalidOperationException,"create socket fail!\n");
        }

        i_receive_UDP_stuct.sin_family = AF_INET;
        i_receive_UDP_stuct.sin_port = htons(UDP_port);
        i_receive_UDP_stuct.sin_addr.s_addr = INADDR_ANY;

        memset(i_receive_UDP_stuct.sin_zero, 0, 8);
        ret = bind(i_receive_socket_fd, reinterpret_cast<struct sockaddr*>(&i_receive_UDP_stuct), \
          sizeof(sockaddr));
        
        if(ret == -1)
        {
            THROW_EXCEPTION(InvalidOperationException,"bind socket fail!\n");
        }
    }

    void test(void)
    {
        cout << getpid() << endl;
    }
    /*data send function*/
    int receivr_thread(sockaddr_in *i_client_UDP_stuct, char* reice_buf, int len);
    int send_thread(sockaddr_in *i_client_UDP_stuct, char* reice_buf, int len);
    virtual ~yixiRtp(void)
    {
        close(i_receive_socket_fd);
    }
};

int yixiRtp::receivr_thread(sockaddr_in *i_client_UDP_stuct, char* reice_buf, int len)
{

    int addr_len = sizeof(struct sockaddr);
    int receive_len = recvfrom(i_receive_socket_fd, reice_buf, len, 0, \
      reinterpret_cast<struct sockaddr*>(i_client_UDP_stuct),reinterpret_cast<socklen_t *>(&addr_len));
    if(receive_len > 0)
    {
        reice_buf[receive_len] = '\0';
    } 
    return receive_len;                   
}

int yixiRtp::send_thread(sockaddr_in *i_client_UDP_stuct, char* send_buf, int len)
{
      return sendto(i_receive_socket_fd, send_buf, len, 0, \
          reinterpret_cast<struct sockaddr*>(i_client_UDP_stuct), sizeof(struct sockaddr)); 
}



}

#endif