# -*- coding: utf-8 -*-
"""
Created on Thu Dec 12 16:31:09 2019

@author: Gille
"""

import numpy as np
import matplotlib.pyplot as plt
import pandas as pd 

import pyeit.mesh as mesh
from pyeit.eit.fem import Forward
from pyeit.eit.utils import eit_scan_lines
import pyeit.eit.bp as bp

def split_list(a_list):
    half = len(a_list)//2
    return a_list[:half], a_list[half:]

# traverse in the string   
def formatvalue(z):
    #First change list into string data
    str1 = ""  
    splitvalue = 0
    for ele in z:  
     str1 += ele 
    #Split the string on ':'
    splitvalue = str1.split(":")
    #Take value which is second in the list
    return(splitvalue[1:2])

def lookfor(f):
    #First change list into string data
    str1 = ""  
    splitvalue = 0
    for ele in f:  
     str1 += ele 
    #Split the string on ':'
    splitvalue = str1.split(":")
    #Take value which is second in the list
    print(splitvalue)
    if (splitvalue == '40000'):
        savedData.append(int(splitvalue))
        print(int(splitvalue))
        return

f = open('data.txt')

CurrentCycle = []
VoltCycle = []
Frequency = []
Impedance = []
Magnitude = []

savedData = []

for line in f:
  fields = line.split(",")
  #and let's extract the data:
  CurrentCycle.append(formatvalue(fields[0:1]))
  VoltCycle.append(formatvalue(fields[1:2]))
  Frequency.append(formatvalue(fields[2:3]))
  Impedance.append(formatvalue(fields[3:4]))
  Magnitude.append(formatvalue(fields[4:5]))
f.close()

'''
print (CurrentCycle)
print (VoltCycle)
print (Frequency)
print (Impedance)
print (Magnitude)
'''

print (type(CurrentCycle))

Ordered_list = pd.DataFrame(
    {'CurrentProbe': CurrentCycle,
     'VoltProbe': VoltCycle,
     'Frequency': Frequency,
     'Impedance': Impedance,    
     'Magnitude': Magnitude,
    })

Ordered_list.dropna
Ordered_list.dropna(axis='columns')
Ordered_list.drop([0, 1])
print(Ordered_list.iloc[0:1])
Ordered_list['CurrentProbe'] = pd.to_numeric(Ordered_list['CurrentProbe'])


print(Ordered_list[Ordered_list.Magnitude != '-nan'])
#print(type(Ordered_list.iloc[0, 2]))

loop = 0
for match in Ordered_list.iterrows():
    Specific = lookfor(Ordered_list.iloc[loop, 2])
    loop= loop+1
    
print(type(savedData))
print(savedData)
 

