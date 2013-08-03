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
vector<node>v;                      //v�����洢������С�������ı�

int prim()
{
    int ans=0,len=1;
    MEM(used);
    used[0]=true;
    farm[0]=0;                      //��ѡһ����Ϊ��ʼ��
    for(int p=1; p<n; p++)          //n-1��ѭ��
    {
        int pre=-1,next,minn=-1;    //next����һ��Ҫ����ĵ�
        FOR(i,len)                  //ö�����ù��ĵ�
        {
            FOR(j,n)                //ö��û�ù��ĵ�
            {
                if(used[j]||connect[farm[i]][j]==-1)        //farm[i]��j����Ҫ�б�
                    continue;
                if(minn==-1||minn>connect[farm[i]][j])      //ȡ������С�ĵ�
                {
                    pre=farm[i];
                    next=j;
                    minn=connect[farm[i]][j];
                }
            }
        }
        if(pre==-1)                 //pre=-1��ʾ�����ѭ��û���ҵ����������ı�,����ʱ��û�м���n-1����
            return -1;              //��˵��ɾȥһ���ߺ����ɵĲ���һ����,���û����С������
        used[next]=true;
        farm[len++]=next;
        ans+=minn;                  //minn��next�����Ѿ�������ĵ�ľ������Сֵ

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
        flag=true;      //flag������¼�Ƿ�����С������
        v.clear();      //һ����Ҫ�������vector������
        int x,y,w;
        FOR(i,m)
        {
            scanf("%d%d%d",&x,&y,&w);
            x--;        //��Ŀ��x�ķ�Χ��1~n,���x--,��x�ķ�Χ��Ϊ0~n-1
            y--;
            connect[x][y]=w;
            connect[y][x]=w;
        }
        sum=prim();         //û��ɾ��֮ǰ����С��������Ȩֵ֮��
        int len=v.size();
        FOR(i,len)          //v��0~len-1����������С�������ı�,�Ժ��prim������v�е�Ԫ��,����Ӱ��ǰlen-1��Ԫ��
        {
            int before=connect[v[i].x][v[i].y];     //��¼�±仯ǰ����ֵ
            connect[v[i].x][v[i].y]=-1;             //ɾȥ��v[i].x->v[i].y
            connect[v[i].y][v[i].x]=-1;             //ɾȥ��v[i].y->v[i].x
            tem=prim();
            if(sum==tem)
            {
                flag=false;
                break;
            }
            connect[v[i].x][v[i].y]=before;         //��ԭ��v[i].x->v[i].y
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
