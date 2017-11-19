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

#define maxn 201

struct edge
{
    int to,from,next,value,num;         //num��¼���������ߵı��
} e[maxn*maxn*2];

int level[maxn],pre[maxn],next[maxn],minadd[maxn];
int n,m,ans,cnt;
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
    int pos,to;
    q.push(start);
    MEST(level);
    level[start]=0;
    while(!q.empty())
    {
        pos=q.front();
        q.pop();
        for(int id=next[pos];id!=-1;id=e[id].next)
        {
            to=e[id].to;
            if(e[id].value>0&&level[to]==-1)
            {
                q.push(to);
                level[to]=level[pos]+1;
            }
        }
    }
    return level[end]!=-1;              //�ܵ���end�򷵻�true�������򷵻�false
}

void dfs(int start,int end)
{
    int pos=start,to,change,minn=-1,minpos,id;
    while(1)                            //�ǵݹ�dfs
    {
        bool flag=false;
        for(id=next[pos];id!=-1;id=e[id].next)      //��һ�������ߵ�·
        {
            int i=e[id].to;
            if(level[i]==level[pos]+1&&e[id].value>0)
            {
                flag=true;
                to=i;
                break;
            }
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
                while(1)              //һֱ�ӻ����˵�Դ�㣬����ÿ��·������
                {
                    minadd[e[id].to]-=change;
                    e[id].value-=change;
                    e[id^1].value+=change;
                    if(e[id].value==0)
                        pos=e[id].from;           //u���˵�������Ϊ0��·�ĵ�֮ǰ
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
        MEST(pre);		        //dfs�У������Ҫ���ݣ��ͻ��ݵ�pre�еĽڵ㡣
        MEST(minadd);       //minadd��������ʣ������
        dfs(s,t);
    }
    return ans;
}

void ini()
{
    MEST(next);
    cnt=0;
}

int main()
{
    int x,y,z;
    while(scanf("%d%d",&m,&n)!=EOF)
    {
        ini();
        FOR(i,m)
        {
            scanf("%d%d%d",&x,&y,&z);
            insert(x,y,z);
        }
        printf("%d\n",dinic(1,n));
    }
    return 0;
}
