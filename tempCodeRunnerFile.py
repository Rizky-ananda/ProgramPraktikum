
    for sensor in expected_sensors
}

MAX_DATA = 10
TIMEOUT = 5   # detik tanpa data → tidak terbaca


# -------- MQTT CALLBACK --------
def on_connect(client, userdata, flags, rc):
    print("Terhubung ke broker:", rc)
    client.subscribe("DHT/#")


def on_message(client, userdata, msg):