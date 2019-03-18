#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
#include <cstdlib>

#define MAXN ((int)1e6+5)

using namespace std;
class KMP {
public:
    KMP() {}
    void read_substring() {scanf("%s",substring);}
    void read_mainstring() {scanf("%s",mainstring);}
    void get_next();
    void kmp();
    void print_next();
private:
    int _next[MAXN];
    char mainstring[MAXN],substring[MAXN];
};
void KMP::get_next() {
    _next[0]=-1;
    int k=-1;
    for(int i=1;substring[i];i++) {
        while(k>-1 && substring[k+1]!=substring[i]) k=_next[k]; // 如果不相等就一直回溯到相等或者回溯到头为止
        if(substring[k+1]==substring[i]) k++;
        // 如果二者相同，指针++。因为二者相同，所以当此位置失配时，通过next转移的位置也必然失配。KMP算法和MP算法的区别就在于避免了这种失配。此处为MP算法（自我感觉已经很快了，够用了）
        _next[i]=k;
    }
}
void KMP::kmp() {
    int k=-1,len=strlen(substring);
    for(int i=0;mainstring[i];i++) {
        while(k>-1 && mainstring[i]!=substring[k+1])    k=_next[k];
        if(mainstring[i]==substring[k+1])   k++;
        if(k==len-1) {
            printf("%d\n",i-len+2);
            k=_next[k];
        }
    }
}
void KMP::print_next() {
    int len=strlen(substring);
    for(int i=0;i<len;i++)  printf("%d ",_next[i]+1);
}
KMP s;
int main() {
    s.read_mainstring();
    s.read_substring();
    s.get_next();
    s.kmp();
    s.print_next();
    return 0;
}
