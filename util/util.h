//
// Created by Shivanshu Gupta on 09/07/17.
//

#ifndef MYLIBRARY_UTIL_H
#define MYLIBRARY_UTIL_H

#include "bits/stdc++.h"
using namespace std;

#define debug(x) cout << '>' << #x << ':' << x << endl;

#define fori(i,a,b) for(int i = (a); i < (b); i++)
#define ford(i,a,b) for(int i = (a); i > (b); i--)
#define rep(i,n) fori(i,0,n)

#define ms0(a) memset(a, 0, sizeof(a))
#define ms1(a) memset(a, 0xff, sizeof(a))
#define msv0(v) memset(&(v)[0], 0, sizeof((v)[0]) * (v).size())
#define msv1(v) memset(&(v)[0], 0xff, sizeof((v)[0]) * (v).size())
#define fillv(v, x) fill((v).begin(), (v).end(), (x))

#define gc() getchar_unlocked()
#define pc(x) putchar_unlocked(x)

#define sz(C) (C.size())
#define all(C) C.begin(), C.end()
#define tr(it, C) \
	  for(decltype(C.begin()) it = C.begin(); it != C.end(); it++)

#define spresent(S, k) (S.find(k) != S.end())
#define cpresent(C, e) (find(all(C), e) != C.end())

#define mod(a, b) (((a) % (b) + (b)) % (b))     // correctly compute a mod b even if a < 0

#define vectypes(T) typedef vector<T> V##T; typedef vector<V##T> VV##T
typedef int I; vectypes(I);
typedef double D; vectypes(D);
typedef pair<int, int> II; vectypes(II);

void read_int(int &ret);
void printVI(const VI &a);

#endif //MYLIBRARY_UTIL_H
