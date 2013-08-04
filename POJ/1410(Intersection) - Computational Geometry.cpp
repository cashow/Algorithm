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

#define zero(x) (((x)>0?(x):-(x))<eps)

#define MEM(a) memset(a,0,sizeof(a));
#define FOR(i,n) for(int i=0;i<n;i++)

struct point
{
    double x,y;
} p[10];
struct line
{
    point a,b;
} l[5];

double xmult(point p1,point p2,point p0)
{
    return (p1.x-p0.x)*(p2.y-p0.y)-(p2.x-p0.x)*(p1.y-p0.y);
}
int dots_inline(point p1,point p2,point p3)
{
    return zero(xmult(p1,p2,p3));
}
int same_side(point p1,point p2,line l)
{
    return xmult(l.a,p1,l.b)*xmult(l.a,p2,l.b)>eps;
}
int dot_online_in(point p,point l1,point l2)
{
    return zero(xmult(p,l1,l2))&&(l1.x-p.x)*(l2.x-p.x)<eps&&(l1.y-p.y)*(l2.y-p.y)<eps;
}

bool intersect_in(line u,line v)
{
    if (!dots_inline(u.a,u.b,v.a)||!dots_inline(u.a,u.b,v.b))
        return !same_side(u.a,u.b,v)&&!same_side(v.a,v.b,u);
    return dot_online_in(u.a,v.a,v.b)||dot_online_in(u.b,v.a,v.b)||dot_online_in(v.a,u.a,u.b)||dot_online_in(v.b,u.a,u.b);
}
bool inside(point a,point b,point c)
{
    if(a.x>max(b.x,c.x)||a.x<min(b.x,c.x))
        return false;
    if(a.y>max(b.y,c.y)||a.y<min(b.y,c.y))
        return false;
    return true;
}


int main()
{
    int t;
    bool flag;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%lf%lf%lf%lf%lf%lf%lf%lf",&p[0].x,&p[0].y,&p[1].x,&p[1].y,&p[2].x,&p[2].y,&p[3].x,&p[3].y);
        l[0].a=p[0];
        l[0].b=p[1];
        p[4].x=p[2].x;
        p[4].y=p[3].y;
        p[5].x=p[3].x;
        p[5].y=p[2].y;
        l[1].a=p[2];
        l[1].b=p[4];
        l[2].a=p[2];
        l[2].b=p[5];
        l[3].a=p[3];
        l[3].b=p[4];
        l[4].a=p[3];
        l[4].b=p[5];
        flag=false;/*
        for(int i=0;i<5;i++)
        {
            printf("%f %f %f %f\n",l[i].a.x,l[i].a.y,l[i].b.x,l[i].b.y);
        }*/
        for(int i=1; i<=4; i++)
        {
            if(intersect_in(l[0],l[i]))
            {
                flag=true;
                break;
            }
        }
        if(inside(p[0],p[2],p[3])&&inside(p[1],p[2],p[3]))
            flag=true;
        if(flag)
        {
            printf("T\n");
        }
        else
        {
            printf("F\n");
        }
    }
    return 0;
}
