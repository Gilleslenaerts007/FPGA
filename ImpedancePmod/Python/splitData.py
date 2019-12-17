# -*- coding: utf-8 -*-
"""
Created on Thu Dec 12 16:31:09 2019

@author: Gille
"""

import numpy as np
import matplotlib.pyplot as plt
import pandas as pd 

'''
import pyeit.mesh as mesh
from pyeit.eit.fem import Forward
from pyeit.eit.utils import eit_scan_lines
import pyeit.eit.bp as bp
'''

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

f = open('dataRcal.txt') #dataRcal for Example

Frequency = []
Impedance = []
Magnitude = []

savedData = []

for line in f:
  fields = line.split(",")
  #and let's extract the data:
  if (fields[0] != '\n'):
      Frequency.append(formatvalue(fields[0:1]))
      Impedance.append(formatvalue(fields[1:2]))
      Magnitude.append(formatvalue(fields[2:3]))
f.close()

Ordered_list = pd.DataFrame(
    {'Frequency': Frequency,
     'Impedance': Impedance,    
     'Magnitude': Magnitude,
    })

#Change values from list to string
Ordered_list.dropna
print(Ordered_list.head())
print (type(Ordered_list.loc[0, 'Frequency']))
Ordered_list['Frequency'] = Ordered_list['Frequency'].str.get(0)
Ordered_list['Impedance'] = Ordered_list['Impedance'].str.get(0) 
Ordered_list['Magnitude'] = Ordered_list['Magnitude'].str.get(0)

Ordered_list['Frequency'] = Ordered_list['Frequency'].astype(int)
Ordered_list['Impedance'] = Ordered_list['Impedance'].astype(int)
Ordered_list['Magnitude'] = Ordered_list['Magnitude'].astype(float)

print(Ordered_list.head())
ax = plt.gca()
Ordered_list.plot(kind='line',x='Frequency',y='Impedance',ax=ax)
Ordered_list.plot(kind='line',x='Frequency',y='Magnitude', color='red', ax=ax)
plt.show()

c1 = Ordered_list.loc[:,'Frequency']
c2 = Ordered_list.loc[:,'Impedance']
fig = plt.figure()
ax = fig.add_subplot(111)

plt.plot(c1,c2,'k--')
plt.yscale('log')
plt.grid(True,which="both")
plt.xlabel(r"Scattering Angle $\Theta$ ($^\circ$)")
plt.ylabel(r"$P_{11}$")
plt.show()



