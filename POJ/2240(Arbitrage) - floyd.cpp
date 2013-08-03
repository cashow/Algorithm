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

map<string,int>m;
struct node
{
    int x,y;
    double w;
} e[31];
int n,k;
double connect[31][31];

void floyd()
{
    FOR(i,n)
    {
        FOR(j,n)
        {
            FOR(k,n)
            {
                if(connect[j][i]*connect[i][k]>connect[j][k]+eps)
                    connect[j][k]=connect[j][i]*connect[i][k];
            }
        }
    }
}

int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    double w;
    string s,ss;
    int cnt=0;
    while(1)
    {
        cnt++;
        scanf("%d",&n);
        FOR(i,n)
        {
            FOR(j,n)
            {
                connect[i][j]=0.0;
            }
            connect[i][i]=1.0;
        }
        if(n==0)
            break;
        FOR(i,n)
        {
            cin>>s;
            m[s]=i;
        }
        scanf("%d",&k);
        FOR(i,k)
        {
            cin>>s>>w>>ss;
            connect[m[s]][m[ss]]=w;
        }
        floyd();
        bool flag=false;
        FOR(i,n)
        {
//            cout<<connect[i][i]<<endl;
            if(connect[i][i]-1.0>eps)
            {
                flag=true;
                break;
            }
        }
        if(flag)
        {
            printf("Case %d: Yes\n",cnt);
        }
        else
        {
            printf("Case %d: No\n",cnt);
        }
    }
    return 0;
}
