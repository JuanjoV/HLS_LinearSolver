
import LinearSolver
import random
import numpy as np
import timeit
import cmath

def matrixGen(N,bits):
    matrix = []

    for  _ in range(N):
        fila = []
        for _ in range(N):
            n = random.randint(0,2**bits -1)
            fila.append(n)
        matrix.append(fila)
    return matrix

def symMatrixGen(N,bits):
    matrix = []

    for  i in range(N):
        fila = []
        for j in range(i+1):
            n = random.randint(0,2**bits -1)
            fila.append(n)
        matrix.append(fila)
    
    for j in range(N):
        for i in range(j+1,N):
            matrix[j].append(matrix[i][j])

    return matrix

def formatedPrint(m):
    for linea in m:
        l =""
        for columna in linea:
            l += str(columna)+"\t"
        print(l)

def checkSolution(m):
    mm = np.array(m)
    d = np.linalg.det(mm)
    if (d < 1e-6 and d > -1e-6):
        return False
    else:
        return True

def sysGen(N,bits,sym = False):
    if (sym):
        A = symMatrixGen(N,bits)
    else:    
        A = matrixGen(N,bits)
    while (not checkSolution(A)):
        A = matrixGen(N,bits)

    b = [ [random.randint(0,2**bits-1)] for  i in range(N)]

    return A,b

def matrixCopy(A):
    result = []
    length = len(A)
    length1 = len(A[0])

    for i in range(length):
        fila = []
        for j in range(length1):
            fila.append(A[i][j])
        result.append(fila)

    return result

gold = open("out.gold.dat","w")
size = 10
bitlen = 8
random.seed(50)
extimes = []
for j in range(10):
    A,b = sysGen(size,bitlen,True)
    AA = matrixCopy(A)
    bb = matrixCopy(b)
    start_time = timeit.default_timer()
    res = LinearSolver.CholeskySolver(AA,bb)
    elapsed_time = timeit.default_timer() - start_time
    extimes.append(elapsed_time)
    print("Tiempo transcurrido: ", round(elapsed_time*1e6,6), " us")
    for line in range(size):
        for col in range(size):
            gold.write(str(A[line][col])+"\t\t")
        gold.write(str(round(b[line][0],6))+"\n")

    for line in range(size):
        gold.write(str(round(res[line][0].real,6))+"\n")
        if (res[line][0].imag > 1e-9):
            print("Solucion imaginaria encontrada! ", j)

gold.close()
print("Promedio de tiempo: ", round(sum(extimes)/len(extimes) * 1e6 ,6)," us")