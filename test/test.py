#!/usr/bin/env python
from runner import get_total_time,Runner
from random import randint
times = 1000
hi = 10**10000
lo = -hi
debugMode = False
from sys import argv
from sys import exit
op = argv[1]
if debugMode:
	print(op)
def mydiv(a, b):
	if bool(a>=0) == bool(b>=0):
		return a // b
	return -(abs(a) // abs(b))
def mymod(a, b):
	if bool(a>=0) == bool(b>=0):
		return a % b
	return -(abs(a) % abs(b)) if a<0 else abs(a) % abs(b)
for i in range(times):
	a = randint(lo,hi)
	b = randint(lo,hi)
	rst = None
	if op=='add':
		rst = a + b
	elif op=='sub':
		rst = a - b
	elif op=='mul':
		rst = a * b
	elif op=='div':
		rst = mydiv(a, b)
	elif op=='mod':
		rst = mymod(a, b)
	else:
		exit(2)
	if debugMode:
		print(a)
		print(b)
		print(rst)
	run = Runner("./testprog"+op)
	run.run(str(a) + " " + str(b))
	opt = run.get_output()
	if opt!=str(rst):
		if debugMode:print(opt)
		exit(1)
total_time=get_total_time()
print(op+' totaltime= '+str(total_time)+'s')
