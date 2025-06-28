---

# Device-things

> ⚙️ A tool to check Android device info, root status, and optionally unlock bootloader + flash boot image.
> 📱 Android cihaz bilgilerini kontrol eden, root durumunu algılayan ve isteğe bağlı olarak bootloader kilidini açıp boot.img flashlayan bir araç.

---

## 🇬🇧 English Description

**Device-things** is a C++ command-line tool for Android device diagnostics and fastboot automation.
It can detect root access, get model/codename info, and optionally unlock the bootloader or flash a boot image in fastboot mode.

### ✅ Features

* Detects if the device is rooted (su, magisk, or binaries)
* Displays device brand/model and codename
* Checks for bootloader unlock status
* Optionally unlocks bootloader and flashes a custom boot.img
* Manufacturer-specific handling for Xiaomi and Huawei

### 🛠 Requirements

* ADB and Fastboot installed (adb, fastboot commands)
* Android device with USB Debugging enabled
* Linux or Windows (tested on both)

### 🚀 Build & Run

**Linux:**

```bash
g++ main.cpp lang.cpp -o device-things
./device-things
```

**Windows (with MinGW-w64 or cross-compiler):**

```bash
g++ win_main.cpp lang.cpp -o device-things.exe
device-things.exe
```

Make sure `adb.exe` and `fastboot.exe` are in the same directory or in your system PATH on Windows.

---

## 🇹🇷 Türkçe Açıklama

**Device-things**, Android cihazlarda root kontrolü, cihaz bilgisi alma ve bootloader işlemleri yapmak için geliştirilen bir C++ terminal uygulamasıdır.

### ✅ Özellikler

* Root var mı kontrol eder (su, magisk vs.)
* Marka/model ve cihaz kod adını gösterir
* Bootloader kilidi açık mı kontrol eder
* İsteğe bağlı olarak bootloader kilidi açar ve boot.img yükler
* Xiaomi & Huawei cihazlar için özel kontrol ve uyarılar

### 🛠 Gereksinimler

* ADB ve Fastboot kurulu olmalı (adb, fastboot komutları çalışmalı)
* USB hata ayıklama açık bir Android cihaz
* Linux veya Windows (ikisiyle de uyumlu)

### 🚀 Derleme & Çalıştırma

**Linux:**

```bash
g++ main.cpp lang.cpp -o device-things
./device-things
```

**Windows (MinGW-w64 veya çapraz derleyici ile):**

```bash
g++ win_main.cpp lang.cpp -o device-things.exe
device-things.exe
```

Windows’ta `adb.exe` ve `fastboot.exe`, çalıştırılabilir dosyayla aynı klasörde olmalı ya da sistem PATH değişkenine eklenmelidir.

---

## 🌐 Dil Desteği

* Türkçe (`lang_tr.txt`)
* İngilizce (`lang_en.txt`)

Program sistem dili (`LANG`) üzerinden otomatik dil algılar. Manuel seçim gerekmez.

---

## 📁 Proje Dosyaları

```
main.cpp           // Linux için kaynak kod
win_main.cpp       // Windows için kaynak kod
lang.cpp           // Dil sistemi implementasyonu
lang.h             // Dil yönetimi başlığı
lang_tr.txt        // Türkçe metinler
lang_en.txt        // İngilizce metinler
README.md          // Bu dosya
device-things      // Linux için derlenmiş binary (opsiyonel)
device-things.exe  // Windows için derlenmiş binary (opsiyonel)
```

---

## ⚠️ Uyarılar / Warnings

* Bootloader kilidini açmak cihazdaki tüm verileri siler.
* Yanlış boot.img yüklemek cihazın açılmamasına neden olabilir.
* Bu yazılımı kullanmak tamamen sizin sorumluluğunuzdadır.

---
