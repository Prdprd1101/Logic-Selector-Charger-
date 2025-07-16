import serial
import matplotlib.pyplot as plt
import matplotlib.animation as animation
from collections import deque

# ตั้งค่า Serial
ser = serial.Serial('COM6', 115200, timeout=1)

# เตรียม buffer เก็บข้อมูล
max_len = 500    # เริ่มจาก 500 จุด เพื่อดูว่าแสดงผลได้ก่อน
data = deque([0]*max_len, maxlen=max_len)

# สร้างกราฟ
fig, ax = plt.subplots()
line, = ax.plot(data)
ax.set_ylim(0, 1023)        # ค่าดิบ analog (0–1023)
ax.set_title("Real-Time Serial Plot")
ax.set_xlabel("Samples")
ax.set_ylabel("Analog Value")

# ฟังก์ชันอัปเดตกราฟ
def update(frame):
    try:
        line_raw = ser.readline().decode('utf-8').strip()
        if line_raw:
            value = int(line_raw)
            data.append(value)
            line.set_ydata(data)
            line.set_xdata(range(len(data)))
            ax.set_xlim(0, max_len)
            print(f"Value: {value}")
    except ValueError:
        pass
    return line,

# วาดกราฟ
ani = animation.FuncAnimation(fig, update, interval=1)
plt.show()

ser.close()
