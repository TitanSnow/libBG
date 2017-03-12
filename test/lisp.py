#!/usr/bin/env python
import sys
from math import factorial
class istream:
    def __init__(self):
        self.__buf=[]
        self.__eof=False
    def get(self):
        if not len(self.__buf):
            t=sys.stdin.read(1)
            if t=='':
                self.__eof=True
            return t
        t=self.__buf[0]
        self.__buf=self.__buf[1:]
        return t
    def ungetc(self,ch):
        self.__buf=[ch]+self.__buf
    def iseof(self):
        return self.__eof
    def get_num(self):
        ch=None
        arr=[]
        while True:
            ch=self.get()
            if not ch.isdigit() and ch!='-':break
            arr.append(ch)
        t=long(''.join(arr))
        self.ungetc(ch)
        return t
    def get_string(self):
        ch=None
        arr=[]
        while True:
            ch=self.get()
            if not (not ch.isspace() and ch!=''):break
            arr.append(ch)
        t=''.join(arr)
        self.ungetc(ch)
        return t
cin=istream()
def skip_space():
    ch=None
    while True:
        ch=cin.get()
        if not(ch.isspace()):break
    cin.ungetc(ch)
table={}
def awd():
    skip_space()
    if cin.iseof():return {"nil":True}
    ch=cin.get()
    if ch==')':return {"nil":True}
    if ch!='(':
        cin.ungetc(ch)
        x=cin.get_num()
        return {"nil":False,"val":x}
    op=cin.get_string()
    args=[]
    t=None
    while True:
        t=awd()
        if not (not t["nil"]):break
        args.append(t)
    return table[op](args)
def mydiv(a, b):
	if bool(a>=0) == bool(b>=0):
		return a // b
	return -(abs(a) // abs(b))
def mymod(a, b):
	if bool(a>=0) == bool(b>=0):
		return a % b
	return -(abs(a) % abs(b)) if a<0 else abs(a) % abs(b)
def regFunc():
    def pr(args):
        print(' '.join([str(x["val"]) for x in args]))
        return {"nil":False,"val":0}
    table["print"]=pr
    def pl(args):
        return {"nil":False,"val":reduce(lambda a,b:a+b,[x["val"] for x in args])}
    table["+"]=pl
    def sb(args):
        return {"nil":False,"val":reduce(lambda a,b:a-b,[x["val"] for x in args])}
    table["-"]=sb
    def ml(args):
        return {"nil":False,"val":reduce(lambda a,b:a*b,[x["val"] for x in args])}
    table["*"]=ml
    def dv(args):
        return {"nil":False,"val":reduce(mydiv,[x["val"] for x in args])}
    table["/"]=dv
    def md(args):
        return {"nil":False,"val":reduce(mymod,[x["val"] for x in args])}
    table["%"]=md
    table["abs"]=lambda args:{"nil":False,"val":abs(args[0]["val"])}
    table["fac"]=lambda args:{"nil":False,"val":factorial(args[0]["val"])}
    table["pow"]=lambda args:{"nil":False,"val":args[0]["val"]**args[-1]["val"]}
    table["<"]=lambda args:{"nil":False,"val":long(args[0]["val"]<args[-1]["val"])}
    table[">"]=lambda args:{"nil":False,"val":long(args[0]["val"]>args[-1]["val"])}
    table["<="]=lambda args:{"nil":False,"val":long(args[0]["val"]<=args[-1]["val"])}
    table[">="]=lambda args:{"nil":False,"val":long(args[0]["val"]>=args[-1]["val"])}
    table["=="]=lambda args:{"nil":False,"val":long(args[0]["val"]==args[-1]["val"])}
    table["!="]=lambda args:{"nil":False,"val":long(args[0]["val"]!=args[-1]["val"])}
def main():
    regFunc()
    awd()
    while not cin.iseof():
        awd()
if __name__=="__main__":
    main()
