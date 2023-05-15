/***
 * Implement Suffix tree using Ukkonen's algorithm
 *
 */
#include <iostream>
#include <vector>
using namespace std;
class TrieNode {
public:
    TrieNode *children[27];
    int st, *en = nullptr;
    int constEn = -1;
    TrieNode *parent, *suffixLink;
    bool isLeaf;
    TrieNode() {
        for (int i = 0; i < 27; i++) {
            children[i] = nullptr;
        }
        st = -1;
        en = &constEn;
        parent = suffixLink = nullptr;
        isLeaf = false;
    }
};

class SuffixTree{
    string s;
    int n;
    TrieNode *root;
    TrieNode *lastInternal;

public:
    SuffixTree(string &_s) {
        this->s = _s + "$";
        this->n = this->s.size();
        root = new TrieNode();
        root->suffixLink = root;
        lastInternal = root;
        int i = 0;
        for (i = 0; i < n; i++) {
            // for each phase
            phase(i); // phase i
        }
        // correct for sanity's sake
        i = n - 1;
    }

    int getIdx(char &c) {
        if (c == '$')
            return 26;
        else
            return c - 'a';
    }

    void phase(int &p) {
        lastInternal = root;
        TrieNode *curr = root;
        for (int i = 0; i <= p; i++) {
            // insert s[i..p]
            int j = i;
            while (j <= p && curr) {
                int k = curr->st;
                while (j <= p && k <= *(curr->en)) {
                    if (k == -1) {
                        // k++;
                        break;
                    }
                    if (s[j] == s[k]) {
                        j++;
                        k++;
                    } else {
                        // split, rule 2
                        // new internal node
                        TrieNode *newNode = new TrieNode();
                        newNode->st = curr->st;
                        newNode->constEn = k - 1;
                        newNode->en = &(newNode->constEn);
                        newNode->parent = curr->parent;
                        curr->parent = newNode;
                        curr->st = k;
                        newNode->children[getIdx(s[k])] = curr;
                        if (newNode->parent) {
                            newNode->parent->children[getIdx(s[newNode->st])] = newNode;
                        }
                        if (lastInternal != root)
                            lastInternal->suffixLink = newNode; // invert
                        newNode->suffixLink = root;
                        lastInternal = newNode;
                        curr = newNode;
                    }
                }
                if (j == p + 1) {
                    if (k <= *(curr->en)) {
                        // rule 3
                        // end this phase now
                        return;
                    } // rule 1
                    // extension ends
                    curr = curr->parent->suffixLink;
                } else {
                    if (!curr->children[getIdx(s[j])]) {
                        TrieNode *newLeaf = new TrieNode();
                        newLeaf->st = j;
                        newLeaf->en = &p;
                        newLeaf->parent = curr;
                        newLeaf->isLeaf = true;
                        curr->children[getIdx(s[j])] = newLeaf;
                    }
                    curr = curr->children[getIdx(s[j])];
                }
            }
        }
    }

    bool search(string &pat) {
        int pn = pat.size();
        int i = 0, j;
        TrieNode *curr = root;
        while (i < pn && curr) {
            j = curr->st;
            while (i < pn && j >= 0 && j <= *curr->en) {
                if (pat[i] == s[j]) {
                    i++;
                    j++;
                } else {
                    return false;
                }
            }
            if (i == pn)
                return true;
            curr = curr->children[getIdx(pat[i])];
        }
        return false;
    }
};

int main() {
    string text = "iamawesomedeveloper";
    cout << "text is \"" << text << '"' << endl;
    SuffixTree st(text);
    vector<string> cases = {"developer", "awesome", "iam", "dev", "awesomedeveloper",
                            "iamawesome", "iamawesomedeveloper", "eve", "pro", "xyz"};

    for (string &s : cases) {
        cout << '"' << s << '"' << " " << (st.search(s) ? "found" : "not found") << endl;
    }
    cout << "done" << endl;
}