// GROUP:   X
// ID:      XXXXXXXX
// Assign:  09
// Assign:  Knapsack
// UVA:     10130
// Name:    XXX MY FULL NAME

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Obj
{
	int v; // value (price) of object
	int w; // weight of object
};

Obj a[1000];

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int T1[1001][31];
int Knapsack1(int n, int w);
int ComputeKnapsack1(int N, int W); // Recursive - memoization - initialize T then call Knapsack1(N,W);

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int T2[1001][31];
int ComputeKnapsack2(int N, int W); // Bottom-up, do not save space

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int T3[2][31];
int ComputeKnapsack3(int N, int W); // Bottom-up, use two rows only

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int T4[31];
int ComputeKnapsack4(int N, int W); // Bottom-up, save maximum space

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int ComputeKnapsack(int N, int W) // Here we can choose the method
{
	//return ComputeKnapsack1(N,W);
	//return ComputeKnapsack2(N,W);
	//return ComputeKnapsack3(N,W);
	return ComputeKnapsack4(N,W);
}

void Compute(); // Get input and call ComputeKnapsack() whenever needed

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	//freopen("input_assign09_10130.txt", "r", stdin);
	Compute();
	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
