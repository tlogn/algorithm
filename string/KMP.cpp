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
        while(k>-1 && substring[k+1]!=substring[i]) k=_next[k];
        if(substring[k+1]==substring[i]) _next[i]=_next[++k];
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
            k=-1;
            i=i-len+1;
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
