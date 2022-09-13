from turtle import position
import numpy as np
def create_co_matrix(corpus, vacab_size, window_size=1):
    co_matrix = [[0] * vacab_size for _ in range(vacab_size)]
    for i in range(len(corpus)):
        pos1 = corpus[i]
        start = max(i - window_size, 0)
        end = min(i + window_size, vacab_size-1)
        for j in range(start, end+1):
            if j != i:
                pos2 =  corpus[j]
                co_matrix[pos1][pos2] += 1
    return co_matrix

def cos_similarity(x, y):
    nx = x / np.sqrt(np.sum(x**2))
    ny = y / np.sqrt(np.sum(y**2))
    return np.dot(nx, ny)