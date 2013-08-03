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

#define N 2000
#define M 5000

int w[N],edge,id[N],an[M];
long long dp[N][2],dis[N];

struct qq
{
    int id;
    long long l;
} q[M];

struct node
{
    int v,next;
    long long l;
} e[N*2];

void add(int u,int v,long long l)
{
    e[edge].v=v;
    e[edge].l=l;
    e[edge].next=w[u];
    w[u]=edge++;
}

void dfs1(int u,int no)
{
    for(int i=w[u]; i!=-1; i=e[i].next)
    {
        int v=e[i].v;
        if(v!=no)
        {
            dfs1(v,u);
            if(dp[v][0]+e[i].l>dp[u][0])
            {
                dp[u][1]=dp[u][0];
                id[u]=v,dp[u][0]=dp[v][0]+e[i].l;
            }
            else if(dp[v][0]+e[i].l>dp[u][1]) dp[u][1]=dp[v][0]+e[i].l;
        }
    }
}

void dfs2(int u,int no,long long l)
{
    dis[u]=max(l,dp[u][0]);
    for(int i=w[u]; i!=-1; i=e[i].next)
    {
        int v=e[i].v;
        if(v!=no)
        {
            if(v==id[u]) dfs2(v,u,max(l,dp[u][1])+e[i].l);
            else dfs2(v,u,dis[u]+e[i].l);
        }
    }
}

int main()
{
    int n,m,a,b;
    long long c;
    while(scanf("%d%d",&n,&m))
    {
        if(!n&&!m) break;
        edge=0;
        memset(w,-1,sizeof(int)*(n+1));
        for(int i=1; i<n; ++i)
        {
            scanf("%d%d%I64d",&a,&b,&c);
            add(a,b,c);
            add(b,a,c);
        }
        memset(dis,0,sizeof(long long)*(n+1));
        memset(dp,0,sizeof(dp));
        dfs1(1,1);
        dfs2(1,1,0);
    }
    return 0;
}
