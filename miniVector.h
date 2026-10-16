#ifndef MINIVECTOR_H
#define MINIVECTOR_H
#include <iostream>

using namespace std;

class intVector {
	public:
		intVector(){
			max = 10;
			vec = new int[max];
			size = 0;
		}
		~intVector(){
			delete[] vec;
			vec = NULL;
		}
		void AddInt(int newInt);
		void RemoveIntAt(int address);
		void RemoveInt(int number);
		void AdjustSize();
		void PrintVals();
		int GetSize();
		int& operator[](int address);
	private:
		int* vec;
		int size;
		int max;
};


#endif
