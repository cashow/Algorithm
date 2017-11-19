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

#define maxn 500

long long dis[maxn][maxn];
long long connect[maxn][maxn];
long long minadd[maxn];
long long level[maxn],pre[maxn],next[maxn];
long long n,m,ans,sum,anss;
queue<long long>q;

struct edge
{
    long long x,y;
} p[maxn];

bool bfs(long long start,long long end)               //更新level并确定是否能到达汇点
{
    q.push(start);
    memset(level,-1,sizeof(level));
    level[start]=0;
    while(!q.empty())
    {
        long long p=q.front();
        q.pop();
        for(long long i=start; i<=end; i++)
        {
            if(connect[p][i]&&level[i]==-1)
            {
                q.push(i);
                level[i]=level[p]+1;
            }
        }
    }
    return level[end]!=-1;              //能到达end则返回true，不能则返回false
}

void dfs(long long start,long long end)
{
    long long pos=start,to,change;
    long long minn,minpos;
    minn=-1;
    while(1)                            //非递归dfs
    {
        bool flag=false;
        for(long long i=start; i<=end; i++)         //找一条可以走的路
        {
            if(connect[pos][i]&&level[i]==level[pos]+1)
            {
                flag=true;
                to=i;
                break;
            }
        }
        if(flag)                        //找到一个可以走的路径
        {
            next[pos]=to;
            pre[to]=pos;
            if(minadd[pos]==-1)         //minadd[pos]取最小。到达end时minadd[end]为增广路可加的最大流量
                minadd[to]=connect[pos][to];
            else
                minadd[to]=min(minadd[pos],connect[pos][to]);
            pos=to;			            //从找到的节点开始在层次图里找路
            if(pos==end) 	            //找到t后，增广
            {
                ans+=minadd[end];        //minadd[end]:增广路可加的最大流量
                change=minadd[end];
                for(long long i=end; i!=start; i=pre[i])    //一直从汇点回退到源点，更新每条路的容量
                {
                    minadd[i]-=change;
                    connect[pre[i]][i]-=change;
                    connect[i][pre[i]]+=change;
                    if(connect[pre[i]][i]==0)
                    {
                        pos=pre[i];           //u回退到容量边为0的路的点之前
                    }
                }
            }
        }
        else
        {
            if(pos!=start)	            //如果pos!=start那么这条路走不通的话，从pos的上一个节点继续找。
            {
                level[pos]=-2;          //相当于从层次图里删除这个节点。
                pos=pre[pos];           //dfs回溯
            }
            else                        //如果从源点找不到增广路，就结束了。
                return ;
        }
    }
}

void print()
{
    rep(i,n)
    {
        rep(j,n)
        {
            if(i==j)
                continue;
            if(connect[2*i-1][2*j])
                printf("%I64d -> %I64d\n",2*i-1,2*j);
        }
    }
}

long long dinic(long long s,long long t)          //求从s点到t点的最大流量
{
    ans=0;
//    print();
    while(bfs(s,t))             //每一次先求出最短路径,建好层次图
    {
        MEM(pre);		        //dfs中，如果需要回溯，就回溯到pre中的节点。
        MEST(minadd);       //minadd里面存的是剩余流量
        dfs(s,t);
    }
    return ans;
}

void flyod()
{
    for(long long k=1; k<=n; k++)
    {
        for(long long i=1; i<=n; i++)
        {
            if(dis[i][k]==0)
                continue;
            for(long long j=1; j<=n; j++)
            {
                if(dis[k][j]==0)
                    continue;
                if(dis[i][j]==0||dis[i][k]+dis[k][j]<dis[i][j])
                {
                    dis[i][j]=dis[i][k]+dis[k][j];
                }
            }
        }
    }
}

void ini()
{
    anss=-1;
    sum=0;
    MEM(dis);
}

void rebuild(long long mid)
{
    MEM(connect);
    rep(i,n)
    {
        connect[0][2*i-1]=p[i].x;
        connect[2*i][2*n+1]=p[i].y;
        connect[2*i-1][2*i]=99999999;
    }
    rep(i,n)
    {
        rep(j,n)
        {
            if(dis[i][j]&&dis[i][j]<=mid)
            {
//                printf("insert %I64d->%I64d=%I64d\n",i,j,dis[i][j]);
                connect[2*i-1][2*j]=99999999;
            }
        }
    }
}

int main()
{
    long long x,y,z;
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    while(scanf("%I64d%I64d",&n,&m)!=EOF)
    {
        ini();
        for(long long i=1; i<=n; i++)
        {
            scanf("%I64d%I64d",&p[i].x,&p[i].y);
            sum+=p[i].x;
        }
        FOR(i,m)
        {
            scanf("%I64d%I64d%I64d",&x,&y,&z);
            if(dis[x][y])
                dis[x][y]=min(dis[x][y],z);
            else
                dis[x][y]=z;
            dis[y][x]=dis[x][y];
        }
        flyod();

        long long left=0,right=0;
        rep(i,n)
        {
            dis[i][i]=0;
            rep(j,n)
            {
                right=max(right,dis[i][j]);
            }
        }
//        printf("sum=%I64d\n",sum);

        while(1)
        {
            long long mid=(left+right)>>1;
            rebuild(mid);

            long long tem=dinic(0,2*n+1);
//            printf("left=%I64d,right=%I64d,mid=%I64d,tem=%I64d\n",left,right,mid,tem);

            if(tem==sum)
            {
                anss=mid;
                right=mid-1;
            }
            if(tem>sum)
            {
                right=mid-1;
            }
            if(tem<sum)
            {
                left=mid+1;
            }
//            printf("ans=%I64d\n",anss);
            if(left>right)
                break;
        }
        printf("%I64d\n",anss);
    }
    return 0;
}
