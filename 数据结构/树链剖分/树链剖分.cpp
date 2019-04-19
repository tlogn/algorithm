/*
树链剖分
先剖分出轻链和重链，再用线段树维护树上的链
*/

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <queue>
#include <iostream>
using namespace std;

const int MAXN = 1e6;

class SegmentTree {
public:
	SegmentTree() {};
	~SegmentTree() {};
    int x[MAXN],mod;
    void build_tree(int v,int left,int right);
	void update(int v,int left,int right,int goal_left,int goal_right,int value);
	long long query(int v,int left,int right,int goal_left,int goal_right);
private:

	void pushdown(int v,int left,int right);

	long long tree[MAXN*4],lazy[MAXN*4];
};

void SegmentTree::pushdown(int v,int left,int right) {
	if(lazy[v]) {
		int mid=(left+right)>>1;
		tree[v<<1]=(tree[v<<1]+lazy[v]*(mid-left+1))%mod;
		tree[v<<1|1]=(tree[v<<1|1]+lazy[v]*(right-mid))%mod;
		lazy[v<<1]=(lazy[v<<1]+lazy[v])%mod;
		lazy[v<<1|1]=(lazy[v<<1|1]+lazy[v])%mod;
		lazy[v]=0;
	}
}

// [left,right]区间和
long long SegmentTree::query(int v,int left,int right,int goal_left,int goal_right) {
	int mid=(left+right)>>1;
	long long ret=0;
	pushdown(v,left,right);
	if(goal_left<=left && right<=goal_right)	return tree[v]%mod;
	if(mid>=goal_left)	ret=(ret+query(v<<1,left,mid,goal_left,goal_right))%mod;
	if(mid<goal_right)	ret=(ret+query(v<<1|1,mid+1,right,goal_left,goal_right))%mod;
	return ret%mod;
}

void SegmentTree::update(int v,int left,int right,int goal_left,int goal_right,int value) {
	pushdown(v,left,right);	
    if(goal_left<=left && right<=goal_right) {
        tree[v]=(tree[v]+(long long)(right-left+1)*value)%mod;
        lazy[v]=(lazy[v]+value)%mod;
        return;
    }
	int mid=(left+right)>>1;
	if(mid>=goal_left)	update(v<<1,left,mid,goal_left,goal_right,value);
	if(mid<goal_right)	update(v<<1|1,mid+1,right,goal_left,goal_right,value);
	tree[v]=(tree[v<<1]+tree[v<<1|1])%mod;
}

void SegmentTree::build_tree(int v,int left,int right) {
	if(left==right)	{tree[v]=x[left]%mod;return;}
	int mid=(left+right)>>1;
	build_tree(v<<1,left,mid);
	build_tree(v<<1|1,mid+1,right);
	tree[v]=(tree[v<<1]+tree[v<<1|1])%mod;
}

class Tree : public SegmentTree {
public:
    Tree() : SegmentTree() {}
    void readin();
private:  
    vector<int>tree[MAXN];
    int val[MAXN],fa[MAXN],size[MAXN],depth[MAXN],heavy_son[MAXN],id[MAXN],top[MAXN];
    int n,m,root;
    int cnt=0;
    void dfs1(int v,int u,int d);
    void dfs2(int v,int top_v);
    void update_tree(int left,int right,int value);
    long long query_tree(int left,int right);
};

void Tree::update_tree(int left,int right,int value) {
    while(top[left] != top[right]) {
        if(depth[top[left]] > depth[top[right]])  swap(left,right); // 比较两条链的顶点的深度
        update(1,1,n,id[top[right]],id[right],value);
        right=fa[top[right]];
    }
    if(depth[left] > depth[right])  swap(left,right);               // 在一条链上后维护这条链上的值
    update(1,1,n,id[left],id[right],value);
}

long long Tree::query_tree(int left,int right) {
    long long ret=0;
    while(top[left] != top[right]) {
        if(depth[top[left]] > depth[top[right]])  swap(left,right);
        ret=(ret+query(1,1,n,id[top[right]],id[right]))%mod;
        right=fa[top[right]];
    }
    if(depth[left] > depth[right])  swap(left,right);
    ret=(ret+query(1,1,n,id[left],id[right]))%mod;
    return ret;
}

void Tree::dfs1(int v,int u,int d) {
    depth[v]=d;             // 记录每个点的深度
    fa[v]=u;                // 记录每个点的父亲
    size[v]=1;              // 记录每个以v为根节点的子树大小
    int max_size=-1;
    for(int i=tree[v].size()-1;i>=0;i--) {
        if(tree[v][i]!=fa[v]) {  
            dfs1(tree[v][i],v,d+1);
            size[v]+=size[tree[v][i]];      // 更新子树大小
            if(max_size < size[tree[v][i]]) {       // 找到重儿子
                heavy_son[v] = tree[v][i];
                max_size = size[tree[v][i]];
            }
        }
    }
}

void Tree::dfs2(int v,int top_v) {
    id[v]=++cnt;                // 记录原来的点对应的新编号
    top[v]=top_v;               // 记录这条链上的最高处
    x[cnt]=val[v];            // 将原来的值赋予新编号后的线段树
    if(!heavy_son[v])   return;
    dfs2(heavy_son[v],top_v);       // 重儿子
    for(int i=tree[v].size()-1;i>=0;i--) {
        if(tree[v][i] != fa[v] && tree[v][i] != heavy_son[v]) {
            dfs2(tree[v][i],tree[v][i]);    // 轻儿子
        }
    }
}

void Tree::readin() {
    scanf("%d%d%d%d",&n,&m,&root,&mod);
    for(int i=1;i<=n;i++)   scanf("%d",&val[i]);
    for(int t1,t2,i=1;i<n;i++) {
        scanf("%d%d",&t1,&t2);
        tree[t1].push_back(t2);
        tree[t2].push_back(t1);
    }
    dfs1(root,0,1);
    dfs2(root,root);
    build_tree(1,1,n);      // 建立线段树维护
    for(int t1,t2,t3,t4,i=1;i<=m;i++) {
        scanf("%d",&t1);
        if(t1==1) {
            scanf("%d%d%d",&t2,&t3,&t4);
            update_tree(t2,t3,t4%mod);
        }
        else if(t1==2) {
            scanf("%d%d",&t2,&t3);
            printf("%lld\n",query_tree(t2,t3));
        }
        else if(t1==3) {
            scanf("%d%d",&t2,&t3);
            update(1,1,n,id[t2],id[t2]+size[t2]-1,t3%mod);      
            // 查询/修改 子树 v ，由于新建的编号连续，其在线段树上所对应的的区间就是[id[v],id[v]+size[v]-1]
            // 即子树根节点的新编号加上子树的大小减一即可
        }
        else {
            scanf("%d",&t2);
            printf("%lld\n",query(1,1,n,id[t2],id[t2]+size[t2]-1));
        }
    }
}

Tree s;

int main(){
    s.readin();
    return 0;
}