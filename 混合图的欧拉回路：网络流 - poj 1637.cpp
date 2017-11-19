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
#define FOR(i,n) for(int i=0;i<n;i++)
#define maxn 2001
#define maxm 9000


struct edge
{
    int to,from,next,value,num;         //num��¼���������ߵı��
} e[maxm];

int level[maxn],pre[maxn],next[maxn];
int minadd[maxn];
int out[maxn],in[maxn],dif[maxn],father[maxn];
int n,m,ans,cnt,sum;
queue<int>q;

void insert(int from,int to,int value)
{
    e[cnt].to=to;
    e[cnt].from=from;
    e[cnt].next=next[from];
    e[cnt].value=value;
    e[cnt].num=cnt;
    next[from]=cnt++;

    swap(from,to);

    e[cnt].to=to;
    e[cnt].from=from;
    e[cnt].next=next[from];
    e[cnt].value=0;
    e[cnt].num=cnt;
    next[from]=cnt++;
}

bool bfs(int start,int end)               //����level��ȷ���Ƿ��ܵ�����
{
    q.push(start);
    memset(level,-1,sizeof(level));
    level[start]=0;
    while(!q.empty())
    {
        int p=q.front();
        q.pop();
        int id=next[p];
        while(id!=-1)
        {
            int to=e[id].to;
            if(e[id].value>0&&level[to]==-1)
            {
                q.push(to);
                level[to]=level[p]+1;
            }
            id=e[id].next;
        }
    }
    return level[end]!=-1;              //�ܵ���end�򷵻�true�������򷵻�false
}

void dfs(int start,int end)
{
    int pos=start,to,change;
    int minn,minpos;
    minn=-1;
    while(1)                            //�ǵݹ�dfs
    {
        bool flag=false;
        int id=next[pos];               //��һ�������ߵ�·
        while(id!=-1)
        {
            int i=e[id].to;
            if(level[i]==level[pos]+1&&e[id].value>0)
            {
                flag=true;
                to=i;
                break;
            }
            id=e[id].next;
        }

        if(flag)                            //�ҵ�һ�������ߵ�·��
        {
            pre[to]=id;                     //pre[to]��¼����pos->to�����ߵ�id
            if(minadd[pos]==-1)             //minadd[pos]ȡ��С������endʱminadd[end]Ϊ����·�ɼӵ��������
                minadd[to]=e[id].value;
            else
                minadd[to]=min(minadd[pos],e[id].value);
            pos=to;			                //���ҵ��Ľڵ㿪ʼ�ڲ��ͼ����·
            if(pos==end) 	                //�ҵ�t������
            {
                ans+=minadd[end];           //minadd[end]:����·�ɼӵ��������
                change=minadd[end];
                int id=pre[end];
                while(1)                    //һֱ�ӻ����˵�Դ�㣬����ÿ��·������
                {
                    minadd[e[id].to]-=change;
                    e[id].value-=change;
                    e[id^1].value+=change;
                    if(e[id].value==0)
                    {
                        pos=e[id].from;           //u���˵�������Ϊ0��·�ĵ�֮ǰ
                    }
                    if(pre[e[id].from]==-1)
                        break;
                    id=pre[e[id].from];
                }
            }
        }
        else
        {
            if(pos!=start)	            //���pos!=start��ô����·�߲�ͨ�Ļ�����pos����һ���ڵ�����ҡ�
            {
                level[pos]=-2;          //�൱�ڴӲ��ͼ��ɾ������ڵ㡣
                pos=e[pre[pos]].from;           //dfs����
            }
            else                        //�����Դ���Ҳ�������·���ͽ����ˡ�
                return ;
        }
    }
}

int dinic(int s,int t)          //���s�㵽t����������
{
    ans=0;
    while(bfs(s,t))             //ÿһ����������·��,���ò��ͼ
    {
        memset(pre,-1,sizeof(pre));		        //dfs�У������Ҫ���ݣ��ͻ��ݵ�pre�еĽڵ㡣
        memset(minadd,-1,sizeof(minadd));       //minadd��������ʣ������
        dfs(s,t);
    }
    return ans;
}

int getfather(int x)
{
    if(father[x]==x)
        return x;
    return father[x]=getfather(father[x]);
}

void ini()
{
    memset(next,-1,sizeof(next));
    MEM(in);
    MEM(out);
    cnt=0;
    sum=0;
}

int main()
{
    int x,y,z,t;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d",&n,&m);
        ini();
        FOR(i,m)
        {
            scanf("%d%d%d",&x,&y,&z);
            if(x==y)
                continue;
            out[x]++;
            in[y]++;
            father[getfather(x)]=getfather(y);
            if(z==0)
            {
                insert(x,y,1);
            }
        }
        bool flag=true;
        for(int i=1; i<=n; i++)
        {
            dif[i]=max(out[i]-in[i],in[i]-out[i]);
            if(dif[i]%2==1)
            {
                flag=false;
                break;
            }
            dif[i]/=2;
        }
        for(int i=2; i<=n; i++)             //ͼ�п��ܲ���ͨ
        {
            if(getfather(1)!=getfather(i))
            {
                flag=false;
                break;
            }
        }
        if(!flag)
        {
            printf("impossible\n");
            continue;
        }
        for(int i=1; i<=n; i++)
        {
            if(out[i]>in[i])
            {
                insert(0,i,dif[i]);
                sum+=dif[i];
            }
            if(out[i]<in[i])
            {
                insert(i,n+1,dif[i]);
            }
        }
        if(dinic(0,n+1)==sum)
            printf("possible\n");
        else
            printf("impossible\n");
    }
    return 0;
}
