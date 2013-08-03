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

int main()
{
    int t,n,i,j,k;
    char a[10001];
    scanf("%d",&t);
    while(t--)
    {
        scanf("%s",a);
        n=strlen(a);
        i=0;j=1;                                //i,j����ö��ǰ׺�ĳ�ʼλ��
        while(1)
        {
            k=0;
            while(a[(i+k)%n]==a[(j+k)%n])
            {
                k++;
                if(k>=n)
                    break;
            }
            if(k>=n)
                break;
            if(a[(i+k)%n]>a[(j+k)%n])           //����a[i+k]>a[j+k],��a[i~a+k]������ǰ׺
            {
                i=i+k+1;
                if(i==j)
                    i++;
            }
            if(a[(i+k)%n]<a[(j+k)%n])           //����a[i+k]<a[j+k],��a[j~j+k]������ǰ׺
            {
                j=j+k+1;
                if(i==j)
                    j++;
            }
        }
        printf("%d\n",min(i,j)+1);
    }
    return 0;
}
