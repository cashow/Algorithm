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

int connect[1001][1001],farm[1001];
bool used[1001];
int n,m;
struct node
{
    int x,y;
} line;
vector<node>v;                      //v用来存储构成最小生成树的边

int prim()
{
    int ans=0,len=1;
    MEM(used);
    used[0]=true;
    farm[0]=0;                      //任选一点作为起始点
    for(int p=1; p<n; p++)          //n-1重循环
    {
        int pre=-1,next,minn=-1;    //next是下一个要加入的点
        FOR(i,len)                  //枚举已用过的点
        {
            FOR(j,n)                //枚举没用过的点
            {
                if(used[j]||connect[farm[i]][j]==-1)        //farm[i]到j必须要有边
                    continue;
                if(minn==-1||minn>connect[farm[i]][j])      //取距离最小的点
                {
                    pre=farm[i];
                    next=j;
                    minn=connect[farm[i]][j];
                }
            }
        }
        if(pre==-1)                 //pre=-1表示上面的循环没有找到符合条件的边,但此时还没有加入n-1条边
            return -1;              //这说明删去一条边后生成的不是一颗树,因此没有最小生成树
        used[next]=true;
        farm[len++]=next;
        ans+=minn;                  //minn是next点与已经加入过的点的距离的最小值

        line.x=pre;
        line.y=next;
        v.push_back(line);
    }
    return ans;
}

int main()
{
    int t,sum,tem;
    bool flag;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d",&n,&m);
        FOR(i,n)
        {
            FOR(j,n)
            {
                connect[i][j]=-1;
            }
        }
        flag=true;      //flag用来记录是否有最小生成树
        v.clear();      //一定不要忘了清空vector！！！
        int x,y,w;
        FOR(i,m)
        {
            scanf("%d%d%d",&x,&y,&w);
            x--;        //题目中x的范围是1~n,因此x--,把x的范围改为0~n-1
            y--;
            connect[x][y]=w;
            connect[y][x]=w;
        }
        sum=prim();         //没有删边之前的最小生成树的权值之和
        int len=v.size();
        FOR(i,len)          //v中0~len-1的数据是最小生成树的边,以后的prim会增加v中的元素,但不影响前len-1个元素
        {
            int before=connect[v[i].x][v[i].y];     //记录下变化前的数值
            connect[v[i].x][v[i].y]=-1;             //删去边v[i].x->v[i].y
            connect[v[i].y][v[i].x]=-1;             //删去边v[i].y->v[i].x
            tem=prim();
            if(sum==tem)
            {
                flag=false;
                break;
            }
            connect[v[i].x][v[i].y]=before;         //还原边v[i].x->v[i].y
            connect[v[i].y][v[i].x]=before;
        }
        if(flag)
        {
            printf("%d\n",sum);
        }
        else
        {
            printf("Not Unique!\n");
        }
    }
    return 0;
}
