int getint()
{
    int ret=0;
    char tmp;
    while(!isdigit(tmp=getchar()));
    do
    {
        ret=(ret<<3)+(ret<<1)+tmp-'0';
    }
    while(isdigit(tmp=getchar()));
    return ret;
}

