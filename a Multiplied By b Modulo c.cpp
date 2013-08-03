long long mulmod(long long x,long long y,long long m)
{
    long long r=0;
    while(y)
    {
        if(y&1)
        {
            r+=x;
            if(r>=x)r-=m;
        }
        y>>=1;x<<=1;
        if(x>=m)x-=m;
    }
    return r;
}
