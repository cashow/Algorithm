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

int connect[101][101],n,father[101];

struct node
{
    int x,y,weight;
} p;
bool operator<(node a,node b)
{
    return a.weight<b.weight;
}

vector<node>v;

int getfather(int x)        //并查集查找x的father数值
{
    if(father[x]==x)
        return x;
    return father[x]=getfather(father[x]);
}

int kruskal()
{
    int ans=0,cnt=0;
    FOR(i,v.size())
    {
        if(cnt==n-1)        //添加n-1条边后生成树就已经完成了
            break;
        if(getfather(v[i].x)!=getfather(v[i].y))    //x和y必须属于不同的集合
        {
            father[father[v[i].x]]=father[v[i].y];  //并查集合并x,y
            ans+=v[i].weight;
            cnt++;
        }
    }
    return ans;
}

int main()
{
    while(scanf("%d",&n)!=EOF)
    {
        FOR(i,n)            //每个点都和其他点属于不同的集合
        {
            father[i]=i;
        }
        v.clear();          //一定要记得初始化
        FOR(i,n)
        {
            FOR(j,n)
            {
                scanf("%d",&connect[i][j]);
            }
        }
        FOR(i,n)
        {
            FOR(j,n)
            {
                p.x=i;
                p.y=j;
                p.weight=connect[i][j];
                v.push_back(p);
            }
        }
        sort(v.begin(),v.end());
        printf("%d\n",kruskal());
    }
    return 0;
}
