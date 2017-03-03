#!/usr/bin/python3
from subprocess import check_output, check_call

NO_EXECS = 5

all_cases = [('sampledata/test-flat.16x16x16.uint8', 1),
        ('sampledata/CThead.256x256x113.uint16', 33904),
        ('sampledata/CThead-2by2.256x512x226.uint16', 135682),
        ('sampledata/CThead-2by4.256x512x452.uint16', 271041),
        ('sampledata/CThead-twice.256x256x226.uint16', 67842),
        ('sampledata/MRbrain.256x256x109.uint16', 88515),
        ('sampledata/bucky.32x32x32.uint8', 607),
        ('sampledata/nucleon.41x41x41.uint8', 439),
        ('sampledata/test-one.16x16x16.uint8', 2)]

def correct(case_result):
    test_case, correct_result = case_result
    res = check_output(['./simple', '-c', '-i', test_case])
    return res.decode('utf-8') == 'Number of nodes in the tree: ' + str(correct_result) + '\n'

def average_execution_time(case):
    total_time = 0.0
    for _ in range(NO_EXECS):
        check_call(['time', '-o', 'output', '-f', '%e', './simple', '-c', '-i', case])
        time_file = open('output', 'r')
        [execution_time] = [float(line) for line in time_file]
        total_time += execution_time
    return total_time / NO_EXECS


#if all(map(correct, all_cases)):
#    print ('All tested ran correctly')
#else:
#    print ('Failed :((')


run_times = list(map((lambda case: (case[0], average_execution_time(case[0]))), all_cases))

for (case, t) in run_times:
    print ('EXECUTION TIME: ' + case + ' ' + str(t))


