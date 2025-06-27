
markdown
# Device-things

> ⚙️ A tool to check Android device info, root status, and optionally unlock bootloader + flash boot image.  
> 📱 Android cihaz bilgilerini kontrol eden, root durumunu algılayan ve isteğe bağlı olarak bootloader kilidini açıp boot.img flashlayan bir araç.

---

## 📋 Description / Açıklama
**English**  
C++ CLI tool for Android device diagnostics and fastboot automation. Detects root status, shows device info, and handles bootloader operations.

**Türkçe**  
Android cihaz tanılama ve fastboot otomasyonu için C++ terminal aracı. Root durumunu tespit eder, cihaz bilgilerini gösterir ve bootloader işlemlerini yönetir.

---

## ✅ Features / Özellikler
**English**  
- Detects root access (`su`, `magisk`, binaries)
- Shows device brand/model/codename
- Checks bootloader unlock status
- Unlocks bootloader (optional)
- Flashes boot images (optional)
- Auto-detects system language

**Türkçe**  
- Root erişimini tespit eder (`su`, `magisk`, binary'ler)
- Cihaz marka/model/kod adı gösterir
- Bootloader kilitsizlik durumunu kontrol eder
- Bootloader kilidini açar (isteğe bağlı)
- Boot imajlarını flashlar (isteğe bağlı)
- Sistem dilini otomatik algılar

---

## 🛠 Requirements / Gereksinimler
**English**  
- Linux OS (Debian-based tested)
- `adb` and `fastboot` installed
- USB debugging enabled
- Android device connected

**Türkçe**  
- Linux işletim sistemi (Debian tabanlı test edildi)
- `adb` ve `fastboot` kurulu olmalı
- USB hata ayıklama etkinleştirilmeli
- Android cihaz bağlı olmalı

---

## 🚀 Usage / Kullanım
```bash
# Both languages / Her iki dil
g++ main.cpp -o device-things
./device-things
```

---

## ⚠️ Warnings / Uyarılar
**English**  
- Unlocking bootloader ERASES ALL DATA!
- Incorrect flashing may brick device
- Use at your own risk
- Backup critical data first

**Türkçe**  
- Bootloader'ı açmak TÜM VERİLERİ SİLER!
- Yanlış flashlama cihazı bozabilir
- Kullanım kullanıcı sorumluluğundadır
- Önemli verileri yedekleyin

---

## 🌐 Language Support / Dil Desteği
**English**  
- Automatically switches based on system `LANG`
- Supports English (en) and Turkish (tr)
- Contribute translations via GitHub

**Türkçe**  
- Sistem `LANG` değişkenine göre otomatik seçer
- İngilizce (en) ve Türkçe (tr) destekler
- Çeviriler için GitHub'dan katkı yapabilirsiniz

---

## 📂 Project Structure / Proje Yapısı
```
.
├── main.cpp          // Main logic / Ana mantık
├── lang.h            // Language manager / Dil yöneticisi
├── README.md         // This document / Bu belge
└── LICENSE           // Usage terms / Kullanım şartları
```

---

## ❓ FAQ / SSS
**English**  
Q: Can I use this on Windows?  
A: No, Linux-only due to USB stack differences.

**Türkçe**  
S: Windows'ta kullanabilir miyim?  
C: Hayır, sadece Linux'ta çalışır (USB yapısı farklılıkları nedeniyle).
