from random import randint
from sys import argv


def generate_and_write(filename, n, m, zero_count):
    mtrx = [[randint(1, 100) for j in range(m)] for i in range(n)]
            
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
    
    filename_1 = argv[1]
    filename_2 = argv[5]
    
    filling_1 = int(argv[4])
    filling_2 = int(argv[8])
    
    n_1, m_1 = int(argv[2]), int(argv[3])
    n_2, m_2 = int(argv[6]), int(argv[7])
    
    zero_c_1 = n_1 * m_1 - int(n_1 * m_1 * (filling_1 / 100))
    zero_c_2 = n_2 * m_2 - int(n_2 * m_2 * (filling_2 / 100))
    
    generate_and_write(filename_1, n_1, m_1, zero_c_1)
    generate_and_write(filename_2, n_2, m_2, zero_c_2)