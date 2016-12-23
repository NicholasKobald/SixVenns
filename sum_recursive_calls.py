
f = open('timing_output_fivevenn_no_prunning_four.txt')

l = f.readlines()
sum = 0
for line in l:
    sum += int(line)

print sum
