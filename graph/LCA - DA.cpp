#include<cstdio>
#include<cstring>
#include<queue>

const int NSIZE = 50000;
const int DEG = 20;

struct trees
{

    int fa[DEG];
    int head,deg;
} tree[NSIZE];

struct edges
{
    int to , next;
} edge[NSIZE];

struct states
{
    int u,fu,deg;
};

int L;

void add_edge(int x, int y)
{
    edge[L].to = y;
    edge[L].next = tree[x].head;
    tree[x].head = L++;
}

int Root;

inline void BFS(int s)
{
    std::queue<states> que;
    states st;
    st.deg=0;
    st.fu=st.u=s;
    que.push(st);
    while(!que.empty())
    {
        states st=que.front();
        que.pop();
        tree[st.u].deg = st.deg;
        tree[st.u].fa[0] = st.fu;
        for (int i=1;i<DEG;i++)
            tree[st.u].fa[i]=s;
        for (int tmp=st.fu,num=1;tree[tmp].deg;tmp=tree[st.u].fa[num++])
            tree[st.u].fa[num]=tree[tmp].fa[num-1];
        for(int i = tree[st.u].head ; i != -1; i = edge[i].next)
        {
            int v = edge[i].to;
            if (v == st.fu)
                continue;
            states nst;
            nst.u=v;
            nst.fu=st.u;
            nst.deg=st.deg+1;
            que.push(nst);
        }
    }
}

inline int LCA(int x, int y)
{
    if(tree[x].deg > tree[y].deg)
        std::swap(x,y);
    int hx=tree[x].deg,hy=tree[y].deg;
    int tx=x,ty=y;
    for (int det=hy-hx,i=0; det; det>>=1,i++)
        if (det&1)
            ty=tree[ty].fa[i];
    if(tx == ty)
        return tx;
    for (int i=DEG-1; i>=0; i--)
    {
        if(tree[tx].fa[i] == tree[ty].fa[i])
            continue;
        tx = tree[tx].fa[i];
        ty = tree[ty].fa[i];
    }
    return tree[tx].fa[0];
}

int main()
{
    int t;
    scanf("%d",&t);
    while(t--)
    {
        int n;
        scanf("%d",&n);
        L = 0;
        for(int i = 0 ; i < n ; i++)
            tree[i].head = -1;
        for(int i = 0 ; i < n-1 ; i++)
        {
            int a,b;
            scanf("%d%d",&a ,&b);
            add_edge(a-1,b-1);
            add_edge(b-1,a-1);
        }
        Root=0;
        BFS(Root);
        int a,b;
        scanf("%d%d",&a,&b);
        int lca=LCA(a-1,b-1)+1;
        printf("%d\n",lca);
    }
    return 0;
}

