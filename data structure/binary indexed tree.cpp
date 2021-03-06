int tree[MAXX];

inline void update(int pos,const int &val)
{
    while(pos<MAXX)
    {
        tree[pos]+=val;
        pos+=pos&-pos;
    }
}

inline int read(int pos)
{
    int re(0);
    while(pos>0)
    {
        re+=tree[pos];
        pos-=pos&-pos;
    }
    return re;
}

int find_Kth(int k) 
{ 
    int now=0; 
    for (char i=20;i>=0;--i)
    { 
        now|=(1<<i); 
        if (now>MAXX || tree[now]>=k)
            now^=(1<<i); 
        else k-=tree[now]; 
    } 
    return now+1; 
}

