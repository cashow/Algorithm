#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <stack>
#include <algorithm>
#include <cstdio>
#include <queue>
#include <string>
#include <cmath>
#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std;

const double eps=1e-8;

#define MEM(a) memset(a,0,sizeof(a));
#define FOR(i,n) for(int i=0;i<n;i++)

int gcd(int x,int y)
{
    if(x<y)
    {
        int t=x;
        x=y;
        y=t;
    }
    if(x%y==0)
        return y;
    return gcd(y,x%y);
}

int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int c,s,ans;
    while(1)
    {
        scanf("%d",&s);                //c:颜色数     s:长度
        if(s==-1)
            break;
        if(s==0)
        {
            cout<<0<<endl;
            continue;
        }
        c=3;
        long long rotation=0,turn;
        for(int i=1; i<=s; i++)             //旋转
            rotation+=pow(c,gcd(s,i));
        if(s&1)                             //翻转
            turn=s*pow(c,s/2+1);
        else
            turn=(s/2)*pow(c,s/2)+(s/2)*pow(c,s/2+1);
        ans=(rotation+turn)/(2*s);
        printf("%d\n",ans);
    }
    return 0;
}
