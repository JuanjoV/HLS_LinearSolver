
#include "CholeskyLS.h"
#include <iostream>

constexpr int UNROLL_FACTOR = 5;
constexpr int ARRAY_SIZE = A_LEN/2;

void MatrixTranspose(fixedP A[A_LEN][A_LEN],fixedP AT[A_LEN][A_LEN])
{
	for (int i = 0; i < A_LEN ; i++)
	{
#pragma HLS UNROLL
		for (int j = 0; j < A_LEN; j++)
		{
#pragma HLS UNROLL
			AT[i][j] = A[j][i];
		}
	}

}

void BackwardSubstitution(fixedP U[A_LEN][A_LEN], fixedP b[A_LEN], fixedP res[A_LEN])
{
	for (int k = 0; k < A_LEN; k++)
	{
#pragma HLS UNROLL factor=UNROLL_FACTOR
#pragma HLS PIPELINE
		res[k] = 0;
	}
	fixedP aux;

	for (int i = A_LEN - 1 ; i >= 0; i--)
	{
#pragma HLS UNROLL factor=UNROLL_FACTOR
		aux = b[i];

		for (int j = 0; j < A_LEN; j++)
		{
#pragma HLS UNROLL factor=UNROLL_FACTOR
			if (j >= i)
			{
				aux -= U[i][j] * res[j];
			}
		}
		res[i] = aux / U[i][i];
	}

}

void ForwardSubstitution(fixedP U[A_LEN][A_LEN], fixedP b[A_LEN], fixedP res[A_LEN])
{
	for (int k = 0; k < A_LEN; k++)
	{
#pragma HLS UNROLL factor=UNROLL_FACTOR
#pragma HLS PIPELINE
		res[k] = 0;
	}
	fixedP aux;

	for (int i = 0; i < A_LEN; i++)
	{
#pragma HLS UNROLL factor=UNROLL_FACTOR
		aux = b[i];

		for (int j = 0; j < A_LEN; j++)
		{
#pragma HLS UNROLL factor=UNROLL_FACTOR
			if (j < i)
			{
				aux -= U[i][j] * res[j];
			}
		}
		res[i] = aux / U[i][i];
	}

}

void CholeskyFactor(fixedP A[A_LEN][A_LEN], fixedP L[A_LEN][A_LEN], fixedP D[A_LEN])
{
	fixedP dSum;
	fixedP auxSum;
	int k, row;

	for (int col = 0; col < A_LEN; col++)
	{
#pragma HLS PIPELINE
#pragma HLS UNROLL

		dSum = 0;

		for (k = 0; k < A_LEN; k++)
		{
#pragma HLS PIPELINE

			if (k < col)
			{
				dSum += D[k] * L[col][k] * L[col][k];
			}
		}
		D[col] = A[col][col] -dSum;
		L[col][col] = 1;

		for (row = 0; row < A_LEN; row++)
		{
#pragma HLS PIPELINE
#pragma HLS UNROLL
			if (row >= col + 1)
			{
				auxSum = 0;

				for (k = 0; k < A_LEN; k++)
				{
#pragma HLS PIPELINE

					if (k < col)
					{
						auxSum += L[row][k] * L[col][k] * D[k];
					}
				}
				L[row][col] = (A[row][col] - auxSum) / D[col];
			}
			else
			{
				if (row != col) L[row][col] = 0;
			}
		}
	}

}
/*
void MatrixCopy(fixedP A[A_LEN][A_LEN], fixedP B[A_LEN][A_LEN])
{
	for (int i = 0; i < A_LEN; i++)
	{

		for(int j = 0; j < A_LEN; j++)
		{

			B[i][j] = A[i][j];
		}
	}
}

void ZeroFill(fixedP L[A_LEN][A_LEN])
{
	for (int i = 0; i < A_LEN; i++)
		{

			for(int j = 0; j < A_LEN; j++)
			{
				L[i][j] = 0;
			}
		}
}
*/

void DiagonalSubstitution(fixedP D[A_LEN], fixedP y[A_LEN],fixedP z [A_LEN] )
{
	for (int i = 0; i < A_LEN; i++)
	{
#pragma HLS UNROLL
		z[i] = y[i]/D[i];
	}
}
/* ONLY FOR TESTBENCH DEBUG
void MatrixPrint(fixedP A[A_LEN][A_LEN])
{
	for (int i = 0; i < A_LEN; i++)
	{
		for (int j = 0; j < A_LEN; j++)
		{
			std::cout << A[i][j] << "\t";
		}
		std::cout << std::endl;
	}
}

void VectorPrint(fixedP D[A_LEN])
{
	for (int i = 0; i < A_LEN; i++)
	{
		std::cout << D[i] << std::endl;
	}
}
*/
void CholeskyLS(fixedP A[A_LEN][A_LEN],fixedP b[A_LEN], fixedP res[A_LEN])
{
#pragma HLS ARRAY_PARTITION variable=res dim=1 cyclic factor=ARRAY_SIZE
#pragma HLS ARRAY_PARTITION variable=b dim=1 cyclic factor=ARRAY_SIZE
#pragma HLS ARRAY_PARTITION variable=A dim=1 cyclic factor=ARRAY_SIZE

	fixedP L[A_LEN][A_LEN];
	fixedP LT[A_LEN][A_LEN];
	fixedP D[A_LEN];
	fixedP z[A_LEN];
	fixedP y[A_LEN];

	CholeskyFactor(A,L,D);
	MatrixTranspose(L,LT);
	ForwardSubstitution(L,b,y);
	DiagonalSubstitution(D,y,z);
	BackwardSubstitution(LT,z,res);

}
