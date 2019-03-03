/*
splay维护区间，针对区间翻转操作
luogu: 3391
*/

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
#include <vector>

#define MAXN (100000+5)

int n,m;

class Splay{
public:
    
    int root;
    
    Splay() {tot=0;root=0;}     // 初始化已用节点数，根结点
    
    void print_tree(int v);     // 输出以v为根结点的树
    
    void insert(int v);         // 插入数v
    void reverse(int left,int right);   // 翻转[left,right]区间
    
    void print_ans(int v);
    
    ~Splay() {}
    
private:
    
    struct node {
        int son[2],fa,cnt,value,sum,lazy;
        node() {son[0]=son[1]=fa=cnt=value=sum=lazy=0;}      // cnt：自身重复的次数   value：该编号的值  sum：以该编号为根结点的树的总元素数(包括自身的重复次数)   lazy：翻转标记
    }tree[MAXN];
    
    int tot;
    
    void rotate(int v);                     // 上旋
    void splay(int v,int u);                      // 将编号v的节点上旋到编号为u的结点
    void update_sum(int v);                 // 更新以编号v的节点为根结点的树的总元素树
    void connect(int v,int u,int loc);      // 连接编号v的节点(父节点)和编号u的节点(子节点)，loc表示子节点的左右
    int ck_loc(int v);                      // 返回编号v的节点是其父节点的左或右
    
    int find_loc(int v);                    // 返回翻转后区间的第v位
    void pushdown(int v);                   // 将lazy标记向下传递一层
};

void Splay::print_tree(int v) {
    if(!v)  return;
    printf("%d %d %d\n",tree[v].value,tree[tree[v].son[0]].value,tree[tree[v].son[1]].value);
    Splay::print_tree(tree[v].son[0]);
    Splay::print_tree(tree[v].son[1]);
}

void Splay::print_ans(int v) {          // splay的操作不影响中序遍历的结果
    pushdown(v);
    if(tree[v].son[0])  Splay::print_ans(tree[v].son[0]);
    if(v>1 && v<(n+2))  printf("%d ",v-1);
    // 由于添加了辅助边界点1和n+2，所有点的编号都加了一，在输出的时候减一还原，并且不输出边界点
    if(tree[v].son[1])  Splay::print_ans(tree[v].son[1]);
}

int Splay::find_loc(int v) {
    int temp=root,loc=0,ret=0;
    while(temp) {
        pushdown(temp);
        // 在找第v位的时候一定要pushdown，不然左右子树没有翻转，找到的节点不对
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
    return ret;
}

void Splay::pushdown(int v) {
    if(tree[v].lazy) {
        tree[v].lazy=0;
        tree[tree[v].son[0]].lazy^=1;
        tree[tree[v].son[1]].lazy^=1;
        std::swap(tree[v].son[0],tree[v].son[1]);
    }
}

void Splay::reverse(int left,int right) {
    // 原理：先将left-1节点旋到根结点，再将right+1节点旋到根结点的右儿子上
    // 则根结点的右儿子的左儿子就是所要翻转的区间[left,right]
    
    int L=find_loc(left),R=find_loc(right+2);
    // 由于添加了辅助边界点1和n+2，所以所有的点的编号都要加一
    // 此处翻转[left,right]，实则翻转[left+1,right+1]，故找的前驱和后继是[left,right+2]
    
    splay(L,root);
    splay(R,tree[root].son[1]);
    tree[tree[tree[root].son[1]].son[0]].lazy^=1;
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

int main() {
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n+2;i++) s.insert(i);        // 为了让边界点也能翻转，故增加两个辅助边界点1和n+2
    for(int t1,t2,i=1;i<=m;i++) {
        scanf("%d%d",&t1,&t2);
        s.reverse(t1,t2);                       // 翻转一个区间，即为这个区间的所有树的左右子树互换
    }
    s.print_ans(s.root);
    return 0;
}

