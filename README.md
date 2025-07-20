# 🚗 Vehicle Dashboard Monitoring System using LPC1768

This embedded systems project simulates a basic **vehicle dashboard** using an **LPC1768 microcontroller**. It monitors vehicle speed and engine temperature using ADCs, displays data on an LCD and 7-segment display, and alerts the driver for over-speeding using a buzzer.

---

## 🛠️ Features

- 📈 **Speed Monitoring** via ADC0 (simulating accelerator input)
- 🌡️ **Engine Temperature Monitoring** via ADC1
- 📺 **LCD Display** showing current speed
- 🔢 **7-Segment Display** (via SPI) showing engine temperature
- 🎯 **Speed Alerts**:
  -> Over 80 kmph: Quick warning beep
  -> Over 120 kmph: Continuous over-speeding warning
- 🔊 **Buzzer Alerts** for safety
- ⚙️ Peripheral integration: ADC, SPI, PWM, LCD, GPIO, Timer

---

## 🔧 Hardware & Tools

- **Microcontroller**: LPC1768 (ARM Cortex-M3)
- **LCD 16x2 Display**
- **7-Segment Display** (SPI controlled)
- **Buzzer**
- **Analog sensors or variable potentiometer** (for simulating speed and temperature)
- **Keil uVision** / **Flash Magic**

---

## 🔄 How It Works

1. **Initialize peripherals**: ADC, SPI, LCD, PWM, Timer.
2. **Read accelerator input** via ADC0.
3. **Convert speed to PWM signal** and send to motor logic.
4. **Read engine temperature** using ADC1.
5. **Display data** on LCD and 7-segment.
6. **Trigger alerts** using buzzer based on speed thresholds.

---
