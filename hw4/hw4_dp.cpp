#include <bits/stdc++.h>

using namespace std;

const int INF = INT_MAX;

int tsp(int n, vector<vector<int>>& cost, vector<vector<int>>& dp, vector<vector<int>>& prev) {
    dp[0][1] = 0;
    
    for (int mask = 1; mask < (1 << n); mask++) {
        for (int i = 0; i < n; i++) {
            if ((mask & (1 << i)) == 0)
                continue;
            
            for (int j = 0; j < n; j++) {
                if (i == j || (mask & (1 << j)) == 0 || dp[j][mask ^ (1 << i)] == INF)
                    continue;
                
                if (dp[i][mask] > cost[j][i] + dp[j][mask ^ (1 << i)]) {
                    dp[i][mask] = cost[j][i] + dp[j][mask ^ (1 << i)];
                    prev[i][mask] = j;
                }
            }
        }
    }
    
    int minCost = INF;
    int lastCity = -1;
    for (int i = 1; i < n; i++) {
        if (cost[i][0] != INF && dp[i][(1 << n) - 1] != INF) {
            if (minCost > cost[i][0] + dp[i][(1 << n) - 1]) {
                minCost = cost[i][0] + dp[i][(1 << n) - 1];
                lastCity = i;
            }
        }
    }
    
    // Reconstruct the path
    vector<int> path;
    int mask = (1 << n) - 1;
    while (lastCity != -1) {
        path.push_back(lastCity);
        int prevCity = prev[lastCity][mask];
        mask ^= (1 << lastCity);
        lastCity = prevCity;
    }
    reverse(path.begin(), path.end());
    
    // Output the shortest Hamiltonian cycle path
    cout << "Shortest Hamiltonian cycle path: ";
    for (int city : path) {
        cout << city + 1 << " ";
    }
    cout << "1" << endl;
    
    return minCost;
}

int main() {
    int n;
    cin >> n;
    
    vector<vector<int>> cost(n, vector<int>(n));
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> cost[i][j];
        }
    }
    
    vector<vector<int>> dp(n, vector<int>(1 << n, INF));
    vector<vector<int>> prev(n, vector<int>(1 << n, -1));
    double a = clock();
    int minCost = tsp(n, cost, dp, prev);
    double b = clock();
    cout << "Total cost: " << minCost << endl;
    cout << "Time : " << fixed << setprecision(6) << ((b-a)/CLOCKS_PER_SEC) << "\n";
    return 0;
}
