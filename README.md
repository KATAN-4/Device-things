---

# Device-things

> ⚙️ Android device info checker, root detection, bootloader unlocking, and boot image flashing CLI tool.
> ⚙️ Android cihaz bilgisi kontrolü, root algılama, bootloader kilidini açma ve boot imajı flashlama için çok yönlü bir komut satırı aracı. 📱

---

## Overview / Genel Bakış

**Device-things** is a C++ CLI tool designed for Android developers and advanced users to easily view device info, check root status, manage bootloader status, and flash boot images via Fastboot. It includes special support for Xiaomi and Huawei devices. 🚀
**Device-things**, Android geliştiricileri ve ileri seviye kullanıcılar için cihaz bilgilerini kolayca görüntülemek, root durumunu kontrol etmek, bootloader durumunu yönetmek ve Fastboot kullanarak boot imajı flashlamak amacıyla geliştirilmiş C++ tabanlı bir CLI aracıdır. Xiaomi ve Huawei gibi üreticilere özel işlemlerle uyumluluk artırılmıştır. 🚀

---

## Key Features / Temel Özellikler

* 🔍 **Root Detection:** Detects root via `su`, `magisk`, and system file checks.
* 🔍 **Root Algılama:** `su`, `magisk` ve sistem dosyalarını kontrol ederek root durumunu tespit eder.
* 📟 **Device Info:** Shows brand, model, and codename.
* 📟 **Cihaz Bilgisi:** Marka, model ve kod adını görüntüler.
* 🔓 **Bootloader Management:** Checks and unlocks bootloader if requested.
* 🔓 **Bootloader Yönetimi:** Bootloader kilidinin açık olup olmadığını kontrol eder, istenirse kilidi açabilir.
* 🔥 **Flashing:** Allows flashing `boot.img` via Fastboot.
* 🔥 **Flashlama:** Fastboot üzerinden `boot.img` dosyası flashlama imkanı sunar.
* 🤖 **Vendor Support:** Special warnings and support for Xiaomi and Huawei devices.
* 🤖 **Üretici Desteği:** Xiaomi ve Huawei cihazlara özel uyarılar ve destek sağlar.

---

## System Requirements / Sistem Gereksinimleri

* 📥 **ADB and Fastboot:** Must be installed and accessible from the command line.
* 📥 **ADB ve Fastboot:** Komut satırından erişilebilir şekilde kurulu olmalıdır.
* 📱 **Android Device:** USB debugging enabled and connected via USB.
* 📱 **Android Cihaz:** USB hata ayıklama (debugging) açık ve USB ile bağlı olmalıdır.
* 💻 **Supported OS:** Linux (Debian-based) and Windows.
* 💻 **Desteklenen İşletim Sistemleri:** Linux (Debian tabanlı) ve Windows.

---

## Build & Usage / Derleme & Kullanım

### Linux

To build and run on Linux:
Linux sürümünü derlemek ve çalıştırmak için:

```bash
g++ main.cpp lang.cpp -o device-things
./device-things
```

### Windows

To build and run on Windows (using MinGW-w64 or similar):
Windows sürümünü MinGW-w64 veya benzeri derleyicilerle derlemek ve çalıştırmak için:

```bash
g++ win_main.cpp lang.cpp -o device-things.exe
device-things.exe
```

> ⚠️ Make sure `adb.exe` and `fastboot.exe` are in your PATH or in the executable’s directory on Windows.
> ⚠️ Windows’ta `adb.exe` ve `fastboot.exe` dosyalarının PATH ortam değişkeninde olduğundan veya yürütülebilir dosyanın bulunduğu klasörde yer aldığından emin olun.

---

## Language Support / Dil Desteği

Automatically selects language based on system language (`LANG` environment variable):
Uygulama sisteminizin dil ayarlarına (`LANG` çevre değişkeni) göre otomatik dil seçimi yapar:

* 🇹🇷 Turkish / Türkçe
* 🇬🇧 English / İngilizce

Translation files are located in `lang_tr.txt` and `lang_en.txt`.
Çeviri dosyaları `lang_tr.txt` ve `lang_en.txt` içinde bulunmaktadır.

---

## Important Warnings / Önemli Uyarılar

* 🔐 **Unlocking bootloader** will erase all user data. Backup important data.
* 🔐 **Bootloader Kilidini Açmak:** Bu işlem cihazdaki tüm kullanıcı verilerini silecektir. Önemli verilerinizi yedekleyin.
* ⚠️ **Flashing risks:** Flashing an incompatible or wrong `boot.img` can cause device malfunction or soft-brick. Use with caution.
* ⚠️ **Flashlama Riski:** Uyumsuz veya yanlış `boot.img` dosyasının flashlanması cihazda sorunlara veya soft-brick durumuna yol açabilir. Dikkatli olun.
* 📛 **Disclaimer:** Provided “as-is” without warranty. Use at your own risk.
* 📛 **Sorumluluk Reddi:** Yazılım “olduğu gibi” sağlanmaktadır. Kullanımı tamamen size ait olup oluşabilecek zararların sorumluluğu kullanıcıya aittir.

---

## Project Structure / Proje Yapısı

```
main.cpp           # Linux source code / Linux için kaynak kod  
win_main.cpp       # Windows source code / Windows için kaynak kod  
lang.cpp           # Language management implementation / Dil yönetimi uygulaması  
lang.h             # Language management header / Dil yönetimi başlık dosyası  
lang_en.txt        # English translations / İngilizce çeviri metinleri  
lang_tr.txt        # Turkish translations / Türkçe çeviri metinleri  
README.md          # Project documentation / Proje dokümantasyonu  
device-things      # Linux executable (optional) / Linux için derlenmiş çalıştırılabilir dosya (opsiyonel)  
device-things.exe  # Windows executable (optional) / Windows için derlenmiş çalıştırılabilir dosya (opsiyonel)  
```

---
