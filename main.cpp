#include <iostream>
#include <limits>
#include "AdjMatrix.h"
#include "miniVector.h"
#include <fstream>
#include <string>

using namespace std;

int findRoom(){
	ifstream roomList("roomListNumbered.txt");
	string userRoom, givenRoom;
	int roomIndex;
	cin >> userRoom;
	while(roomList >> roomIndex >> givenRoom){
		if(givenRoom == userRoom){
			return roomIndex;
		}
	}
	return -1;
}


int main(){
	int SIZE = 10;
	AdjMatrix matrix(SIZE);

	ifstream in("data.txt");
	int pStart, pEnd, pDistance;

	while (in >> pStart >> pEnd >> pDistance){
		matrix.SetDistance(pStart, pEnd, pDistance);
	}

	int distance[SIZE+1];
	int previous[SIZE];
	int explored[SIZE];
	intVector unexplored;

	for(int i = 0; i < SIZE; i++){
		distance[i] = numeric_limits<int>::max();
		previous[i] = -1;
	}
	distance[SIZE+1] = numeric_limits<int>::max();

	cout << "Enter Start Room: ";
	int start = findRoom();
	if(start == -1){ cout << "ERROR: Start room not found." << endl; return 1; }

	cout << "Enter End Room: ";
	int end = findRoom();
	if(end == -1){ cout << "ERROR: End room not found." << endl; return 1; }

	start--;
	previous[start] = start;
	distance[start] = 0;
	int edgeweight, altPathDistance;
	int size = 0;

	while(size < SIZE){
		int nextStart = SIZE-1;
		explored[size] = start;
		unexplored.RemoveInt(start);
		size++;
		int compareVal = numeric_limits<int>::max();
		for(int i = 0; i < SIZE; i++){

			int currDistance = matrix.GetDistance(start, i);
			if(currDistance < numeric_limits<int>::max()){
				edgeweight = currDistance;
				altPathDistance = distance[start] + edgeweight;
				bool isExplored = false;
				for(int j = 0; j < size; j++){
					if(explored[j] == i){
						isExplored = true;
					}
				}

				bool isUnexplored = false;
				if(!isExplored){
					for(int j = 0; j < unexplored.GetSize(); j++){

						if(unexplored[j] == i){
							isUnexplored = true;
						}
					}
				}

				if(!isExplored and !isUnexplored){
					unexplored.AddInt(i);
				}

				if(altPathDistance < distance[i]){
					distance[i] = altPathDistance;
					previous[i] = start;
				}

				for(int j = 0; j < unexplored.GetSize(); j++){
					for(int k = 0; k < size; k++){
						int newDistance = matrix.GetDistance(unexplored[j], explored[k]) + distance[explored[k]];
						if((newDistance < compareVal) and (newDistance > 0)){
							compareVal = newDistance;
							nextStart = unexplored[j];
						}
					}
				}
			}
		}
		start = nextStart;
	}

	int stack[SIZE];
	int stackIndex;
	string currRoom;

	for(int i = 0; i < SIZE; i++){
		if(i+1 != end) { continue; }

		start = i;
		int a = 1+i;
		int roomIndex = 1;
		ifstream roomList("roomListNumbered.txt");
		while((roomList >> roomIndex >> currRoom) and (roomIndex != a)){}

		cout << currRoom << " distance = ";

		if( distance[i] == numeric_limits<int>::max() ){
			cout << "ERROR: Cannot be reached.";
		} else {
			cout << distance[i] << " | Path = ";

			stackIndex = 0;
			stack[stackIndex] = start;
			stackIndex++;
			while(distance[start] != 0){
				start = previous[start];
				stack[stackIndex] = start;
				stackIndex++;
			}


			for(int j = stackIndex-1; j > -1; j--){
				ifstream roomList("roomListNumbered.txt");
				while((roomList >> roomIndex >> currRoom) and (roomIndex != stack[j]+1)){}

				cout << currRoom;

				if(j != 0){
					cout << " ";
				}
			}
		}
		cout << endl;
	}
	return 0;
}
