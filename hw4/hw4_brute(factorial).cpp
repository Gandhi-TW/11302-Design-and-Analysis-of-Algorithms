#include<bits/stdc++.h>
using namespace std;

const int INF = 1e9;

int calculateCost(const vector<vector<int>>& graph, const vector<int>& path) {
	int cost = 0;
	int n = graph.size();
	for (int i = 0; i < n - 1; ++i) {
		int src = path[i];
		int dest = path[i + 1];
		cost += graph[src][dest];
	}
	
	int start = path[0];
	int end = path[n - 1];
	cost += graph[end][start];
	return cost;
}
pair<vector<int>, int> tspBruteForce(const vector<vector<int>>& graph){
	int n = graph.size();
	vector<int> path(n);
	for(int i = 0; i < n; ++i){
		path[i] = i;
	}

	int minCost = INF;
	vector<int> minPath;

	do{
		int cost = calculateCost(graph, path);
		if(cost < minCost){
			minCost = cost;
			minPath = path;
		}
	}while(next_permutation(path.begin() + 1, path.end()));

	return make_pair(minPath, minCost);
}

int main(){
	int n;
	cin.tie(0)->sync_with_stdio(0);
	cin >> n;

	vector<vector<int>> graph(n, vector<int>(n));
	for(int i = 0; i < n; ++i){
		for(int j = 0; j < n; ++j){
			cin >> graph[i][j];
		}
	}
	double a = clock();
	pair<vector<int>, int> result = tspBruteForce(graph);
	vector<int> minPath = result.first;
	int minCost = result.second;
	double b = clock();
	cout << "Shortest Hamiltonian cycle: ";
	for (int i = 0; i < minPath.size(); ++i) {
		cout << minPath[i] + 1<< " ";
	}
	cout << minPath[0] + 1 << "\n";
	cout << "Total cost: " << minCost << "\n";
	cout << "Time : " << fixed << setprecision(6) << ((b-a)/CLOCKS_PER_SEC) << "\n";
	return 0;
}
