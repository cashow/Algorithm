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

#define maxn 110
#define inf 999999999

struct point
{
    int x,y;
} pos_k[maxn],pos_h[maxn];

int n,m;
int dis[maxn][maxn];
int lx[maxn],ly[maxn];
int linky[maxn];
int used_left[maxn],used_right[maxn];
int slack[maxn];
int nx,ny;

bool dfs(int x)
{
    used_left[x] = true;
    rep(y,ny)
    {
        if(used_right[y])
            continue;
        int t = lx[x] + ly[y] - dis[x][y];
        if(t==0)
        {
            used_right[y] = true;
            if(linky[y]==-1 || dfs(linky[y]))
            {
                linky[y] = x;
                return true;        //找到增广轨
            }
        }
        else
        {
            slack[y]=min(slack[y],t);
        }
    }
    return false;                   //没有找到增广轨（说明顶点x没有对应的匹配,与完备匹配(相等子图的完备匹配)不符）
}

int KM()                //返回最优匹配的值
{
    MEST(linky);
    MEM(ly);
    rep(i,nx)
    {
        lx[i] = -inf;
        rep(j,nx)
        {
            lx[i] = max(lx[i],dis[i][j]);
        }
    }

    rep(x,nx)
    {
        rep(i,nx)
        {
            slack[i] = inf;
        }
        while(1)
        {
            MEM(used_left);
            MEM(used_right);
            if(dfs(x))                     //找到增广轨,退出
                break;
            int d = inf;
            rep(i,nx)          //没找到,对l做调整(这会增加相等子图的边),重新找
            {
                if(!used_right[i] && d > slack[i])
                    d = slack[i];
            }
            rep(i,nx)
            {
                if(used_left[i])
                    lx[i] -= d;
            }
            rep(i,ny)
            {
                if(used_right[i])
                    ly[i] += d;
                else
                    slack[i] -= d;
            }
        }
    }
    int result = 0;
    rep(i,ny)
    {
        if(linky[i]>-1)
            result += dis[linky[i]][i];
    }
    return result;
}


int dist(point a,point b)
{
    int dis=0;
    dis+=(a.x-b.x)>0?(a.x-b.x):(b.x-a.x);
    dis+=(a.y-b.y)>0?(a.y-b.y):(b.y-a.y);
    return dis;
}

int main()
{
    while(1)
    {
        scanf("%d%d",&n,&m);
        if(n+m==0)
            break;
        nx=0,ny=0;

        getchar();
        char buf[maxn];
        for(int i=1; i<=n; i++)
        {
            gets(buf);
            for(int j=0; j<m; j++)
            {
                if(buf[j]=='H')
                {
                    pos_h[ny].x=i;
                    pos_h[ny++].y=j+1;
                }
                else if(buf[j]=='m')
                {
                    pos_k[nx].x=i;
                    pos_k[nx++].y=j+1;
                }
            }
        }

        for(int i=0; i<nx; i++)
        {
            for(int j=0; j<ny; j++)
            {
                dis[i+1][j+1]=-dist(pos_k[i],pos_h[j]);//取负
            }
        }
        printf("%d\n",-KM());
    }
    return 0;
}
