#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <stack>
#include <bitset>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cstdio>
#include <queue>
#include <string>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

const double eps=1e-8;

#define MEM(a) memset(a,0,sizeof(a));
#define FOR(i,n) for(int i=0;i<n;i++)

int fun(int x,int y)
{
    int t=1;
    while(y--)
    {
        t*=x;
    }
    return t;
}

int main()
{
    char a[11],ans[11];
    int x,y,z,lena;
    while(scanf("%s%d%d",a,&x,&y)!=EOF)
    {
        lena=strlen(a);
        z=0;
        FOR(i,lena)                 //x->z
        {
            z*=x;
            if(a[i]<='9'&&a[i]>='0')
                z+=a[i]-'0';
            else
                z+=a[i]-'A'+10;
        }

        int pos=0;                  //z->y
        while(z>=fun(y,pos)&&pos<8)
        {
            pos++;
        }
        //cout<<pos<<endl;
        if(pos>7)
        {
            printf("  ERROR\n");
            continue;
        }
        //cout<<"haha";
        ans[pos]='\0';
        FOR(i,7-pos)
        {
            printf(" ");
        }
        while(z)
        {
            if(z%y<10)
                ans[--pos]='0'+z%y;
            else
                ans[--pos]='A'+z%y-10;
            z/=y;
        }
        printf("%s\n",ans);
    }
    return 0;
}
