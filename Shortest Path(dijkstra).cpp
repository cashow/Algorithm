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

int connect[1001][1001],dis[1001];
int n,m;
bool used[1001];

void dijkstra()
{
    int pos=0,minn;
    FOR(i,n-1)              //n-1��ѭ��
    {
        used[pos]=true;
        FOR(j,n)            //ͨ��posȥ�������е��disֵ
        {
            if(dis[pos]+connect[pos][j]<dis[j])
                dis[j]=dis[pos]+connect[pos][j];
        }
        minn=99999999;
        FOR(j,n)            //����һ��û�ù���disֵ��С�ĵ�
        {
            if(!used[j]&&dis[j]<minn)
            {
                minn=dis[j];
                pos=j;
            }
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
            dis[i]=99999999;
            FOR(j,n)
            {
                connect[i][j]=99999999;
            }
        }
        dis[0]=0;
        MEM(used);
        FOR(i,m)
        {
            scanf("%d%d%d",&x,&y,&w);               //���ر�
            x--;
            y--;
            connect[x][y]=min(connect[x][y],w);     //�����ر�ʱȡx->y����Сֵ����x->y�ľ���
            connect[y][x]=min(connect[y][x],w);
        }
        dijkstra();
        printf("%d\n",dis[n-1]);
    }
    return 0;
}
