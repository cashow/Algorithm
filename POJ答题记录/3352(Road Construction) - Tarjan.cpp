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

int outd[10001],start[10001],dfn[10001],low[10001],same[10001];     //start�����ʾ��iλ�ڵ����ʼλ��
int cnt,index;
bool used[5001];
int n,m,a,b;
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
    memset(start,-1,sizeof(start));
    MEM(dfn);
    MEM(low);
    MEM(outd);
}

void tarjan(int i,int father)
{
    dfn[i]=low[i]=++index;  //dfn�����ʾdfs��ʱ�����low��������ȷ��ʲôʱ��ջ
    int id=start[i];
    while(id!=-1)
    {
        int j=e[id].to;
        if(j==father)
        {
            id=e[id].next;
            continue;
        }
        if(!dfn[j])         //����û�з��ʹ�j�������j������low��ֵ
        {
            tarjan(j,i);
        }
        low[i]=min(low[i],low[j]);

        id=e[id].next;
    }
}

void Outdegree()
{
    for(int i=1; i<=n; i++)                         //����
    {
        MEM(used);
        int id=start[i];
        while(id!=-1)
        {
            if(low[e[id].to]!=low[i]&&!used[e[id].to])           //i�����ӵĵ���i����ͬһ��
            {
                outd[low[i]]++;                      //��i�ĳ��ȼ�1
                used[e[id].to]=true;
            }
            id=e[id].next;
        }
    }
    int count=0;
    for(int i=1; i<=n; i++)
    {
        if(outd[i]==1)
        {
            count++;
        }
    }
    printf("%d\n",(count+1)/2);
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
            insert(b,a);
        }
        FOR(i,n)
        {
            if(dfn[i+1]==0)
            {
                tarjan(i+1,-1);
            }
        }
        Outdegree();
//        FOR(i,n)
//        {
//            printf("dfn[%d]=%d,low[%d]=%d,outd[%d]=%d\n",i+1,dfn[i+1],i+1,low[i+1],i+1,outd[i+1]);
//        }
    }
    return 0;
}
