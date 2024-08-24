#include <vector>
#include <string>
using namespace std;

/**
 * @brief Computes the Z-array for a given string.
 * 
 * The Z-array for a string S is an array where the i-th entry is the length of the longest substring 
 * starting from S[i] that is also a prefix of S. This is useful for string matching and various other 
 * string-related problems.
 * 
 * @param S The input string for which the Z-array is to be computed.
 * @return vector<int> The Z-array corresponding to the input string.
 */
vector<int> computeZ(const string& S) {
    int n = S.length();  // Length of the input string
    vector<int> Z(n);    // Z-array to store the result
    int L = 0, R = 0;    // Left and right pointers for the current Z-box

    // Iterate over the string to compute Z-values
    for (int i = 1; i < n; i++) {
        if (i > R) {
            // Case 1: i is outside the current Z-box, so we need to reset L and R
            L = R = i;
            // Match characters between S[R] and S[R-L]
            while (R < n && S[R] == S[R - L])
                R++;
            Z[i] = R - L;  // Length of the match
            R--;           // Adjust R to the last matching position
        } else {
            // Case 2: i is within the current Z-box
            int K = i - L;  // Corresponding position in the prefix that matches S[i]
            if (Z[K] < R - i + 1) {
                // Case 2a: Z[K] does not stretch beyond the Z-box, so just copy Z[K]
                Z[i] = Z[K];
            } else {
                // Case 2b: Z[K] stretches beyond the Z-box, so we need to extend the match
                L = i;
                while (R < n && S[R] == S[R - L])
                    R++;
                Z[i] = R - L;  // Length of the match
                R--;           // Adjust R to the last matching position
            }
        }
    }
    return Z;
}
