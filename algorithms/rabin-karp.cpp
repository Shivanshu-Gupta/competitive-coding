/*
Implementation of Rabin Karp Algorithm using Rollong Hash Technique.

Searches for the string w in the string s (of length k). Returns the
0-based index of the first match (k if no match is found). 

Refernce: https://www.topcoder.com/community/data-science/data-science-tutorials/introduction-to-string-searching-algorithms/
*/

/*
Hash:
If s is a string from alphabet A of size |A|, then we can find hash of s as:
    hash(s) = (s[0] * B^(m – 1) + ... + s[m - 1] * B^0) % M, 
where, 
    B = base of the numeral system (a prime num > |A|),
    M = a large enough prime number.

Rolling Hash Technique:
If  H0 = hash(s[0:k]) = (s[0] * B^(k - 1) + ... + s[k - 1] * B^0) % M
and H1 = hash(s[1:k+1]) = (s[1] * B^(k - 1) + ... + s[k] * B^0) % M,
then, H1 = (H0 - s[0] * B^(k - 1)) * B + s[k]

We use double hashing to decrease the probability of collision.
*/
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <utility>

using namespace std;

// correctly calculates a mod b even if a < 0
#define mod(a, b) (((a) % (b) + (b)) % (b))

// choose large enough primes M.
#define M1 1000003
#define M2 1000033

// Alphabet mapped to its index.
unordered_map<char, int> A;
int n_alpha = 0;

// B and its powers modulo M. (choose a prime B s.t. B > |A|)
int B = 257, expB1[1000000], expB2[1000000];

void getExpB(int n) {
    expB1[0] = 1;
    expB2[0] = 1;
    for(int i = 1; i < n; i++) {
        expB1[i] = (B * expB1[i - 1]) % M1;
        expB2[i] = (B * expB2[i - 1]) % M2;
    }
}

int Rabin_Karp(string &s, string &w){
    int n = s.length(), m = w.length();
    if(n < m) return n; // no match is possible

    // calculate the hash value of the pattern w
    int hp1 = 0, hp2 = 0;
    for(int i = 0; i < m; i++) {
        hp1 = mod(hp1 * B + A[w[i]], M1);
        hp2 = mod(hp2 * B + A[w[i]], M2);
    }
    // calculate the hash value of the 1st m-length segment of s
    int ht1 = 0, ht2 = 0;
    for(int i = 0; i < m; i++) {
        ht1 = mod(ht1 * B + A[s[i]], M1);
        ht2 = mod(ht2 * B + A[s[i]], M2);
    }
    
    int i = 0, j;
    while(i + m <= n) {
        if(ht1 == hp1 && ht1 == hp2) {
            // check char by char if the both hashes of current segment match
            for(j = 0; j < m; j++) { if(s[i + j] != w[j]) break; }
            if(j == m) {
                // Match Found
                return i;
            }
        } 
        if(i) {
            // calculate hash of next segment (rolling hash)
            ht1 = mod(ht1 - mod(A[s[i]] * expB1[m - 1], M1), M1);
            ht1 = mod(ht1 * B, M1);
            ht1 = mod(ht1 + A[s[i + m]], M1);

            ht2 = mod(ht2 - mod(A[s[i]] * expB1[m - 1], M2), M2);
            ht2 = mod(ht2 * B, M2);
            ht2 = mod(ht2 + A[s[i + m]], M2);
        }
        i++;
    }
    return n;
}

void rabinKarpTest()
{
    string s, w;
    cin>>s>>w;
    for(char c : s) {
        if(A.find(c) != A.end()) {
            A.insert(make_pair(c, n_alpha++));
        }
    }
    for(char c : w) {
        if(A.find(c) != A.end()) {
            // If there's a char in w not in s then w can't be a substr of s.
            // cout<<"Not Found\n";
            A.insert(make_pair(c, n_alpha++));
        }
    }

    getExpB(s.length());

    int pos = Rabin_Karp(s, w);
    cout<<pos<<' '<<s.substr(pos, w.length())<<'='<<w<<endl;
}
