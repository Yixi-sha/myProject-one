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
#include "../../DateStructure/Exception/Exception.h"


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

    enum flag_enum  
    {
        c_cflag,
        c_lflag,
        c_iflag,
        c_oflag,
    };
    int i_sfd;
    
    bool flagExit(int flag,flag_enum c_flag);
    int getflage(flag_enum flag);
    void setFlag(int mask, int flag, bool set,flag_enum e_flag);
    void close_ser()
    {
        close(i_sfd);
    }
    void open_ser()
    {
        i_sfd = open("/dev/ttySP1",O_RDWR | O_NOCTTY | O_NDELAY); 
        if(i_sfd < 0)
       {
           THROW_EXCEPTION(InvalidOperationException,"can't open /dev/ttySP0");
       } 
    }

public:
    yixiSer(void) 
    {
        open_ser();
        fcntl(i_sfd, F_SETFL, 0);   /*set serial read do delay*/
        setFlag((IXON | IXOFF | IXANY), (IXON | IXOFF | IXANY), false, c_iflag);
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

    bool isOriginModel();
    void setOriginModel(bool set);
    bool isStandardModel();
    void setStandardModel(bool set);

    bool isOriginOutput();
    void setOriginOutput(bool set);

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
        this->setOriginModel(true);
        this->setReadlyRecv(true);

        this->setOriginOutput(true);


        cout << "read bit "<< this->isReadlyRecv() << endl;
        cout << "one stop bit "<< this->isOnestopBit() << endl;
        cout << "parority is "<< this->isParenb() << endl;
        cout << "oddParority is "<< this->isOddPar() << endl;
        cout << "is origin  "<< this->isOriginModel() << endl;
        cout << "is origin output  "<< this->isOriginOutput() << endl;

        ssize_t n = write(i_sfd,"yixi-sha yixi-sha\n",sizeof("yixi-sha yixi-sha\n"));
        cout << "send size id " <<n << endl;
        n = read(i_sfd, recv_buf,999);
        
        if(n > 0)
        {
            recv_buf[n] = '\0';
            cout << "recv_buf msg is " << recv_buf << endl;
        }
            
    }

    ~yixiSer(void)
    {
       this->close_ser();
    }
};



bool yixiSer::flagExit(int flag, flag_enum c_flag)
{
    int i_ret;
    struct termios i_termios;
    i_ret = tcgetattr(i_sfd, &i_termios);
    if(i_ret)
    {
        THROW_EXCEPTION(InvalidOperationException,"tcgetattr fail ");
    }
    if(c_flag == c_cflag)
        return (i_termios.c_cflag & flag ? true : false);
    else if (c_flag == c_lflag)
        return (i_termios.c_lflag & flag ? true : false);
    else if (c_flag == c_iflag)
        return (i_termios.c_iflag & flag ? true : false);
    else if (c_flag == c_oflag)
        return (i_termios.c_oflag & flag ? true : false);
    else
        THROW_EXCEPTION(InvalidParameterException,"InvalidParameterException"); 
}

void yixiSer::setFlag(int mask, int flag, bool set,flag_enum e_flag)
{
    int i_ret;
    struct termios i_termios;
    i_ret = tcgetattr(i_sfd, & i_termios);
    if(i_ret)
    {
        THROW_EXCEPTION(InvalidOperationException,"tcgetattr fail ");
    }
    if(e_flag == c_cflag)
        i_termios.c_cflag &= (~mask);
    else if(e_flag == c_lflag)
        i_termios.c_lflag &= (~mask);
    else if(e_flag == c_iflag)
        i_termios.c_iflag &= (~mask);
    else if(e_flag == c_oflag)
        i_termios.c_oflag &= (~mask);
    else
        THROW_EXCEPTION(InvalidParameterException,"InvalidParameterException");
    if(set)
    {
        if(e_flag == c_cflag)
            i_termios.c_cflag |= flag;
        else if (e_flag == c_lflag)
            i_termios.c_lflag |= flag;
        else if(e_flag == c_iflag)
            i_termios.c_iflag |= flag;
        else if(e_flag == c_oflag)
            i_termios.c_oflag |= flag;
    }
    i_ret = tcsetattr(i_sfd, TCSANOW,&i_termios);
    if(i_ret)
    {
        THROW_EXCEPTION(InvalidOperationException,"tcsetattr fail ");  
    } 
}

int yixiSer::getflage(flag_enum flag)
{
    int i_ret;
    struct termios i_termios;
    i_ret = tcgetattr(i_sfd, & i_termios);
    int ret = 0;
    if(i_ret)
    {
        THROW_EXCEPTION(InvalidOperationException,"tcgetattr fail ");
    }
    if(flag == c_cflag)
    {
        return ret = i_termios.c_cflag;
    }
    else if (flag == c_lflag)
    {
        return ret = i_termios.c_lflag;
    }
    else
    {
        THROW_EXCEPTION(InvalidParameterException,"InvalidParameterException ");
    }
}

bool yixiSer::isOriginModel()
{
    return !this->flagExit((ICANON | ECHO | ECHOE | ISIG),c_lflag);
}

void yixiSer::setOriginModel(bool set)
{
    this->setFlag((ICANON | ECHO | ECHOE | ISIG), (ICANON | ECHO | ECHOE | ISIG),\
                     !set,c_lflag);
}

bool yixiSer::isOriginOutput()
{
    return !this->flagExit(OPOST,c_oflag);
}
void yixiSer::setOriginOutput(bool set)
{
    this->setFlag(OPOST, OPOST,\
                     !set,c_oflag);
}

bool yixiSer::isStandardModel()
{
    return this->flagExit((ICANON | ECHO | ECHOE ),c_lflag);
}

void yixiSer::setStandardModel(bool set)
{
    this->setFlag((ICANON | ECHO | ECHOE ), (ICANON | ECHO | ECHOE | ISIG),\
                     set,c_lflag);
}

int yixiSer::getBAUD(void)
{
    int ret = this->getflage(c_cflag);
    switch(ret & CBAUD)
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
    this->setFlag(CBAUD, BAUD, true, c_cflag);
}

int yixiSer::getDataBit(void)
{
    int ret = this->getflage(c_cflag);
    switch( ret & CSIZE)
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
    this->setFlag(CSIZE, DataBit, true, c_cflag);
}

 bool yixiSer::isOnestopBit()
 {  
    return !this->flagExit(CSTOPB,c_cflag);
}

void yixiSer::setOneStopBit(bool one)
{
    this->setFlag(CSTOPB, CSTOPB, !one, c_cflag);  
}

bool yixiSer::isReadlyRecv()
{   
    return this->flagExit((CLOCAL | CREAD ), c_cflag);
}

void yixiSer::setReadlyRecv(bool recv)
{
    this->setFlag((CREAD | CLOCAL), (CREAD | CLOCAL), recv, c_cflag);
}

bool yixiSer::isParenb()
{
    return this->flagExit(PARENB, c_cflag);
}


void yixiSer::setParenb(bool par)
{
    this->setFlag(PARENB, PARENB, par,c_cflag);
}

bool yixiSer::isOddPar(void)
{
    return this->flagExit(PARODD, c_cflag);
}

void yixiSer::setOddpar(bool odd)
{
    this->setFlag(PARODD, PARODD, odd, c_cflag);
    this->setFlag((INPCK | ISTRIP), (INPCK | ISTRIP), true, c_iflag);
}

}

#endif