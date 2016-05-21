import sys 
from ctypes import cdll
lib = cdll.LoadLibrary('./lib2.so')
class BigInt(object):
	def __init__(self):
		self.obj = lib.Big_new()
	def read(self,filename,bin):
		lib.Big_read(self.obj,filename,bin)
	def write(self,filename,bin):
		lib.Big_write(self.obj,filename,bin)
	def pow(self,a,p,mod):
		self.obj = lib.Big_pow(a.obj,p.obj,mod.obj)
	def __add__(self, other):
		self.obj =  lib.Big_add(self.obj,other.obj)
	def __sub__(self, other):
		self.obj =  lib.Big_sub(self.obj,other.obj)
	def __mul__(self, other):
		self.obj =  lib.Big_mul(self.obj,other.obj)
	def __div__(self, other):
		self.obj =  lib.Big_div(self.obj,other.obj)
	def __mod__(self, other):
		self.obj =  lib.Big_mod(self.obj,other.obj)



if __name__ == "__main__":
	binstr = "-b"
	bin = False
	if len(sys.argv) < 5:
		print "More parameters are required."
		raise SystemExit(1)
	for i in range(len(sys.argv) - 5):
		binArg = len(sys.argv) - 1 - i
		if sys.argv[len(sys.argv) - 1 - i] == binstr:
			bin = True
	if bin == False:
		binstr = "asd"
		
	f = BigInt()
	f.read(sys.argv[1],binstr)
	g = BigInt()
	g.read(sys.argv[3],binstr)
	if sys.argv[2]=='+':
		f+g
	elif sys.argv[2]=='-':
		f-g
	elif sys.argv[2]=='*':
		f*g
	elif sys.argv[2]=='/':
		f/g
	elif sys.argv[2]=='%':
		f%g
	elif sys.argv[2]=='^':
		if len(sys.argv)==6 and not bin or len(sys.argv)==7 and bin:
			mod = BigInt()
			if bin:
				mod.read(sys.argv[6],binstr)
			else:
				mod.read(sys.argv[5],binstr)
		else:
			print "More parameters are required."
			raise SystemExit(1)
		f.pow(f,g,mod)
	else:
		print "Unknown operator"+ sys.argv[2]
		raise SystemExit(1)
	f.write(sys.argv[4],binstr)