#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;

void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

int partitionDeterministic(vector<int> &arr, int low, int high) {
    int pivot = arr[high];  // choose the last element as pivot
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

int partitionRandomized(vector<int> &arr, int low, int high) {
    // Pick a random pivot index between low and high
    int randomPivotIndex = low + rand() % (high - low + 1);
    swap(arr[randomPivotIndex], arr[high]);  // Move random pivot to end
    return partitionDeterministic(arr, low, high);
}

void quickSortDeterministic(vector<int> &arr, int low, int high) {
    if (low < high) {
        int pivotIndex = partitionDeterministic(arr, low, high);
        quickSortDeterministic(arr, low, pivotIndex - 1);
        quickSortDeterministic(arr, pivotIndex + 1, high);
    }
}

// Randomized Quick Sort function
void quickSortRandomized(vector<int> &arr, int low, int high) {
    if (low < high) {
        int pivotIndex = partitionRandomized(arr, low, high);
        quickSortRandomized(arr, low, pivotIndex - 1);
        quickSortRandomized(arr, pivotIndex + 1, high);
    }
}

// Helper function to print array
void printArray(const vector<int> &arr) {
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;
}

int main() {
    srand(time(0));  // Seed for random number generator

    vector<int> arr = {10, 7, 8, 9, 1, 5};
    int n = arr.size();

    vector<int> arrDet = arr;
    cout << "Deterministic Quick Sort:\n";
    quickSortDeterministic(arrDet, 0, n - 1);
    printArray(arrDet);

    vector<int> arrRand = arr;
    cout << "Randomized Quick Sort:\n";
    quickSortRandomized(arrRand, 0, n - 1);
    printArray(arrRand);

    return 0;
}
