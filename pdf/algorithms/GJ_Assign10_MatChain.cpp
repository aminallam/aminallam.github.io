// GROUP:   X
// ID:      XXXXXXXX
// Assign:  10
// Assign:  MatChain
// UVA:     348
// Name:    XXX MY FULL NAME

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int p[11]; // the dimensions of matrices

int T[11][11]; // T[a][b]=the optimal number of multiplication of p[a]...p[b]
int D[11][11]; // D[a][b]=the decision (value of k) that gets T[a][b]

// Top down version
int MatChain(int a, int b); // Recursive, cost of multiplying the b-a matrices with indexes: a...b-1
void MatChainTopDown(int n); // Initialize T then call MatChain(0,n)

// BottomUp version
void MatChainBottomUp(int n);

// Recursive to output the solution for both versions
void MatChainSol(int a, int b);

void Compute();

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	//freopen("input_assign10_00348.txt", "r", stdin);
	Compute();
	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
