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

void prim()  //最大生成树
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
    int ans=-1;          //min=MAXINT,固定一个顶点P
    FOR(i,n-1)
    {
        prim();           //从点P用“类似”prim的s算法扩展出“最大生成树”,记录最后扩展的顶点和最后扩展的边
        if (ans==-1||minCut < ans)
            ans = minCut;
        //计算最后扩展到的顶点的切割值（即与此顶点相连的所有边权和）,若比min小更新min
        if (ans == 0)
            return 0;
        combine[end] = 1;
        FOR(j,n)
        {
            if(!combine[j])
            {
                //合并最后扩展的那条边的两个端点为一个顶点
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
