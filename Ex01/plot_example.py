# OS 24 EX1
import pandas as pd
import matplotlib.pyplot as plt

data = pd.read_csv(r"C:\Users\Amit Joseph\Desktop\Programming_Courses\Os\Ex01\graphs\r2.csv")
data = data.to_numpy()

l1_size = (128*1024)/4
l2_size = (1024*1024)/4
l3_size = (6*1024*1024)

plt.plot(data[:, 0], data[:, 1], label="Random access")
plt.plot(data[:, 0], data[:, 2], label="Sequential access")
plt.xscale('log')
# plt.yscale('log')
plt.yscale('linear')
plt.axvline(x=l1_size, label="L1 (32 KiB) per Core", c='r')
plt.axvline(x=l2_size, label="L2 (256 KiB) per Core", c='g')
plt.axvline(x=l3_size, label="L3 (6 MiB)", c='brown')
plt.legend()
plt.title("Latency as a function of array size\n Intel (R) Core(TM) i5-7500 CPU @ 3.4GHz\n Debian 11")
plt.ylabel("Latency (ns linear scale)")
plt.xlabel("Bytes allocated (log scale)")
plt.show()
