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

int dis[1001];
int n,m;

struct edge
{
    int to,from,weight;     //表示边to->from,不是邻接表
}e[4001];
int cnt;

void insert(int to,int from,int weight)     //表示插入边to->from,权值为weight
{
    e[cnt].to=to;
    e[cnt].from=from;
    e[cnt++].weight=weight;
}

void bellmanford()
{
    FOR(i,n-1)              //n-1重循环,每次循环通过边a->b去更新dis[b]的值
    {
        FOR(j,cnt)          //枚举每条边
        {
            if(dis[e[j].to]>dis[e[j].from]+e[j].weight)
                dis[e[j].to]=dis[e[j].from]+e[j].weight;
        }
    }
}

int main()
{
    int x,y,w;
    while(scanf("%d%d",&m,&n)!=EOF)
    {
        FOR(i,n)
        {
            dis[i]=99999999;
        }
        dis[0]=0;
        cnt=0;
        FOR(i,m)
        {
            scanf("%d%d%d",&x,&y,&w);
            x--;
            y--;
            insert(x,y,w);
            insert(y,x,w);
        }
        bellmanford();
        printf("%d\n",dis[n-1]);
    }
    return 0;
}
