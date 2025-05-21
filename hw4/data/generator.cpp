#include <bits/stdc++.h>
using namespace std;

const int MIN_COST = 1;
const int MAX_COST = 99;
const int DIAGONAL_COST = 100;

int getRandomNumber(int min, int max){
	return min + rand() % (max - min + 1);
}

void generateMatrixFile(int n){
	string filename = to_string(n) + ".txt";
	ofstream file(filename);

	if(!file.is_open()){
		cout << "Failed to open file: " << filename << endl;
		return;
	}

	file << n << "\n";

	vector<vector<int>> matrix(n, vector<int>(n));
	srand(time(nullptr));

	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			if(i == j){
				matrix[i][j] = DIAGONAL_COST;
			}else{
				matrix[i][j] = getRandomNumber(MIN_COST, MAX_COST);
			}
			file << matrix[i][j] << " ";
		}
		file << "\n";
	}
	
	file.close();
	cout << "Generated file: " << filename << endl;
}

int main(){
	for(int n = 7; n <= 15; n++){
		generateMatrixFile(n);
	}

	return 0;
}
