#include <WiFi.h>
#include <WebServer.h>
#include "mbedtls/md.h"     // Donanimsal HMAC-SHA256 Kutuphanesi

// Ag Gecidi Yapilandirmasi
const char* AP_SSID = "SiberArac";
const char* AP_PASS = "guvenlik123";          // WPA2 Guvenlik Sifresi

#define UART_TX 33
#define UART_RX 32
HardwareSerial LinkSerial(1);
WebServer server(80);

// 256-bit Paylasilan Gizli Anahtar (Sistemin Kalbi - Sadece ESP32 ve STM32 bilir)
static const uint8_t SHARED_KEY[32] = {
  0x4a,0x1f,0x9c,0x07,0x33,0xb2,0x58,0xe1, 0x6d,0x90,0xaa,0x12,0x77,0xc4,0x3e,0x8b,
  0x05,0xd9,0x21,0x64,0xfe,0x47,0x88,0x1a, 0xb3,0x0c,0x55,0x99,0x2d,0xe6,0x70,0xf2
};

// Monoton Artan Paket Sayaci (Replay saldirilarini engellemek icin)
uint32_t sayac = 0;

// Mbedtls Kutuphanesi ile Donanimsal HMAC Uretimi
void hmac_sha256(const uint8_t* data, size_t len, uint8_t out[32]) {
  const mbedtls_md_info_t* info = mbedtls_md_info_from_type(MBEDTLS_MD_SHA256);
  mbedtls_md_context_t ctx; mbedtls_md_init(&ctx);
  mbedtls_md_setup(&ctx, info, 1);
  mbedtls_md_hmac_starts(&ctx, SHARED_KEY, 32);
  mbedtls_md_hmac_update(&ctx, data, len);
  mbedtls_md_hmac_finish(&ctx, out);
  mbedtls_md_free(&ctx);
}

// Komutu paketler, imzalar ve UART uzerinden STM32'ye güvenli şekilde iletir.
// Paket Formatı: [Komut (1 Byte)] + [Sayac (4 Byte LE)] + [HMAC Tag (4 Byte)]
void guvenliKomutGonder(char komut) {
  sayac++;
  uint8_t veri[5];
  veri[0] = (uint8_t)komut;
  
  // Sayaci 4 Byte Little-Endian formatina cevirme
  veri[1] =  sayac        & 0xFF;
  veri[2] = (sayac >> 8)  & 0xFF;
  veri[3] = (sayac >> 16) & 0xFF;
  veri[4] = (sayac >> 24) & 0xFF;

  uint8_t tag[32];
  hmac_sha256(veri, 5, tag);        // Veriyi gizli anahtar ile imzala

  // STM32'ye veriyi ve imzanin ilk 4 byte'ini (Tag) gonder
  LinkSerial.write(veri, 5);
  LinkSerial.write(tag, 4);

  
  Serial.printf("Komut '%c' imzalandi (sayac=%u), tag=%02X%02X%02X%02X gonderildi\n",
                komut, sayac, tag[0], tag[1], tag[2], tag[3]);
}

// Siber Arac Web Kontrol Arayuzu (HTML/CSS)
const char* PAGE =
  "<!DOCTYPE html><html><head><meta charset='utf-8'>"
  "<meta name='viewport' content='width=device-width,initial-scale=1'>"
  "<style>body{font-family:sans-serif;text-align:center;background:#111;color:#eee;margin-top:20px}"
  "button{font-size:22px;width:120px;height:70px;margin:6px;border:none;border-radius:12px;background:#2a8a5a;color:#fff}"
  ".stop{background:#c0392b}</style></head><body><h2>Siber Arac Kontrol</h2>"
  "<div><button onclick=\"fetch('/F')\">Ileri</button></div>"
  "<div><button onclick=\"fetch('/L')\">Sol</button>"
  "<button class='stop' onclick=\"fetch('/S')\">DUR</button>"
  "<button onclick=\"fetch('/R')\">Sag</button></div>"
  "<div><button onclick=\"fetch('/B')\">Geri</button></div></body></html>";

void setup() {
  Serial.begin(115200);
  LinkSerial.begin(115200, SERIAL_8N1, UART_RX, UART_TX);
  
  // Guvenli Wi-Fi Agi Olusturma
  WiFi.mode(WIFI_AP);
  WiFi.softAP(AP_SSID, AP_PASS);
  Serial.print("Ag Gecidi Aktif. IP Adresi: "); Serial.println(WiFi.softAPIP());

  // Web Sunucusu Yonlendirmeleri ve Komut Tetikleyicileri
  server.on("/",  [](){ server.send(200,"text/html",PAGE); });
  server.on("/F", [](){ guvenliKomutGonder('F'); server.send(200,"text/plain","ileri"); });
  server.on("/B", [](){ guvenliKomutGonder('B'); server.send(200,"text/plain","geri"); });
  server.on("/L", [](){ guvenliKomutGonder('L'); server.send(200,"text/plain","sol"); });
  server.on("/R", [](){ guvenliKomutGonder('R'); server.send(200,"text/plain","sag"); });
  server.on("/S", [](){ guvenliKomutGonder('S'); server.send(200,"text/plain","dur"); });
  
  server.begin();
  Serial.println("Sistem Hazir. Cihazlari 'SiberArac' agina baglayabilirsiniz.");
}

void loop() { 
  server.handleClient(); // Gelen web isteklerini dinle
}