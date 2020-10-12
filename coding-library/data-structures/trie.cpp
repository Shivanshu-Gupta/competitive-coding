/*
Implementation of Trie.
- Trie can store information about keys/numbers/strings compactly in a tree. Tries consists of nodes, where each node stores a character/bit.
- Tree based Recursive implementation
- Can implement as a flattened array if the number of children per node is fixed like when storing numbers. (eg. xor-key.cpp).
    - In this case can also make it non-recursively.

Good Tutorial: https://threads-iiith.quora.com/Tutorial-on-Trie-and-example-problems

Sample Problems:
-   Hackerrank  -   xor-key
-   Spoj        -   SUBXOR (good question)
*/

#include "bits/stdc++.h"

using namespace std;

struct Trie {
    int wordFreq = 0; // number of times this word inserted
    int prefixFreq = 0; // number of words with this as prefix.
    unordered_map<char, Trie *> children; // children - may use an array if alphabet is known beforehand.

    // Insert string w[begin:) into the trie
    void insert(string &w, int begin) {
        prefixFreq++;
        if(begin == w.length()) {
            // string end reached - increment it's freq.
            wordFreq++;
        } else {
            // string end not reached - continue
            char c = w[begin];
            if(children.find(c) == children.end()) {
                Trie *t = new Trie;
                children[c] = t;
            }
            children[c]->insert(w, ++begin);
        }
    }

    // Count the number of times the string w[begin:) was inserted
    int getWordFreq(string &w, int begin) {
        if(begin == w.length()) {
            // string found
            return wordFreq;
        } else {
            char c = w[begin];
            
            if(children.find(c) == children.end()) {
                // string never inserted
                return 0;
            } else {
                // continue to next letter
                return children[c]->getWordFreq(w, ++begin);
            }
        }
    }

    // Count the number of times a word with string w[begin:) as prefix was inserted
    int getPrefixFreq(string &w, int begin) {
        if(begin == w.length()) {
            // string found
            return prefixFreq;
        } else {
            char c = w[begin];
            if(children.find(c) == children.end()) {
                // no word with the string as prefix inserted
                return 0;
            } else {
                // continue to the next letter.
                return children[c]->getPrefixFreq(w, ++begin);
            }
        }
    }
};


void trieTest() {
    Trie trie;
    string s;
    cin>>s;
    for(int i = 0; i < s.length(); i++) {
        trie.insert(s, i);
    }
    string p;
    cin>>p;
    cout<<trie.getPrefixFreq(p, 0)<<endl;
}