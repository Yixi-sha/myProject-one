#include <iostream>

#include "../inc/rtp.h"
#include "../inc/serial.h"

using namespace yixi;
using namespace std;

extern "C"
{
    pid_t fork(void);
    void exit(int status);
    unsigned int sleep(unsigned int seconds);
}

int main(void)
{ 
    yixiSer ser;
    ser.test();

/*    yixiRtp RTP;
    sockaddr_in recv;
    char recv_buf[999];
    char count = 'a';
    while(1)
    {
        int len = RTP.receivr_thread(&recv, recv_buf, 999);
        cout << recv_buf << endl;
        if(fork() == 0)
        {   
            sleep(5);
            RTP.send_thread(&recv, recv_buf, len);
            exit(0);
        }        
    }*/
    
      

    return 0;
}