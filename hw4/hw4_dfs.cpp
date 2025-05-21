#include <bits/stdc++.h>
using namespace std;

const int MAX = 15;  // Maximum number of cities

int n;  // Number of cities
int cost[MAX][MAX];  // Cost matrix
vector<int> currentPath;  // Current path
vector<bool> visited(MAX, false);  // Visited cities
vector<int> shortestPath;  // Shortest path
int minCost = INT_MAX;  // Minimum cost

// Function to find the minimum cost Hamiltonian cycle
void tsp(int currCity, int visitedCount, int currCost)
{
    if (visitedCount == n && cost[currCity][0] != 100)  // All cities visited, return to starting city
    {
        currCost += cost[currCity][0];
        if (currCost < minCost)
        {
            minCost = currCost;
            shortestPath = currentPath;
        }
        return;
    }

    for (int nextCity = 0; nextCity < n; nextCity++)
    {
        if (!visited[nextCity] && cost[currCity][nextCity] != 100)
        {
            visited[nextCity] = true;
            currentPath.push_back(nextCity);

            tsp(nextCity, visitedCount + 1, currCost + cost[currCity][nextCity]);

            visited[nextCity] = false;
            currentPath.pop_back();
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

    // Start from city 0
    visited[0] = true;
    currentPath.push_back(0);
    double a = clock();
    tsp(0, 1, 0);
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
