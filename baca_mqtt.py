import paho.mqtt.client as mqtt
import tkinter as tk
from threading import Thread

# Variabel global untuk menyimpan data sensor
suhu_data = []
rh_data = []

# Fungsi untuk menghitung rata-rata
def hitung_rata_rata(data):
    return sum(data) / len(data) if data else 0

# Callback ketika terhubung ke broker
def on_connect(client, userdata, flags, rc):
    print("Terhubung ke broker MQTT dengan kode hasil:", rc)
    client.subscribe("DHT/#")  # Berlangganan ke semua topik DHT/yyy

# Callback ketika menerima pesan dari broker
def on_message(client, userdata, msg):
    payload = msg.payload.decode("utf-8")
    print(f"Pesan diterima di {msg.topic}: {payload}") 
    # print(payload.split(", ")[1].split(":")[1])

    # Parsing data suhu dan RH
    if "Suhu" in payload and "RH" in payload:
        try:
            suhu_val = float(payload.split(", ")[0].split(":")[1])
            rh_val = float(payload.split(", ")[1].split(":")[1])
            if(suhu_val <= 20 or suhu_val == 'nan' or rh_val == 'nan'):
                print("Format pesan tidak sesuai.")
                return
            suhu_data.append(suhu_val)
            rh_data.append(rh_val)

            # Batasi jumlah data yang disimpan
            if len(suhu_data) > 10:
                suhu_data.pop(0)
            if len(rh_data) > 10:
                rh_data.pop(0)

            update_ui()
        except ValueError:
            print("Format pesan tidak sesuai.")

# Fungsi untuk memperbarui UI dengan data rata-rata
def update_ui():
    rata_suhu = hitung_rata_rata(suhu_data)
    rata_rh = hitung_rata_rata(rh_data)
    label_suhu.config(text=f"Rata-rata Suhu: {rata_suhu:.2f} °C")
    label_rh.config(text=f"Rata-rata RH: {rata_rh:.2f} %")

# Fungsi untuk menjalankan client MQTT
def mqtt_loop():
    client = mqtt.Client()
    client.on_connect = on_connect
    client.on_message = on_message
    client.connect("192.168.1.211", 1883, 60)
    client.loop_forever()

# Setup UI menggunakan tkinter
root = tk.Tk()
root.title("Pemantauan Suhu dan RH")

label_suhu = tk.Label(root, text="Rata-rata Suhu: - °C", font=("Helvetica", 16))
label_suhu.pack(pady=10)

label_rh = tk.Label(root, text="Rata-rata RH: - %", font=("Helvetica", 16))
label_rh.pack(pady=10)

# Jalankan MQTT client di thread terpisah
thread = Thread(target=mqtt_loop)
thread.daemon = True
thread.start()

# Jalankan aplikasi UI
root.mainloop()
