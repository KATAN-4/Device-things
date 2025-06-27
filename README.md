````markdown
# Device-things

---

## Türkçe

### Açıklama
Device-things, Android cihazlarda root kontrolü, bootloader durumu kontrolü ve bootloader üzerinden boot image flaşlama işlemleri yapabilen basit bir C++ komut satırı aracıdır. Kullanıcı dostu dil desteği (Türkçe ve İngilizce) ile işlemler kolayca yönetilir.

### Özellikler
- Android cihaz model ve kod adını gösterir.
- Root erişimini kontrol eder.
- Bootloader durumunu sorgular.
- Bootloader kilidini açma işlemi yapabilir.
- Boot image dosyasını fastboot üzerinden flaşlayabilir.
- Kullanıcıdan onay alarak işlemleri yönetir.
- Otomatik dil algılama ve destek (Türkçe / İngilizce).

### Gereksinimler
- ADB ve Fastboot araçlarının sistemde yüklü olması.
- C++17 veya üzeri uyumlu derleyici.
- Android cihazınızda USB hata ayıklama ve gerekli izinlerin aktif olması.

### Kullanım
1. Projeyi derleyin:
   ```bash
   g++ main.cpp -o device-things
````

2. Programı çalıştırın:

   ```bash
   ./device-things
   ```
3. İstenilen adımları takip edin. Dil otomatik algılanır, isterseniz çevrim içi veya yerel ortam dil ayarları ile Türkçe veya İngilizce olarak çalışır.

### Önemli Notlar

* Root kontrolü birkaç farklı komut ile yapılır, bazı cihazlarda farklılık gösterebilir.
* Bootloader kilidini açmak cihazdaki tüm verileri silecektir, dikkatli olunuz.
* Program temel seviye araçlar içerir, gelişmiş özellikler için modifikasyon yapabilirsiniz.
* `lang.h` dosyası ile dil desteği yönetilmektedir.

---

## English

### Description

Device-things is a simple C++ command-line tool to check Android device root status, bootloader state, and flash boot images via bootloader. It supports Turkish and English languages for user-friendly interaction.

### Features

* Displays Android device model and codename.
* Checks for root access.
* Queries bootloader lock status.
* Can unlock the bootloader.
* Flash boot images using fastboot.
* Asks for user confirmation before actions.
* Automatic language detection (Turkish / English).

### Requirements

* ADB and Fastboot tools installed on the system.
* C++17 or later compatible compiler.
* USB debugging and proper permissions enabled on the Android device.

### Usage

1. Compile the project:

   ```bash
   g++ main.cpp -o device-things
   ```
2. Run the program:

   ```bash
   ./device-things
   ```
3. Follow on-screen instructions. Language is auto-detected and supports Turkish or English based on your system locale or input.

### Important Notes

* Root detection is performed via multiple commands and may vary between devices.
* Unlocking the bootloader will erase all user data; proceed carefully.
* This program offers basic functionality; you can modify it for more advanced features.
* Language support is managed via the `lang.h` header file.

---
