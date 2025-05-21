#include <bits/stdc++.h>
using namespace std;

const int MAX = 15;  // Maximum number of cities

int n;  // Number of cities
int cost[MAX][MAX];  // Cost matrix
vector<int> shortestPath;  // Shortest path
int minCost = INT_MAX;  // Minimum cost

struct Node {
    int city;
    int level;
    int cost;
    vector<bool> visited;
    vector<int> path;
    int mask;

    Node(int c, int l, int ct, const vector<bool>& v, const vector<int>& p, int m)
        : city(c), level(l), cost(ct), visited(v), path(p), mask(m) {}

    // Compare nodes based on their cost
    bool operator<(const Node& other) const {
        return cost > other.cost;
    }
};

int calculateLowerBoundDP(int mask, int lastCity)
{
    static vector<vector<int>> dp(1 << MAX, vector<int>(MAX, -1));

    if (dp[mask][lastCity] != -1)
        return dp[mask][lastCity];

    if (mask == (1 << n) - 1)
        return dp[mask][lastCity] = cost[lastCity][0];

    int ans = INT_MAX;
    for (int nextCity = 0; nextCity < n; nextCity++)
    {
        if ((mask & (1 << nextCity)) == 0)
        {
            int newMask = mask | (1 << nextCity);
            int newCost = cost[lastCity][nextCity] + calculateLowerBoundDP(newMask, nextCity);
            ans = min(ans, newCost);
        }
    }

    return dp[mask][lastCity] = ans;
}

void tsp()
{
    priority_queue<Node> pq;

    // Start from city 0
    vector<bool> visited(n, false);
    visited[0] = true;
    vector<int> currentPath;
    currentPath.push_back(0);
    int mask = 1;  // Set the first bit for the starting city

    // Initialize the priority queue with the starting node
    pq.emplace(0, 1, 0, visited, currentPath, mask);

    while (!pq.empty())
    {
        Node node = pq.top();
        pq.pop();

        int currCity = node.city;
        int level = node.level;
        int currCost = node.cost;
        vector<bool> visited = node.visited;
        vector<int> path = node.path;
        int mask = node.mask;

        if (level == n && cost[currCity][0] != 100)
        {
            currCost += cost[currCity][0];
            if (currCost < minCost)
            {
                minCost = currCost;
                shortestPath = path;
            }
            continue;
        }

        for (int nextCity = 0; nextCity < n; nextCity++)
        {
            if (!visited[nextCity] && cost[currCity][nextCity] != 100)
            {
                visited[nextCity] = true;
                path.push_back(nextCity);

                int lowerBound = currCost + calculateLowerBoundDP(mask | (1 << nextCity), nextCity);

                if (lowerBound < minCost)
                {
                    pq.emplace(nextCity, level + 1, currCost + cost[currCity][nextCity], visited, path, mask | (1 << nextCity));
                }

                visited[nextCity] = false;
                path.pop_back();
            }
        }
    }
}

int main()
{
    cin >> n;

    // Read cost matrix
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> cost[i][j];
        }
    }
    double a = clock();
    tsp();
    double b = clock();
    // Print shortest Hamiltonian cycle path and total cost
    cout << "The shortest Hamiltonian cycle:\n";
    for (int i = 0; i < shortestPath.size(); i++)
    {
        cout << shortestPath[i] + 1 << " ";
    }
    cout << shortestPath[0] + 1 << endl;

    cout << "Total cost: " << minCost << endl;
    cout << "Time : " << fixed << setprecision(6) << ((b-a)/CLOCKS_PER_SEC) << "\n";
    return 0;
}
