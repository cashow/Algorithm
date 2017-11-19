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

string a,b;

string getminstr(string x)
{
    int len=x.length(),count=0;
    vector<string>v;
    string y;
    x=x.substr(1,len-2);
    len-=2;
    FOR(i,len)
    {
        if(x[i]=='0')
            count++;
        else
            count--;
        y+=x[i];
        if(count==0)        //��ʱ�ҵ�һ������
        {
            v.push_back(getminstr(y));      //�Ƚ�y�����ֵ�����С���ַ���
            y.erase();
        }
    }
    sort(v.begin(),v.end());    //���ֵ����������,��ԭ��x���ֵ�����С������ԭ�ַ���ͬ�����ַ���
    x.erase();
    FOR(i,v.size())
    {
        x+=v[i];
    }
    return '0'+x+'1';
}

int main()
{
    int t;
    scanf("%d",&t);
    while(t--)
    {
        cin>>a>>b;
        a='0'+a+'1';
        a=getminstr(a);
        b='0'+b+'1';
        b=getminstr(b);
        if(a==b)
        {
            printf("same\n");
        }
        else
        {
            printf("different\n");
        }
    }
    return 0;
}
