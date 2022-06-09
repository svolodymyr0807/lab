#!/usr/bin/python3
import numpy as np
import sys
if len(sys.argv)!=2:
 N = int(input('Size of matrinx'))
else:
 N = int(sys.argv[1])
arr = 1 + 4*np.random.rand(N,N+1, 1, 15)
arr.tofile(f'array_{N}x{N}.txt',sep=' ')