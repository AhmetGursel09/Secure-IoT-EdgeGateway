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

## Rapor 3 İlerlemesi

  Bu aşamada proje, donanım entegrasyon planlamasına odaklandı.
Aşamalı modüler bir prototipleme yaklaşımı tanımlandı, mevcut donanım bileşenleri değerlendirildi ve sistemin ilk fiziksel entegrasyon sırası belirlendi.
