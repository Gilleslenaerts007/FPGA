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
    savedData= []
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
def makeDF(pandaFrame, filetoread):
    Frequency = []
    Impedance = []
    #Magnitude = []
    for line in filetoread:
       fields = line.split(",")
       #and let's extract the data:
       #print(fields)
       if (fields[0] != '\n'):
          Frequency.append(formatvalue(fields[0:1]))
          Impedance.append(formatvalue(fields[1:2]))
         #Magnitude.append(formatvalue(fields[2:3]))
    filetoread.close()
    pandaFrame = pd.DataFrame(
    {'Frequency': Frequency,
     'Impedance': Impedance,    
    # 'Magnitude': Magnitude,
    })
    pandaFrame.dropna
    pandaFrame['Frequency'] = pandaFrame['Frequency'].str.get(0)
    pandaFrame['Impedance'] = pandaFrame['Impedance'].str.get(0) 
    #Ordered_list['Magnitude'] = Ordered_list['Magnitude'].str.get(0)  
    pandaFrame['Frequency'] = pandaFrame['Frequency'].astype(int)
    pandaFrame['Impedance'] = pandaFrame['Impedance'].astype(int)
    #Ordered_list['Magnitude'] = Ordered_list['Magnitude'].astype(float)
    return pandaFrame

#MAIN
f1 = open('dataRcal1.txt')
f2 = open('dataRcal2.txt')
f3 = open('dataRcal3.txt')

df1 = pd.DataFrame
df2 = pd.DataFrame
df3 = pd.DataFrame

df1 = makeDF(df1,f1)
df2 = makeDF(df2,f2)
df3 = makeDF(df3,f3)
print("Rcal1 table")
print(df1.head())
print("Rcal2 table")
print(df2.head())
print("Rcal3 table")
print(df3.head())

dfplot= pd.DataFrame
dfplot= pd.DataFrame(
        {'Frequency': df1['Frequency'],
         'Rcal1':df1['Impedance'],
         'Rcal2':df2['Impedance'],
         'Rcal3':df3['Impedance'],
                })

print(dfplot.head())

#Plot data
plt.xlabel("Frequency")
plt.ylabel('Impedance')

from matplotlib.ticker import NullFormatter  # useful for `logit` scale
ax = plt.gca()
dfplot.plot(kind='line',x='Frequency',y='Rcal1',ax=ax, grid = True)
dfplot.plot(kind='line',x='Frequency',y='Rcal2',ax=ax, grid = True)
dfplot.plot(kind='line',x='Frequency',y='Rcal3',ax=ax, grid = True)

c1 = dfplot.loc[:,'Frequency']
c2 = dfplot.loc[:,'Rcal1']
c3 = dfplot.loc[:,'Rcal2']
c4 = dfplot.loc[:,'Rcal3']


plt.show()


