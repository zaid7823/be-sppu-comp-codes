#include <bits/stdc++.h>
using namespace std;

class items {
    public:
        int profit;
        int weight;
        float ratio;
};

class knapsack {
    vector<items> sack;
    int noOfItems;

    float overallWeight;
    float finalValue;

    public:
    knapsack(int n) {
        sack.reserve(n);
        noOfItems = n;
    }
    // ===================
    void getData() {
        int p, w;
        cout << "Enter the capacity of the sack: ";
        cin >> overallWeight;
        finalValue = 0.0;

        for (int i = 0; i < noOfItems; i++) {
            cout << "\nItem " << i+1 << ":\n";
            cout << "Enter Profit: ";
            cin >> p;

            cout << "Enter Weight: ";
            cin >> w;

            sack.push_back({p, w, float(p / w)});
        }
    }
    // ===================
    float fillKnapsack() {
        getData();

        sort(sack.begin(), sack.end(), [](const items& a, const items& b) {
            return a.ratio > b.ratio;
        });

        for (items &i : sack) {
            if (overallWeight >= i.weight) {
                overallWeight = overallWeight - i.weight;
                finalValue += i.profit;
            }
            else {
                // overallWeight = 0;
                finalValue += i.profit * (overallWeight / i.weight);
                overallWeight = 0.0;
                break;
            }
        }
        return finalValue;
    }
};
// =======================
int main(int argc, char const *argv[]) {
    cout << "\n--- Fractional Knapsack ---\n\n";

    int n;
    cout << "Enter the no. of items: ";
    cin >> n;

    knapsack k(n);
    cout << "\nTotal profit: " << k.fillKnapsack(); 
    return 0;
}
