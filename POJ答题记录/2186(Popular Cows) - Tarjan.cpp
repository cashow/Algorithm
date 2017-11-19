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

int start[10001],dfn[10001],low[10001],same[10001];     //start数组表示第i位节点的起始位置
int cnt,index,Bcnt;
int n,m,a,b;
bool instack[10001];
stack<int>s;
struct edge
{
    int to,next;
} e[50001];

void insert(int a,int b)
{
    e[cnt].to=b;
    e[cnt].next=start[a];
    start[a]=cnt++;
}
void ini()
{
    index=0;
    cnt=0;
    Bcnt=0;
    memset(start,-1,sizeof(start));
    MEM(instack);
    MEM(dfn);
    MEM(low);
}

void tarjan(int i)
{
    int j;
    dfn[i]=low[i]=++index;
    instack[i]=true;
    s.push(i);
    int id=start[i];
    while(id!=-1)
    {
        j=e[id].to;
        if(!dfn[j])         //假如没有访问过j点则访问j并更新low的值
        {
            tarjan(j);
            low[i]=min(low[i],low[j]);
        }
        else if (instack[j])
            low[i]=min(low[i],dfn[j]);
        id=e[id].next;
    }
    if (dfn[i]==low[i])     //当dfn(i)=low(i)时，以i为根的搜索子树上所有节点是一个强连通分量
    {
        Bcnt++;
        //cout<<i+1<<endl;
        do                  //找到一个强连通分量后，将栈中的节点都记录下来放入same数组
        {
            j=s.top();
            s.pop();
            instack[j]=false;
            same[j]=Bcnt;
        }
        while(j!=i);
    }
}

void Outdegree()
{
    int outd[10001],ans,count,tmpi,i;
    MEM(outd);
    for(i=1;i<=n;i++)                           //缩点
    {
        int id=start[i];
        while(id!=-1)
        {
            if(same[e[id].to]!=same[i])         //i所连接的点不能到达i
                outd[same[i]]++;                //则i所在的一组点都不符合条件
            id=e[id].next;
        }
    }
    count=0;
    for(i=1;i<=Bcnt;i++)
    {
        if(outd[i]==0)
        {
            tmpi=i;
            count++;
        }
    }
    ans=0;
    if(count==1)            //假如有两个强连通分量都符合条件，则这两个强连通分量可以合并
    {
        for(i=1;i<=n;i++)
        {
            if(same[i]==tmpi)
                ans++;
        }
        printf("%d\n",ans);
        return;
    }
    printf("0\n");          //有多个强连通分量符合条件时不成立
}

int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    while(scanf("%d%d",&n,&m)!=EOF)
    {
        ini();
        FOR(i,m)
        {
            scanf("%d%d",&a,&b);
            insert(a,b);
            //insert(b,a);
        }
        FOR(i,n)
        {
            if(dfn[i+1]==0)
            {
                tarjan(i+1);
            }
        }
        Outdegree();
    }
    return 0;
}
