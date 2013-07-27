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

int n,m,index,cnt,Bcnt;
bool instack[10001];
int low[10001],dfn[10001],level[10001],next[10001];
stack<int>s;

struct edge
{
    int to,next;
} e[2000016];

void insert(int a,int b)
{
    e[cnt].to=b;
    e[cnt].next=next[a];
    next[a]=cnt++;
}

void tarjan(int i)              //和普通的tarjan没有区别
{
    low[i]=dfn[i]=index++;
    instack[i]=true;
    s.push(i);
    int id=next[i];
    for(int id=next[i];id!=-1;id=e[id].next)
    {
        int j=e[id].to;
        if(!dfn[j])
        {
            tarjan(j);
            low[i]=min(low[i],low[j]);
        }
        else if(instack[j])
            low[i]=min(low[i],dfn[j]);
    }
    int j;
    if(dfn[i]==low[i])
    {
        Bcnt++;
        do
        {
            j=s.top();
            s.pop();
            level[j]=Bcnt;      //level值相同表示属于同一个强连通分量
            instack[j]=false;
        }
        while(j!=i);
    }
}

void ini()
{
    MEM(instack);
    MEM(dfn);
    MEM(low);
    MEM(level);
    MEST(next);
    index=1;
    cnt=0;
    Bcnt=0;
}

int main()
{
    int a1,a2,c1,c2;
    while(scanf("%d%d",&n,&m)!=EOF)
    {
        ini();
        FOR(i,m)
        {
            scanf("%d%d%d%d",&a1,&a2,&c1,&c2);
            insert(2*a1+c1,2*a2+1-c2);          //假如a,b是夫妻，c,d是夫妻,且a,c有矛盾
            insert(2*a2+c2,2*a1+1-c1);          //则选a必选d,选c必选b
        }
        FOR(i,2*n)
        {
            if(!dfn[i])
            {
                tarjan(i);
            }
        }
        bool flag=true;
        FOR(i,n)
        {
            if(level[2*i]==level[2*i+1])        //假如2*i和2*i+1属于同一个强连通分量
                flag=false;                     //则选2*i必选2*i+1，此时不符合条件，即夫妻不能同时出场
        }
        if(flag)
            printf("YES\n");
        else
            printf("NO\n");
    }
    return 0;
}
