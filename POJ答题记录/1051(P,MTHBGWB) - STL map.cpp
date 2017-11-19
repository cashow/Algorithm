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

map<char,string>m;
map<string,char>n;
char a[101];
int len[101];
string ans,tem;

int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    m['A']=".-";        m['B']="-...";      m['C']="-.-.";
    m['D']="-..";       m['E']=".";         m['F']="..-.";
    m['G']="--.";       m['H']="....";      m['I']="..";
    m['J']=".---";      m['K']="-.-";       m['L']=".-..";
    m['M']="--";        m['N']="-.";        m['O']="---";
    m['P']=".--.";      m['Q']="--.-";      m['R']=".-.";
    m['S']="...";       m['T']="-";         m['U']="..-";
    m['V']="...-";      m['W']=".--";       m['X']="-..-";
    m['Y']="-.--";      m['Z']="--..";      m['_']="..--";
    m['.']="---.";      m[',']=".-.-";      m['?']="----";
    for(int i='A';i<='Z';i++)
    {
        n[m[i]]=i;
    }
    n["..--"]='_';      n["---."]='.';
    n[".-.-"]=',';      n["----"]='?';

    int cnt=0,t,l,pos;
    scanf("%d",&t);
    while(t--)
    {
        cnt++;
        ans.clear();
        scanf("%s",a);
        l=strlen(a);
        FOR(i,l)
        {
            ans.append(m[a[i]]);
            len[l-i-1]=m[a[i]].size();
        }
        ans.reserve();
        pos=0;
        cout<<cnt<<": ";
        FOR(i,l)
        {
            tem.clear();
            FOR(j,len[i])
            {
                tem+=ans[pos+j];
            }
            cout<<n[tem];
            pos+=len[i];
        }
        cout<<endl;
    }
    return 0;
}
