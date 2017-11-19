#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <stack>
#include <bitset>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
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

char a[10][10];
bool used[10];
int sum,cnt,ans;
int n,m;

void dfs(int x,int y)
{
    used[y]=true;
    cnt++;
    if(cnt==m)
    {
        ans++;
        return ;
    }
    for(int i=x+1; i<n; i++)
    {
        FOR(j,n)
        {
            if(a[i][j]=='#'&&!used[j])
            {
                dfs(i,j);
                used[j]=false;
                cnt--;
            }
        }
    }
}

int main()
{
    while(1)
    {
        scanf("%d%d",&n,&m);
        if(n==-1&&m==-1)
            break;
        FOR(i,n)
        {
            scanf("%s",a[i]);
        }
        sum=0;
        ans=0;
        FOR(i,n)
        {
            FOR(j,n)
            {
                if(a[i][j]=='#')
                {
                    MEM(used);
                    cnt=0;
                    dfs(i,j);
                }
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}
