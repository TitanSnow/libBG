#!/usr/bin/env python
from runner import get_total_time,Runner
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
