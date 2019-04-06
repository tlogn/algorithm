/*
splay通过点的权值，维护二叉查找树的性质
luogu: 3369
*/

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
#include <vector>

#define MAXN (100000+5)

class Splay{
public:
    
    int root;
    
    Splay() {tot=0;root=0;}     // 初始化已用节点数，根结点
    
    void print_tree(int v);     // 输出以v为根结点的树
    
    void insert(int v);         // 插入数v
    void pop(int v);            // 删除数v
    void find_rank(int v);      // 找到数v的排名，若有多个v，则取最小值
    void find_num(int v);       // 找到排名为v的数
    void find_pre(int v,int u); // 找到在以u为根节点的树中，数v的前驱
    void find_next(int v,int u);// 找到在以u为根结点的树中，数u的后继
    
    ~Splay() {}
    
private:
    
    struct node {
        int son[2],fa,cnt,value,sum;
        node() {son[0]=son[1]=fa=cnt=value=sum=0;}      // cnt：自身重复的次数   value：该编号的值  sum：以该编号为根结点的树的总元素数(包括自身的重复次数)
    }tree[MAXN];
    
    int tot;
    
    int find(int v);                        // 返回数v的编号
    void rotate(int v);                     // 上旋
    void splay(int v,int u);                      // 将编号v的节点上旋到编号为u的结点
    void update_sum(int v);                 // 更新以编号v的节点为根结点的树的总元素树
    void connect(int v,int u,int loc);      // 连接编号v的节点(父节点)和编号u的节点(子节点)，loc表示子节点的左右
    int ck_loc(int v);                      // 返回编号v的节点是其父节点的左或右
    
};

void Splay::print_tree(int v) {
    if(!v)  return;
    printf("%d %d %d\n",tree[v].value,tree[tree[v].son[0]].value,tree[tree[v].son[1]].value);
    Splay::print_tree(tree[v].son[0]);
    Splay::print_tree(tree[v].son[1]);
}

void Splay::insert(int v) {
    tot++;
    if(tot==1) {                // 对根结点特判
        tree[tot].sum++;
        tree[tot].fa=0;
        tree[tot].cnt++;
        tree[tot].value=v;
        tree[0].son[0]=tot;
        root=tot;
    }
    else {                              // 在树的底部插入新节点
        int temp=root;
        int fa=0;
        while(temp) {
            tree[temp].sum++;           // 插入数时经过的每个节点的总元素数加一
            if(tree[temp].value==v) {   // 节点已存在就将次数加一
                tree[temp].cnt++;
                return;
            }
            else if(tree[temp].value>v) {
                fa=temp;
                temp=tree[temp].son[0];
            }
            else {
                fa=temp;
                temp=tree[temp].son[1];
            }
        }
        tree[tot].sum++;                // 初始化该点
        tree[tot].fa=fa;
        tree[tot].cnt++;
        tree[tot].value=v;
        if(v>tree[fa].value)    tree[fa].son[1]=tot;
        else    tree[fa].son[0]=tot;
    }
    splay(tot,root);
}

int Splay::find(int v) {
    int temp=root;
    while(tree[temp].value!=v) {
        temp= tree[temp].value > v ? tree[temp].son[0] : tree[temp].son[1];
    }
    return temp;
}

void Splay::pop(int v) {
    int loc=find(v);
    if(tree[loc].cnt>1) {
        tree[loc].cnt--;            // 出现次数减一
        int temp=loc;
        while(temp) {               // 更新该点的所有祖先节点的总元素数
            tree[temp].sum--;
            temp=tree[temp].fa;
        }
    }
    else {                          // 删除该节点
        splay(loc,root);                 // 先将要删除的节点旋到根结点
        int pre=tree[root].son[0];
        
        if(!tree[root].son[0]) {    // 若该节点旋到根结点后没有左儿子，则直接删除该节点，让其右儿子作为根结点
            root=tree[root].son[1];
            tree[root].fa=0;
        }
        else {
            while(tree[pre].son[1]) pre=tree[pre].son[1];   // 找到要删除的节点的前驱
            
            // 将前驱旋到根结点，此时根结点的右儿子即为要删除的点，而要删除的点没有左儿子，所以直接连接此时的根结点和孙子节点
            splay(pre,root);
            int grandson=tree[tree[root].son[1]].son[1];
            connect(root,grandson,1);
            
            update_sum(root);   // 只有根结点的sum值发生改变
        }
    }
}

