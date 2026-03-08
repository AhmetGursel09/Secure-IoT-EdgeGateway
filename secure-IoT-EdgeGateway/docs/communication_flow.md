# Communication Flow

1. ADXL345 ivme verisini üretir.
2. STM32, I2C üzerinden sensör verisini okur.
3. STM32, biçimlendirilmiş verileri UART üzerinden ESP32'ye gönderir.
4. ESP32 Alınan verileri MQTT broker'ına yayınlar.