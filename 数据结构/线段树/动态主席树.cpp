/*
树状数组套主席树
警告: 本模板自带大常数
*/

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
	SegmentTree() {memset(t3,-1,sizeof(t3));memset(T,0,sizeof(T));cnt=cnt_b=0;};
	~SegmentTree() {};
	void readin();


private:
	int n,m,tot,cnt,cnt_b;					// tot:离散化后总数 cnt:建树时记录所用点
	int a[MAXN],b[MAXN];		// 储存离散化序列
	int T[MAXN];
	int t1[MAXN],t2[MAXN],t3[MAXN];		// 储存询问

	int temp[2][40],temp_cnt[2];				
	// temp储存每次要查询的区间[t1,t2]树状数组编号
	// temp_cnt[i]存储temp[i][]的size
	// 查询的时候, temp[0][]存储[1,t1-1]的区间, temp[1][]存储[1,t2]的区间, 前缀和相减

	struct Node {
		int sum,left,right;
	}tree[MAXN*400];

	int lowbit(int v);
	
	void update_tree(int pos,int value);
	void modify_tree(int &id,int num,int value,int left,int right);

	int query(int left,int right,int goal);
	int query_tree(int left,int right,int goal);
};

int SegmentTree::query_tree(int left,int right,int goal) {
	if(left==right)	return left;
	int sum=0;
	for(int i=1;i<=temp_cnt[0];i++)	sum=sum-tree[tree[temp[0][i]].left].sum;
	for(int i=1;i<=temp_cnt[1];i++)	sum=sum+tree[tree[temp[1][i]].left].sum;
	int mid=(left+right)>>1;
	if(sum>=goal) {
		for(int i=1;i<=temp_cnt[0];i++)	temp[0][i]=tree[temp[0][i]].left;
		for(int i=1;i<=temp_cnt[1];i++)	temp[1][i]=tree[temp[1][i]].left;
		return query_tree(left,mid,goal);
	}
	else {
		for(int i=1;i<=temp_cnt[0];i++)	temp[0][i]=tree[temp[0][i]].right;
		for(int i=1;i<=temp_cnt[1];i++)	temp[1][i]=tree[temp[1][i]].right;
		return query_tree(mid+1,right,goal-sum);
	}
}

int SegmentTree::query(int left,int right,int goal) {
	
	// 初始化
	temp_cnt[0]=temp_cnt[1]=0;
	
	// 通过树状数组找到需要查询的树的编号并存储在temp中
	for(int i=left-1;i;i-=lowbit(i)) {
		temp_cnt[0]++;
		temp[0][temp_cnt[0]]=T[i];
	}
	for(int i=right;i;i-=lowbit(i)) {
		temp_cnt[1]++;
		temp[1][temp_cnt[1]]=T[i];
	}

	// 查询
	return query_tree(1,tot,goal);
	
}

// 每次修改最多只会增加线段树上的一条链, log的时空复杂度
void SegmentTree::modify_tree(int &id,int num,int value,int left,int right) {
	if(!id)	id=++cnt;
	tree[id].sum=tree[id].sum+value;
	if(left==right)	return;
	int mid=(left+right)>>1;
	if(mid>=num)	modify_tree(tree[id].left,num,value,left,mid);
	else	modify_tree(tree[id].right,num,value,mid+1,right);
}

void SegmentTree::update_tree(int pos,int value) {
	int num=lower_bound(b+1,b+1+tot,a[pos])-b;
	for(int i=pos;i<=tot;i+=lowbit(i))
		modify_tree(T[i],num,value,1,tot);
}

int SegmentTree::lowbit(int v) {
	return v&(-v);
}

void SegmentTree::readin() {
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) {
		scanf("%d",&a[i]);
		b[++cnt_b]=a[i];
	}

	for(int i=1;i<=m;i++) {
		char c[20];
		scanf("%s",c);
		if(c[0]=='Q') {
			scanf("%d%d%d",&t1[i],&t2[i],&t3[i]);
		}
		else {
			scanf("%d%d",&t1[i],&t2[i]);
			b[++cnt_b]=t2[i];
		}
	}

	sort(b+1,b+1+cnt_b);
	tot=unique(b+1,b+1+cnt_b)-b-1;	// b : a从小到大排序后并去重的序列 tot : 离散化后总数

	// 建树
	for(int i=1;i<=n;i++)	update_tree(i,1);

	for(int i=1;i<=m;i++) {
		if(t3[i]>-1) {
			printf("%d\n",b[query(t1[i],t2[i],t3[i])]);
		}
		else {
			update_tree(t1[i],-1);
			a[t1[i]]=t2[i];
			update_tree(t1[i],1);
		}
	}
}
SegmentTree s;
int main(){
	s.readin();
    return 0;
}