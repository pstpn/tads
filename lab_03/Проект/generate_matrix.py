from random import randint


def generate_and_write():
    mtrx = [[randint(1, 7777) for j in range(m)] for i in range(n)]
            
    inds = {}
            
    for i in range(zero_count):
        
        rand_i = randint(0, n - 1)
        rand_j = randint(0, m - 1)
        
        while rand_i in inds.keys() and rand_j in inds[rand_i]:
            rand_i = randint(0, n - 1)
            rand_j = randint(0, m - 1)
            
        if rand_i in inds.keys():
            inds[rand_i].append(rand_j)
        else:
            inds[rand_i] = [rand_j]
            
        mtrx[rand_i][rand_j] = 0        

    with open(filename, "w") as f:
        f.write(str(n) + " " + str(m) + "\n")
        
        for i in range(n):
            for j in range(m):
                if j == m - 1:
                    f.write(str(mtrx[i][j]) + "\n")
                else:
                    f.write(str(mtrx[i][j]) + " ")
                    

if __name__ == "__main__":
    n, m = list(map(int, input("Введите кол-во строк и столбцов через пробел: ").split()))

    percent = float(input("Введите процент заполнения матрицы: "))
    zero_count = n * m - int(n * m * (percent / 100))

    filename = input("Введите имя файла, в который сохранить матрицу: ")
    
    generate_and_write()