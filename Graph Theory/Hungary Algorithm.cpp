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

#define MAX 202

int n,m,match;
int adjl[MAX][MAX];
int mat[MAX];
bool used[MAX];

bool crosspath(int k)
{
    for (int i=1; i<=adjl[k][0]; i++)               //从邻接表中列举k能关联到顶点j
    {
        int j=adjl[k][i];
        if (!used[j])                               //j不在增广路上
        {
            used[j]=true;
            if (mat[j]==0 || crosspath(mat[j]))     //j是未盖点或者从j的对应项出发有可增广路
            {
                mat[j]=k;
                return true;
            }
        }
    }
    return false;
}

void hungary()
{
    match=0;
    MEM(mat);
    for (int i=1; i<=m; i++)
    {
        MEM(used);
        if (crosspath(i))               //从i的对应项出有可增广路
            match++;
    }
}

int main()
{
    while(scanf("%d%d",&n,&m)!=EOF)
    {
        int a,b,t;
        MEM(adjl);
        FOR(i,n)
        {
            scanf("%d",&t);
            while(t--)
            {
                scanf("%d",&b);
                a=i+1;
                adjl[a][++adjl[a][0]]=b;
            }
        }
        hungary();
        printf("%d\n",match);
    }
    return 0;
}
