#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

// Partition function (Lomuto partition scheme)
int partition(vector<int>& A, int low, int high) {
    int pivot = A[high];
    int i = low;

    for (int j = low; j < high; ++j) {
        if (A[j] <= pivot) {
            swap(A[i], A[j]);
            ++i;
        }
    }
    swap(A[i], A[high]);
    return i;
}

// Randomized partitioning
int randomizedPartition(vector<int>& A, int low, int high) {
    int pivotIndex = low + rand() % (high - low + 1);
    swap(A[pivotIndex], A[high]);
    return partition(A, low, high);
}

// Randomized Select algorithm
int randomizedSelect(vector<int>& A, int low, int high, int i) {
    if (low == high)
        return A[low];

    int q = randomizedPartition(A, low, high);
    int k = q - low + 1;

    if (i == k)
        return A[q];
    else if (i < k)
        return randomizedSelect(A, low, q - 1, i);
    else
        return randomizedSelect(A, q + 1, high, i - k);
}

// Wrapper function
int findIthSmallest(vector<int>& A, int i) {
    srand(time(0));
    return randomizedSelect(A, 0, A.size() - 1, i);
}

// Main
int main() {
    int n, i;
    vector<int> A;

    cout << "Enter number of elements: ";
    cin >> n;

    cout << "Enter " << n << " elements:\n";
    A.resize(n);
    for (int j = 0; j < n; ++j) {
        cin >> A[j];
    }

    cout << "Enter i (to find the i-th smallest element, 1-based index): ";
    cin >> i;

    if (i < 1 || i > n) {
        cout << "Invalid input. i must be between 1 and " << n << "." << endl;
        return 1;
    }

    int result = findIthSmallest(A, i);
    cout << "The " << i << "-th smallest element is: " << result << endl;

    return 0;
}
