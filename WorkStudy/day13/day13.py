import numpy as np
import matplotlib.pyplot as plt

fs = 1000.0
t = np.arange(0, 1, 1 / fs)
clean = np.sin(2 * np.pi * 5 * t)
noisy = clean + 0.5 * np.random.randn(len(t))

N = 21
kernel = np.ones(N) / N
filtered = np.convolve(noisy, kernel, mode="same")

plt.plot(t, noisy, alpha=0.4, label="noisy")
plt.plot(t, filtered, label="moving average (N=21)")
plt.plot(t, clean, "--", label="true")
plt.legend()
plt.show()