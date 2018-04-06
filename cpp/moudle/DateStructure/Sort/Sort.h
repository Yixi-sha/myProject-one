#ifndef SORT_H
#define SORT_H

#include "DateStructure/Object/Object.h"
#include "DateStructure/Exception/Exception.h"
#include "DateStructure/List/Array/Array.h"

namespace yixi
{
class Sort : public Object
{
private:
    Sort();
    Sort(const Sort& obj);
    Sort& operator = (const Sort& obj);

    template <typename T>
    static void Swap(T& a,T& b)
    {
        T c = a;
        a = b;
        b = c;
    }

    template <typename T>
    static void Merge_2(T src[],T helper[],int bein,int mid,int end,bool min2max = true)
    {
        int m = mid + 1;
        int b = bein;
        int i = bein;
        for(;(b <=mid) && (m<=end) ;i++)
        {
            if(min2max ? src[b] < src[m] : src[b] > src[m] )
            {
                helper[i] = src[b];
                b++;
            }
            else
            {
                helper[i] = src[m];
                m++;
            }
        }
        while(b <= mid)
        {
            helper[i] = src[b];
            b++;
            i++;
        }
        while(m<=end)
        {
            helper[i] = src[m];
            m++;
            i++;
        }
        for(i = bein;i<=end;i++)
        {
            src[i] = helper[i];
        }
    }

    template <typename T>
    static void Merge_2(T src[],T helper[],int begin,int end,bool min2max = true)
    {

        if(begin < end)
        {
            int mid = (begin + end) / 2;
            Merge_2(src,helper,begin,mid,min2max);
            Merge_2(src,helper,mid + 1,end,min2max);
            Merge_2(src,helper,begin,mid,end,min2max);
        }
    }

    template < typename T >
    static int Partition(T array[],int begin,int end,bool min2max)
    {

        T pv = array[begin];

        while(begin < end)
        {
            while( (begin < end) && (min2max ? array[end] > pv : array[end] < pv ))
            {
                end--;
            }
            Swap(array[begin],array[end]);

            while((begin < end) && (min2max ? array[begin] <= pv : array[begin] >= pv ))
            {
                begin++ ;
            }
            Swap(array[end],array[begin]);
        }
        array[begin] = pv;

        return begin;
    }

    template <typename T>
    static void Quick(T array[],int begin,int end,bool min2max)
    {
        if(begin < end)
        {
            int pivot =  Partition(array,begin,end,min2max);
            Quick(array,begin,pivot-1,min2max);
            Quick(array,pivot+1,end,min2max);
        }
    }



public:
    template <typename T>
    static void Select(T array[],int len,bool min2max = true)  // don`t stability
    {
        for(int i = 0;i<len;i++)
        {
            int m = i;

            for(int j = i + 1;j < len;j++)
            {
                if ( min2max ? (array[m] > array[j]) : (array[m] < array[j]) )
                {
                    m = j;
                }
            }
            if(i != m)
            {
                Swap(array[i],array[m]);
            }
        }
    }

    template <typename T>
    static void Select(Array<T>& array,bool min2max = true)  // don`t stability
    {
        Select(array.array(),array.length(),min2max);
    }

    template <typename T>
    static void Insert(T array[],int len,bool min2max = true)   // it is stability
    {
        for( int i = 1 ; i<len;i++)
        {
            int k = i;
            T e = array[i];
            for(int j = i -1;(j>=0) && (min2max ? (e < array[j]) : (e > array[j]));j--)
            {
                array[j + 1] = array[j];
                k = j;
            }
            if( k != i)
            {
                array[k]  = e;
            }
        }
    }

    template <typename T>
    static void Insert(Array<T>& array,bool min2max = true)  // don`t stability
    {
        Insert(array.array(),array.length(),min2max);
    }

    template <typename T>
    static void Bulle(T array[],int len,bool min2max = true)
    {
        bool exchange = true;

        for(int i = 0;i<len && exchange;i++)
        {
            exchange = false;
            for(int j = len -1 ;j>i;j--)
            {
                if(min2max ? (array[j -1] > array[j]) : (array[j -1] < array[j]))
                {
                    Swap(array[j -1],array[j]);
                    exchange = true;
                }
            }
        }
    }

    template <typename T>
    static void Bulle(Array<T>& array,bool min2max = true)  // don`t stability
    {
        Bulle(array.array(),array.length(),min2max);
    }

    template <typename T>
    static void Shell_Selcet(T array[],int len,bool min2max = true)  // it isn`t stability
    {
        int d = len;

        do
        {
            d = d /3 + 1;

            bool exchange = true;

            for(int i = d;i<len && exchange;i+=d)
            {
                exchange = false;
                for(int j = len -d ;j>i;j-=d)
                {
                    if(min2max ? (array[j -d] > array[j]) : (array[j -d] < array[j]))
                    {
                        Swap(array[j -d],array[j]);
                        exchange = true;
                    }
                }
            }

        }while (d > 1);
    }

    template <typename T>
    static void Shell_Selcet(Array<T>& array,bool min2max = true)  // don`t stability
    {
        Shell_Selcet(array.array(),array.length(),min2max);
    }


    template <typename T>
    static void Shell_Bulle(T array[],int len,bool min2max = true)  // it isn`t stability
    {
        int d = len;

        do
        {
            d = d /3 + 1;

            for( int i = d ; i<len;i+=d)
            {
                int k = i;
                T e = array[i];
                for(int j = i -d;(j>=0) && (min2max ? (e < array[j]) : (e > array[j]));j-= d)
                {
                    array[j + d] = array[j];
                    k = j;
                }
                if( k != i)
                {
                    array[k]  = e;
                }
            }

        }while (d > 1);
    }

    template <typename T>
    static void Shell_Bulle(Array<T>& array,bool min2max = true)  // don`t stability
    {
        Shell_Bulle(array.array(),array.length(),min2max);
    }

    template <typename T>
    static void Merge_2(T array[],int len,bool min2max = true) //it is stablity
    {
        T* helper = new T[len];
        if(helper != NULL)
        {
            Merge_2(array,helper,0,len - 1, min2max);
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException,"No Enough Memory to merge");
        }

    }

    template <typename T>
    static void Merge_2(Array<T>& array,bool min2max = true)  // don`t stability
    {
        Merge_2(array.array(),array.length(),min2max);
    }

    template <typename T>
    static void Quick(T array[],int len,bool min2max = true) //it isn`t stablity
    {
        Quick(array,0,len -1,min2max);
    }

    template <typename T>
    static void Quick(Array<T>& array,bool min2max = true)  // don`t stability
    {
        Quick(array.array(),array.length(),min2max);
    }



};
}


#endif // SORT_H
