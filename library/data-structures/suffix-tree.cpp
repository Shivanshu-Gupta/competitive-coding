#include "bits/stdc++.h"

using namespace std;

struct Node{
    int begin, end; // edgeLabel = s[begin:end) <=> end-begin == len(edgeLabel)
    Node *parent;
    Node *suffixLink;
    unordered_map<char, Node*> children;

    Node(int begin, int end, Node *suffixLink) {
        this.begin = begin;
        this.end = end;
        this.suffixLink = suffixLink;
    }
}

struct SuffixTree {
    Node* root;
    Node* full;
    SuffixTree() {
        root = new Node(0, 0, NULL, NULL);
    }

    void build(string s) {
        int n = s.length();
        if(n == 0) return;
        root->children[s[0]] = new Node(0, n, NULL, NULL);;
        full = root->children[s[0]];
        Node *node = root->children[s[0]];
        Node *last;
        int j0 = 0;
        for(int i = 1; i < s.length(); i++) {
            for(int j = 0; j <= i; j++) {
                if(j == 0) {
                    node = full;
                    // node->end++;
                } else if(j == 1) {
                    int leftover = node->end - node->begin;
                    if(node->parent != root) {
                        node = node->parent->suffixLink;
                    } else {
                        node = node->parent;
                    }
                    
                    Node *ch = node->children[a[i-leftover]];
                    while(ch != NULL && leftover >= 1 + ch->end - ch->begin) {
                        leftover -= ch->end - ch->begin;
                        node = ch;
                        ch = node->children[a[i-leftover]];
                    }

                    if(ch == NULL) {

 
                    }

                    if(ch == NULL) {
                        // RULE 2
                        Node *splitNode = new Node(node->begin, node->begin + leftover, node->parent);
                        splitNode->children[a[i+1]] = new Node(i+1, n-1, splitNode);
                        splitNode->children[a[node->begin + leftover + 1]] = node;
                        node->begin += leftover;
                        node->parent->children[a[i - leftover]] = splitNode;
                        node->parent = splitNode;
                        if(last != NULL) last->suffixLink = splitNode;
                        last = splitNode;
                    } else if(node->children.find(a[i+1]) == node->children.end()) {
                        // RULE 1 or 2 according as the node is a leaf or internal node.
                        node->children[a[i+1]] =  new Node(i+1, n-1, node);
                        if(last != NULL) last->suffixLink = node;
                        last = NULL;
                    } else {
                        // RULE 3
                    }
                } else {
                    int leftover;
                    if(node->suffixLink != NULL) {
                        leftover = 0;
                        node = node->suffixLink;
                    } else {
                        leftover = node->end - node->begin;
                        if(node->parent != root) {
                            node = node->parent->suffixLink;
                        } else {
                            node = node->parent;
                        }
                    }
                    // s[node->end - 1] == s[i - leftover]
                }
                int k = j, p = 0;
                while(p < curr->edgeLabel.length() && k < i) {
                    if(curr.edgeLabel[p] == s[j]) {
                        p++;
                        k++;
                    } else {
                        break;
                    }
                }
                if(p == curr->edgeLabel.length() && k == i) {
                    // RULE 1
                    curr->edgeLabel.concat(s[i+1]);
                } else if(p == curr->edgeLabel.length() && k < i) {
                    if(curr->children.find(s[k]) != curr->children.end()) {
                        curr = curr->children[s[k]];
                    } else {
                        // RULE 2
                        curr->children[s[k]] = new Node(s.substr(k, i+1), true, j, NULL);
                    }
                } else {
                    // RULE 2
                    Node splitNode(curr->edgeLabel.substr(p, curr->edgeLabel.length()), curr->isLeaf, curr->nodeLabel, curr->suffixLink);

                }

                while(k <= i && curr->edgeLabel[p] == s[j + k]) {
                    
                }
                for(int k = j; k <= i; k++) {

                }
            }
        }
    }
}