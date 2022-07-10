#!/usr/bin/env python3

import math
import sys

filename = sys.argv[1]

with open(filename, "rb") as file:
    pos = 0
    for byte in file.read():  # read in chunks for large files
        print(f"{byte:#0{4}x}", ", ", sep='', end='')
        pos += 1
        if pos % 30 == 0:
            print("")
