import numpy as np
import matplotlib.pyplot as plt
from scipy.signal import butter, filtfilt, hilbert

fs = 50e6
t = np.arange(0, 100e-6, 1 / fs)

def pulse(t, tc, amp, f0=5e6, sigma=0.15e-6):
    return amp * np.exp(-(t - tc) ** 2 / (2 * sigma ** 2)) * np.sin(2 * np.pi * f0 * t)

def to_brightness(env, dynamic_range_db=60.0):
    env = env / (env.max() + 1e-12)          # 最大を1に正規化
    db = 20 * np.log10(env + 1e-12)          # dB化(0 dBが最大)
    db = np.clip(db, -dynamic_range_db, 0)   # 表示レンジ外を切り捨て
    return ((db + dynamic_range_db) / dynamic_range_db * 255).astype(np.uint8)

targets = [
    (10, 1.0, 1.0),
    (20, 2.5, 0.8),
    (23, 2.5, 0.8),
    (32, 4.0, 0.6),
    (32, 4.03, 0.6),
    (45, 6.0, 0.4),
    (55, 7.0, 0.3),
]

image = np.zeros((len(t), 64))

b,a = butter(4, [3e6 / (fs / 2), 7e6 / (fs / 2)], btype = "band")
depth_cm = t * 1540 / 2 * 100

for line in range(64):
    rf = 0.03 * np.random.randn(len(t))

    for(tl, depth, amp) in targets:
        if(abs(tl - line) <= 1):
            tc = 2 * (depth / 100) / 1540
            rf += pulse(t, tc, amp)

    pulse_filtered = filtfilt(b, a, rf)

    env = np.abs(hilbert(pulse_filtered))
    env_tgc = env * (1.0 + 3 * depth_cm)

    image[:, line] = env_tgc

brightness_image = to_brightness(image, dynamic_range_db=30.0)

plt.imshow(brightness_image, cmap="gray", aspect="auto",
           extent=[0, 64, depth_cm.max(), 0])
plt.xlabel("scan line")
plt.ylabel("depth [cm]")
plt.savefig("day20_image_30db.png")