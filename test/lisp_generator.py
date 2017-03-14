#!/usr/bin/env python
from random import randint
from random import choice
hi = 10**10000
lo = -hi
maxstack = 8
def dwa(dep = 0):
    if dep >= maxstack or choice([True] * 2 + [False]):
        return str(randint(lo, hi))
    rst = '('
    op = choice(("print", "+", "-", "*", "/", "%", "abs", "fac", "pow", "<", ">", "<=", ">=", "==", "!="))
    rst += op
    rst += ' '
    sz = None
    if op in ("abs", "fac"):
        sz = 1
    elif op in ("/", "%", "pow", "<", ">", "<=", ">=", "==", "!="):
        sz = 2
    else:
        sz = randint(2, 8)
    if op in ("/", "%"):
        return rst + dwa(dep + 1) + ' ' + str(choice((1, -1)) * randint(1, hi)) + ')'
    elif op == "fac":
        return rst + str(randint(1, 16)) + ")"
    elif op == "pow":
        return rst + dwa(dep + 1) + ' ' + str(randint(0, 32)) + ')'
    else:
        for i in range(sz):
            rst += dwa(dep + 1) + ' '
        return rst + ')'
import sys
if __name__ == "__main__":
    sys.stdout.write("(print " + dwa() + ")")
