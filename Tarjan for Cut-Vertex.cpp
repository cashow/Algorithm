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

int n,index,ans,son;
bool connect[101][101],gedian[101];
int dfn[101],low[101];

void tarjan(int i,int father)
{
    dfn[i]=low[i]=++index;
    FOR(j,n)
    {
        if(father==j||!connect[i][j])
            continue;
        if(dfn[j]==0)
        {
            if(i==0)
                son++;
            tarjan(j,i);
            low[i]=min(low[i],low[j]);
            if(i!=0&&dfn[i]<=low[j])
                gedian[i]=true;
            if(i==0&&son>1)             //如果是根节点则需要判断是否有两棵子树
                gedian[i]=true;
        }
        else
            low[i]=min(low[i],dfn[j]);
    }
}

void ini()
{
    MEM(dfn);
    MEM(low);
    MEM(connect);
    MEM(gedian);
    ans=0;
    index=0;
    son=0;
}

int main()
{
    int x,y;
    while(1)
    {
        scanf("%d",&n);
        if(n==0)
            break;
        ini();                  //这个一定不能漏了
        while(1)
        {
            scanf("%d",&x);
            if(x==0)
                break;
            x--;
            while(getchar()!='\n')      //这题的读入方式好特别...
            {
                scanf("%d",&y);
                y--;
                connect[x][y]=true;
                connect[y][x]=true;
            }
        }

        tarjan(0,-1);   //因为题目保证图连通,则随便取一点作为起始点即可遍历整个图

        ans=0;
        FOR(i,n)
        {
            if(gedian[i])
            {
                ans++;
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}
