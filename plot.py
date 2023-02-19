import numpy as np
import matplotlib.pyplot as plt



fin_name = "out.txt"
arr = np.loadtxt(fin_name)
plt.figure(figsize=(8,8))
plt.imshow(arr, cmap="gist_gray")
plt.title("display of density")
plt.savefig("im.jpg")
plt.show()