#include <iostream>
#include <string>
#include <string.h>
#include <cstdio>
#include <cstdlib>
using namespace std;

const int maxn = 200005;
int p[maxn<<1];
char A[maxn<<1], B[maxn];

void rebuild(char *str){
    int len = strlen(str);
    A[0] = '$';A[1] = '#';
    for(int i = 1; i <= len; ++i){
        A[(i<<1)] = str[i-1];
        A[(i<<1)+1] = '#';
    }
    A[(len<<1)+2] = '\0';
}
int Manacher(char* str){
    int len = strlen(str),id = 0,maxLimit = 0, max_ans = 0;
    for(int i = 0; i < len; ++i){
        if(maxLimit > i) p[i] = std::min(p[(id<<1)-i], maxLimit-i);
        else p[i] = 1;
        while(A[i+p[i]] == A[i-p[i]]) ++p[i];
        max_ans = std::max(max_ans, p[i]);
        if(i+p[i] > maxLimit) maxLimit = i + p[i], id = i;
    }
    return max_ans - 1;
}
int main(){
    while(scanf("%s", B)!=EOF){
        rebuild(B);
        cout << Manacher(A) << endl;
    }
    return 0;
}
