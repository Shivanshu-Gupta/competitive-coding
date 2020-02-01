#include "bits/stdc++.h"
using namespace std;

typedef vector<int> VI;

/**
 * Binary Heap implementation
 * -    Min-Heap by default.
 * ref:
 * 1. http://code-library.herokuapp.com/binary-heap/java
 * 2. http://www.cprogramming.com/c++11/c++11-lambda-closures.html
 */

template <class V, class Compare = function<bool(const V&, const V&)>>
struct BinaryHeap {
    vector<V> heap;
    Compare compare = less<V>();

    BinaryHeap(Compare f = less<V>()) : compare(f) { }

    BinaryHeap(vector<V> vals, Compare f = less<V>()) : compare(f) {
        heap = vals;
        int n = heap.size();
        // Build Heap
        for(int i = (n-1)>>1; i > 0; i--) {
            down(i);
        }
    }

    void push(V val) {
        heap.push_back(val);
        up(heap.size() -1);
    }

    inline V top() { return heap[0]; }

    void pop() {
        heap[0] = heap.back();
        heap.pop_back();
        down(0);
    }

    inline int size() { return heap.size(); }

    inline bool empty() { return heap.size() == 0; }

private:
    // percolate down a.k.a. heapify
    void down(int pos) {
        while(1) {
            int child = ((pos << 1)|1);
            if(child > size()) break;
            if(child+1 <= size() && compare(heap[child+1], heap[child]))
                child++;
            if(!compare(heap[child], heap[pos])) break;
            swap(heap[pos], heap[child]);
            pos = child;
        }
    }

    //percolate up
    void up(int pos) {
        while(pos) {
            int parent = (pos-1) >> 1;
            if(!compare(heap[pos], heap[parent])) break;
            swap(heap[parent], heap[pos]);
            pos = parent;
        }
    }
};

// random test
void testHeap() {
    srand(time(NULL));
    for (int step = 0; step < 10; step++) {
        int n = rand() % 100 + 1;
        priority_queue<int, vector<int>, greater<int>> q;

        BinaryHeap<int> h;
        switch(rand()%4) {
            case 1:
                h = BinaryHeap<int>(less<int>());
                break;
            case 2:
                h = BinaryHeap<int>([] (const int& lhs, const int& rhs) {
                    return lhs<rhs;
                });
                break;
            case 3:
                h = BinaryHeap<int>([] (const int& lhs, const int& rhs) -> bool {
                    return lhs<rhs;
                });
                break;
        }
        for (int op = 0; op < 1000; op++) {
            if (q.size() < n) {
                int v = rand()%1000;
                q.push(v);
                h.push(v);
                if(1) cout << v << endl;
            } else if (!q.empty()) {
                if(1) cout << q.top() << '\t' << h.top() << endl;
                assert(q.top() == h.top());
                q.pop();
                h.pop();
            }
        }
    }
}

int main() {
    testHeap();
    return 0;
}
