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

int connect[maxn][maxn],level[maxn],pre[maxn],next[maxn],minadd[maxn];
int n,m,ans;
queue<int>q;

bool bfs(int start,int end)               //����level��ȷ���Ƿ��ܵ�����
{
    q.push(start);
    MEST(level);
    level[start]=0;
    while(!q.empty())
    {
        int pos=q.front();
        q.pop();
        for(int i=start; i<=end; i++)
        {
            if(connect[pos][i]&&level[i]==-1)
            {
                q.push(i);
                level[i]=level[pos]+1;
            }
        }
    }
    return level[end]!=-1;              //�ܵ���end�򷵻�true�������򷵻�false
}

void dfs(int start,int end)
{
    int pos=start,to,change,minn=-1,minpos;
    while(1)                            //�ǵݹ�dfs
    {
        bool flag=false;
        for(int i=start; i<=end; i++)         //��һ�������ߵ�·
        {
            if(connect[pos][i]&&level[i]==level[pos]+1)
            {
                flag=true;
                to=i;
                break;
            }
        }
        if(flag)                        //�ҵ�һ�������ߵ�·��
        {
            next[pos]=to;
            pre[to]=pos;
            if(minadd[pos]==-1)         //minadd[pos]ȡ��С������endʱminadd[end]Ϊ����·�ɼӵ��������
                minadd[to]=connect[pos][to];
            else
                minadd[to]=min(minadd[pos],connect[pos][to]);
            pos=to;			            //���ҵ��Ľڵ㿪ʼ�ڲ��ͼ����·
            if(pos==end) 	            //�ҵ�t������
            {
                ans+=minadd[end];        //minadd[end]:����·�ɼӵ��������
                change=minadd[end];
                for(int i=end; i!=start; i=pre[i])    //һֱ�ӻ����˵�Դ�㣬����ÿ��·������
                {
                    minadd[i]-=change;
                    connect[pre[i]][i]-=change;
                    connect[i][pre[i]]+=change;
                    if(connect[pre[i]][i]==0)
                        pos=pre[i];           //u���˵�������Ϊ0��·�ĵ�֮ǰ
                }
            }
        }
        else
        {
            if(pos!=start)	            //���pos!=start��ô����·�߲�ͨ�Ļ�����pos����һ���ڵ�����ҡ�
            {
                level[pos]=-2;          //�൱�ڴӲ��ͼ��ɾ������ڵ㡣
                pos=pre[pos];           //dfs����
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
        MEM(pre);		        //dfs�У������Ҫ���ݣ��ͻ��ݵ�pre�еĽڵ㡣
        MEST(minadd);       //minadd��������ʣ������
        dfs(s,t);
    }
    return ans;
}

int main()
{
    int x,y,z;
    while(scanf("%d%d",&m,&n)!=EOF)
    {
        MEM(connect);
        FOR(i,m)
        {
            scanf("%d%d%d",&x,&y,&z);
            connect[x][y]+=z;
        }
        printf("%d\n",dinic(1,n));
    }
    return 0;
}
