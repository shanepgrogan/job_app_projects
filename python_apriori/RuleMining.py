import csv
import itertools
import math

# Global variables
data = []
totalCollectionL = []
C = []
L = []
itemTypes = []

## Helper functions ##

# returns absolute support
def count(itemset):
    N = 0
    for entry in data:
        if set(itemset) <= set(entry):
            N += 1
    return N

# get itemsets that pass minimum support
def getFrequentItemsets(cands):
    frequentItemsets = []
    for itemset in cands:
        sup = calculateSupport(itemset)
        if sup >= MIN_SUP:
            frequentItemsets.append(itemset)
    return frequentItemsets

# use frequent k-itemsets to product candidate (k+1)-itemsets
def join(level, k):
    cands = []
    for i in range(len(level) - 1):
        for j in range(i + 1, len(level)):
            union = list(set(level[i]) | set(level[j]))
            if union not in cands and len(union) == k:
                cands.append(union)
    return cands

# use apriori property to remove unnecessary candidates
def prune(candidates, level, k):
    remove = []
    for itemset in candidates:
        subsets = list(map(list,itertools.combinations(itemset, k)))
        for subset in subsets:
            if subset not in level:
                remove.append(itemset)
    returnList = [I for I in candidates if I not in remove]
    return returnList

# returns set of all subsets
def generateAllSubsets(itemset):
    subsets = []
    for k in range(1, len(itemset)):
        subsets += map(list,itertools.combinations(itemset, k))
    return subsets

# returns relative support
def calculateSupport(itemset):
    return float(count(itemset)) / len(data)

# returns confidence that A => B
def calculateConfidence(A,B):
    union = list(set(A) | set(B))
    return calculateSupport(union) / calculateSupport(A)

# returns string with properly formatted association rule for printing
def formatRules(inputSet):
    outputString = ""
    currentIndex = 0
    for item in inputSet:
        i = 0
        while i < len(itemTypes):
            if item in itemTypes[i]:
                newPart = header[i] + "=" + str(item)
                if currentIndex != len(inputSet) - 1:
                    newPart += ", "
                outputString += newPart
                break
            i += 1
        currentIndex += 1
    return outputString

## Process input ##
with open('Play_Tennis_Data_Set.csv', 'r') as f:
    csvreader = csv.reader(f)
    for line in csvreader:
        data.append(line)
header = data[0]
data = data[1:]

M = len(header)
for col in range(M):
    itemType = []
    for entry in data:
        if entry[col] not in itemType:
            itemType.append(entry[col])
    itemTypes.append(itemType)

# handles user input; input prompt is written twice so that it can
# be written to the output file while being displayed in the terminal
# to prompt the user
f = open("Rules.txt", "w")
f.write("User Input:\n")
f.write("\nSupport: ")
MIN_SUP = float(input("Support: "))
f.write(str(MIN_SUP))
f.write("\nConfidence: ")
MIN_CONF = float(input("Confidence: "))
f.write(str(MIN_CONF))

# iterate over data to add singletons to C
for entry in data:
    for item in entry:
        if [item] not in C:
            C.append([item])

L = getFrequentItemsets(C)
prevLSize = len(L)

# find itemsets
k = 2
while prevLSize != 0:

    # add frequent (k-1)-itemset to the total collection
    totalCollectionL.append(L)
    
    # generate candidate set
    C = join(L,k)
    
    # prune candidate set
    C = prune(C, L, k-1)

    # get frequent itemsets by comparing to min_sup
    prevLSize = len(L)
    L = getFrequentItemsets(C)

    k += 1

# find association rules
f.write("\n\nRules:\n")
counter = 0
for L in totalCollectionL:
    for I in L:
        subsets = generateAllSubsets(I)
        for s in subsets:
            A = s
            B = [x for x in I if x not in A] # I - s
            support = calculateSupport(I)
            confidence = calculateConfidence(A,B)
            if confidence >= MIN_CONF:
                counter += 1
                f.write("\nRule#%d: {%s} => {%s}\n(Support=%.2f, Confidence=%.2f)\n" % (counter, formatRules(A), formatRules(B), support, confidence))
     
f.close()
