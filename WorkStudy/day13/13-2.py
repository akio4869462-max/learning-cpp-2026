from scipy.signal import hilbert
import numpy as np
import matplotlib.pyplot as plt

fs = 50e6
t = np.arange(0, 4e-6, 1 / fs)
# clean = np.sin(2 * np.pi * 5 * t)
pulse1 = np.exp(-((t - 1.7e-6) ** 2) / (2 * (0.3e-6) ** 2)) * np.sin(2 * np.pi * 5e6 * t)
# pulse2 = np.exp(-((t - 2e-6) ** 2) / (2 * (0.3e-6) ** 2)) * np.sin(2 * np.pi * 5e6 * t)
pulse3 = np.exp(-((t - 2.3e-6) ** 2) / (2 * (0.3e-6) ** 2)) * np.sin(2 * np.pi * 5e6 * t)
pulse = pulse1 + pulse3

env = np.abs(hilbert(pulse))

plt.plot(t * 1e6, pulse, label="RF echo(5 MHz)")
plt.plot(t * 1e6, env, "r", lw=2, label="envelope")
plt.xlabel("time [us]")
plt.legend()
plt.show()