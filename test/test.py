#!/usr/bin/env python
import subprocess
from time import time
class Runner:
	def __init__(self, args):
		self.__process = subprocess.Popen(args, universal_newlines=True, stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)

	def run(self, input):
		self.__start_time = time()
		self.__output=self.__process.communicate(input)[0]
		self.__end_time = time()

	def get_output(self):
		return self.__output

	def get_running_time(self):
		return self.__end_time - self.__start_time

from random import randint
times = 10000
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
total_time = 0
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
	total_time += run.get_running_time()
	if opt!=str(rst):
		if debugMode:print(opt)
		exit(1)
print(op+' totaltime= '+str(total_time)+'s')
