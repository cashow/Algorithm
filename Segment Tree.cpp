struct treee
{
    int left,right,num;
} tree[150000];

void build_tree(int left,int right,int pos)
{
    tree[pos].left=left;
    tree[pos].right=right;
    if(tree[pos].left==tree[pos].right)
    {
        scanf("%d",&tree[pos].num);
        return;
    }
    int mid=(left+right)/2;
    build_tree(left,mid,2*pos);
    build_tree(mid+1,right,2*pos+1);
    tree[pos].num=tree[2*pos].num+tree[2*pos+1].num;
}

int query(int left,int right,int pos)
{
    if(tree[pos].left==left&&tree[pos].right==right)
    {
        return tree[pos].num;
    }
    int mid=(tree[pos].left+tree[pos].right)/2;
    if(mid>=right)
        return query(left,right,2*pos);
    if(mid<left)
        return query(left,right,2*pos+1);
    return query(left,mid,2*pos)+query(mid+1,right,2*pos+1);
}

void add(int pos,int addnum,int num)
{
    tree[pos].num+=num;
    if(tree[pos].left==tree[pos].right)
        return ;
    int mid=(tree[pos].left+tree[pos].right)/2;
    if(addnum>mid)
        add(2*pos+1,addnum,num);
    else
        add(2*pos,addnum,num);
}

char a[10];

int main()
{
    int t,n,x,y,cnt=0;
    scanf("%d",&t);
    while(t--)
    {
        cnt++;
        scanf("%d",&n);
        build_tree(1,n,1);
        printf("Case %d:\n",cnt);
        while(1)
        {
            scanf("%s",a);
            if(a[0]=='E')
                break;
            scanf("%d%d",&x,&y);
            if(a[0]=='Q')
                printf("%d\n",query(x,y,1));
            if(a[0]=='A')
                add(1,x,y);
            if(a[0]=='S')
                add(1,x,-y);
        }
    }
    return 0;
}
