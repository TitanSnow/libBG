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

times = 100
debugMode = False
from sys import exit
if __name__ == "__main__":
    for kase in range(times):
        gen = Runner("./lisp_generator.py")
        gen.run("")
        inp = gen.get_output()
        if debugMode:
            print(inp)
        c = Runner("./lisp")
        p = Runner("./lisp.py")
        c.run(inp)
        p.run(inp)
        co = c.get_output()
        po = p.get_output()
        if debugMode:
            print(po)
            print(co)
        if po != co:
            exit(1)
