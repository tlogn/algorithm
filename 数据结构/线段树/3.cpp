/*
线段树——区间更新
*/

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <queue>
#include <iostream>
using namespace std;

const int MAXN = 1e6+5;

class SegmentTree {
public:
	SegmentTree() {};
	~SegmentTree() {};
	void readin();
private:
	void build_tree(int v,int left,int right);
	void update(int v,int left,int right,int goal_left,int goal_right,int value);
	long long query(int v,int left,int right,int goal_left,int goal_right);
	void pushdown(int v,int left,int right);

	int n,m;
	int x[MAXN];
	long long tree[MAXN*4],lazy[MAXN*4];
};

void SegmentTree::pushdown(int v,int left,int right) {
	if(lazy[v]) {
		int mid=(left+right)>>1;
		tree[v<<1]+=lazy[v]*(mid-left+1);	// 此处必须将左右儿子更新，因为pushup会用到左右儿子的值
		tree[v<<1|1]+=lazy[v]*(right-mid);
		lazy[v<<1]+=lazy[v];
		lazy[v<<1|1]+=lazy[v];
		lazy[v]=0;
	}
}

// [left,right]区间和
long long SegmentTree::query(int v,int left,int right,int goal_left,int goal_right) {
	int mid=(left+right)>>1;
	long long ret=0;
	pushdown(v,left,right);
	if(goal_left<=left && right<=goal_right)	return tree[v];
	if(mid>=goal_left)	ret+=query(v<<1,left,mid,goal_left,goal_right);
	if(mid<goal_right)	ret+=query(v<<1|1,mid+1,right,goal_left,goal_right);
	return ret;
}

// [left,right]每个值加value
void SegmentTree::update(int v,int left,int right,int goal_left,int goal_right,int value) {
	if(goal_left<=left && right<=goal_right) {tree[v]+=(long long)(right-left+1)*value;lazy[v]+=value;return;}
	int mid=(left+right)>>1;
	pushdown(v,left,right);
	if(mid>=goal_left)	update(v<<1,left,mid,goal_left,goal_right,value);
	if(mid<goal_right)	update(v<<1|1,mid+1,right,goal_left,goal_right,value);
	tree[v]=tree[v<<1]+tree[v<<1|1];
}

void SegmentTree::build_tree(int v,int left,int right) {
	if(left==right)	{tree[v]=x[left];return;}
	int mid=(left+right)>>1;
	build_tree(v<<1,left,mid);
	build_tree(v<<1|1,mid+1,right);
	tree[v]=tree[v<<1]+tree[v<<1|1];
}

void SegmentTree::readin() {
	scanf("%d%d",&n,&m);
	build_tree(1,1,n);
	for(int t1,t2,t3,t4,i=1;i<=m;i++) {
		scanf("%d",&t1);
		if(t1==1) {
			scanf("%d%d%d",&t2,&t3,&t4);
			update(1,1,n,t2,t3,t4);
		}
		else {
			scanf("%d%d",&t2,&t3);
			printf("%lld\n",query(1,1,n,t2,t3));

		}
	}
}

SegmentTree s;

int main(){
	s.readin();
    return 0;
}