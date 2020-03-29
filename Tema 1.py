import time
import random

def generator(nr_numere, max_nr):
    global vector
    vector = []
    for i in range(0, nr_numere):
        x = random.randint(1, max_nr)
        vector.append(x)

def bubblesort(vector, n):
    for i in range(n):
        for j in range(n-i-1):
            if vector[j] > vector[j+1]:
                vector[j], vector[j+1] = vector[j+1], vector[j]
    print(vector)

def countsort(vector, max_nr):
    vec_aparitii = [0] * (max_nr+1)
    for i in vector:
        vec_aparitii[i] += 1
    vector.clear()
    for i in range(max_nr+1):
        while vec_aparitii[i]:
            vector.append(i)
            vec_aparitii[i] -= 1
    print(vector)

def radixsort(vector):
    for k in range(0, 32, 8):
        buck = [[] for p in range(256)]
        for x in vector:
            buck[(x >> k) & 255].append(x)
        index = 0
        for i in range(0, 256):
            for j in range(0, len(buck[i])):
                vector[index] = buck[i][j]
                index += 1
    print(vector)

def mergesort(vector, n):
    if n <= 1:
        return vector
    else:
        mij = n // 2
        n = mij
        st = mergesort(vector[:mij], n)
        dr = mergesort(vector[mij:], n)
        return interclasare(st, dr)

def interclasare(st, dr):
    i = j = 0
    vector_sortat = []
    n = len(st)
    m = len(dr)
    while i < n and j < m:
        if st[i] <= dr[j]:
            vector_sortat.append(st[i])
            i += 1
        else:
            vector_sortat.append(dr[j])
            j += 1
    vector_sortat.extend(st[i:])
    vector_sortat.extend(dr[j:])
    return(vector_sortat)

def quicksort(vector, inc, fin):
    if inc >= fin:
        return vector
    p = parti(vector, inc, fin)
    quicksort(vector, inc, p-1)
    quicksort(vector, p+1, fin)

def parti(vector, inc, fin):
    i = j = inc
    while i < fin:
        if vector[i] <= vector[fin]:
            vector[j], vector[i] = vector[i], vector[j]
            j += 1
        i += 1
    vector[j], vector[fin] = vector[fin], vector[j]
    return j

f = open('date.in')
ok = 0
nr_teste = int(f.readline())

for i in range(nr_teste):
    ok += 1
    n = int(f.readline())
    max_nr = int(f.readline())
    generator(n, max_nr)
    #print(vector)

    if ok == 1:
        inceput = time.time()
        print('Bubblesort:')
        bubblesort(vector, n)
        final = time.time()
        timp_sortare = final - inceput
        print('Timp:', timp_sortare)

    if ok == 2:
        inceput = time.time()
        print('Countsort:')
        countsort(vector, max_nr)
        final = time.time()
        timp_sortare = final - inceput
        print('Timp:', timp_sortare)

    if ok == 3:
        inceput = time.time()
        print('Radixsort:')
        radixsort(vector)
        final = time.time()
        timp_sortare = final - inceput
        print('Timp:', timp_sortare)

    if ok == 4:
        inceput = time.time()
        print('Mergesort:')
        v = mergesort(vector, n)
        print(v)
        final = time.time()
        timp_sortare = final - inceput
        print('Timp:', timp_sortare)

    v = []

    if ok == 5:
        inceput = time.time()
        print('Quicksort:')
        quicksort(vector, 0, n-1)
        print(vector)
        final = time.time()
        timp_sortare = final - inceput
        print('Timp:', timp_sortare)

    print()
