#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <stack>
#include <algorithm>
#include <cstdio>
#include <queue>
#include <string>
#include <cstring>
#include <cstdlib>

using namespace std;

const double eps=1e-8;

#define MEM(a) memset(a,0,sizeof(a));
#define FOR(i,n) for(int i=0;i<n;i++)

int u[5010],l[5010],a[5010],b[5010],sum[5010],ans[5010];
int x1,x2,y1,y2,n,i,j,m,llll,rrrr,mid;
int partition(int a[],int b[],int p,int r)
{
    int x,i,j,swap;
    x=a[r];
    i=p-1;
    for(j=p; j<r; j++)
    {
        if(a[j]<=x)
        {
            i++;
            swap=a[i];
            a[i]=a[j];
            a[j]=swap;
            swap=b[i];
            b[i]=b[j];
            b[j]=swap;
        }
    }
    swap=a[i+1];
    a[i+1]=a[r];
    a[r]=swap;
    swap=b[i+1];
    b[i+1]=b[r];
    b[r]=swap;
    return i+1;
}
void quicksort(int a[],int b[],int p,int r)
{
    int q;
    if(p<r)
    {
        q=partition(a,b,p,r);
        quicksort(a,b,p,q-1);
        quicksort(a,b,q+1,r);
    }
}
int direction(int mid,int i)
{
    return (l[mid]-a[i])*(y1-b[i])-(u[mid]-a[i])*(y2-b[i]);
}
int main()
{
    while(1)
    {
        MEM(sum);
        MEM(ans);
        scanf("%d",&n);
        if(n==0)
            break;
        scanf("%d%d%d%d%d",&m,&x1,&y1,&x2,&y2);
        u[0]=0;
        l[0]=0;
        u[n+1]=x2;
        l[n+1]=x2;
        for(i=1; i<=n; i++)
            scanf("%d%d",&u[i],&l[i]);
        for(i=0; i<m; i++)
            scanf("%d%d",&a[i],&b[i]);
        quicksort(l,u,1,n);
        for(i=0; i<m; i++)
        {
            llll=0;
            rrrr=n;
            mid=(llll+rrrr)/2;
            while(1)
            {
                if(direction(mid,i)<0&&direction(mid+1,i)<0)
                {
                    if(llll==rrrr-1)
                        mid=rrrr;
                    else
                    {
                        llll=mid;
                        mid=(llll+rrrr)/2;
                    }
                }
                else
                {
                    if(direction(mid,i)>0&&direction(mid+1,i)>0)
                    {
                        if(llll==rrrr-1)
                            mid=rrrr;
                        else
                        {
                            rrrr=mid;
                            mid=(llll+rrrr)/2;
                        }
                    }
                    else
                    {
                        sum[mid]++;
                        break;
                    }
                }
            }
        }
        for(i=0; i<=n; i++)
        {
            ans[sum[i]]++;
        }
        printf("Box\n");
        for(i=1; i<=n; i++)
        {
            if(ans[i]!=0)
                printf("%d: %d\n",i,ans[i]);
        }
    }
    return 0;
}
