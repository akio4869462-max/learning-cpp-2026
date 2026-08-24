import numpy as np
import matplotlib.pyplot as plt
from scipy.signal import butter, filtfilt, hilbert, find_peaks

def to_brightness(env, dynamic_range_db=60.0):
    env = env / (env.max() + 1e-12)          # 最大を1に正規化
    db = 20 * np.log10(env + 1e-12)          # dB化(0 dBが最大)
    db = np.clip(db, -dynamic_range_db, 0)   # 表示レンジ外を切り捨て
    return ((db + dynamic_range_db) / dynamic_range_db * 255).astype(np.uint8)

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

brightness = to_brightness(env, dynamic_range_db=90.0)

# plt.plot(t * 1e6, pulse_filtered)
# plt.plot(depth_cm, env_db)
# plt.plot(depth_cm, brightness)
# plt.xlabel("depth [cm]")
# plt.title("Hilbert RF signal with noise")
# plt.savefig("day17_bright_90db.png")

image = np.tile(brightness, (50, 1))  # 50回縦に複製
plt.imshow(image, cmap="gray", aspect="auto",
           extent=[depth_cm.min(), depth_cm.max(), 0, 1])
plt.xlabel("depth [cm]")
plt.savefig("day17_image.png")
