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

int dp[40001],w[4000],v[4000];

int main()
{
    int n,m,maxx;
    while(scanf("%d%d",&n,&m)!=EOF)
    {
        MEM(dp);
        maxx=-1;
        FOR(i,n)
        {
            scanf("%d%d",&w[i],&v[i]);
        }
        FOR(i,n)
        {
            for(int j=m; j>=0; j--)
            {
                if(j>=w[i])
                    dp[j]=max(dp[j],dp[j-w[i]]+v[i]);
            }
        }
        FOR(i,m+1)
        {
            if(maxx<dp[i])
            {
                maxx=dp[i];
            }
        }
        cout<<maxx<<endl;
    }
    return 0;
}
