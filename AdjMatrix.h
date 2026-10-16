#ifndef ADJMATRIX_H
#define ADJMATRIX_H


class AdjMatrix {
	public:
		AdjMatrix(int inSize);
		~AdjMatrix();
		void SetDistance(int head, int tail, int distance);
		int GetDistance(int head, int tail);
		void PrintMatrix();
	protected:
		int** listList;
		int size;
};


#endif
