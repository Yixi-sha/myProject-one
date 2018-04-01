#ifndef YIXISER_H
#define YIXISER_H

#include <iostream>
#include <cstdio>

/*for getpid*/
#include <sys/types.h>
#include <unistd.h>

/*for ser*/
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>  
#include <termios.h>   
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
         

/*using yixi lib*/
#include "../DateStructure/Exception/Exception.h"



extern "C"
{
    int close(int fd);
    ssize_t write(int fd, const void *buf, size_t count);
    int fcntl(int fd, int cmd, ... );
    int tcgetattr(int fd, struct termios *termios_p);
    int tcsetattr(int fd, int optional_actions,    \
                     const struct termios *termios_p);
}

using namespace std;

namespace yixi
{
class yixiSer : public  Object
{
private:
    int i_ret ;

    int i_sfd;
    struct termios i_termios;
public:
    yixiSer(void) : i_ret(0)
    {
       i_sfd = open("/dev/ttySP0",O_RDWR | O_NOCTTY | O_NDELAY); 
       if(i_sfd < 0)
       {
           THROW_EXCEPTION(InvalidOperationException,"can't open /dev/ttySP0");
       }   
       /*fcntl(i_sfd, F_SETFL, 0);  */ /*set serial read don`t delay*/
    }

    void test(void)
    {
        cout << i_sfd << endl;
        this->getBAUD() ;
        this->setBAUD(B115200);
        this->getBAUD();
        ssize_t n = write(i_sfd,"yixi-sha",8);
        cout << n << endl;
    }
    
    int getBAUD(void);
    void setBAUD(int BAUD);

    ~yixiSer(void)
    {
       close(i_sfd);
    }
};


int yixiSer::getBAUD(void)
{
    i_ret = tcgetattr(i_sfd, & i_termios);
    int ret;
    if(i_ret)
    {
        THROW_EXCEPTION(InvalidOperationException,"tcgetattr fail ");
    }
    ret = i_termios.c_cflag & CBAUD ;
    switch( ret )
    {
        case B0 :
            cout << "this 0 " << endl;
            break;
        case B110 :
            cout << "this B110 " << endl;
            break;
        case B134 :
            cout << "this B134 " << endl;
            break;
        case B1200 :
            cout << "this B1200 " << endl;
            break;
        case B4800 :
            cout << "this B4800 " << endl;
            break;
        case B9600 :
            cout << "this B9600 " << endl;
            break;
        case B19200 :
            cout << "this B19200 " << endl;
            break;
        case B57600 :
            cout << "this B57600 " << endl;
            break;
        case B115200 :
            cout << "this B115200 " << endl;
            break;
        case B460800 :
            cout << "this B460800 " << endl;
            break;
        default :
            cout << "this no " << endl;
    }

    return ret;
}

void yixiSer::setBAUD(int BAUD)
{
    i_termios.c_cflag = ( (i_termios.c_cflag & BAUD ) |  BAUD );
    i_ret = tcsetattr(i_sfd, TCSANOW,&i_termios);
    if(i_ret)
    {
        THROW_EXCEPTION(InvalidOperationException,"tcsetattr fail ");  
    }
}


}

#endif