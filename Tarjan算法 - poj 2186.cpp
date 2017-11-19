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

int outd[10001],lastshow[10001],dfn[10001],low[10001],same[10001];     //lastshow数组表示第i位节点的起始位置
int cnt,index;
bool used[5001];
int n,m,a,b;
struct edge
{
    int to,next;
} e[50001];

void insert(int a,int b)
{
    e[cnt].to=b;
    e[cnt].next=lastshow[a];
    lastshow[a]=cnt++;
}
void ini()
{
    index=0;
    cnt=0;
    memset(lastshow,-1,sizeof(lastshow));
    MEM(dfn);
    MEM(low);
    MEM(outd);
}

void tarjan(int i,int father)
{
    dfn[i]=low[i]=++index;  //dfn数组表示dfs的时间戳,low数组用来确定什么时候弹栈
    int id=lastshow[i];     //在有向图中,弹栈过程中的点属于同一个强连通分量
    while(id!=-1)           //在无向图中,low值相同的点即属于同一个强连通分量
    {
        int j=e[id].to;
        if(j==father)
        {
            id=e[id].next;
            continue;
        }
        if(!dfn[j])         //假如没有访问过j点则访问j并更新low的值
        {
            tarjan(j,i);
        }
        low[i]=min(low[i],low[j]);      //low值相同表示在同一个强连通分量里

        id=e[id].next;
    }
}

void Outdegree()
{
    for(int i=1; i<=n; i++)             //缩点
    {
        MEM(used);
        int id=lastshow[i];
        while(id!=-1)
        {
            if(low[e[id].to]!=low[i]&&!used[e[id].to])  //i所连接的点与i不在同一层
            {
                outd[low[i]]++;         //则low[i]的出度加1,此时将low值相同的点当做一个点
                used[e[id].to]=true;
            }
            id=e[id].next;
        }
    }
    int count=0;
    for(int i=1; i<=n; i++)
    {
        if(outd[i]==1)
        {
            count++;
        }
    }
    printf("%d\n",(count+1)/2);
}

int main()
{
    while(scanf("%d%d",&n,&m)!=EOF)
    {
        ini();
        FOR(i,m)
        {
            scanf("%d%d",&a,&b);        //无向图,a->b和b->a都要加进去
            insert(a,b);
            insert(b,a);
        }
        FOR(i,n)
        {
            if(dfn[i+1]==0)
            {
                tarjan(i+1,-1);
            }
        }
        Outdegree();
    }
    return 0;
}
