void add(char a[],char b[],char c[])		//c=a+b
{
    int lena=strlen(a);
    int lenb=strlen(b);
    reverse(a,a+lena);
    reverse(b,b+lenb);
    int ans[1100000];
    MEM(ans);
    int up=0;
    for(int i=0; i<max(lena,lenb); i++)
    {
        if(i<lena)
            ans[i]+=a[i]-'0';
        if(i<lenb)
            ans[i]+=b[i]-'0';
        ans[i]+=up;
        up=ans[i]/10;
        ans[i]%=10;
    }
    int pos=max(lena,lenb);
    while(up>0)
    {
        ans[pos]=up;
        up=ans[pos]/10;
        ans[pos]%=10;
        pos++;
    }
    FOR(i,pos)
    {
        c[i]=ans[i]+'0';
    }
    pos=min(pos,100);
    c[pos]=0;
    reverse(c,c+pos);
}
