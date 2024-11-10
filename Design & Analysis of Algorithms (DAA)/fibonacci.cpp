#include <bits/stdc++.h>
using namespace std;

// Memoization array
vector<int> memo(100, -1); // Assuming we won't calculate fib(n) for n > 99

// Memoized recursive Fibonacci function
int fibMemo(int n) {
    if (n <= 1) return n;
    // Check if value is already computed
    if (memo[n] != -1) return memo[n];
    // Compute and store the value
    memo[n] = fibMemo(n - 1) + fibMemo(n - 2);
    
    return memo[n];
}
// ===============================
int fibRec(int n) {
    if (n <= 1) return n;
    return fibRec(n - 1) + fibRec(n - 2);
}
// ===============================
int fibNonRec(int n) {
    int a = 0, b = 1, c;
    if (n == 0) return 0;
    if (n == 1) return 1;
    for (int i = 2; i <= n; i++) {
        c = a + b;
        a = b;
        b = c;
    }
    return b;
}
// ===============================
int main(int argc, char const *argv[]) {
    cout << "-- Fibonacci Series --\n\n";
    int n;
  
    cout << "Enter the nth number: ";
    cin >> n;

    cout << "\nRecursive:\n" << n << "th Fibonacci Number: " << fibRec(n);
  
    cout << "\n\nNon-Recursive:\n" << n << << "th Fibonacci Number: " << fibNonRec(n);

    cout << "\n\nMemoized Fibonacci:\n" << fibMemo(n);

    return 0;
}
