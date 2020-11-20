
#include <ap_int.h>

#define W_LEN 	32
#define W_INT  	17
#define A_LEN 	10
#define N_SYS   10


typedef ap_fixed<W_LEN,W_INT> fixedP;
//typedef float fixedP;

void CholeskyLS(fixedP A[A_LEN][A_LEN], fixedP b[A_LEN], fixedP res[A_LEN]);
void MatrixTranspose(fixedP A[A_LEN][A_LEN], fixedP AT[A_LEN][A_LEN]);
void BackwardSubstitution(fixedP U[A_LEN][A_LEN], fixedP b[A_LEN], fixedP res[A_LEN]);
void CholeskyFactor(fixedP A[A_LEN][A_LEN], fixedP L[A_LEN][A_LEN],fixedP D[A_LEN]);
void MatrixCopy(fixedP A[A_LEN][A_LEN], fixedP B[A_LEN][A_LEN]);
void ZeroFill(fixedP L[A_LEN][A_LEN]);
void ForwardSubstitution(fixedP U[A_LEN][A_LEN], fixedP b[A_LEN], fixedP res[A_LEN]);
void DiagonalSubstitution(fixedP D[A_LEN], fixedP y[A_LEN],fixedP z [A_LEN] );
