import numpy as np
import matplotlib.pyplot as plt

f_signal = 9.0
fs_low = 12.0

t_fine = np.linspace(0, 1, 1000)
t_samp = np.arange(0, 1, 1 / fs_low)

plt.plot(t_fine, np.sin(2 * np.pi * f_signal * t_fine), label="true 9 Hz signal")

plt.plot(t_samp, np.sin(2 * np.pi * f_signal * t_samp), "o-", label="sampled at 10 Hz")

plt.legend()
plt.title("Aliasing: 9 Hz disguised as 1 Hz")
plt.show()