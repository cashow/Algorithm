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

int outd[10001],lastshow[10001],dfn[10001],low[10001],same[10001];     //lastshow�����ʾ��iλ�ڵ����ʼλ��
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
    e[cnt].next=lastshow[a];
    lastshow[a]=cnt++;
}
void ini()
{
    index=0;
    cnt=0;
    memset(lastshow,-1,sizeof(lastshow));
    MEM(dfn);
    MEM(low);
    MEM(outd);
}

void tarjan(int i,int father)
{
    dfn[i]=low[i]=++index;  //dfn�����ʾdfs��ʱ���,low��������ȷ��ʲôʱ��ջ
    int id=lastshow[i];     //������ͼ��,��ջ�����еĵ�����ͬһ��ǿ��ͨ����
    while(id!=-1)           //������ͼ��,lowֵ��ͬ�ĵ㼴����ͬһ��ǿ��ͨ����
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
        low[i]=min(low[i],low[j]);      //lowֵ��ͬ��ʾ��ͬһ��ǿ��ͨ������

        id=e[id].next;
    }
}

void Outdegree()
{
    for(int i=1; i<=n; i++)             //����
    {
        MEM(used);
        int id=lastshow[i];
        while(id!=-1)
        {
            if(low[e[id].to]!=low[i]&&!used[e[id].to])  //i�����ӵĵ���i����ͬһ��
            {
                outd[low[i]]++;         //��low[i]�ĳ��ȼ�1,��ʱ��lowֵ��ͬ�ĵ㵱��һ����
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
    while(scanf("%d%d",&n,&m)!=EOF)
    {
        ini();
        FOR(i,m)
        {
            scanf("%d%d",&a,&b);        //����ͼ,a->b��b->a��Ҫ�ӽ�ȥ
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
    }
    return 0;
}
