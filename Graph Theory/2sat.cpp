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

void tarjan(int i)              //����ͨ��tarjanû������
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
            level[j]=Bcnt;      //levelֵ��ͬ��ʾ����ͬһ��ǿ��ͨ����
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
            insert(2*a1+c1,2*a2+1-c2);          //����a,b�Ƿ��ޣ�c,d�Ƿ���,��a,c��ì��
            insert(2*a2+c2,2*a1+1-c1);          //��ѡa��ѡd,ѡc��ѡb
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
            if(level[2*i]==level[2*i+1])        //����2*i��2*i+1����ͬһ��ǿ��ͨ����
                flag=false;                     //��ѡ2*i��ѡ2*i+1����ʱ�����������������޲���ͬʱ����
        }
        if(flag)
            printf("YES\n");
        else
            printf("NO\n");
    }
    return 0;
}
