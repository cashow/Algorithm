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

int n,m,cnt,Bcnt;
bool connect[2001][2001],instack[2001];
int dfn[2001],low[2001],level[2001];
stack<int>s;

struct node
{
    int a,b;
} e[2001];

void tarjan(int i)
{
    low[i]=dfn[i]=cnt++;
    s.push(i);
    instack[i]=true;
    FOR(j,2*n)
    {
        if(!connect[i][j])
            continue;
        if(!dfn[j])
        {
            tarjan(j);
            low[i]=min(low[i],low[j]);
        }
        else if(instack[j])
        {
            low[i]=min(low[i],dfn[j]);
        }
    }
    if(dfn[i]==low[i])
    {
        Bcnt++;
        int j;
        do
        {
            j=s.top();
            s.pop();
            level[j]=Bcnt;
            instack[j]=false;
        }
        while(i!=j);
    }
}

void ini()
{
    MEM(connect);
    MEM(dfn);
    MEM(low);
    MEM(instack);
    MEM(level);
    cnt=0;
    Bcnt=0;
}

void insert(int x,int y)
{
    printf("insert: %d %d\n",x,y);
    connect[x][y]=true;
    connect[y][x]=true;
}

bool solve()
{
    FOR(i,2*n)
    {
        if(!dfn[i])
        {
            tarjan(i);
        }
    }
    FOR(i,n)
    {
        if(level[i]==level[i+n])
        {
            return false;
        }
    }
    return true;
}

int main()
{
    //freopen("1004.in","r",stdin);
    //freopen("out.txt","w",stdout);
    int x,y,c;
    string op;
    while(scanf("%d%d",&n,&m)!=EOF)
    {
        ini();
//        FOR(i,n)
//        {
//            connect[i][n+i]=true;
//            connect[n+i][i]=true;
//        }
        FOR(i,m)
        {
            cin>>x>>y>>c>>op;
            if(op=="AND")
            {
                if(c==0)                        //x&y=0
                {
                    connect[x+n][y]=true;       //x:1->y:0
                    connect[y+n][x]=true;       //y:1->x:0
                }
                else                            //x&y=1
                {
                    connect[x+n][y+n]=true;     //x:1->y:1
                    connect[y+n][x+n]=true;     //y:1->x:1
                    connect[x][x+n]=true;       //x:0->x:1,这表示x不能取0
                    connect[y][y+n]=true;       //y:0->y:1
                }
            }
            if(op=="OR")
            {
                if(c==0)                        //x||y=0
                {
                    connect[x][y]=true;         //x:0->y:0
                    connect[y][x]=true;         //y:0->x:0
                    connect[x+n][x]=true;       //x:1->x:0,这表示x不能取1
                    connect[y+n][y]=true;       //y:1->y:0
                }
                else                            //x||y=1
                {
                    connect[x][y+n]=true;       //x:0->y:1
                    connect[y][x+n]=true;       //y:0->x:1
                }
            }
            if(op=="XOR")
            {
                if(c==0)                        //x^y=0
                {
                    connect[x][y]=true;         //x:0->y:0
                    connect[x+n][y+n]=true;     //x:1->y:1
                    connect[y][x]=true;         //y:0->x:0
                    connect[y+n][x+n]=true;     //y:1->x:1
                }
                else                            //x^y=1
                {
                    connect[x][y+n]=true;       //x:0->y:1
                    connect[x+n][y]=true;       //x:1->y:0
                    connect[y][x+n]=true;       //y:0->x:1
                    connect[y+n][x]=true;       //y:1->x:0
                }
            }
        }

        if(solve())
        {
            printf("YES\n");
        }
        else
        {
            printf("NO\n");
        }
//        FOR(i,2*n)
//        {
//            printf("%d ",level[i]);
//        }
//        printf("\n");
    }
    return 0;
}
