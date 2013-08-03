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

int father[50001];
bool used[50001];

int getfather(int x)
{
    if(father[x]==x)
        return x;
    return father[x]=getfather(father[x]);
}

int main()
{
    int n,m,x,y,ans,cnt=0;
    while(scanf("%d%d",&n,&m)!=EOF)
    {
        if(n==0&&m==0)
            break;
        cnt++;
        ans=0;
        FOR(i,n)
        {
            father[i]=i;
        }
        MEM(used);
        FOR(i,m)
        {
            scanf("%d%d",&x,&y);
            x--;
            y--;
            father[getfather(x)]=getfather(y);
        }
        FOR(i,n)
        {
            getfather(i);
        }
        FOR(i,n)
        {
            if(!used[father[i]])
                ans++;
            used[father[i]]=true;
        }
        printf("Case %d: %d\n",cnt,ans);
    }
    return 0;
}
