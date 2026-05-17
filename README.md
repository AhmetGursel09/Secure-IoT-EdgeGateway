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

# Rapor 6 İlerleme Durumu

## Donanım Entegrasyon Durumu

Bu rapor döneminde Secure IoT Edge Gateway prototipinin donanımsal entegrasyon aşaması fiziksel bağlantı düzeyinde tamamlanmıştır.

Sistem bileşenleri 4WD Smart Car platformu üzerinde konumlandırılmış ve gerekli bağlantılar kurulmuştur. Proje bu aşamadan sonra yazılım geliştirme, haberleşme doğrulama, hareket testi ve temel güvenlik kontrolleri için hazır duruma getirilmiştir.

## Tamamlanan Donanım Bağlantıları

- STM32 NUCLEO-H753ZI ana kontrol birimi olarak konumlandırılmıştır.
- ESP32-POE-ISO-IND gateway ve kablosuz haberleşme birimi olarak konumlandırılmıştır.
- ADXL345 ivmeölçer sensörü STM32’ye I2C hattı üzerinden bağlanmıştır.
- ATECC608A authentication chip, SOIC-8 to DIP-8 adaptör kullanılarak sisteme dahil edilmiştir.
- SN65HVD233 CAN transceiver, SOIC-8 to DIP-8 adaptör kullanılarak sisteme dahil edilmiştir.
- L298N motor sürücü, 4WD Smart Car motorlarına bağlanmıştır.
- STM32 GPIO pinleri, L298N motor kontrol girişlerine bağlanmıştır.
- STM32 ile ESP32 arasındaki UART haberleşme hattı fiziksel olarak kurulmuştur.
- STM32, ESP32, L298N, breadboard, sensör ve yardımcı entegreler arasında ortak GND yapısı oluşturulmuştur.
- Breadboard üzerinde 3.3V ve GND güç dağıtım hatları düzenlenmiştir.

## Motor Sürücü Bağlantıları

L298N motor sürücü, 4WD Smart Car motor gruplarına bağlanmıştır.

- Sol motor grubu → OUT1 / OUT2
- Sağ motor grubu → OUT3 / OUT4
- L298N IN1 → STM32 D2
- L298N IN2 → STM32 D3
- L298N IN3 → STM32 D4
- L298N IN4 → STM32 D5

## Sensör ve I2C Bağlantıları

ADXL345 ivmeölçer sensörü, STM32’ye I2C haberleşme arayüzü üzerinden bağlanmıştır.

- ADXL345 VCC → 3.3V
- ADXL345 GND → GND
- ADXL345 CS → 3.3V
- ADXL345 SDA → STM32 SDA
- ADXL345 SCL → STM32 SCL
- ADXL345 SDO → SDO hattı

ATECC608A authentication chip de aynı I2C hattı üzerinden sisteme dahil edilmiştir.

- ATECC608A VCC → 3.3V
- ATECC608A GND → GND
- ATECC608A SDA → STM32 D14 / SDA
- ATECC608A SCL → STM32 D15 / SCL

## CAN Transceiver Bağlantıları

SN65HVD233 CAN transceiver, STM32’nin FDCAN pinlerine bağlanmıştır.

- SN65HVD233 VCC → 3.3V
- SN65HVD233 GND → GND
- SN65HVD233 TXD → STM32 PD1
- SN65HVD233 RXD → STM32 PD0

CANH ve CANL hatları, yazılım tarafında FDCAN yapılandırması tamamlandıktan sonra doğrulama aşamasında kullanılmak üzere ayrılmıştır.

## ESP32 Gateway Bağlantısı

ESP32 gateway kartı, STM32 ile UART haberleşmesi kuracak şekilde bağlanmıştır.

- ESP32 TX → STM32 D0 / RX
- ESP32 RX → STM32 D1 / TX
- ESP32 GND → Ortak GND

ESP32; Wi-Fi/MQTT haberleşmesi, OTA güncelleme değerlendirmesi ve gateway taraflı veri aktarımı için kullanılacaktır.

## Mevcut Durum

Bu aşamada donanım prototipi fiziksel bağlantı düzeyinde tamamlanmıştır.

Yazılım geliştirme ve doğrulama süreci çalışma videosuna kadar devam edecektir. Bundan sonraki geliştirme adımları; firmware uygulaması, haberleşme testleri, hareket kontrolü ve temel IoT güvenlik kontrollerine odaklanacaktır.

## Sonraki Geliştirme Adımları

- STM32 I2C üzerinden ADXL345 sensöründen gerçek ivme verisi okunması
- I2C adres taraması ile ADXL345 ve ATECC608A bileşenlerinin doğrulanması
- L298N için STM32 motor kontrol fonksiyonlarının geliştirilmesi
- 4WD Smart Car platformu üzerinde araç hareketinin test edilmesi
- STM32 ile ESP32 arasındaki UART haberleşmesinin doğrulanması
- ESP32 üzerinden MQTT ile sensör verisinin yayımlanması
- ESP32 OTA güncelleme mekanizmasının temel düzeyde değerlendirilmesi
- SN65HVD233 üzerinden CAN/FDCAN haberleşmesinin doğrulanması
- STM32 C firmware tarafında temel güvenli kodlama uygulamalarının yapılması
- ESP32 C++ firmware tarafında giriş doğrulama ve bağlantı kontrollerinin uygulanması
- Test sonuçlarının çalışma videosu için belgelenmesi

## Özet

Rapor 6, projenin donanımsal entegrasyondan yazılım geliştirme ve doğrulama aşamasına geçişini temsil etmektedir.

Fiziksel prototip tamamlanmış olup sistem; firmware geliştirme, hareket testi, haberleşme doğrulaması ve güvenlik değerlendirmeleri için hazır hale getirilmiştir.
