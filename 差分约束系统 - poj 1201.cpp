#include <cstdio>
#include <queue>
#include <cstring>

using namespace std;

const double eps=1e-8;

#define MEM(a) memset(a,0,sizeof(a));
#define FOR(i,n) for(int i=0;i<n;i++)

#define maxm 250000
#define maxn 70000

struct edge
{
    int to,next,value;
} e[maxm];
int next[maxn],dis[maxn];
int cnt,n,left,right;
bool inqueue[maxn];
queue<int>q;

void insert(int a,int b,int c)
{
    e[cnt].to=b;
    e[cnt].next=next[a];
    e[cnt].value=c;
    next[a]=cnt++;
}

void ini()
{
    cnt=0;
    MEM(inqueue);
    memset(next,-1,sizeof(next));
    memset(dis,-1,sizeof(dis));
}

void spfa()
{
    q.push(left);
    dis[left]=0;
    while(!q.empty())
    {
        int p=q.front();
        q.pop();
        inqueue[p]=false;
        int id=next[p];
        while(id!=-1)
        {
            int to=e[id].to;
            if(dis[to]<dis[p]+e[id].value)
            {
                dis[to]=dis[p]+e[id].value;
                if(!inqueue[to])
                {
                    q.push(to);
                    inqueue[to]=true;
                }
            }
            id=e[id].next;
        }
    }
}

int main()
{
    int a,b,c;
    scanf("%d",&n);
    ini();
    FOR(i,n)
    {
        scanf("%d%d%d",&a,&b,&c);
        b++;
        if(i==0)
        {
            left=a;
            right=b;
        }
        left=min(a,left);
        right=max(b,right);
        insert(a,b,c);
    }
    for(int i=left-1; i<=right+1; i++)
    {
        insert(i,i+1,0);
        insert(i,i-1,-1);
    }
    spfa();
    printf("%d\n",dis[right]);
    return 0;
}
