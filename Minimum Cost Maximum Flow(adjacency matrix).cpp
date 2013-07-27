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

int n,m,x,y,ans;
char a[maxn][maxn];
int connect[maxn][maxn],cost[maxn][maxn],pre[maxn];
int dis[maxn];
bool inqueue[maxn];

struct node
{
    int x,y;
} house[101],people[101];

queue<int>q;

bool spfa(int start,int end)
{
    memset(dis,-1,sizeof(dis));
    MEM(inqueue);
    MEM(pre);
    dis[start]=0;
    inqueue[start]=true;
    q.push(start);
    while(!q.empty())
    {
        int pos=q.front();
        q.pop();
        inqueue[pos]=false;
        for(int next=start; next<=end; next++)
        {
            if(!connect[pos][next])
                continue;
            if(dis[next]==-1||dis[next]>dis[pos]+cost[pos][next])
            {
                dis[next]=dis[pos]+cost[pos][next];
                pre[next]=pos;
                if(!inqueue[next])
                {
                    q.push(next);
                    inqueue[next]=true;
                }
            }
        }
    }
    return dis[end]!=-1;
}

void mincost(int start,int end)
{
    ans=0;
    int minn=-1;
    while(spfa())
    {
        for(int i=end; i!=start; i=pre[i])
        {
            if(minn==-1||connect[pre[i]][i]<minn)
            {
                minn=connect[pre[i]][i];
            }
        }
        for(int i=end; i!=start; i=pre[i])
        {
            connect[pre[i]][i]-=minn;
            connect[i][pre[i]]+=minn;
            ans+=cost[pre[i]][i]*minn;
        }
    }
}

int main()
{
    while(1)
    {
        scanf("%d%d",&n,&m);
        if(n==0&&m==0)
            break;
        MEM(connect);
        MEM(cost);
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
            connect[0][i]=1;
            for(int j=x+1; j<=x+y; j++)
            {
                connect[j][x+y+1]=1;
                connect[i][j]=1;
                cost[i][j]=fabs(0.0+house[i-1].x-people[j-x-1].x)+fabs(0.0+house[i-1].y-people[j-x-1].y);
                cost[j][i]=-cost[i][j];
            }
        }
        mincost(0,x+y+1);
        printf("%d\n",ans);
    }
    return 0;
}
