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

#define maxn 10010

int in[maxn],next[maxn],level[maxn];
int father[maxn],ancestor[maxn];
bool used[maxn];
int n,cnt;
vector<int>q[maxn];

struct edge
{
    int to,next;
}e[maxn*maxn];

void insert(int from,int to)
{
    e[cnt].to=to;
    e[cnt].next=next[from];
    next[from]=cnt++;
}

int getfather(int x)
{
    if(father[x]==x)
    return x;
    return father[x]=getfather(father[x]);
}

void uni(int x,int y)
{
    int a=getfather(x);
    int b=getfather(y);
    if(a==b)
    return;
    if(level[a]>level[b])
    {
        father[b]=a;
        level[a]+=level[b];
    }
    else
    {
        father[a]=b;
        level[b]+=level[a];
    }
}

void lca(int pos)
{
    ancestor[pos]=pos;
    int id=next[pos];
    while(id!=-1)
    {
        int to=e[id].to;
        lca(to);
        uni(pos,to);
        ancestor[getfather(pos)]=pos;
        id=e[id].next;
    }
    used[pos]=true;
    FOR(i,q[pos].size())
    {
        int to=q[pos][i];
        if(used[to])
        {
            printf("%d\n",ancestor[getfather(to)]);     //这一步输出的是pos和to的LCA
        }
    }
}

void ini()
{
    cnt=0;
    MEM(in);
    MEM(used);
    MEST(next);
    rep(i,n)
    {
        father[i]=i;
        level[i]=1;
        q[i].clear();
    }
}

int main()
{
    int t,x,y;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d",&n);
        ini();
        FOR(i,n-1)
        {
            scanf("%d%d",&x,&y);
            insert(x,y);
            in[y]++;
        }
        scanf("%d%d",&x,&y);
        q[x].push_back(y);
        q[y].push_back(x);
        rep(i,n)
        {
            if(in[i]==0)
            {
                lca(i);
                break;
            }
        }
    }
    return 0;
}

