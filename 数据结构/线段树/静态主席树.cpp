#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <queue>
#include <iostream>
using namespace std;

const int MAXN = 2e5+5;

class SegmentTree {
public:
	SegmentTree() {};
	~SegmentTree() {};
	void readin();
	int build(int left,int right);
	int update_tree(int pre,int left,int right,int value);
	int query(int u,int v,int left,int right,int goal);
private:
	int n,m,tot,cnt=0,a[MAXN],b[MAXN],h[MAXN],T[MAXN];
	struct Node {
		int sum,left,right;
		Node() {sum=left=right=0;}
	}tree[MAXN*32];
};

int SegmentTree::update_tree(int pre,int left,int right,int value) {
	int mid=(left+right)>>1;
	int ret=++cnt;
	tree[ret].sum=tree[pre].sum+1;
	if(left<right) {
		if(value>mid) {
			tree[ret].left=tree[pre].left;
			tree[ret].right=update_tree(tree[pre].right,mid+1,right,value);
		}
		else {
			tree[ret].right=tree[pre].right;
			tree[ret].left=update_tree(tree[pre].left,left,mid,value);
		}
	}
	return ret;
}

int SegmentTree::build(int left,int right) {
	int mid=(left+right)>>1;
	int ret=++cnt;
	if(left<right) {
		tree[ret].left=build(left,mid);
		tree[ret].right=build(mid+1,right);
	}
	return ret;
}

// u为t1-1的线段树遍历到的子树根节点，v为t2的线段树遍历到的子树根节点
int SegmentTree::query(int u,int v,int left,int right,int goal) {
	int mid=(left+right)>>1,temp=tree[tree[v].left].sum-tree[tree[u].left].sum;
	if(left==right)	return left;
	if(temp<goal) return query(tree[u].right,tree[v].right,mid+1,right,goal-temp);
	else return query(tree[u].left,tree[v].left,left,mid,goal);
}

void SegmentTree::readin() {
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) {
		scanf("%d",&a[i]);
		b[i]=a[i];
	}
	sort(b+1,b+1+n);
	tot=unique(b+1,b+1+n)-b-1;	// b : a从小到大排序后并去重的序列 tot : 离散化后总数
	for(int i=1;i<=n;i++) {
		h[i]=lower_bound(b+1,b+1+tot,a[i])-b;	// h : a离散化后的序列
	}
	// 建树
	T[0]=build(1,tot);

	// 将区间后面的节点一一加入
	for(int i=1;i<=n;i++) {
		T[i]=update_tree(T[i-1],1,tot,h[i]);
	}

	for(int t1,t2,t3,i=1;i<=m;i++) {
		scanf("%d%d%d",&t1,&t2,&t3);
		printf("%d\n",b[query(T[t1-1],T[t2],1,tot,t3)]);	// 查询区间[t1,t2]中第t3大的数
	}
}
SegmentTree s;
int main(){
	s.readin();
    return 0;
}