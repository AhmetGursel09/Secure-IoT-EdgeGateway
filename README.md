# Secure-IoT-EdgeGateway

  Bu repo, endüstriyel IoT veri toplama ve güvenli bulut iletişimi için tasarlanmış modüler bir güvenli uç ağ geçidi prototipinin ürün yazılımını ve dokümantasyonunu içermektedir.

## Sisteme Genel Bakış

Sistem mimarisi içerir:

- STM32H753ZI için sensör verisi toplama ve gerçek zamanlı işleme
- ESP32-POE-ISO-IND için ağ geçidi, ağ iletişimi ve MQTT/TLS
- ADXL345 için titreşim verilerinin toplanması 
- SN65HVD233 için CAN veri yolu fiziksel katman iletişimi 
- ATECC608A donanım tabanlı kriptografik kimlik ve anahtar koruması için

## Repository Yapısı

- `stm32-firmware/` : STM32 sensör ve haberleşme firmware
- `esp32-gateway/` : ESP32 gateway yazılımı
- `docs/` : Mimari ve Geliştirme Notları

## Rapor 5 İlerlemesi

Bu aşamada soic8 to dip8 adaptör, montajı bitmemiş smart car 4wd ve L298 motor temin edildi. IoT Hardening ve güvenli kod yazımı üzerinde duruldu.  
