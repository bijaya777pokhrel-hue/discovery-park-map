#include "AdjMatrix.h"
#include <iostream>
#include <limits>

using namespace std;

AdjMatrix::AdjMatrix(int inSize){
	size = inSize;
	listList = new int*[size];
	for(int i = 0; i < size; i++){
		listList[i] = new int[size];
		for(int j = 0; j < size; j++){
			listList[i][j] = numeric_limits<int>::max();
		}
	}
}

AdjMatrix::~AdjMatrix(){
	for(int i = 0; i < size; i++){
		delete[] listList[i];
	}
	delete[] listList;
}

void AdjMatrix::SetDistance(int head, int tail, int distance){
	listList[head][tail] = distance;
	listList[tail][head] = distance;
}

int AdjMatrix::GetDistance(int head, int tail){
	return listList[head][tail];
}

void AdjMatrix::PrintMatrix(){
	cout << "   ";
	char outChar = 'a';
	for(int i = 0; i < size; i++){
		cout <<"  " << outChar << "  ";
		outChar++;
	}
	cout << endl;
	outChar = 'a';
	for(int i = 0; i < size; i++){
		cout << outChar << "  ";
		outChar++;
		for(int j = 0; j < size; j++){
			if(listList[i][j] != numeric_limits<int>::max()){
				if(listList[i][j] < 10){
					cout << "  " << listList[i][j] << "  ";
				}
				else if(listList[i][j] < 100){
					cout << "  " << listList[i][j] << " ";
				}
				else {
					cout << " " << listList[i][j] << " ";
				}
			}
			else {
				cout << " inf ";
			}
		}
		cout << endl;
	}
}
