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

#define maxnum 501

int connect[maxnum][maxnum];
bool used[maxnum];
int wet[maxnum];
int combine[maxnum];
int start,end,minCut,n,m;

void prim()  //���������
{
    int maxx,tmp;
    MEM(used);
    MEM(wet);
    start=end=-1;
    FOR(i,n)
    {
        maxx=-1;
        FOR(j,n)
        {
            if(!combine[j]&&!used[j]&&wet[j]>maxx)
            {
                tmp = j;
                maxx = wet[j];
            }
        }
        if (end == tmp)
            return;
        start = end;
        end = tmp;
        minCut = maxx;
        used[tmp] = true;
        FOR(j,n)
        {
            if(!combine[j]&&!used[j])
            {
                wet[j]+=connect[tmp][j];
            }
        }
    }
}

int stoer_wagner()
{
    MEM(combine);
    int ans=-1;          //min=MAXINT,�̶�һ������P
    FOR(i,n-1)
    {
        prim();           //�ӵ�P�á����ơ�prim��s�㷨��չ���������������,��¼�����չ�Ķ���������չ�ı�
        if (ans==-1||minCut < ans)
            ans = minCut;
        //���������չ���Ķ�����и�ֵ������˶������������б�Ȩ�ͣ�,����minС����min
        if (ans == 0)
            return 0;
        combine[end] = 1;
        FOR(j,n)
        {
            if(!combine[j])
            {
                //�ϲ������չ�������ߵ������˵�Ϊһ������
                connect[start][j] += connect[end][j];
                connect[j][start] += connect[j][end];
            }
        }
    }
    return ans;
}

int main()
{
    while(scanf("%d%d",&n,&m)!=EOF)
    {
        MEM(connect);
        FOR(i,m)
        {
            int a,b,c;
            scanf("%d%d%d",&a,&b,&c);
            connect[a][b]+=c;
            connect[b][a]+=c;
        }
        printf ("%d\n", stoer_wagner());
    }
    return 0;
}
