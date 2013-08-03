#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <stack>
#include <algorithm>
#include <iostream>
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
#define MEST(a) memset(a,-1,sizeof(a));
#define FOR(i,n) for(int i=0;i<n;i++)
#define rep(i,n) for(int i=1;i<=n;i++)

int connect[101][101],farm[101],len,n;
bool used[101];

int prim()
{
    int ans=0,len=1;
    farm[0]=0;                  //任选一点作为起始点
    used[0]=true;
    for(int p=1; p<n; p++)      //n-1重循环
    {
        int next,minn=-1;       //next是下一个要加入的点
        FOR(i,len)              //枚举已用过的点
        {
            FOR(j,n)            //枚举没用过的点
            {
                if(used[j])
                    continue;
                if(minn==-1||minn>connect[farm[i]][j])      //取距离最小的点
                {
                    next=j;
                    minn=connect[farm[i]][j];
                }
            }
        }
        used[next]=true;
        farm[len++]=next;
        ans+=minn;              //minn是next点与已经加入过的点的距离的最小值
    }
    return ans;
}

int main()
{
    while(scanf("%d",&n)!=EOF)
    {
        MEM(used);
        FOR(i,n)
        {
            FOR(j,n)
            {
                scanf("%d",&connect[i][j]);
            }
        }
        printf("%d\n",prim());
    }
    return 0;
}
