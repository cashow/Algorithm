int main()
{
    int i,j,n,max,a[10001],b[10001];
    while(scanf("%d",&n)!=EOF)
    {
        for(i=0; i<n; i++)
            scanf("%d",&a[i]);
        b[0]=1;
        max=1;
        for(i=1; i<n; i++)
        {
            b[i]=1;
            for(j=0; j<i; j++)
            {
                if((a[j]<a[i])&&(b[j]+1>b[i]))
                    b[i]=b[j]+1;
            }
            if(b[i]>max)
                max=b[i];
        }
        printf("%d\n",max);
    }
    return 0;
}
