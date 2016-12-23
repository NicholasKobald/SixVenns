#PickRandomVenns.py
#usage: python PRYV.py <filename.txt> <number>
#where the file is a file containing Venn diagrams, and the number
#is the number of Venn diagrams you want.
#
#
# N. Kobald - 2016-12-17
import sys


def main(argv):
    if len(argv) < 2:
        print "USAGE: python PRYV.py <filename>.txt <number>"
        sys.exit()
    file = argv[0]
    number = argv[1]
    print "Finding", number, "Venn Diagrams from", file

    """"
    with open(file) as fp:
        for i, line in enumerate(fp):
            if i == 25:
                # 26th line
            elif i == 29:
                # 30th line
            elif i > 29:
                break
    """

if __name__ == '__main__':
    main(argv[1:])
