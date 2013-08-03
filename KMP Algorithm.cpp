char a[10001],b[1000010];
int next[10001];

void get_next()
{
    int i=0,j=-1;
    next[0]=-1;
    int len=strlen(a);
    while(i<len)
    {
        if(j==-1 || a[i]==a[j])
        {
            ++i,++j;
            next[i]=j;
        }
        else j=next[j];
    }
}

void kmp()
{
    int i=0,j=0,ans=0;;
    int lena=strlen(a),lenb=strlen(b);
    while(j<lenb)
    {
        if(i>=lena)
        {
            --j;
            ++ans;
            i=next[lena-1];
            continue;
        }
        if(i==-1||a[i]==b[j])
        {
            ++i,++j;
        }
        else
        {
            i=next[i];
        }
    }
    if(i>=lena) ++ans;
    printf("%d\n",ans);
}

int main()
{
    int t;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%s",&a);
        scanf("%s",&b);
        get_next();
        kmp();
    }
    return 0;
}
