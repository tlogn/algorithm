#include <cstdio>
#include <iostream>
#include <algorithm>
#include <set>
#include <cstring>
using namespace std;
const long long mod = 1000000007;
struct Mat{
    int wid;
    long long mat[105][105];
    Mat operator * (const Mat &w) {
        Mat ret;
        ret.wid=wid;
        for(int i=1;i<=wid;i++) {
            for(int j=1;j<=wid;j++) {
                ret.mat[i][j]=0;
                for(int k=1;k<=wid;k++) {
                    ret.mat[i][j]=(ret.mat[i][j]+(mat[i][k]*w.mat[k][j])%mod)%mod;
                }
            }
        }
        return ret;
    }
    void print() {
        for(int i=1;i<=wid;i++) {
            for(int j=1;j<=wid;j++) {
                cout<<mat[i][j]<<' ';
            }
            cout<<endl;
        }
    }
};
Mat base1,base2;
long long n,m,x,y;
string st;
void init() {
    scanf("%lld%lld",&n,&m);
    
    cin>>st;
    long long temp=100;
    x=(st[0]-'0')*1000;
    for(int i=2;i<st.size();i++)
        x+=(st[i]-'0')*temp,temp/=10;

    cin>>st;
    temp=100;
    y=(st[0]-'0')*1000;
    for(int i=2;i<st.size();i++)
        y+=(st[i]-'0')*temp,temp/=10;
    

    base1.wid=m+1;
    base1.mat[1][1]=(1000-y*m-x+mod)%mod;
    for(int i=2;i<=m+1;i++) {
        base1.mat[i][i-1]=((m-(i-2))*y)%mod;
        base1.mat[i][i]=(1000-(m-(i-1))*y-x+mod)%mod;
    }
//    base1.mat[m+1][m]=(long long)(y*1000);
//    base1.mat[m+1][m+1]=(long long)((1.0-x)*1000);

    base2.wid=2;
    base2.mat[1][1]=1000-x;
    base2.mat[1][2]=0;
    base2.mat[2][1]=x;
    base2.mat[2][2]=1000;
}
Mat power(Mat base,long long r) {
    Mat ret;
    ret.wid=base.wid;
    for(int i=1;i<=ret.wid;i++) {
        for(int j=1;j<=ret.wid;j++) {
            ret.mat[i][j]=0;
        }
        ret.mat[i][i]=1;
    }
    while(r) {
        if(r&1) ret=ret*base;
        base=base*base;
        r>>=1;
    }
    return ret;
}
int main() {  
    init();
    if(n<=0) {
        printf("0\n");
        return 0;
    }
    
    Mat temp1=power(base1,n);
    Mat temp2=power(base2,n);
    long long ans=0;

//    temp1.print();
//    temp2.print();
    
    ans+=temp1.mat[m+1][1];
    ans+=temp2.mat[2][1];
    printf("%lld\n",ans%mod);
    return 0;
}   
/*
4 2
0.1 0.2
*/