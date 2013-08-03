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

int n,m,cnt,Bcnt;
bool connect[1001][1001],instack[1001];
int dfn[1001],low[1001],level[1001];
stack<int>s;

struct node
{
    int a,b;
} e[1001];

void tarjan(int i)
{
    low[i]=dfn[i]=cnt++;
    s.push(i);
    instack[i]=true;
    FOR(j,2*m)
    {
        if(!connect[i][j])
            continue;
        if(!dfn[j])
        {
            tarjan(j);
            low[i]=min(low[i],low[j]);
        }
        else if(instack[j])
        {
            low[i]=min(low[i],dfn[j]);
        }
    }
    if(dfn[i]==low[i])
    {
        Bcnt++;
        int j;
        do
        {
            j=s.top();
            s.pop();
            level[j]=Bcnt;
            instack[j]=false;
        }
        while(i!=j);
    }
}

void ini()
{
    MEM(connect);
    MEM(dfn);
    MEM(low);
    MEM(instack);
    MEM(level);
    cnt=0;
    Bcnt=0;
}

int main()
{
    //freopen("1004.in","r",stdin);
    //freopen("out.txt","w",stdout);
    int x,y;
    while(scanf("%d%d",&n,&m)!=EOF)
    {
        ini();
        FOR(i,m)
        {
            scanf("%d%d",&x,&y);
            e[i].a=min(x,y);
            e[i].b=max(x,y);
        }
        for(int i=0; i<m; i++)
        {
            for(int j=i+1; j<m; j++)
            {
                if(e[i].a<e[j].a&&e[i].b>e[j].a&&e[i].b<e[j].b)
                {
                    connect[i][j+m]=true;
                    connect[i+m][j]=true;
                    connect[j+m][i]=true;
                    connect[j][i+m]=true;
                }
                if(e[j].a<e[i].a&&e[j].b>e[i].a&&e[j].b<e[i].b)
                {
                    connect[i][j+m]=true;
                    connect[i+m][j]=true;
                    connect[j+m][i]=true;
                    connect[j][i+m]=true;
                }
            }
        }
        FOR(i,2*m)
        {
            if(!dfn[i])
            {
                tarjan(i);
            }
        }
        bool flag=true;
        FOR(i,m)
        {
            if(level[i]==level[i+m])
            {
                flag=false;
                break;
            }
        }
        if(flag)
        {
            printf("panda is telling the truth...\n");
        }
        else
        {
            printf("the evil panda is lying again\n");
        }
    }
    return 0;
}
