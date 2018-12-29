#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NewLength 10000
#define NewK 40
#define InHeap(n, i) ((0<i)&&(i<n+1))
#define Parent(i) ((i)/2)
#define LChild(i) ((i)*2)
#define RChild(i) ((i)*2+1)
#define LChildValid(n, i) InHeap(n, LChild(i))
#define RChildValid(n, i) InHeap(n, RChild(i))
int COMPARE(int arg1, int arg2, ...);
void add(int comparedResults[][NewLength + 1], int index[], int size, int num);
void Heapify(int comparedResults[][NewLength + 1], int index[], int length);
int siftDown(int comparedResults[][NewLength + 1], int index[], int length, int i);
int properParent(int comparedResults[][NewLength + 1], int index[], int length, int i);
int delMin(int comparedResults[][NewLength + 1], int index[], int length);
int myCOMPARE(int comparedResults[][NewLength + 1], int i, int j);
static int looptime = 0;

int doalg(int n, int k, int Best[]) {
	int i = 1, j;
	int indexHeap[NewK + 1];

	static comparedResults[NewLength + 1][NewLength + 1] = { 0 };
	looptime++;
	while (i < NewK + 1) {
		indexHeap[i] = i;
		i++;
	}
	Heapify(comparedResults, indexHeap, NewK);
	i = NewK + 1;
	while (i < NewLength + 1) {
		add(comparedResults, indexHeap, NewK, i++);
	}
	i = NewK;
	while (0 < i) {
		Best[i - 1] = delMin(comparedResults, indexHeap, i);
		i--;
	}
	memset(comparedResults, 0, (NewLength + 1)*(NewLength + 1) * sizeof(int));
	if ((looptime != 0) && (looptime % 10 == 0)) {
		printf("Loop No.%d finished.\n", looptime);
	}
	return(1);
}

void add(int comparedResults[][NewLength + 1], int index[], int length, int num) {
	if (myCOMPARE(comparedResults, num, index[1]) == 1) {
		index[1] = num;
		siftDown(comparedResults, index, length, 1);
	}
}

void Heapify(int comparedResults[][NewLength + 1], int index[], int length) {
	int i = Parent(length);
	while (InHeap(length, i)) {
		siftDown(comparedResults, index, length, i);
		i--;
	}
}

int siftDown(int comparedResults[][NewLength + 1], int index[], int length, int i) {
	int j;
	while (i != (j = properParent(comparedResults, index, length, i))) {
		index[i] = index[j] ^ index[i];
		index[j] = index[j] ^ index[i];
		index[i] = index[j] ^ index[i];
		i = j;
	}
	return i;
}

int properParent(int comparedResults[][NewLength + 1], int index[], int length, int i) {
	int j;
	if (RChildValid(length, i)) {
		if (myCOMPARE(comparedResults, index[LChild(i)], index[i]) == 1)        j = i;
		else j = LChild(i);
		if (myCOMPARE(comparedResults, index[RChild(i)], index[j]) == 2)        j = RChild(i);
	}
	else if (LChildValid(length, i)) {
		if (myCOMPARE(comparedResults, index[LChild(i)], index[i]) == 1)        j = i;
		else j = LChild(i);
	}
	else j = i;
	return j;
}

int delMin(int comparedResults[][NewLength + 1], int index[], int length) {
	int min = index[1];
	index[1] = index[length];
	siftDown(comparedResults, index, length, 1);
	return min;
}

int myCOMPARE(int comparedResults[][NewLength + 1], int i, int j) {
	if (comparedResults[i][j] != 0) {
		return comparedResults[i][j];
	}
	else {
		comparedResults[i][j] = COMPARE(i, j);
		comparedResults[j][i] = 3 - comparedResults[i][j];
		return comparedResults[i][j];
	}
}