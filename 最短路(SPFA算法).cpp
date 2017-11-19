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

int dis[1001],countt[1001];     //countt��¼i���������еĴ���,����n����˵���и���
int n,m;                    //����û�и�Ȩ·,���ⲻ��Ҫcountt����

struct edge             //�ڽӱ�
{
    int to,next,weight;
} e[4001];
int lastshow[1001];
int cnt;

void insert(int a,int b,int weight)
{
    e[cnt].to=b;
    e[cnt].next=lastshow[a];
    e[cnt].weight=weight;
    lastshow[a]=cnt++;
}
queue<int>q;

void spfa()             //��bfsȥ����dis����
{
    q.push(0);          //��0��ʼ������չ
    countt[0]++;
    while(!q.empty())
    {
        int p=q.front();
        q.pop();
        int id=lastshow[p];
        while(id!=-1)
        {
            int j=e[id].to;
            if(dis[j]>dis[p]+e[id].weight)      //�����ܸ���dis[j],��˵��ͨ��j���п��ܸ��µ�������ľ���
            {
                dis[j]=dis[p]+e[id].weight;
                countt[j]++;
                q.push(j);
            }
            id=e[id].next;
        }
    }
}

int main()
{
    int x,y,w;
    while(scanf("%d%d",&m,&n)!=EOF)
    {
        FOR(i,n)
        {
            lastshow[i]=-1;
            dis[i]=99999999;
        }
        dis[0]=0;
        cnt=0;
        while(!q.empty())
            q.pop();
        FOR(i,m)
        {
            scanf("%d%d%d",&x,&y,&w);
            x--;
            y--;
            insert(x,y,w);
            insert(y,x,w);
        }
        spfa();
        printf("%d\n",dis[n-1]);
    }
    return 0;
}
