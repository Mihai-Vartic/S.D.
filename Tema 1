def generator(nr_numere, max_nr):
    import random
    global vector
    vector = []
    for i in range(0, nr_numere):
        x = random.randint(1, max_nr)
        vector.append(x)

def bubblesort(n, vector):
    for i in range(n):
        for j in range(n-i-1):
            if vector[j] > vector[j+1]:
                vector[j], vector[j+1] = vector[j+1], vector[j]
    print(vector)

def countsort(max_nr, vector):
    vec_aparitii = [0] * (max_nr+1)
    for i in vector:
        vec_aparitii[i] += 1
    vector.clear()
    for i in range(max_nr+1):
        while vec_aparitii[i]:
            vector.append(i)
            vec_aparitii[i] -= 1
    print(vector)

f = open('date.in')

ok = 0
nr_teste = int(f.readline())
for i in range(nr_teste):
    ok += 1
    n = int(f.readline())
    max_nr = int(f.readline())
    generator(n, max_nr)
    print(vector)
    if ok == 1:
        bubblesort(n, vector)
    if ok == 2:
        countsort(max_nr, vector)
    print()
