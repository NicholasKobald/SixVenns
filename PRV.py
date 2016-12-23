#PickRandomVenns.py
#usage: python PRYV.py <filename>.txt <number of graphs you want> <outputfilename>.txt
#where the file is a file containing Venn diagrams, and the number
#is the number of Venn diagrams you want.
#
# Program output:
#   Takes the specified number of lines from the file
#   We garuntee no duplicates, and that we select the lines
#   uniformly randomly. 
#
#
#WE ASSUME EVERY LINE IN THE INPUT FILE CONTAINS A GRAPH.
#
# N. Kobald - 2016-12-17
import sys, random

def main(argv):
    if len(argv) < 3:
        print "Too few arguements."
        print "USAGE:\n>python PRYV.py <filename>.txt <number> <outputfilename>.txt"
        sys.exit()

    file_name = argv[0]
    out_name = argv[2]
    num_graphs_wanted = int(argv[1])

    print "Finding", num_graphs_wanted, "Venn Diagrams from", file_name
    print "Counting graphs in file..."
    num_lines = sum(1 for line in open(file_name))
    print "Sampling from", num_lines, "total graphs."
    choices = random.sample(xrange(num_lines), num_graphs_wanted)
    graph_list = []
    with open(file_name) as fp:
        for i, line in enumerate(fp):
            if i in choices:
                graph_list.append(line)

    output_file = open(str(out_name), 'w')
    output_file.writelines(["%s" % item for item in graph_list])
    print "PRV finished correctly."

if __name__ == '__main__':
    main(sys.argv[1:])
