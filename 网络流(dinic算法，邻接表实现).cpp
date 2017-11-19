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

struct edge
{
    int to,from,next,value,num;         //num记录的是这条边的编号
} e[maxn*maxn*2];

int level[maxn],pre[maxn],next[maxn],minadd[maxn];
int n,m,ans,cnt;
queue<int>q;

void insert(int from,int to,int value)
{
    e[cnt].to=to;
    e[cnt].from=from;
    e[cnt].next=next[from];
    e[cnt].value=value;
    e[cnt].num=cnt;
    next[from]=cnt++;

    swap(from,to);

    e[cnt].to=to;
    e[cnt].from=from;
    e[cnt].next=next[from];
    e[cnt].value=0;
    e[cnt].num=cnt;
    next[from]=cnt++;
}

bool bfs(int start,int end)               //更新level并确定是否能到达汇点
{
    int pos,to;
    q.push(start);
    MEST(level);
    level[start]=0;
    while(!q.empty())
    {
        pos=q.front();
        q.pop();
        for(int id=next[pos];id!=-1;id=e[id].next)
        {
            to=e[id].to;
            if(e[id].value>0&&level[to]==-1)
            {
                q.push(to);
                level[to]=level[pos]+1;
            }
        }
    }
    return level[end]!=-1;              //能到达end则返回true，不能则返回false
}

void dfs(int start,int end)
{
    int pos=start,to,change,minn=-1,minpos,id;
    while(1)                            //非递归dfs
    {
        bool flag=false;
        for(id=next[pos];id!=-1;id=e[id].next)      //找一条可以走的路
        {
            int i=e[id].to;
            if(level[i]==level[pos]+1&&e[id].value>0)
            {
                flag=true;
                to=i;
                break;
            }
        }

        if(flag)                            //找到一个可以走的路径
        {
            pre[to]=id;                     //pre[to]记录的是pos->to这条边的id
            if(minadd[pos]==-1)             //minadd[pos]取最小。到达end时minadd[end]为增广路可加的最大流量
                minadd[to]=e[id].value;
            else
                minadd[to]=min(minadd[pos],e[id].value);
            pos=to;			                //从找到的节点开始在层次图里找路
            if(pos==end) 	                //找到t后，增广
            {
                ans+=minadd[end];           //minadd[end]:增广路可加的最大流量
                change=minadd[end];
                int id=pre[end];
                while(1)              //一直从汇点回退到源点，更新每条路的容量
                {
                    minadd[e[id].to]-=change;
                    e[id].value-=change;
                    e[id^1].value+=change;
                    if(e[id].value==0)
                        pos=e[id].from;           //u回退到容量边为0的路的点之前
                    if(pre[e[id].from]==-1)
                        break;
                    id=pre[e[id].from];
                }
            }
        }
        else
        {
            if(pos!=start)	            //如果pos!=start那么这条路走不通的话，从pos的上一个节点继续找。
            {
                level[pos]=-2;          //相当于从层次图里删除这个节点。
                pos=e[pre[pos]].from;           //dfs回溯
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
        MEST(pre);		        //dfs中，如果需要回溯，就回溯到pre中的节点。
        MEST(minadd);       //minadd里面存的是剩余流量
        dfs(s,t);
    }
    return ans;
}

void ini()
{
    MEST(next);
    cnt=0;
}

int main()
{
    int x,y,z;
    while(scanf("%d%d",&m,&n)!=EOF)
    {
        ini();
        FOR(i,m)
        {
            scanf("%d%d%d",&x,&y,&z);
            insert(x,y,z);
        }
        printf("%d\n",dinic(1,n));
    }
    return 0;
}
