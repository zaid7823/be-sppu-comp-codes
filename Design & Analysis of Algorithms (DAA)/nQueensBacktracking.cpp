#include <bits/stdc++.h>
using namespace std;

void printSolution(const vector<vector<int>>& board) {
    int N = board.size();
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (board[i][j]) cout << "Q ";
            else cout << ". ";
        }
        cout << "\n";
    }
    cout << "\n";
}
// =====================================
bool isSafe(const vector<vector<int>>& board, int row, int col) {
    int N  = board.size();

    // Check the row on the left side
    for (int i = 0; i < col; i++) {
        if (board[row][i]) return false;
    }

    // Check upper left diagonal from the position
    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--) {
        if (board[i][j]) return false;
    }

    // Check lower left diagonal from the position
    for (int i = row, j = col; i < N && j >= 0; i++, j--) {
        if (board[i][j]) return false;
    }

    return true;
}
// =====================================
bool solveNQueens(vector<vector<int>>& board, int col) {
    int N = board.size();
    if (col >= N) { // Print the board if all queens are placed
        printSolution(board);
        return true;
    }
    // Backtracking
    bool hasSolution = false;

    // For every row of given column
    for (int i = 0; i < N; i++) {
        if (isSafe(board, i, col)) {
            board[i][col] = 1;  // Place Queen
            hasSolution = solveNQueens(board, col + 1) || hasSolution; // Recur to place next queen
            board[i][col] = 0;  // remove the queen
        }
    }
    return hasSolution;
}
// =====================================
int main(int argc, char const *argv[]) {
    int n;
    cout << "Enter the size of the board(N): ";
    cin >> n;

    vector<vector<int>>board(n, vector<int>(n, 0));

    if (!solveNQueens(board, 0)) {
        cout << "No soution exists for " << n << " queens\n";
    } 
    else {
        cout << "All solutions found!" << endl;
    }
    return 0;
}
