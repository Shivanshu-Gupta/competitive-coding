/*
    Finding rank of an element in the sorted array.
*/

#include "bits/stdc++.h"

using namespace std;

bool cmp(const pair<int, int> p1, pair<int, int> p2) {
    return p1.first < p2.first;
}

void sortingTest() {
    int A[6] = {5, 7, 4, 2, 3, 8};
    int idx[6], rank[6];
    
    vector<pair<int, int>> temp;
    for(int i = 0; i < 6; i++) temp.push_back(pair<int, int>(A[i], i));

    sort(temp.begin(), temp.end(), cmp);
    for(int i = 0; i < 6; i++) {
        idx[i] = temp[i].second;
        rank[idx[i]] = i;
    }
    for(int i = 0; i < 6; i++) {
        cout<<A[i]<<'\t'<<rank[i]<<endl;
    }

}