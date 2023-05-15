#include <iostream>
#include <string>
#include <cmath>
using namespace std;

#define POW(prime, i) static_cast<int>(pow(prime, i))

class RabinKarp {
private:
    const int DICT_SIZE = 26;
    int power = 0;
public:
    int search(string text, string pattern) {
        int n = text.size();
        int m = pattern.size();
        if(n < m) {
            throw "Text can't be smaller than pattern." ;
        }
        power = pow(DICT_SIZE, m-1);
        int pattern_hash = hash(pattern, m);

        int current_hash = hash(text, m);

        if(current_hash == pattern_hash) {
            return 0;
        }

        for(int i=m; i<n; i++) {
            current_hash = rehash(text, m, i, current_hash);
            if(current_hash == pattern_hash) {
                if(pattern == text.substr(i-m+1, m)) {
                    return i-m+1;
                }
            }
        }

        return -1;
    }

private:
    int hash(string s, int n) {
        int hash = 0;
        for(int i = 0; i<n; i++) {
            hash *= DICT_SIZE;
            hash += (s[i] - 'a');
        }
        return hash;
    }

    int rehash(string& s, int len, int i, int prevHash) {
        int hash = prevHash;
        hash -= power * (s[i-len] - 'a');
        hash *= DICT_SIZE;
        hash += (s[i] - 'a');
        return hash;
    }
};

class RabinKarpAlgorithm {
private:
    RabinKarp rk;

public:
    int search(string text, string pattern) {
        return rk.search(text, pattern);
    }
};

int main() {
    string text, pattern;
    cout << "Enter text: ";
    cin >> text;
    cout << "Enter pattern: ";
    cin >> pattern;

    RabinKarpAlgorithm rka;
    int index = rka.search(text, pattern);
    if(index == -1) {
        cout << "Pattern not found." << endl;
    }
    else {
        cout << "Pattern found at index " << index << "." << endl;
    }

    return 0;
}