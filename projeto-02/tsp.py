import sys
import math

def dist(p1, p2):
    return math.sqrt((p1[0] - p2[0])**2 +
                     (p1[1] - p2[1])**2 )

def path_dist(seq, points):
    d = dist(points[seq[-1]], points[seq[0]])
    for i in range(len(seq)-1):
        d += dist(points[seq[i]], points[seq[i+1]])
    return d

def backtrack(points, idx, curr_cost, curr_sol, 
              best_cost, best_seq):
    if idx == len(points):
        curr_cost += dist(points[curr_sol[0]], points[curr_sol[-1]])
        if curr_cost < best_cost:
            best_seq[:] = curr_sol.copy()
            best_cost = curr_cost
            print('best:', best_cost, file=sys.stderr)
        return best_cost

    for i in range(len(points)):
        if not usado[i]:
            usado[i] = True
            curr_sol[idx] = i

            new_cost = curr_cost + dist(points[curr_sol[idx-1]], points[curr_sol[idx]])
            best_cost = backtrack(points, idx+1, new_cost, curr_sol, best_cost, best_seq)

            usado[i] = False
            curr_sol[idx] = -1
    
    return best_cost

if __name__ == "__main__":
    N = int(input())
    points = []
    for i in range(N):
        x, y = [float(x) for x in input().split()]
        points.append((x, y))
    
    usado = [False] * N
    curr_sol = [-1] * N
    best_sol = [-1] * N

    curr_sol[0] = 0
    usado[0] = True

    backtrack(points, 1, 0, curr_sol, math.inf, best_sol)

    print(path_dist(best_sol, points), '1')
    print(' '.join([str(i) for i in best_sol]))

