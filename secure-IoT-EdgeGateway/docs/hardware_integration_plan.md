# Donanım Entegre Planı

## Genel İnceleme
Bu aşama, modüler güvenli edge gateway prototipi için aşamalı donanım entegrasyonu planlamasına odaklanmaktadır.

## Entegrasyon Yaklaşımı
Sistem, tüm donanım modüllerinin aynı anda birleştirilmesi yerine, adım adım entegre edilecek şekilde planlanmıştır.

## Bu Aşamada Olan Bileşenler 
- STM32 NUCLEO-H753ZI
- ESP32-POE-ISO-IND
- ADXL345 sensor module
- ATECC608A security component
- SN65HVD233 CAN communication component
- Breadboard
- Jumper wires
- USB cables
- 120Ω resistors

## Donanım entegre sırası 
1. STM32 board validation
2. Sensor connection preparation
3. STM32 to ESP32 UART connection planning
4. Gateway-side communication preparation
5. End-to-end modular integration

## Sonuç
Proje için aşamalı bir donanım entegrasyon yol haritası belirlenmiştir.
