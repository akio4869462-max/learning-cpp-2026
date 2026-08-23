import numpy as np
import matplotlib.pyplot as plt

fs = 1000.0
t = np.arange(0, 1, 1 / fs)

# x = (1.0 * np.sin(2 * np.pi * 50 * t)
#      + 0.5 * np.sin(2 * np.pi * 120 * t)
#      + 0.3 * np.random.randn(len(t)))
x = np.sin(2 * np.pi * 900 * t)

X = np.fft.rfft(x)
freqs = np.fft.rfftfreq(len(x), 1 / fs)
amp = np.abs(X) / len(x) * 2

fig, (ax1, ax2) = plt.subplots(2, 1, figsize=(8,6))
ax1.plot(t[:200], x[:200])
ax1.set_title("Time domain (first 0.2 s)")
ax2.plot(freqs, amp)
ax2.set_title("Frequency domain (spectrum)")
ax2.set_xlabel("Frequency [Hz]")
plt.tight_layout()
plt.show()