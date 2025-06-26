import os
import platform
import subprocess
import urllib.request
import zipfile
import locale
import time

PLATFORM_TOOLS_URL = {
    "Windows": "https://dl.google.com/android/repository/platform-tools-latest-windows.zip",
    "Linux": "https://dl.google.com/android/repository/platform-tools-latest-linux.zip",
    "Darwin": "https://dl.google.com/android/repository/platform-tools-latest-darwin.zip"
}

TOOLS_DIR = "platform-tools"
ADB = os.path.join(TOOLS_DIR, "adb.exe" if platform.system() == "Windows" else "adb")
FASTBOOT = os.path.join(TOOLS_DIR, "fastboot.exe" if platform.system() == "Windows" else "fastboot")

def get_system_language():
    lang = locale.getdefaultlocale()[0]
    if lang is None:
        return "en"
    if lang.startswith("tr"):
        return "tr"
    return "en"

LANG = get_system_language()

def _(key):
    translations = {
        "connect_device": {
            "tr": "Lütfen cihazınızı USB ile bağlayın ve USB hata ayıklamayı etkinleştirin...",
            "en": "Please connect your device via USB and enable USB debugging..."
        },
        "device_found": {
            "tr": "Cihaz bulundu. Fastboot moduna geçiliyor...",
            "en": "Device detected. Rebooting into fastboot mode..."
        },
        "device_not_found": {
            "tr": "Cihaz bulunamadı.",
            "en": "Device not found."
        },
        "checking_bl": {
            "tr": "Bootloader durumu kontrol ediliyor...",
            "en": "Checking bootloader status..."
        },
        "bl_unlocked": {
            "tr": "✅ Bootloader açık.",
            "en": "✅ Bootloader is unlocked."
        },
        "bl_locked": {
            "tr": "🔒 Bootloader KAPALI.",
            "en": "🔒 Bootloader is LOCKED."
        },
        "bl_unknown": {
            "tr": "❓ Bootloader durumu anlaşılamadı.",
            "en": "❓ Bootloader status could not be determined."
        },
        "adb_not_found": {
            "tr": "ADB bulunamadı. İndiriliyor...",
            "en": "ADB not found. Downloading..."
        },
        "unlocking": {
            "tr": "Bootloader kilidini açmak ister misiniz?",
            "en": "Would you like to unlock the Bootloader?"
        },
        "bootloader_already": {
            "tr": "Cihaz zaten bootloader modunda.",
            "en": "Device is already in bootloader mode."
        },
        "operation_cancelled": {
            "tr": "İşlem iptal edildi.",
            "en": "Operation cancelled."
        },
        "bootloader_not_found": {
            "tr": "Bootloader modunda cihaz bulunamadı.",
            "en": "No device found in bootloader mode."
        },
        "unlocking_in_progress": {
            "tr": "Bootloader kilidi açılıyor...",
            "en": "Unlocking bootloader..."
        }
    }
    return translations.get(key, {}).get(LANG, key)

def confirm(prompt):
    while True:
        answer = input(prompt + " (E/h): ").strip().lower()
        if answer in ['e', 'h']:
            return answer == 'e'
        print("Lütfen sadece 'E' veya 'h' giriniz.")

def run(cmd):
    try:
        return subprocess.check_output(cmd, shell=True, stderr=subprocess.STDOUT).decode()
    except subprocess.CalledProcessError as e:
        return e.output.decode()

def adb_missing():
    output = run("adb devices")
    return "not found" in output or "command not found" in output

def download_and_extract_tools():
    system = platform.system()
    url = PLATFORM_TOOLS_URL.get(system)
    if not url:
        raise Exception(f"{system} işletim sistemi desteklenmiyor.")

    zip_name = "platform-tools.zip"
    print(_(f"adb_not_found"))
    urllib.request.urlretrieve(url, zip_name)
    print("İndirme tamamlandı. Zip çıkarılıyor...")

    with zipfile.ZipFile(zip_name, "r") as zip_ref:
        zip_ref.extractall(".")

    os.remove(zip_name)

    if system != "Windows":
        os.chmod(ADB, 0o755)
        os.chmod(FASTBOOT, 0o755)

    print("platform-tools hazır.")

def device_connected(adb_cmd):
    output = run(f"{adb_cmd} devices").splitlines()
    for line in output:
        if "\tdevice" in line:
            return True
    return False

def fastboot_device_connected(fastboot_cmd):
    output = run(f"{fastboot_cmd} devices").splitlines()
    for line in output:
        if line.strip() != "":
            return True
    return False

def get_device_id(adb_cmd):
    output = run(f"{adb_cmd} devices")
    lines = output.splitlines()
    for line in lines:
        if "\tdevice" in line:
            return line.split("\t")[0]
    return None

def get_device_name(adb_cmd):
    brand = run(f'{adb_cmd} shell getprop ro.product.brand').strip()
    model = run(f'{adb_cmd} shell getprop ro.product.model').strip()
    if brand and model:
        return f"{brand} {model}"
    return None

def bootloader_unlocked(fastboot_cmd):
    output = run(f"{fastboot_cmd} getvar unlocked")
    if "unlocked: yes" in output:
        return True
    elif "unlocked: no" in output:
        return False
    else:
        print(output.strip())
        return None

def main():
    if adb_missing():
        download_and_extract_tools()
        adb_cmd = ADB
    else:
        adb_cmd = "adb"

    fastboot_cmd = FASTBOOT if adb_cmd == ADB else "fastboot"

    if fastboot_device_connected(fastboot_cmd):
        print(_(f"bootloader_already"))
        print(_(f"checking_bl"))
        unlocked = bootloader_unlocked(fastboot_cmd)
        if unlocked is True:
            print(_(f"bl_unlocked"))
        elif unlocked is False:
            print(_(f"bl_locked"))
            time.sleep(2)
            if confirm(_(f"unlocking")):
                print(_(f"unlocking_in_progress"))
        else:
            print(_(f"bl_unknown"))
        return

    print(_(f"connect_device"))

    if not device_connected(adb_cmd):
        print(_(f"device_not_found"))
        return

    device_id = get_device_id(adb_cmd)
    device_name = get_device_name(adb_cmd)
    if device_name and device_id:
        print(f"Cihaz algılandı: {device_name} ({device_id})")
    elif device_id:
        print(f"Cihaz algılandı: {device_id}")
    else:
        print(_(f"device_found"))

    if confirm("Bootloader'a (Fastboot) geçmek ister misiniz?"):
        run(f"{adb_cmd} reboot bootloader")
        print(_(f"checking_bl"))
        time.sleep(5) 
        if fastboot_device_connected(fastboot_cmd):
            unlocked = bootloader_unlocked(fastboot_cmd)
            if unlocked is True:
                print(_(f"bl_unlocked"))
            elif unlocked is False:
                print(_(f"bl_locked"))
                time.sleep(2)
                if confirm(_(f"unlocking")):
                    print(_(f"unlocking_in_progress"))

            else:
                print(_(f"bl_unknown"))
        else:
            print(_(f"bootloader_not_found"))
    else:
        print(_(f"operation_cancelled"))

if __name__ == "__main__":
    main()

