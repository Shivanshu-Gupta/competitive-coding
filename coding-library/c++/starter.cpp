#include "bits/stdc++.h"

#define debug(x) cout << '>' << #x << ':' << x << endl

#define rep(i,n) for(int i = 0; i < (n); i++)
#define fori(i,a,b) for(int i = (a); i < (b); i++)
#define ford(i,a,b) for(int i = (a); i > (b); i--)

// memset and fill
#define ms(a, x) memset(a, x, sizeof(a))
#define ms0(a) ms(a, 0)
#define ms1(a) ms(a, 0xff)
#define fillv(v, x) fill((v).begin(), (v).end(), (x))

// io
#define gc() getchar_unlocked()
#define pc(x) putchar_unlocked(x)

// traversal
#define all(C) C.begin(), C.end()
#define tr(it, C) \
      for(auto it = C.begin(); it != C.end(); it++) 

// search
#define spresent(S, k) (S.find(k) != S.end())
#define cpresent(C, e) (find(all(C), e) != C.end())

#define MAX(type) numeric_limits<type>::max()
#define MIN(type) numeric_limits<type>::min()

using namespace std;

#define vectypes(T) typedef vector<T> V##T; typedef vector<V##T> VV##T

typedef int I; vectypes(I);
typedef double D; vectypes(D);
typedef pair<int, int> II; vectypes(II);

// fast integer read
void read_int(int &ret) {
    ret = 0;
    int sign = 1;
    char c = gc();
    while(c != '-' && (c<'0' || c>'9')) c = gc();
    if(c == '-') {
        sign = -1;
        c = gc();
    }
    while(c>='0' && c<='9') {
        ret = (ret<<3) + (ret<<1) + c - '0';
        c = gc();
    }
    ret *= sign;
}

int main() {
    ios::sync_with_stdio(false);
    int ip;
    
    return 0;
}