import subprocess as sp
from win32api import OpenProcess
from win32process import GetProcessTimes
from win32con import PROCESS_QUERY_INFORMATION,FALSE
total_time=0
def get_total_time():
	return total_time*0.0000001
class Runner:
	def __init__(self, args):
		self.__process = sp.Popen(args, universal_newlines=True, stdin=sp.PIPE, stdout=sp.PIPE, stderr=sp.STDOUT)
		self.__handle = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, self.__process.pid)

	def run(self, input):
		self.__output=self.__process.communicate(input)[0]
		global total_time
		total_time+=GetProcessTimes(self.__handle)["UserTime"]

	def get_output(self):
		return self.__output
