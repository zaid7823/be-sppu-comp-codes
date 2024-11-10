#include <bits/stdc++.h>
using namespace std;

void printDPTable(vector<vector<int>>& dp, int items, int capacity) {
	cout << "i/w";
	int m = 0;
	if (capacity > 10) m = capacity - 5;

	for (int w = m; w <= capacity; w++) {
		cout << "\t" << w;
	}
	cout << "\n\n";
	for (int i = 0; i <= items; i++) {
		cout << i;

		for (int w = m; w <= capacity; w++) {
			cout << "\t" << dp[i][w];
		}
		cout << "\n\n";
	}
}

int knapsack(int items, int capacity, vector<int>& profits, vector<int>& weights) {

	// 1. Create the DP table & populate with ZEROs
	vector<vector<int>> dp(items + 1, vector<int>(capacity + 1,0));

	// 2. Run the DP logic
	for (int i = 1; i <= items; i++) {
		for (int w = 1; w <= capacity; w++) {
			if (weights[i - 1] <= w) {	// If item can fit into the current weight of the backpack

				// Inclusion: Add current item profit + profit from the remaining weight
				int inclusion = profits[i - 1] + dp[i - 1][w - weights[i - 1]];
				// Exclusion: Add last item's profit
				int exclusion = dp[i - 1][w];
				// Find which one is bigger
				dp[i][w] = max(inclusion, exclusion);
			}
			else {	// If not enough capacity to fit entire item
				// put last item profit as current item profit
				dp[i][w] = dp[i - 1][w];
			}
		}
	}
	printDPTable(dp, items, capacity);
	return dp[items][capacity];
}

//  ====================================
int main(int argc, char const *argv[]) {
	cout << "--- 0/1 Knapsack Problem\n\n";

	int items, capacity;

	cout << "Enter the no. of items: ";
	cin >> items;

	cout << "Enter the knapsack capacity: ";
	cin >> capacity;

	vector<int> profits(items, 0);
	vector<int> weights(items, 0);

	for (int i = 0; i < items; i++) {
		cout << "\nItem " << i+1 << ":\n";
		cout << "Enter Profit: ";
		cin >> profits[i];
		
		cout << "Enter Weight: ";
		cin >> weights[i];
	}

	int maxProfit = knapsack(items, capacity, profits, weights);
	cout  << "\nMax Profit = " << maxProfit << endl;

	return 0;
}
