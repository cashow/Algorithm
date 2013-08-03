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

#define maxn 201

int connect[maxn][maxn],level[maxn],pre[maxn],next[maxn],minadd[maxn];
int n,m,ans;
queue<int>q;

bool bfs(int start,int end)               //更新level并确定是否能到达汇点
{
    q.push(start);
    MEST(level);
    level[start]=0;
    while(!q.empty())
    {
        int pos=q.front();
        q.pop();
        for(int i=start; i<=end; i++)
        {
            if(connect[pos][i]&&level[i]==-1)
            {
                q.push(i);
                level[i]=level[pos]+1;
            }
        }
    }
    return level[end]!=-1;              //能到达end则返回true，不能则返回false
}

void dfs(int start,int end)
{
    int pos=start,to,change,minn=-1,minpos;
    while(1)                            //非递归dfs
    {
        bool flag=false;
        for(int i=start; i<=end; i++)         //找一条可以走的路
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
                for(int i=end; i!=start; i=pre[i])    //一直从汇点回退到源点，更新每条路的容量
                {
                    minadd[i]-=change;
                    connect[pre[i]][i]-=change;
                    connect[i][pre[i]]+=change;
                    if(connect[pre[i]][i]==0)
                        pos=pre[i];           //u回退到容量边为0的路的点之前
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

int dinic(int s,int t)          //求从s点到t点的最大流量
{
    ans=0;
    while(bfs(s,t))             //每一次先求出最短路径,建好层次图
    {
        MEM(pre);		        //dfs中，如果需要回溯，就回溯到pre中的节点。
        MEST(minadd);       //minadd里面存的是剩余流量
        dfs(s,t);
    }
    return ans;
}

int main()
{
    int x,y,z;
    while(scanf("%d%d",&m,&n)!=EOF)
    {
        MEM(connect);
        FOR(i,m)
        {
            scanf("%d%d%d",&x,&y,&z);
            connect[x][y]+=z;
        }
        printf("%d\n",dinic(1,n));
    }
    return 0;
}
