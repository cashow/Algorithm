int f[1001][1001];
int main()
{
    char a[1001],b[1001];
    int i,j;
    while(scanf("%s%s",a,b)!=EOF)
    {
        for(i=0;i<=strlen(a);i++)
        for(j=0;j<=strlen(b);j++)
        {
            if(i==0||j==0)
            {
                f[i][j]=0;
                continue;
            }
            if(a[i-1]==b[j-1])
            {
                f[i][j]=f[i-1][j-1]+1;
            }
            else
            if(f[i-1][j]>f[i][j-1])
            f[i][j]=f[i-1][j];
            else
            f[i][j]=f[i][j-1];
        }
        printf("%d\n",f[strlen(a)][strlen(b)]);
    }
    return 0;
}
