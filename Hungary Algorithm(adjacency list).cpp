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

#define maxn 202
int n,m,match,cnt;
int mat[maxn],next[maxn];
bool used[maxn];
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

bool crosspath(int k)
{
    int id=next[k];
    while(id!=-1)               //从邻接表中列举 k 能关联到顶点 j
    {
        int j=e[id].to;
        if (!used[j])
        {
            used[j]=true;                           //j 不在增广路上
            if (mat[j]==-1 || crosspath(mat[j]))
            {
                mat[j]=k;
                return true;
            }
        }
        id=e[id].next;
    }
    return false;
}

void hungary()
{
    match=0;
    MEST(mat);
    FOR(i,n)
    {
        MEM(used);
        if (crosspath(i))
            match++;
    }
}

int main()
{
    while(scanf("%d%d",&n,&m)!=EOF)
    {
        int b,t,cnt=0;
        MEST(next);
        FOR(i,n)
        {
            scanf("%d",&t);
            while(t--)
            {
                scanf("%d",&b);
                b--;
                insert(i,b);
            }
        }
        hungary();
        printf("%d\n",match);
    }
    return 0;
}
