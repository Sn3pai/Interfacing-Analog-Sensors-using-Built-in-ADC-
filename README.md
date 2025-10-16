Got it — here’s a **short, portfolio-style GitHub README** version that’s perfect for showcasing your project 👇

---

# 🌡️ Interfacing Analog Sensors using Built-in ADC

This project demonstrates how to interface an **LM35 temperature sensor** with an **ATmega328P** microcontroller using its **built-in ADC**.
The analog output from the LM35 is converted to a digital value and displayed on a **serial terminal** via **UART** at **115200 baud rate**.
It accurately measures temperatures from **0 °C to +150 °C**.

---

### ⚙️ Features

* Reads analog temperature data using ADC
* Displays live temperature readings over UART
* Supports negative and positive temperatures
* Compact and efficient embedded C/C++ code

---

### 🧩 Components

* ATmega328P
* LM35 Temperature Sensor
* Virtual Terminal / Serial Monitor
* 5 V DC Power Supply

---

### 🧱 Files

| File             | Description                                                       |
| ---------------- | ----------------------------------------------------------------- |
| `main.cpp`       | Initializes ADC and UART, reads LM35 data, and prints temperature |
| `debug_prints.c` | Contains UART and ADC driver functions                            |

---

### 🖥️ Working

1. The LM35 outputs an analog voltage proportional to the temperature (10 mV / °C).
2. The ATmega328P reads the analog value via its ADC.
3. The temperature is calculated and sent to the serial terminal.
4. The result updates live as the sensor temperature changes.

---

### 📡 Formula Used

```
Temperature (°C) = ((ADC_value * 5.0) / 1024.0) * 100
```

---


