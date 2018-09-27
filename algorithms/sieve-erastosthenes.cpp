/*
Implemetation of Sieve of Erastosthenes for getting primes less than N.

Input: an integer n > 1

    Let A be an array of Boolean values, indexed by integers 2 to n,
    initially all set to true.

    for i = 2, 3, 4, ..., not exceeding √n:
        if A[i] is true:
            for j = i^2, i^2+i, i^2+2i, i^2+3i, ..., not exceeding n :
              A[j] := false

Output: all i such that A[i] is true.
Time Complexity:  O(n log log n)
*/

#include <cstring>
#include <cmath>
#include <iostream>
#include <vector>
#include <bitset>
using namespace std;

const int MAX = 1000000000;
bitset<MAX> prime;

void Sieve(int n, vector<int> &primes) {
    if(n < 2) return;
    
    prime.flip();

    prime[0] = false;
    prime[1] = false;

    // Apply Sieve of Erastosthenes
    int imax = sqrt(n) + 1;
    for(int i = 2; i < imax; i++) {
        if(prime[i]) {
            int j = i*i;
            while(j <= n) {
                prime[j] = false;
                j += i;
            }
        }
    }

    for(int i = 2; i <= n; i++) {
        if(prime[i]) primes.push_back(i);
    }
}

void sieveErastosthenesTest() {
    int n;
    cin>>n;
    vector<int> primes;
    Sieve(n, primes);
    for(int p : primes) {
        cout<<p<<',';
    }
}


