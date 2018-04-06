#ifndef QUEUESOLUTION_H
#define QUEUESOLUTION_H

#include "DateStructure/List/ListChain/linklist.h"
#include <iostream>

using namespace std;

namespace yixi
{
template <int SZIE>
class QueueSolution
{
protected:
    enum { N = SZIE + 2};
    struct Pos : public Object
    {
        Pos (int px = 0, int py = 0) : x(px),y(py) {}
        int x;
        int y;
    };
    int m_chessboard[N][N];
    Pos m_direction[3];
    LinkList<Pos> m_solution;
    int m_count;


    void init()
    {
        m_count = 0;
        for(int i = 0;i<N;i+= (N-1))
        {
            for(int j=0;j<N;j++)
            {
                m_chessboard[i][j] = 2;
                m_chessboard[j][i] = 2;
            }
        }

        for(int i = 1;i<=SZIE;i++)
        {
            for(int j =1;j<=SZIE;j++)
            {
                m_chessboard[i][j] = 0;
            }
        }

        m_direction[0].x = -1;
        m_direction[0].y = -1;
        m_direction[1].x = 0;
        m_direction[1].y = -1;
        m_direction[2].x = 1;
        m_direction[2].y = -1;

    }

    void printf()
    {
        for(m_solution.move(0);!m_solution.end();m_solution.next())
        {
            cout << "(" <<m_solution.current().x <<","<<m_solution.current().y << ")" <<endl;
        }
        cout <<endl;
        for(int i = 0;i<N;i++)
        {
            for(int j = 0;j<N;j++)
            {
                switch(m_chessboard[i][j])
                {
                case 0: cout << " " ;break;
                case 1: cout << "#" ;break;
                case 2: cout << "*" ;break;
                }
            }
            cout<<endl;
        }
    }

    bool check(int x,int y, int d)
    {
        bool flag = true;

        do
        {
            x +=m_direction[d].x;
            y +=m_direction[d].y;
            flag = flag && (m_chessboard[x][y] == 0);
        }while(flag);
        return (m_chessboard[x][y] == 2);
    }

    void run(int j)
    {
        if(j <= SZIE)
        {
            for(int i = 1;i<=SZIE;i++)
            {
                if(check(i,j,0) && check(i,j,1) && check(i,j,2))
                {
                    m_chessboard[i][j] = 1;
                    m_solution.insert(Pos(i,j));

                    run(j+1);

                    m_chessboard[i][j] = 0;
                    m_solution.remove(m_solution.length() - 1);
                }
            }
        }
        else
        {
            m_count ++;
            printf();
        }
    }

public:
    QueueSolution()
    {
        init();
    }

    void run()
    {
        run(1);
        cout << "Total :" << m_count <<endl;
    }


};
}
#endif // QUEUESOLUTION_H
