import paho.mqtt.client as mqtt
import tkinter as tk
from threading import Thread
import time

# -----------------------------
#   DAFTAR 15 SENSOR
# -----------------------------
expected_sensors = [f"DHT/{i:02d}" for i in range(1, 16)]  # DHT/01 - DHT/15

# Data penyimpanan
data_sensors = {
    sensor: {"suhu": [], "rh": [], "last_update": 0}
    for sensor in expected_sensors
}

MAX_DATA = 10
TIMEOUT = 5   # detik tanpa data → tidak terbaca


# -------- MQTT CALLBACK --------
def on_connect(client, userdata, flags, rc):
    print("Terhubung ke broker:", rc)
    client.subscribe("DHT/#")


def on_message(client, userdata, msg):
    topic = msg.topic
    payload = msg.payload.decode("utf-8")

    if topic not in expected_sensors:
        return

    try:
        bagian = payload.split(", ")
        suhu = float(bagian[0].split(":")[1])
        rh = float(bagian[1].split(":")[1])

        if suhu <= 0 or suhu > 100:
            return

        d = data_sensors[topic]
        d["suhu"].append(suhu)
        d["rh"].append(rh)
        d["last_update"] = time.time()

        if len(d["suhu"]) > MAX_DATA:
            d["suhu"].pop(0)
        if len(d["rh"]) > MAX_DATA:
            d["rh"].pop(0)

    except:
        print("Format payload tidak sesuai.")


# -------- FUNGSI PEMBANTU --------
def hitung_rata(data):
    return sum(data) / len(data) if data else None


def update_terminal_output():
    line = ""

    for sensor in expected_sensors:
        d = data_sensors[sensor]

        if time.time() - d["last_update"] > TIMEOUT:
            line += f"{sensor}: - | "
        else:
            suhu_avg = hitung_rata(d["suhu"])
            rh_avg = hitung_rata(d["rh"])
            line += f"{sensor}: Suhu {suhu_avg:.1f}°C, RH {rh_avg:.1f}% | "

    print(line)


# -------- UPDATE UI TKINTER --------
def update_ui_labels():
    for sensor in expected_sensors:
        d = data_sensors[sensor]
        elapsed = time.time() - d["last_update"]

        if elapsed > TIMEOUT:
            label_suhu[sensor].config(text="Suhu : Tidak terbaca")
            label_rh[sensor].config(text="RH   : Tidak terbaca")
        else:
            suhu_avg = hitung_rata(d["suhu"])
            rh_avg = hitung_rata(d["rh"])
            label_suhu[sensor].config(text=f"Suhu : {suhu_avg:.1f} °C")
            label_rh[sensor].config(text=f"RH   : {rh_avg:.1f} %")


def loop_checker():
    update_ui_labels()
    update_terminal_output()
    root.after(1000, loop_checker)


# -------- MQTT THREAD --------
def mqtt_loop():
    client = mqtt.Client()
    client.on_connect = on_connect
    client.on_message = on_message
    client.connect("192.168.2.211", 1883, 60)
    client.loop_forever()


# -------- TKINTER UI --------
root = tk.Tk()
root.title("Monitoring 15 Sensor DHT")

frame_main = tk.Frame(root)
frame_main.pack(padx=20, pady=20)

label_suhu = {}
label_rh = {}

# -----------------------------
#  GRID 5 kolom × 3 baris
# -----------------------------
for index, sensor in enumerate(expected_sensors):

    row = index // 5   # 0–2
    col = index % 5    # 0–4

    frame = tk.Frame(frame_main, padx=20, pady=10)
    frame.grid(row=row, column=col)

    tk.Label(frame, text=sensor, font=("Helvetica", 16, "bold")).pack()

    label_suhu[sensor] = tk.Label(frame, text="Suhu : -", font=("Helvetica", 12))
    label_suhu[sensor].pack(anchor="w")

    label_rh[sensor] = tk.Label(frame, text="RH   : -", font=("Helvetica", 12))
    label_rh[sensor].pack(anchor="w")

# Jalankan MQTT
thread = Thread(target=mqtt_loop)
thread.daemon = True
thread.start()

# Mulai loop UI
root.after(1000, loop_checker)
root.mainloop()