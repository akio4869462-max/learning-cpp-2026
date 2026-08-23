import numpy as np
import matplotlib.pyplot as plt
from scipy.signal import butter, filtfilt, hilbert, find_peaks

fs = 50e6
t = np.arange(0, 100e-6, 1 / fs)

pulse1 = np.exp(-((t - 13e-6) ** 2) / (2 * (0.3e-6) ** 2)) * np.sin(2 * np.pi * 5e6 * t)
pulse3 = np.exp(-((t - 39e-6) ** 2) / (2 * (0.3e-6) ** 2)) * np.sin(2 * np.pi * 5e6 * t)
pulse6 = np.exp(-((t - 78e-6) ** 2) / (2 * (0.3e-6) ** 2)) * np.sin(2 * np.pi * 5e6 * t)

pulse = pulse1 + 0.4 * pulse3 + 0.1 * pulse6

pulse += 0.03 * np.random.randn(len(t))

b,a = butter(4, [3e6 / (fs / 2), 7e6 / (fs / 2)], btype = "band")
pulse_filtered = filtfilt(b, a, pulse)

env = np.abs(hilbert(pulse_filtered))
depth_cm = t * 1540 / 2 * 100

env_tgc = env * (1.0 + 3 * depth_cm)
env_db = 20 * np.log10(env + 1e-12)

peaks, _ = find_peaks(env, height=0.09, distance=10)

print(depth_cm[peaks])

# plt.plot(t * 1e6, pulse_filtered)
plt.plot(depth_cm, env_db)
plt.xlabel("depth [cm]")
plt.title("Hilbert RF signal with noise")
plt.savefig("day14_hilbert_db.png")