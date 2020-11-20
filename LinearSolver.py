
def AscendentSustitution(U,b):
	#Solves the system Ux=b with ascendent sustitution
	#Assumes that U is an upper triangular matrix
	
	n = len(U)
	x = [[0] for i in range(n)]
	aux = 0
	
	for i in range(n-1,-1,-1):
		aux = b[i][0]
		
		for j in range(i,n):
			aux -= U[i][j] * x[j][0]
			
		x[i] = [aux / U[i][i]]
	
	return x

def DescendentSustitution(U,b):
	n = len(U)
	x = [[0] for i in range(n)]
	aux = 0

	for i in range(n):
		aux = b[i][0]

		for j in range(i):
			aux -= U[i][j] * x[j][0]

		x[i] = [aux / U[i][i]]
	
	return x


def rowExchange(row1, row2, matrix):
	matrix.insert(row1, matrix.pop(row2))
	
	if (row1+1 < row2):
		matrix.insert(row2, matrix.pop(row1+1))
		
	elif (row1-1 > row2):
		matrix.insert(row2, matrix.pop(row1-1))
	
	return matrix

def createIdentity(n):
	I = []

	for j in range (n):
		row = [int(k==j) for k in range(n)]
		I.append(row)

	return I

def rowPivot(matrix, col):
	max = abs(matrix[col][col])
	maxPos = col
	n = len(matrix)
	i = col + 1

	while (i < n):
    		
		if (max < abs(matrix[i][col])):
			max = abs(matrix[i][col])
			maxPos = i

		i += 1

	P = createIdentity(n)

	if (col != maxPos):
		matrix = rowExchange(col,maxPos,matrix)
		P = rowExchange(col,maxPos,P)
	return matrix,P

def matrixMult(A,B):
	"C = AxB"
	#n x m
	An = len(A)
	Am = len(A[0])
	Bm = len(B[0])

	Crows = [0 for i in range(Bm)]
	C = [Crows[:] for i in range(An)]

	for Arow in range(An):
		
		for Bcol in range(Bm):
			aux = 0

			for element in range(Am):
				aux += A[Arow][element] * B[element][Bcol]

			C[Arow][Bcol] = aux
			

	return C

def matrixTranspose(A):
	n = len(A)
	m = len(A[0])

	Crows = [0 for i in range(m)]
	C = [Crows[:] for i in range(n)]

	for i in range(m):
		
		for j in range(n):
			C[i][j] = A[j][i]

	return C

def rowSum(row1, row2, coeff, matrix):
	"row2 + coeff * row1"

	n = len(matrix[0])

	for i in range(n):
		matrix[row2][i] += coeff * matrix[row1][i]

	return matrix


def rowNormalize(row, matrix):
	n = len(matrix[0])
	pivot = 0
	for i in range(n):
	
		if (pivot == 0):
			pivot = matrix[row][i]

		else:
			matrix[row][i] /= pivot

	return matrix

def matrixCmp(A,B):
	An = len(A)
	Am = len(A[0])
	Bn = len(B)
	Bm = len(B[0])

	if ((An != Bn) or (Am != Bm)):
		return False

	for i in range(An):
		
		for j in range(Am):
    			
			if (A[i][j] != B[i][j]):
				return False

	return True

def LDLCholesky(A):
	n = len(A)
	L = [[0 for j in range(n)] for i in range(n)]
	D = [[0 for j in range(n)] for i in range(n)]

	for col in range(n):
		dSum = 0

		for k in range(col):
			dSum += D[k][k] * L[col][k] *L[col][k]

		D[col][col] = A[col][col] - dSum
		L[col][col] = 1

		for row in range(col + 1,n):
			auxSum = 0

			for k in range(col):
				auxSum += L[row][k] * L[col][k] * D[k][k]

			L[row][col] = (A[row][col]- auxSum)/D[col][col]

	return L, D

def choleskyFactor(A):
	n = len(A)
	L = [[0 for j in range(n)] for i in range(n)]

	for col in range(n):
		dSum = 0
		
		for k in range(col):
			dSum += L[col][k] * L[col][k]
		
		L[col][col] = (A[col][col] - dSum)**0.5

		for row in range(col + 1, n):
			auxSum = 0

			for k in range(col):
				auxSum += L[row][k] * L[col][k]

			L[row][col] = (A[row][col] - auxSum) / L[col][col]
	
	return L



def DirectLinearSolver(A,b):
	#Applies Gauss elimination method
	#Receive coefficient matrix A and vector b with the right side of the system of equations
	#Example:
	#A [Row][Column]
	#A = [[1, 2, 3],[4, 5, 6],[7, 8, 9]]
	#b = [5, 10, 15]
	n = len(b)
	L = createIdentity(n)
	P = createIdentity(n)
	AT = matrixTranspose(A)
	
	if (matrixCmp(A,AT)):
		#L = choleskyFactor(A)
		L, D = LDLCholesky(A)
		LT = matrixTranspose(L)
		y = DescendentSustitution(L,b)
		z = DescendentSustitution(D,y)
		x = AscendentSustitution(LT,z)

	else:
    		
		for col in range(n):
			A, Paux = rowPivot(A,col)
			P = matrixMult(Paux, P)
			pivot = A[col][col]
			
			for row in range(col + 1, n):
				coeff = A[row][col] / pivot
				A = rowSum(col,row,-coeff,A)
				L[row][col] = coeff

		P = matrixTranspose(P)
		b2 = matrixMult(P,b)
		y = DescendentSustitution(L,b2)
		x = AscendentSustitution(A,y)
	#print("P",P)
	#print("A",A)
	#print("L",L)
	return x

def CholeskySolver(A,b):
	L, D = LDLCholesky(A)
	LT = matrixTranspose(L)
	y = DescendentSustitution(L,b)
	z = DescendentSustitution(D,y)
	x = AscendentSustitution(LT,z)

	return x

if (__name__ == "__main__"):
	#A = [[1, -3, 2], [-2, 8, -1], [4, -6, 5]]

	A = [[1, 2, 3],[2, 2, 5],[3 , 5, 2]]
	b = [[1], [4], [8]]

	print("RES",DirectLinearSolver(A,b))