void Splay::find_rank(int v) {
    int temp=root,ret=0;
    while(temp) {
        if(tree[temp].value==v) {
            ret+=tree[tree[temp].son[0]].sum+1;
            break;
        }
        else if(tree[temp].value<v) {
            ret+=tree[tree[temp].son[0]].sum+tree[temp].cnt;
            temp=tree[temp].son[1];
        }
        else {
            temp=tree[temp].son[0];
        }
    }
    if(temp)    splay(temp,root);
    printf("%d\n",ret);
}

void Splay::find_num(int v) {
    int temp=root,loc=0,ret=0;
    while(temp) {
        int son0=tree[temp].son[0],son1=tree[temp].son[1];
        if(tree[son0].sum+tree[temp].cnt+loc<v) {
            loc+=tree[son0].sum+tree[temp].cnt;
            temp=son1;
        }
        else if(tree[son0].sum+loc>=v) {
            temp=son0;
        }
        else if(loc+tree[son0].sum<v && loc+tree[son0].sum+tree[temp].cnt>=v){
            ret=temp;
            break;
        }
    }
    if(temp)    splay(temp,root);
    printf("%d\n",tree[ret].value);
}

void Splay::find_pre(int v,int u) {
    int pre=-1e7,temp=u;
    while(temp) {
        if(tree[temp].value<v) {
            pre=tree[temp].value;
            temp=tree[temp].son[1];
        }
        else    temp=tree[temp].son[0];
    }
    printf("%d\n",pre);
}

void Splay::find_next(int v,int u) {
    int next=1e7,temp=u;
    while(temp) {
        if(tree[temp].value>v) {
            next=tree[temp].value;
            temp=tree[temp].son[0];
        }
        else temp=tree[temp].son[1];
    }
    printf("%d\n",next);
}

int Splay::ck_loc(int v) {
    return v==tree[tree[v].fa].son[0] ? 0:1;
}

void Splay::update_sum(int v) {
    int son0=tree[v].son[0],son1=tree[v].son[1];
    tree[v].sum=tree[son0].sum+tree[son1].sum+tree[v].cnt;
}

void Splay::connect(int v,int u,int loc) {      // v:father u:son
    tree[v].son[loc]=u;
    tree[u].fa=v;
}

void Splay::rotate(int v) {
    int u=tree[v].fa;
    int loc_v=ck_loc(v),loc_u=ck_loc(u);
    
    connect(u,tree[v].son[loc_v^1],loc_v);
    connect(tree[u].fa,v,loc_u);
    connect(v,u,loc_v^1);
    
    update_sum(u);
    update_sum(v);
}

void Splay::splay(int v,int u) {                // 将编号为v的节点旋到编号为u的节点
    int to=tree[u].fa;                          // 必须设置一个to将u的父节点记录下来，因为u的父节点可能会随着v的上旋而改变
    while(tree[v].fa!=to) {
        if(tree[tree[v].fa].fa==to)  rotate(v);
        else if(ck_loc(v)==ck_loc(tree[v].fa)) {     // 三点一线需先旋转父节点
            rotate(tree[v].fa);
            rotate(v);
        }
        else {
            rotate(v);
            rotate(v);
        }
    }
    if(!tree[v].fa) root=v;
}

Splay s;
int n;

int main() {
    scanf("%d",&n);
    for(int t1,t2,i=1;i<=n;i++) {
        scanf("%d%d",&t1,&t2);
        if(t1==1)   s.insert(t2);
        else if(t1==2)  s.pop(t2);
        else if(t1==3)  s.find_rank(t2);
        else if(t1==4)  s.find_num(t2);
        else if(t1==5)  s.find_pre(t2,s.root);
        else if(t1==6)  s.find_next(t2,s.root);
    }
    return 0;
}

