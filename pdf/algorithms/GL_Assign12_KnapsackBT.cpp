// GROUP:   X
// ID:      XXXXXXXX
// Assign:  12
// Assign:  KnapsackBT
// UVA:     10130
// Name:    XXX MY FULL NAME

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<class Type>
void Merge(Type* a, int n, bool (*IsBefore)(Type& a, Type& b));

template<class Type>
void MergeSort(Type* a, int n, bool (*IsBefore)(Type& a, Type& b));

////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Obj
{
	int v;
	int w;
};

int n;       // number of objects (input)
Obj a[1000]; // objects (input)

////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool IsBefore(Obj& a, Obj& b); // return true if unit value of a is greater than unit value of b

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int best_val; // the best total value found until now

int Bound(int i, int w); // upper bound on the total value of items [i..n-1] that can fit in w

void BackTrack(int i, int w, int cur_val); // starting from item i, remaining weight w, cur_value of objects[0..i-1]

int ComputeKnapsack(int N, int W); // solve knapsack of N objects and W weight

void Compute();

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	//freopen("input_assign12_10130.txt", "r", stdin);
	Compute();
	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
