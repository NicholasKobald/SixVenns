#Five Venn parser
#Parse output from FHC when printing all 5 venns to one file.
#
#USAGE:
#   python FVP.py <inputfilename>.txt
#
# N. Kobald 2016 12 16
#
# FORMATS LATEX FRIENDLY TEXT TO COPY PASTE

import sys

def main(argv):
    f = open(argv[0])

    graph_outputs = []
    count_cycles = 0
    for line in f.readlines():
        path = line.split(' ')
        if -1 == int(path[0]):
            graph_outputs.append(count_cycles)
            count_cycles = 0
        count_cycles += 1

    for i in range(len(graph_outputs)):
        #Divide by two since we don't prevent 'reverse' cycles.
        print  i, "&", graph_outputs[i]/2, "\\\\"

if __name__ == '__main__':
    main(sys.argv[1:])
