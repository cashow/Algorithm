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

#define maxn 1001

int n,m,x,y,cnt,ans;
char a[maxn][maxn];
bool inqueue[maxn];
int pre[maxn],dis[maxn],next[maxn];

struct node
{
    int x,y;
} house[maxn],people[maxn];

struct edge
{
    int to,from,next,flow,cost,num;
} e[maxn*maxn];

void insert(int a,int b,int flow,int cost)
{
    e[cnt].from=a;
    e[cnt].to=b;
    e[cnt].next=next[a];
    e[cnt].flow=flow;
    e[cnt].cost=cost;
    e[cnt].num=cnt;
    next[a]=cnt++;

    swap(a,b);

    e[cnt].from=a;
    e[cnt].to=b;
    e[cnt].next=next[a];
    e[cnt].flow=0;
    e[cnt].cost=-cost;
    e[cnt].num=cnt;
    next[a]=cnt++;
}

queue<int>q;

bool spfa(int start,int end)
{
    MEM(inqueue);
    MEST(dis);
    MEST(pre);
    dis[start]=0;
    inqueue[start]=true;
    q.push(start);
    while(!q.empty())
    {
        int pos=q.front();
        q.pop();
        inqueue[pos]=false;
        int id=next[pos];
        while(id!=-1)
        {
            int to=e[id].to;
            if(e[id].flow==0)
            {
                id=e[id].next;
                continue;
            }
            if(dis[to]==-1||dis[to]>dis[pos]+e[id].cost)
            {
                dis[to]=dis[pos]+e[id].cost;
                pre[to]=e[id].num;
                if(!inqueue[to])
                {
                    q.push(to);
                    inqueue[to]=true;
                }
            }
            id=e[id].next;
        }
    }
    return dis[end]!=-1;
}

void mincost(int start,int end)
{
    ans=0;
    int minn=-1;
    while(spfa(start,end))
    {
        int id=pre[end];
        while(id!=-1)
        {
            if(minn==-1||e[id].flow<minn)
            {
                minn=e[id].flow;
            }
            id=pre[e[id].from];
        }
        id=pre[end];
        while(id!=-1)
        {
            e[id].flow-=minn;
            e[id^1].flow+=minn;
            ans+=e[id].cost*minn;
            id=pre[e[id].from];
        }
    }
}

void ini()
{
    cnt=0;
    MEST(next);
}

int main()
{
    while(1)
    {
        scanf("%d%d",&n,&m);
        if(n==0&&m==0)
            break;
        ini();
        FOR(i,n)
        {
            scanf("%s",a[i]);
        }
        x=y=0;
        FOR(i,n)
        {
            FOR(j,m)
            {
                if(a[i][j]=='H')
                {
                    house[x].x=i;
                    house[x].y=j;
                    x++;
                }
                if(a[i][j]=='m')
                {
                    people[y].x=i;
                    people[y].y=j;
                    y++;
                }
            }
        }
        for(int i=1; i<=x; i++)
        {
            insert(0,i,1,0);
        }
        for(int j=x+1; j<=x+y; j++)
        {
            insert(j,x+y+1,1,0);
        }
        for(int i=1; i<=x; i++)
        {
            for(int j=x+1; j<=x+y; j++)
            {
                int dist=fabs(0.0+house[i-1].x-people[j-x-1].x)+fabs(0.0+house[i-1].y-people[j-x-1].y);
                insert(i,j,1,dist);
            }
        }
        mincost(0,x+y+1);
        printf("%d\n",ans);
    }
    return 0;
}
