import numpy as np
import matplotlib.pyplot as plt

def adjMatrixFromFile(fileName):
    file = open(fileName, 'r')
    N = int(file.readline())
    adjMat = np.zeros((N,N))
    for i in range(N):
        ints = file.readline().split()
        j = 0
        while j < len(ints):
            a = int(ints[j])
            b = int(ints[j+1])
            adjMat[a][b] += 1
            j += 2
    return adjMat

def outDegrees(adjMat):
    N = len(adjMat)
    outDegs = np.zeros((N,1))
    for i in range(N):
        s = 0
        for j in range(N):
            s += adjMat[i][j]
        outDegs[i] = s
    return outDegs

def transitionProbabilities(A, O):
    N = len(A)
    T = np.zeros((N,N))
    for i in range(N):
        for j in range(N):
            T[i][j] = (0.90*A[i][j]/O[i]) + 0.10/N
    return T

def simRanks(fileName, numTrials):
    
    print("\nSimulated Rank: \n")
    print("file name: " + fileName + '\n')
    print("numTrials: " + str(numTrials) + '\n')

    adjMat = adjMatrixFromFile(fileName)
    outDegs = outDegrees(adjMat)
    p = transitionProbabilities(adjMat, outDegs)

    N = len(adjMat)
    visits = np.zeros((N,1))

    k = 0

    for i in range(numTrials):
        r = np.random.uniform(0,1)
        s = 0
        j = 0
        while s < r:
            s += p[k][j]
            j += 1
        k = j-1
        visits[k] += 1

    visits = np.divide(visits, numTrials)

    print("Adjacency Matrix:\n " + str(adjMat) + '\n')
    print("Out Degrees:\n " + str(outDegs) + '\n')
    print("Transition Matrix:\n " + str(p) + '\n')
    print("Transition Matrix (Transpose):\n " + str(np.transpose(p)) + '\n')
    print("Simulated Ranks:\n " + str(visits) + '\n')
    return visits

def powerRanks(fileName, numTrials):

    print("\nPower Method Rank: \n")
    print("file name: " + fileName + '\n')
    print("numTrials: " + str(numTrials) + '\n')

    adjMat = adjMatrixFromFile(fileName)
    outDegs = outDegrees(adjMat)
    p = transitionProbabilities(adjMat, outDegs)

    N = len(adjMat)

    x = np.zeros((N, 1))
    x[0][0] = 1

    for k in range(numTrials):
        x = np.transpose(p)@x

    print("Adjacency Matrix:\n " + str(adjMat) + '\n')
    print("Out Degrees:\n " + str(outDegs) + '\n')
    print("Transition Matrix:\n " + str(p) + '\n')
    print("Transition Matrix (Transpose):\n " + str(np.transpose(p)) + '\n')
    print("Power Method Ranks:\n " + str(x))
    return x

print("\n#1")
simRanks('tiny.txt', 100)
powerRanks('tiny.txt', 100)

print("\n#2")
simRanksTiny = simRanks('tiny.txt', 100000)
simRanksMed = simRanks('medium.txt', 100000)

plt.title('(2) Simulation Ranks, 100,000 Trials')
plt.xlabel('ranks')
plt.ylabel('frequency')
plt.hist(simRanksTiny)
plt.hist(simRanksMed)
plt.show()
plt.clf()

powerRanksTiny = powerRanks('tiny.txt', 100000)
powerRanksMed = powerRanks('medium.txt', 100000)

plt.title('(2) Power Method Ranks, 100,000 Trials')
plt.xlabel('ranks')
plt.ylabel('frequency')
plt.hist(powerRanksTiny)
plt.hist(powerRanksMed)
plt.show()
plt.clf()

print("\n#3")
powerRanksModTiny = powerRanks('tinyNoDoubles.txt', 100000)
powerRanksModMed = powerRanks('mediumNoDoubles.txt', 100000)

plt.title('(3) Power Method Ranks, No Multiple Edges, 100,000 Trials')
plt.xlabel('ranks')
plt.ylabel('frequency')
plt.hist(powerRanksModTiny)
plt.hist(powerRanksModMed)
plt.show()
plt.clf()

print("Slight left skew in the modified histogram for medium")

print("\n#4")
powerRanksMedAdded = powerRanks('mediumAddedLinks.txt', 100000)

plt.title('(4) Power Method Ranks, Added Edges to 23, 100,000 Trials')
plt.xlabel('ranks')
plt.ylabel('frequency')
plt.hist(powerRanksMedAdded)
plt.show()
