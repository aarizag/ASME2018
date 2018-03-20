import numpy as np
import matplotlib.pyplot as plt
import re

f = open("fullRotate.txt", "r")
x = []
y = []

for line in f:
    print(line)
    xIN = re.search(r'[0-9]+', line)
    yIN = re.search(r'[0-9]+', line[xIN.end():])
    x.append(int(xIN.group()))
    y.append(int(yIN.group()))


plt.scatter(x, y)
plt.show()
