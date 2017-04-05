import resource as res
import subprocess as sp
def get_total_time():
	return res.getrusage(res.RUSAGE_CHILDREN).ru_utime
class Runner:
	def __init__(self, args):
		self.__process = sp.Popen(args, universal_newlines=True, stdin=sp.PIPE, stdout=sp.PIPE, stderr=sp.STDOUT)

	def run(self, input):
		self.__output=self.__process.communicate(input)[0]

	def get_output(self):
		return self.__output
