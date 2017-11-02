
/**********************************************************
*    > File Name: test.cpp
*    > Author: 51CC_baosongshan
*    > Mail: baosongshan2006@163.com 
*    > Created Time: 2017年09月23日 星期六 14时25分33秒
**********************************************************/

#include<iostream>
#include<unistd.h>
using namespace std;

int main(int argc, char *argv[])
{
    opterr = 0;
    char ch;
    while((ch = getopt(argc, argv, "nxa:b::y")) != -1)
    {
        switch(ch)
        {
        case 'n':
            cout<<"This is n option."<<endl;
            break;
        case 'x':
            cout<<"This is x option."<<endl;
            break;
        case 'y':
            cout<<"This is y option."<<endl;
            break;
        case 'a':
            cout<<"This is a option, a = "<<optarg<<endl;
            break;
        case 'b':
            cout<<"This is b option, b = "<<optarg<<endl;
            break;
        case '?':
            cout<<(char)optopt<<" option is invalid."<<endl;
            break;
        }
    }
    return 0;
}


