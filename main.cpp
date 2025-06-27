#include "lang.h"
#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <sys/wait.h>
#include <algorithm>
#include <cctype>
#include <cstring>

// Sistem komutları
int executeCommand(const std::string& cmd, bool silent = true) {
    std::string full_cmd = silent ? cmd + " >/dev/null 2>&1" : cmd;
    return system(full_cmd.c_str());
}

std::string executeCommandWithOutput(const std::string& cmd) {
    std::string result;
    char buffer[128];
    FILE* pipe = popen(cmd.c_str(), "r");
    if (!pipe) return "";
    
    // Hata düzeltildi: nullptr kontrolü ve doğru parantez kullanımı
    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        result += buffer;
    }
    
    pclose(pipe);
    
    if (!result.empty() && result.back() == '\n') {
        result.pop_back();
    }
    return result;
}

// Cihaz bilgileri
std::string getDeviceModel() {
    std::string brand = executeCommandWithOutput("adb shell getprop ro.product.brand");
    std::string model = executeCommandWithOutput("adb shell getprop ro.product.model");
    std::string market_name = executeCommandWithOutput("adb shell getprop ro.product.marketname");
    
    if (!brand.empty()) brand[0] = toupper(brand[0]);
    if (market_name.empty()) {
        market_name = executeCommandWithOutput("adb shell getprop ro.product.vendor.device");
    }
    
    return market_name.empty() ? brand + " " + model : market_name;
}

std::string getCodename() {
    std::string codename = executeCommandWithOutput("adb shell getprop ro.product.device");
    if (codename.empty()) {
        codename = executeCommandWithOutput("adb shell getprop ro.product.vendor.device");
    }
    return codename.empty() ? "unknown" : codename;
}

// Root ve Bootloader kontrol
bool isRooted() {
    return executeCommand("adb shell 'su -c \"id\" | grep -q \"uid=0\"'") == 0 ||
           executeCommand("adb shell '[ -f /system/bin/su ] || [ -f /system/xbin/su ]'") == 0 ||
           executeCommand("adb shell '[ -d /sbin/.magisk ] || [ -f /data/adb/magisk ]'") == 0;
}

bool isBootloaderUnlocked() {
    std::string result = executeCommandWithOutput("fastboot getvar unlocked 2>&1");
    return result.find("unlocked: yes") != std::string::npos;
}

// Onay mekanizması
bool confirm(const std::string& prompt, bool default_yes = true) {
    std::cout << prompt;
    std::string input;
    std::getline(std::cin, input);
    
    if (input.empty()) return default_yes;
    
    if (LanguageManager::currentLanguage == "tr") {
        return (input == "E" || input == "e");
    } else {
        return (input == "Y" || input == "y");
    }
}

// Bootloader işlemleri
void unlockBootloader() {
    executeCommand("fastboot flashing unlock", false);
    executeCommand("fastboot flashing unlock_critical", false);
    executeCommand("fastboot reboot bootloader", false);
    sleep(3);
}

void flashBootImage() {
    std::string path;
    std::cout << LanguageManager::get("ask_boot_img");
    std::getline(std::cin, path);
    
    if (!path.empty()) {
        std::cout << LanguageManager::get("flashing") << std::endl;
        executeCommand("fastboot flash boot " + path, false);
        std::cout << LanguageManager::get("success") << std::endl;
        executeCommand("fastboot reboot", false);
    }
}

// Ana fonksiyon
int main() {
    // Dil yükleme
    const char* lang_env = getenv("LANG");
    std::string lang = "en";
    if (lang_env) {
        std::string lang_str(lang_env);
        if (lang_str.find("tr") != std::string::npos) {
            lang = "tr";
        }
    }
    LanguageManager::loadLanguage(lang);

    // Cihaz bilgileri
    std::cout << LanguageManager::get("device_info") << getDeviceModel() << std::endl;
    std::cout << LanguageManager::get("codename_info") << getCodename() << std::endl;

    // Root kontrol
    if (isRooted()) {
        std::cout << LanguageManager::get("root_detected") << std::endl;
        return EXIT_SUCCESS;
    }

    std::cout << LanguageManager::get("no_root") << std::endl;

    // Bootloader'a geçiş
    if (confirm(LanguageManager::get("ask_bootloader"))) {
        executeCommand("adb reboot bootloader");
        sleep(5);

        // Bootloader kontrol
        if (isBootloaderUnlocked()) {
            std::cout << LanguageManager::get("unlocked") << std::endl;
            flashBootImage();
        } else if (confirm(LanguageManager::get("ask_unlock"))) {
            unlockBootloader();
            flashBootImage();
        } else {
            std::cout << LanguageManager::get("canceled") << std::endl;
        }
    } else {
        std::cout << LanguageManager::get("canceled") << std::endl;
    }

    return EXIT_SUCCESS;
}
