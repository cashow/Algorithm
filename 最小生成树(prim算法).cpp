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

int connect[101][101],farm[101],len,n;
bool used[101];

int prim()
{
    int ans=0,len=1;
    farm[0]=0;                  //��ѡһ����Ϊ��ʼ��
    used[0]=true;
    for(int p=1; p<n; p++)      //n-1��ѭ��
    {
        int next,minn=-1;       //next����һ��Ҫ����ĵ�
        FOR(i,len)              //ö�����ù��ĵ�
        {
            FOR(j,n)            //ö��û�ù��ĵ�
            {
                if(used[j])
                    continue;
                if(minn==-1||minn>connect[farm[i]][j])      //ȡ������С�ĵ�
                {
                    next=j;
                    minn=connect[farm[i]][j];
                }
            }
        }
        used[next]=true;
        farm[len++]=next;
        ans+=minn;              //minn��next�����Ѿ�������ĵ�ľ������Сֵ
    }
    return ans;
}

int main()
{
    while(scanf("%d",&n)!=EOF)
    {
        MEM(used);
        FOR(i,n)
        {
            FOR(j,n)
            {
                scanf("%d",&connect[i][j]);
            }
        }
        printf("%d\n",prim());
    }
    return 0;
}
