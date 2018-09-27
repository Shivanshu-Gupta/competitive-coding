const int mod = 1E9 + 7;

int exp(int x, int n) {
    int res = 1;
    int p = x;
    while(n) {
        if(n & 1) res = res * p;
        n >>= 1;
        p = p * p;
    }
    return res;
}

int modexp(int x, int n) {
    if(x == 0) return 0;
    int res = 1;
    int p = x % mod;
    while(n) {
        if(n & 1) res = (res * p) % mod;
        n >>= 1;
        p = (p * p) % mod;
    }
    return res;
}



