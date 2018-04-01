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
#include "../DateStructure/Exception/Exception.h"


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

    unsigned int sleep(unsigned int seconds);
    pid_t fork(void);
    void exit(int status);
}

using namespace std;

namespace yixi
{
class xiyiRtp : public  Object
{
private:
    /*define send socket type*/
    int i_send_socket_fd;
    struct sockaddr_in i_send_UDP_stuct;
    in_addr_t i_send_addr;

    /*define reicev socket type*/
    int i_receive_socket_fd;
    struct sockaddr_in i_receive_UDP_stuct;
    struct sockaddr_in i_client_UDP_stuct;
    char reice_buf[999];
    
    /*RTP head*/
    char *i_RTPhead;

public:
    xiyiRtp(void)
    {
        i_RTPhead = reinterpret_cast<char*>(malloc(sizeof(char) * 12));
        if(i_RTPhead == NULL)
        {
            THROW_EXCEPTION(NoEnoughMemoryException,"NoEnoughMemoryException to creat i_RTPhead");
        }
        setV(2);

    }

    void test(void)
    {
        cout << getpid() << endl;
    }

    void setV(int v);

    /*data send function*/
    void send_thread();
    void receivr_thread();
    virtual ~xiyiRtp(void)
    {
        free(i_RTPhead);
    }
};


void xiyiRtp::setV(int v)
{
    if((v >= 0) && (v <= 2))
        {
            char i_v = i_RTPhead[0];
            if(v == 0)
            {
                i_v &= (0x3f);
            }
            else if(v == 1)
            {
                i_v = (i_v & (0x3f)) | (0x40);
            }
            else if(v == 2)
            {
                i_v = (i_v & (0x3f)) | (0x80);
            }
        }
        else 
        {
            THROW_EXCEPTION(InvalidOperationException,"setV V is invail operation ");
        }
}

void xiyiRtp::send_thread()
{
    int ret = 0;
    char recv_buf[99];
    /*construct socket*/
    i_send_socket_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if(i_send_socket_fd == -1)
    {
        THROW_EXCEPTION(InvalidOperationException,"create socket fail!\n");
    }

    /*set zero to sockaddr of i_send_UDP_stuct*/
    memset(i_receive_UDP_stuct.sin_zero, 0, 8);
    i_send_addr = inet_addr("192.168.0.149");

    i_send_UDP_stuct.sin_port = htons(UDP_port);
    i_send_UDP_stuct.sin_addr.s_addr = i_send_addr;
    i_send_UDP_stuct.sin_family = AF_INET;

    ret = connect(i_send_socket_fd, reinterpret_cast<struct sockaddr*>(&i_send_UDP_stuct), \
      sizeof(sockaddr));
    if(ret == -1)
    {
        THROW_EXCEPTION(InvalidOperationException,"connect socket fail!\n");
    }

    send(i_send_socket_fd, "yixi-sha",8,0);

    socklen_t addr_len = sizeof(struct sockaddr);
    ssize_t recv_count =  recvfrom(i_send_socket_fd, recv_buf, 99, 0,
      reinterpret_cast<struct sockaddr*>(&i_send_UDP_stuct), &addr_len); 

	if(recv_count > 0)
	{
		recv_buf[recv_count] = '\0';
		printf("recv : %s \n",recv_buf);
	}


    close(i_send_socket_fd);
}
void xiyiRtp::receivr_thread()
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

    while(1)
    {
        int addr_len = sizeof(struct sockaddr);
        int receive_len = recvfrom(i_receive_socket_fd, reice_buf, 999, 0, \
          reinterpret_cast<struct sockaddr*>(&i_client_UDP_stuct),reinterpret_cast<socklen_t *>(&addr_len));

        if(receive_len > 0)
        {
            reice_buf[receive_len] = '\0';
            cout << "Msg from " << inet_ntoa(i_client_UDP_stuct.sin_addr) << " " << reice_buf <<endl ;
        
            int childpPid = fork();
            if(childpPid == 0)
            {
                sleep(5);
                char test_buf[] = "I`m test";
                sendto(i_receive_socket_fd, test_buf, sizeof(test_buf), 0, \
                  reinterpret_cast<struct sockaddr*>(&i_client_UDP_stuct), sizeof(struct sockaddr)); 
                exit(0);
            }
            

        }
    } 

    close(i_receive_socket_fd);

}


}

#endif