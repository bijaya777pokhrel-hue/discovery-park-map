#include "miniVector.h"
#include <iostream>

void intVector::AddInt(int newInt){
	size++;
	AdjustSize();
	vec[size-1] = newInt;
}

void intVector::PrintVals(){
	for(int i = 0; i < size; i++){
		cout << vec[i];
		if(i < size-1){
			cout << ", ";
		}
	}
	cout << endl;
}

void intVector::AdjustSize(){
	if(size >= max){
		max+=10;
		int* newvec = new int[max];
		for(int i = 0; i < size; i++){
			newvec[i] = vec[i];
		}
		delete[] vec;
		vec = newvec;
	}
}

void intVector::RemoveIntAt(int address){
	for(int i = address; i < size; i++){
		vec[i] = vec[i+1];
	}
	size--;
}

void intVector::RemoveInt(int number){
	if(size > 0){
		bool remove = false;
		for(int i = 0; i < size; i++){
			if(vec[i] == number){
				remove = true;
			}
			if(remove){
				vec[i] = vec[i+1];
			}
		}
		size--;
	}
}

int& intVector::operator[](int address){
	return vec[address];
}

int intVector::GetSize(){
	return size;
}
