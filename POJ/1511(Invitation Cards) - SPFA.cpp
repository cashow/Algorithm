#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <stack>
#include <bitset>
#include <iostream>
#include <algorithm>
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
#define FOR(i,n) for(int i=0;i<n;i++)

long long lastshow[1000001],dis[1000001];
bool inqueue[1000001];
long long cnt,n,m;

queue<long long>q;
struct edge
{
    long long to,next,w;
}e[1000001];

struct ee
{
    long long x,y,w;
}p[1000001];

void insert(long long a,long long b,long long w)
{
    e[cnt].to=b;
    e[cnt].next=lastshow[a];
    e[cnt].w=w;
    lastshow[a]=cnt++;
}

void spfa()
{
    long long pos,id,next;
    q.push(0);
    while(!q.empty())
    {
        pos=q.front();
        q.pop();
        id=lastshow[pos];
        inqueue[pos]=false;
        while(id!=-1)
        {
            next=e[id].to;
            if(dis[next]==-1||dis[pos]+e[id].w<dis[next])
            {
                dis[next]=dis[pos]+e[id].w;
                if(!inqueue[next])
                {
                    inqueue[next]=true;
                    q.push(next);
                }
            }
            id=e[id].next;
        }
    }
}

void ini()
{
    cnt=0;
    memset(lastshow,-1,sizeof(lastshow));
    FOR(i,n)
    {
        dis[i]=-1;
    }
    dis[0]=0;
    MEM(inqueue);
}


int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    long long t,ans,x,y,w;
    scanf("%I64d",&t);
    while(t--)
    {
        scanf("%I64d%I64d",&n,&m);
        ini();
        FOR(i,m)
        {
            scanf("%I64d%I64d%I64d",&x,&y,&w);
            x--;
            y--;
            p[i].x=y;
            p[i].y=x;
            p[i].w=w;
            insert(x,y,w);
        }
        spfa();
        ans=0;
        FOR(i,n)
        {
            ans+=dis[i];
        }

        ini();
        FOR(i,m)
        {
            insert(p[i].x,p[i].y,p[i].w);
        }
        spfa();
        FOR(i,n)
        {
            ans+=dis[i];
        }
        printf("%I64d\n",ans);
    }
    return 0;
}
