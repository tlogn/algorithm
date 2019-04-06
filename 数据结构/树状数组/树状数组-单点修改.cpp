/*
树状数组的精彩讲解：
https://blog.csdn.net/FlushHip/article/details/79165701
*/

/*
单点更新的树状数组
*/

#include <cstdio>
#include <iostream>
#include <cstring>

#define MAXN 500005

class BinaryIndexTree {
public:
	BinaryIndexTree() {
		memset(tree,0,sizeof(tree));
	}
	void readin();
	void update(int id,int value);
	int query(int id1,int id2);
private:
	int sum(int id);
	int lowbit(int id);
	int n,m,tree[MAXN];
};

int BinaryIndexTree::lowbit(int id) {	
	return id&(-id);
}

void BinaryIndexTree::update(int id,int value) {	// 更新单点
	for(int i=id;i<=n;i+=lowbit(i)) {
		tree[i]+=value;
	}
}

int BinaryIndexTree::sum(int id) {		// 查询1~id的前缀和
	int ret=0;
	for(int i=id;i;i-=lowbit(i)) {
		ret+=tree[i];
	}
	return ret;
}

int BinaryIndexTree::query(int id1,int id2) {	// 通过前缀和相减得到id1~id2的区间和
	return sum(id2)-sum(id1-1);
}

void BinaryIndexTree::readin() {
	scanf("%d%d",&n,&m);
	for(int temp,i=1;i<=n;i++) {
		scanf("%d",&temp);
		update(i,temp);
	}
	for(int i=1;i<=m;i++) {
		int order,t1,t2;
		scanf("%d%d%d",&order,&t1,&t2);
		if(order==1) update(t1,t2);
		else	printf("%d\n",query(t1,t2));
	}

}
BinaryIndexTree s;
int main() {
	s.readin();
	return 0;
}