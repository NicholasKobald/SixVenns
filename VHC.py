# VerifyHamiltonianCycle.py
# Checks that the output of the FHC program was correct.
# 482 Project
# N. Kobald 2016-12-14

import sys, os

#Returns yes iff path is a hamiltonian cycle in G
def viable_cycle(G, path, numvertices):

    p = path.split(' ')
    p = [int(x) for x in p]
    numvertices = int(numvertices)

    if not (len(p) == numvertices):
        return False

    for i in range(len(p)-1):
        if not edge_exists(p[i], p[(i+1)], G[p[i]]):
            return False
    if not edge_exists(p[-1], p[0], G[p[-1]]):
        return False

    return True

def edge_exists(v, u, l):
    if u in l[1:]:
        return True
    return False


def main(argv):
    f = open(argv[0])
    f = f.readlines()
    l = []
    for line in f:
        l.append(line.strip())
    path = l[0]
    num_vertices = l[1]
    adj_list = []

    for i in range(int(num_vertices)):
        cur_line = l[i+2]
        templist = cur_line.split(' ')
        templist = [int(x) for x in templist]
        adj_list.append(templist)

    if viable_cycle(adj_list, path, num_vertices):
        pass
    else:
        print "False"

if __name__ == '__main__':
    main(sys.argv[1:])
