# coding: utf-8
""" demo code for back-projection """
# Copyright (c) Benyuan Liu. All Rights Reserved.
# Distributed under the (new) BSD License. See LICENSE.txt for more info.
from __future__ import division, absolute_import, print_function

import numpy as np
import matplotlib.pyplot as plt

import pyeit.mesh as mesh
from pyeit.eit.fem import Forward
from pyeit.eit.utils import eit_scan_lines
import pyeit.eit.bp as bp

def split_list(a_list):
    half = len(a_list)//2
    return a_list[:half], a_list[half:]

f = open('data.txt')
datalist = [][]

for line in f:
    print(line)
    
f.close()

