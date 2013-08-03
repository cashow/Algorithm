string s,ss;
int cnt;

struct node
{
    int id;
    node *next[26], *fail;
    node()
    {
        id = 0;
        fail = NULL;
        memset(next, 0, sizeof(next));
    }
}*head;
queue<node*> q;

void Build_trie(string s,node *head,int id)
{
    int len = s.size();
    for(int i=0; i<len; i++)
    {
        int k = s[i]-'a';
        if( head->next[k] == NULL )
            head->next[k] = new node();
        head = head->next[k];
    }
    head->id++;
}

void Build_fail(node *head)
{
    head->fail = NULL;
    q.push(head);
    while( !q.empty() )
    {
        node *now = q.front();
        q.pop();
        for(int i=0; i<26; i++)
        {
            if(!(now->next[i]) )
            {
                continue;
            }
            node *p = now->fail;
            while( p )
            {
                if( p->next[i] )
                {
                    now->next[i]->fail = p->next[i];
                    break;
                }
                p = p->fail;
            }
            if( p == NULL )
                now->next[i]->fail = head;
            q.push(now->next[i]);
        }

    }
}

void AC_find(node *head, string s)
{
    int len = s.size() ;
    cnt = 0;
    node* p = head;
    for(int i=0; i<len; i++)
    {
        int k = s[i]-'a';
        while( p->next[k] == NULL && p != head )
            p = p->fail;
        p = p->next[k] == NULL ? head : p->next[k];

        node *tmp = p;
        while( tmp != head &&tmp->id!=-1)
        {
            if(tmp->id)
            cnt+=tmp->id;
            tmp->id=-1;
            tmp = tmp->fail;
        }
    }
}

int main()
{
    int n,t;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d", &n);
        head = new node();
        for(int i=1; i<=n; i++)
        {
            cin>>ss;
            Build_trie(ss, head, i);
        }

        Build_fail( head );

        cin>>s;
        AC_find( head, s);
        printf("%d\n", cnt);
    }

    return 0;
}
