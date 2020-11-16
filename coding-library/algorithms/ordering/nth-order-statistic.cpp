#include <iostream>
#include <vector>

using namespace std;

typedef vector<int> VI;

void print(const VI &a);

/**
 * Given an unsorted vector a, partitions the range a[beg:end) using the element at pivotidx.
 * If k elements are less than pivot, sets:
 * a[beg:beg+k) < pivot, a[beg+k] = pivot, and a[beg+k+1:end) >= pivot
 * @return k - final pivot index.
 */
int partition(VI &a, int beg, int end, int pivotidx) {
    assert(0 <= beg && beg <= pivotidx && pivotidx < end && end <= a.size());
    int l = beg, r = end, pivot = a[pivotidx];
    swap(a[l], a[pivotidx]);    // store pivot at a[beg]
    // invariant: a[beg+1:l] <= pivot, a[r:end-1] >= pivot
    while(r-l > 1) {
        while(r-l > 1 && a[l+1] < pivot) l++;
        while(r-l > 1 && a[r-1] >= pivot) r--;
        if(r-l <= 1) break;
        swap(a[++l], a[--r]);
    }
    swap(a[beg], a[l]); // last element of first group is set to the pivot.
    return l;
}

/**
 * Given an unsorted vector a, sets a[n] to the element that will be there if a[l:r) were sorted.
 * -    Time Complexity: O(n) average.
 * -    Space Complexity: O(1)
 * -    Modifies the vector.
 */
void nth_element(VI &a, int l, int r, int n) {
    assert(0 <= l && l <= n && n < r && r <= a.size());
    // invariant: nth smallest element lies in range [l, r)
    while(1) {
        int pivotidx = l+rand()%(r-l);
        int k = partition(a, l, r, pivotidx);
        if(k == n) return;
        if(k < n) {
            l = k + 1;
        } else {
            r = k;
        }
    }
}

/**
 * Given an unsorted vector a, returns the element that a[n] will be set to if a[l:r) were sorted.
 * -    Uses binary search.
 * -    Time Complexity: O(nlogd) where d = max(a) - min(a).
 * -    Space Complexity: O(1)
 * -    Doesn't modify the vector.
 */
int nth_element2(const VI &a, int l, int r, int n) {
    assert(0 <= l && l <= n && n < r && r <= a.size());
    int k = n - l + 1;
    int lo = INT_MAX, hi = INT_MIN;
    for(int i = l; i < r; i++) {
        if(lo > a[i]) lo = a[i];
        if(hi < a[i]) hi = a[i];
    }
    while(lo <= hi) {
        int mid = lo + (hi - lo)/2;
        int less = 0, equal = 0, greater = 0;
        for(int i = l; i < r; i++) {
            if(a[i] < mid) less++;
            else if(a[i] == mid) equal++;
            else greater++;
        }
        if(less >= k) hi = mid-1;
        else if(less+equal >= k) return mid;
        else lo = mid + 1;
    }
    return -1;
}


void testPartition() {
    srand(434234);
    for(int step = 0; step < 10000; step++) {
        int len = 1 + rand() % 10;
        VI a(len);
        for(int i = 0; i < len; i++)
            a[i] = rand() % 10;
        int pivotidx = rand() % len;
        int k = partition(a, 0, len, pivotidx);
        for(int i = 0; i < len; i++) {
            assert((i < k && a[i] <= a[k]) || (i == k && a[i] == a[k]) || (i > k && a[i] >= a[k]));
        }
    }
}

void testNthSmallest() {
    srand(434234);
    for (int step = 0; step < 10000; step++) {
        int n = 1 + rand() % 30; cout << n << endl;
        VI a(n);
        for(int i = 0; i < n; i++) a[i] = rand() % 10;
        print(a);
        VI b(a), sa(a);
        int l = rand() % n;
        int r = l + 1 + rand() % (n-l);
        int k = l + rand() % (r-l);
        cout << l << ' ' << k << ' ' << r << endl;
        int kth = nth_element2(a, l, r, k);
        nth_element(a, l, r, k); print(a);
        nth_element(b.begin()+l, b.begin() + k, b.begin()+r); print(b);
        sort(sa.begin()+l, sa.begin()+r); print(sa);

        cout << k << ' ' << kth << ' ' << a[k] << ' ' << sa[k] << ' ' << b[k] << endl;
        assert(a[k] == kth);
        assert(a[k] == sa[k]);
        assert(a[k] == b[k]);
        for (int i = l; i < r; i++) {
            assert((i < k && a[i] <= a[k]) || (i == k) || (i > k && a[i] >= a[k]));
        }
        cout << endl;
    }
}

//int main() {
//    testNthSmallest();
//    return 0;
//}

void print(const VI &a) {
    for(int x : a) cout << x << ' ';
    cout << endl;
}
