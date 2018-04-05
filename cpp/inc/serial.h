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
    int i_sfd;
    
    bool flagExit(int flag);
    int getflage(int mask);
    void setFlag(int mask, int flag, bool set);
public:
    yixiSer(void) 
    {
       i_sfd = open("/dev/ttySP1",O_RDWR | O_NOCTTY | O_NDELAY); 
       if(i_sfd < 0)
       {
           THROW_EXCEPTION(InvalidOperationException,"can't open /dev/ttySP0");
       }   
       fcntl(i_sfd, F_SETFL, 0);   /*set serial read do delay*/
    }

    int getBAUD(void);
    void setBAUD(int BAUD);
    int getDataBit(void);
    void setDataBit(int DataBit);
    bool isOnestopBit(void);
    void setOneStopBit(bool one);
    bool isReadlyRecv(void);
    void setReadlyRecv(bool recv);
    bool isParenb();
    void setParenb(bool par);
    bool isOddPar(void);
    void setOddpar(bool odd);

    void test(void)
    {
        char recv_buf[999];
        cout << i_sfd << endl;
        

        /*set getDataBit*/
        this->setDataBit(CS8);
        this->getDataBit();

        /*set BAUD*/
        this->setBAUD(B115200);
        this->getBAUD();

        
        this->setOneStopBit(true);

        this->setParenb(false);
        this->setReadlyRecv(true);


        cout << "read bit "<< this->isReadlyRecv() << endl;
        cout << "one stop bit "<< this->isOnestopBit() << endl;
        cout << "parority is "<< this->isParenb() << endl;
        cout << "oddParority is "<< this->isOddPar() << endl;

        ssize_t n = write(i_sfd,"yixi-sha\n",sizeof("yixi-sha\n"));
        cout << "send size id " <<n << endl;
        n = read(i_sfd, recv_buf,999);
        recv_buf[n] = '\0';
        cout << "recv_buf msg is " << recv_buf << endl;

    }
    
    ~yixiSer(void)
    {
       close(i_sfd);
    }
};

bool yixiSer::flagExit(int flag)
{
    int i_ret;
    struct termios i_termios;
    i_ret = tcgetattr(i_sfd, &i_termios);
    if(i_ret)
    {
        THROW_EXCEPTION(InvalidOperationException,"tcgetattr fail ");
    }
    return (i_termios.c_cflag & flag ? true : false);
}

void yixiSer::setFlag(int mask, int flag, bool set)
{
    int i_ret;
    struct termios i_termios;
    i_ret = tcgetattr(i_sfd, & i_termios);
    if(i_ret)
    {
        THROW_EXCEPTION(InvalidOperationException,"tcgetattr fail ");
    }
    i_termios.c_cflag &= (~mask);
    if(set)
    {
        i_termios.c_cflag |= flag;
    }
    
    i_ret = tcsetattr(i_sfd, TCSANOW,&i_termios);
    if(i_ret)
    {
        THROW_EXCEPTION(InvalidOperationException,"tcsetattr fail ");  
    } 
}

int yixiSer::getflage(int mask)
{
    int i_ret;
    struct termios i_termios;
    i_ret = tcgetattr(i_sfd, & i_termios);
    int ret = 0;
    if(i_ret)
    {
        THROW_EXCEPTION(InvalidOperationException,"tcgetattr fail ");
    }
    return ret = i_termios.c_cflag & mask;
}

int yixiSer::getBAUD(void)
{
    int ret = this->getflage(CBAUD);
    switch(ret)
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
            cout << "CBAUD no " << endl;
    }

    return ret;
}

void yixiSer::setBAUD(int BAUD)
{
    this->setFlag(CBAUD, BAUD, true);
}

int yixiSer::getDataBit(void)
{
    int ret = this->getflage(CSIZE);
    switch( ret)
    {
        case CS5 :
            cout << "this CS5 " << endl;
            break;
        case CS6 :
            cout << "this CS6 " << endl;
            break;
        case CS7 :
            cout << "this CS7 " << endl;
            break;
        case CS8 :
            cout << "this CS8 " << endl;
            break;
        default :
            cout << "CSIZE no " << endl;
    }
    return ret;
}

void yixiSer::setDataBit(int DataBit)
{
    this->setFlag(CSIZE, DataBit, true);
}

 bool yixiSer::isOnestopBit()
 {
    
    return !this->flagExit(CSTOPB);
}

void yixiSer::setOneStopBit(bool one)
{
    this->setFlag(CSTOPB, CSTOPB, !one);  
}

bool yixiSer::isReadlyRecv()
{   
    return (this->flagExit(CLOCAL | CREAD  ));
}

void yixiSer::setReadlyRecv(bool recv)
{
    this->setFlag((CREAD | CLOCAL), (CREAD | CLOCAL), recv);
}

bool yixiSer::isParenb()
{
    return this->flagExit(PARENB);
}


void yixiSer::setParenb(bool par)
{
    this->setFlag(PARENB, PARENB, par);
}

bool yixiSer::isOddPar(void)
{
    return this->flagExit(PARODD);
}

void yixiSer::setOddpar(bool odd)
{
    this->setFlag(PARODD, PARODD, odd);
}

}

#endif