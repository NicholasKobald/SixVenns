import sys

#'first_1000_timings_NOPRUNNING.txt'

f = open(sys.argv[1])
count = 0
count_small_case =0
lines_read = 0
worst = 0
for i in f.readlines()[:-3]:
    #print i
    lines_read+=1
    temp = float(i)
    worst = max(worst, temp)
    if temp>3:
        count += 1
    if temp<3 and temp>1:
        count_small_case+=1


print "Graphs that took over 3.0 seconds:", count
print "Graphs that took a wierd amount of time:", count_small_case
print "percentage of graphs that took over 1.5 seconds:", count/1000
print "Worst case:", worst
