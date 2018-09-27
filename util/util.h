//
// Created by Shivanshu Gupta on 09/07/17.
//

#ifndef MYLIBRARY_UTIL_H
#define MYLIBRARY_UTIL_H

#include "bits/stdc++.h"

#define debug(x) cout << '>' << #x << ':' << x << endl;

#define rep(i,n) for(int i = 0; i < (n); i++)
#define fori(i,a,b) for(int i = (a); i < (b); i++)
#define ford(i,a,b) for(int i = (a); i > (b); i--)

#define ms0(x) memset(x,0,sizeof(x))
#define ms1(x) memset(x,0xff,sizeof(x))
#define fillv(v, x) fill((v).begin(), (v).end(), (x))

#define gc() getchar_unlocked()
#define pc(x) putchar_unlocked(x)

#define sz(C) (C.size())
#define all(C) C.begin(), C.end()
#define tr(it, C) \
	  for(decltype(C.begin()) it = C.begin(); it != C.end(); it++)

#define spresent(S, k) (S.find(k) != S.end())
#define cpresent(C, e) (find(all(C), e) != C.end())

void read_int(int &ret);

#endif //MYLIBRARY_UTIL_H
