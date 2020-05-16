#include "bits/stdc++.h"

using namespace std;

typedef pair<int, int> II;
typedef vector<int> VI;

/**
 * Min-Heap implementation
 */
template <class I, class V, class Compare = function<bool(const V&, const V&)>>
struct BinaryHeap {
    vector<V> heap;
    vector<I> pos2id;
    unordered_map<I, int> id2pos; // may use array instead if ids are dense
    Compare compare = less<V>();

    BinaryHeap(Compare f = less<V>()) : compare(f) { }

    BinaryHeap(vector<I> ids, vector<V> vals, Compare f = less<V>())
            : compare(f) {
        heap = vals;
        pos2id = ids;
        for(int i = 0; i < ids.size(); i++) {
            id2pos[ids[i]] = i;
        }

        // build heap
        int n = heap.size();
        for(int i = (n-1)>>1; i >= 0; i--) {
            down(i);
        }
    }

    void push(I id, V val) {
        if(hasId(id)) return;
        heap.push_back(val);
        pos2id.push_back(id);
        id2pos[id] = heap.size()-1;
        up(heap.size()-1);
    }


    void modify(I id, V val) {
        assert(hasId(id));
        int pos = id2pos[id];
        V oldval = heap[pos];
        heap[pos] = val;
        if(compare(val, oldval)) up(pos);
        else down(pos);
    }

    inline pair<I, V> top() { return {pos2id[0], heap[0]}; }

    void pop() {
        heap[0] = heap.back(); heap.pop_back();
        pos2id[0] = pos2id.back(); pos2id.pop_back();
        id2pos[pos2id[0]] = 0;
        down(0);
    }

    inline bool hasId(I id) { return id2pos.find(id) != id2pos.end(); }
    inline int size() { return heap.size(); }
    inline bool empty() { return heap.size() == 0; }

private:

    // percolate down a.k.a. heapify
    void down(int pos) {
        while(1) {
            int child = (pos << 1) | 1;
            if(child > size()) break;
            if(child+1 <= size() && compare(heap[child+1], heap[child]))
                child++;
            if(!compare(heap[child], heap[pos])) break;
            swapNode(pos, child);
            pos = child;
        }
    }

    // percolate up
    void up(int pos) {
        while(pos) {
            int parent = (pos-1) >> 1;
            if(!compare(heap[pos], heap[parent])) break;
            swapNode(parent, pos);
            pos = parent;
        }
    }

    void swapNode(const int &i, const int &j) {
        swap(heap[i], heap[j]);
        swap(pos2id[i], pos2id[j]);
        id2pos[pos2id[i]] = i;
        id2pos[pos2id[j]] = j;
    }
};

// random test
void testHeapPrioUpdate() {
    srand(time(NULL));
    for (int step = 0; step < 10; step++) {
        int n = rand() % 100 + 1;
        priority_queue<int, vector<int>, greater<int>> q;

        BinaryHeap<int, int> h;
        switch(rand()%4) {
            case 1:
                h = BinaryHeap<int, int>(less<int>());
                break;
            case 2:
                h = BinaryHeap<int, int>([] (const int& lhs, const int& rhs) {
                    return lhs<rhs;
                });
                break;
            case 3:
                h = BinaryHeap<int, int>([] (const int& lhs, const int& rhs) -> bool {
                    return lhs<rhs;
                });
                break;
        }
        for (int op = 0; op < 1000; op++) {
            if (q.size() < n) {
                int v = rand()%1000;
                q.push(v);
                h.push(op, v);
                if(1) cout << v << endl;
            } else if (!q.empty()) {
                if(1) cout << q.top() << '\t' << h.top().second << endl;
                assert(q.top() == h.top().second);
                q.pop();
                h.pop();
            }
        }
    }
}

int main() {
    testHeapPrioUpdate();
    return 0;
}

