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

bool father[1000],used[1000];       //father数组表示i是否有father节点，用来找根节点
vector<int >vec;
int son[1000],bro[1000],cnt;
queue<int >q;

void insert(int x, int y)
{
    bro[y]=son[x];
    son[x]=y;
    father[y]=true;
}

bool bfs()
{
    while(!q.empty())
    {
        int id=q.front();
        q.pop();
        //cout<<"out :"<<id<<endl;

        if(son[id]!=-1)
        {
            id=son[id];
            q.push(id);
            cnt++;
            //cout<<"in :"<<id<<endl;
            //cout<<"used :"<<used[son[id]]<<endl;
            if(used[id])
            {
                //cout<<"haha"<<endl;
                return false;
            }
            used[id]=true;
            while(bro[id]!=-1)
            {
                id=bro[id];
                //cout<<"in :"<<id<<endl;
                //cout<<"used :"<<used[id]<<endl;
                if(used[id])
                {
                    //cout<<"haha"<<endl;
                    return false;
                }
                used[id]=true;
                q.push(id);
                cnt++;
            }
        }

    }
    if(cnt==vec.size())
        return true;
    else
        return false;
}

void ini()
{
    MEM(used);
    MEM(father);
    cnt=1;
    memset(bro,-1,sizeof(bro));
    memset(son,-1,sizeof(son));
    vec.clear();
    while(!q.empty())
        q.pop();
}

int main()
{
    int x,y,sum=0;
    ini();
    while(1)
    {
        scanf("%d%d",&x,&y);
        if(x==-1&&y==-1)
            break;
        if(x==0&&y==0)
        {
            sum++;
            if(vec.size()==0)
            {
                printf("Case %d is a tree.\n",sum);
                ini();
                continue;
            }
            int pos=-1;
            /*FOR(i,vec.size())
            {
                cout<<"son ["<<vec[i]<<"]="<<son[vec[i]]<<endl;
            }*/
            FOR(i,vec.size())
            {
                if(!father[vec[i]])
                {
                    pos=vec[i];
                    break;
                }
            }
            if(pos==-1)             //假如找不到根节点则不是tree
            {
                printf("Case %d is not a tree.\n",sum);
                ini();
                continue;
            }
            q.push(pos);
            //cout<<"pos="<<pos<<endl;
            MEM(used);
            if(bfs())
            {
                printf("Case %d is a tree.\n",sum);
            }
            else
            {
                printf("Case %d is not a tree.\n",sum);
            }
            //cout<<cnt<<endl;
            ini();
        }
        else
        {
            insert(x,y);
            if(!used[x])
            {
                vec.push_back(x);
                used[x]=true;
            }
            if(!used[y])
            {
                vec.push_back(y);
                used[y]=true;
            }
        }
    }
    return 0;
}
