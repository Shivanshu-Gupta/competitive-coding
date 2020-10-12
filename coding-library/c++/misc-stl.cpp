#include "../util/util.h"

using namespace std;

#define SIZE 6

// helper function to sort indices
template <typename T>
vector<size_t> sort_indices(const vector<T>& v) {
    
    //initialize original index locations
    vector<size_t> idx(v.size());
    for(size_t i=0; i<idx.size(); i++) { idx[i]=i; }

    sort(idx.begin(), idx.end(), 
        [&v](size_t i1, size_t i2) { return v[i1] < v[i2]; });

    return idx;
}

int main() {
    ios::sync_with_stdio(false);
    int ip;
    
    vector<int> v1(SIZE);
    
    fori(i, 0, SIZE) {
        cin>>v1[i];
    }

    // set<int> s(all(v1));
    set<int> s;
    copy(all(v1), inserter(s, s.begin()));
    vector<int> v2(all(s));     // v2 will now have unique elements of v1 in sorted order.

    sort(all(v1));
    tr(it, v1) {
        cout<<*it<<' ';
    }
    cout<<endl;

    tr(it, v2) {
        cout<<*it<<' ';
    }
    cout<<endl;

    // do all permutations in a sorted list
    // do {
    //     tr(it, v2) {
    //         cout<<*it<<' ';
    //     }

    //     cout<<endl;
    // } while(next_permutation(all(v2)));

    map<string, int> M;
    M["a"] = 1;
    M["b"] = 2;
    M["c"] = 3;
    M["d"] = 4;
    debug(M.find("a")->second);
    debug((--M.find("b"))->first);
    vector< pair<string, int> > V(all(M));

    tr(it, V) {
        debug(it->first);
        debug(it->second);
    }

    return 0;
}