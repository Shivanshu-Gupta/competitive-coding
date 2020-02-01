#include "bits/stdc++.h"
#include "../util/util.h"
using namespace std;

typedef vector<int> VI;

int kthSmallestRecur(const VI &a, int l1, const VI &b, int l2, int k) {
    int size1 = a.size() - l1, size2 = b.size() - l2;
    assert(0 < k && k <= size1 + size2);
    if(size1 == 0) return b[l2+k-1];
    if(size2 == 0) return a[l1+k-1];
    if(k == 1) return min(a[l1], b[l2]);
    int i = k/2, j = k - i;
    if(j <= size2 && (i > size1 || a[l1+i-1] > b[l2+j-1]))
        return kthSmallestRecur(a, l1, b, l2 + j, k - j);
    else
        return kthSmallestRecur(a, l1 + i, b, l2, k - i);
}

int kthSmallestIter(const VI &a, int al, const VI &b, int bl, int k) {
    assert(0 < k && k <= a.size() + b.size());
    while(1) {
        if(al == a.size()) return b[bl+k-1];
        if(bl == b.size()) return a[al+k-1];
        if(k == 1) return min(a[al], b[bl]);
        int i = k/2, j = k - i;
        if(bl+j <= b.size() && (al+i > a.size() || a[al+i-1] > b[bl+j-1])) {
            bl += j; k -= j;
        } else {
            al += i; k -= i;
        }
    }

}

double median(const VI &a, const VI &b) {
    int size = a.size() + b.size();
    if(size&1) {
        double med = kthSmallestIter(a, 0, b, 0, (size+1)/2);
        return med;
    } else {
        double med1 = kthSmallestIter(a, 0, b, 0, (size)/2);
        double med2 = kthSmallestIter(a, 0, b, 0, 1+(size)/2);
        return (med1 + med2) / 2;
    }
}

// or just use c++ merge - http://www.cplusplus.com/reference/algorithm/merge/ (better implementation of merge)
VI merge(const VI &a, const VI &b, VI &merged) {
    int m = a.size(), n = b.size();
    merged.resize(m + n);
    int i = 0, j = 0, k = 0;
    while(i < m && j < n) {
        if(a[i] > b[j]) {
            merged[k++] = b[j++];
        } else {
            merged[k++] = a[i++];
        }
    }
    while(i < m) merged[k++] = a[i++];
    while(j < n) merged[k++] = b[j++];

    return merged;
}

void testKthSmallest() {
    srand(434234);
    for (int step = 0; step < 10000; step++) {
        int m = 1 + rand() % 20, n = 1 + rand() % 20;
        cout << m << ' ' << n << endl;

        VI a(m), b(n), c;
        for(int i = 0; i < m; i++) a[i] = rand() % 20;
        sort(a.begin(), a.end());
        for(int i = 0; i < n; i++) b[i] = rand() % 20;
        sort(b.begin(), b.end());
        printVI(a); printVI(b);

        int k = 1 + rand() % (m + n);
        int kth = kthSmallestIter(a, 0, b, 0, k);
        merge(a, b, c); printVI(c);
        cout << k << ' ' << kth << ' ' << c[k- 1] << endl;
        assert(kth == c[k-1]);
        cout << endl;
    }
}

int main() {
    testKthSmallest();
    return 0;
}
