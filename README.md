# Device-things

> ⚙️ A tool to check Android device info, root status, and optionally unlock bootloader + flash boot image.
> 📱 Android cihaz bilgilerini kontrol eden, root durumunu algılayan ve isteğe bağlı olarak bootloader kilidini açıp boot.img flashlayan bir araç.

---

## 🇬🇧 English Description

**Device-things** is a C++ CLI tool designed for Android device diagnostics and simple fastboot automation.
It detects root access, retrieves device model/codename, and allows you to unlock bootloader and flash a boot image in fastboot mode.

### ✅ Features

* Detects if the device is rooted via `su`, `magisk`, or binary checks.
* Displays brand/model and codename of the connected Android device.
* Offers reboot to bootloader (fastboot) and checks its unlock status.
* Optionally unlocks bootloader and flashes `boot.img`.

### 🛠 Requirements

* Linux (tested on Debian-based distros)
* `adb` and `fastboot` installed
* A connected Android device with USB debugging enabled

### 🚀 Usage

```bash
g++ main.cpp -o device-things
./device-things
```

---

## 🇹🇷 Türkçe Açıklama

**Device-things**, Android cihazlarda root algılama, cihaz kod adı/model bilgisi okuma ve bootloader işlemlerini otomatikleştirmek için yazılmış bir C++ terminal uygulamasıdır.

### ✅ Özellikler

* Cihazın root'lu olup olmadığını tespit eder (`su`, `magisk` dizinleri vs.).
* Marka/model ve kod adı bilgilerini gösterir.
* Cihazı bootloader (fastboot) moduna geçirir ve kilidinin açık olup olmadığını kontrol eder.
* İsteğe bağlı olarak bootloader kilidini açar ve `boot.img` flashlar.

### 🛠 Gereksinimler

* Linux (Debian tabanlı dağıtımlarda test edildi)
* `adb` ve `fastboot` komutları sistemde yüklü olmalı
* USB hata ayıklama (debugging) açık Android cihaz

### 🚀 Kullanım

```bash
g++ main.cpp -o device-things
./device-things
```

---

## 🌐 Dil Desteği

* Türkçe (`tr`)
* İngilizce (`en`)

> Sistem diline göre otomatik belirlenir (`LANG` çevre değişkeni).

---

## ⚠️ Uyarılar

* Bootloader kilidi açmak cihazdaki tüm verileri silebilir.
* Yanlış `boot.img` flashlamak cihazın açılmamasına (soft brick) neden olabilir.
* Kullanım tamamen sizin sorumluluğunuzdadır.

---

## 📂 Proje Yapısı

```text
.
├── main.cpp          // Ana uygulama
├── lang.h            // Dil yönetimi (LanguageManager sınıfı)
└── README.md         // Bu dosya
```

---
