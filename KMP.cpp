#include <iostream>
#include <vector>
using namespace std;

// Function to compute the Longest Prefix Suffix (LPS) array
void computeLPSArray(const string& pattern, vector<int>& lps) {
    int m = pattern.length();
    int len = 0; // length of the previous longest prefix suffix
    lps[0] = 0;  // lps[0] is always 0

    int i = 1;
    while (i < m) {
        if (pattern[i] == pattern[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

// KMP search function
void KMPSearch(const string& pattern, const string& text) {
    int n = text.length();
    int m = pattern.length();

    vector<int> lps(m);
    computeLPSArray(pattern, lps);

    int i = 0; // index for text[]
    int j = 0; // index for pattern[]
    while (i < n) {
        if (pattern[j] == text[i]) {
            i++;
            j++;
        }

        if (j == m) {
            cout << "Pattern found at index " << (i - j) << endl;
            j = lps[j - 1];
        }
        // mismatch after j matches
        else if (i < n && pattern[j] != text[i]) {
            if (j != 0)
                j = lps[j - 1];
            else
                i++;
        }
    }
}

// Driver code
int main() {
    string text = "ABABDABACDABABCABAB";
    string pattern = "ABABCABAB";

    KMPSearch(pattern, text);

    return 0;
}
#include <iostream>
#include <vector>
using namespace std;

// Function to compute the Longest Prefix Suffix (LPS) array
void computeLPSArray(const string& pattern, vector<int>& lps) {
    int m = pattern.length();
    int len = 0; // length of the previous longest prefix suffix
    lps[0] = 0;  // lps[0] is always 0

    int i = 1;
    while (i < m) {
        if (pattern[i] == pattern[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

// KMP search function
void KMPSearch(const string& pattern, const string& text) {
    int n = text.length();
    int m = pattern.length();

    vector<int> lps(m);
    computeLPSArray(pattern, lps);

    int i = 0; // index for text[]
    int j = 0; // index for pattern[]
    while (i < n) {
        if (pattern[j] == text[i]) {
            i++;
            j++;
        }

        if (j == m) {
            cout << "Pattern found at index " << (i - j) << endl;
            j = lps[j - 1];
        }
        // mismatch after j matches
        else if (i < n && pattern[j] != text[i]) {
            if (j != 0)
                j = lps[j - 1];
            else
                i++;
        }
    }
}


int main() {
    string text = "ABABDABACDABABCABAB";
    string pattern = "ABABCABAB";

    KMPSearch(pattern, text);

    return 0;
}
