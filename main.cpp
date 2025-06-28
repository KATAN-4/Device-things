#include "lang.h"
#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <sys/wait.h>
#include <algorithm>
#include <cctype>
#include <cstring>
#include <fstream>
#include <stdexcept>

using namespace std;

// Sistem komutları
int executeCommand(const string& cmd, bool silent = true) {
    string full_cmd = silent ? cmd + " >/dev/null 2>&1" : cmd;
    return system(full_cmd.c_str());
}

string executeCommandWithOutput(const string& cmd) {
    string result;
    char buffer[128];
    FILE* pipe = popen(cmd.c_str(), "r");
    if (!pipe) return "";
    
    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        result += buffer;
    }
    
    pclose(pipe);
    
    if (!result.empty() && result.back() == '\n') {
        result.pop_back();
    }
    return result;
}

// Cihaz kontrol fonksiyonları
bool isDeviceConnected() {
    return executeCommand("adb devices | grep -w device") == 0;
}

bool isHuaweiDevice() {
    string hardware = executeCommandWithOutput("adb shell getprop ro.hardware");
    string platform = executeCommandWithOutput("adb shell getprop ro.board.platform");
    
    transform(hardware.begin(), hardware.end(), hardware.begin(), ::tolower);
    transform(platform.begin(), platform.end(), platform.begin(), ::tolower);
    
    return (hardware.find("hi") == 0 || 
            hardware.find("kirin") == 0 ||
            platform.find("hi") == 0 ||
            platform.find("kirin") == 0);
}

bool isXiaomiDevice() {
    string brand = executeCommandWithOutput("adb shell getprop ro.product.brand");
    string manufacturer = executeCommandWithOutput("adb shell getprop ro.product.manufacturer");
    string hardware = executeCommandWithOutput("adb shell getprop ro.hardware");
    
    // Tümünü küçük harfe çevir
    transform(brand.begin(), brand.end(), brand.begin(), ::tolower);
    transform(manufacturer.begin(), manufacturer.end(), manufacturer.begin(), ::tolower);
    transform(hardware.begin(), hardware.end(), hardware.begin(), ::tolower);
    
    // Xiaomi, Redmi, POCO ve işlemci kontrolü (qcom/mediatek)
    return (brand == "xiaomi" || brand == "redmi" || brand == "poco" ||
            manufacturer == "xiaomi" ||
            hardware.find("qcom") != string::npos || 
            hardware.find("mt") == 0); // Mediatek işlemciler mt ile başlar
}

// Cihaz bilgileri
string getDeviceModel() {
    string brand = executeCommandWithOutput("adb shell getprop ro.product.brand");
    string model = executeCommandWithOutput("adb shell getprop ro.product.model");
    string market_name = executeCommandWithOutput("adb shell getprop ro.product.marketname");
    
    if (!brand.empty()) brand[0] = toupper(brand[0]);
    if (market_name.empty()) {
        market_name = executeCommandWithOutput("adb shell getprop ro.product.vendor.device");
    }
    
    return market_name.empty() ? brand + " " + model : market_name;
}

string getCodename() {
    string codename = executeCommandWithOutput("adb shell getprop ro.product.device");
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
    string result = executeCommandWithOutput("fastboot getvar unlocked 2>&1");
    return result.find("unlocked: yes") != string::npos;
}

// Onay mekanizması
bool confirm(const string& prompt, bool default_yes = true) {
    cout << prompt;
    string input;
    getline(cin, input);
    
    if (input.empty()) return default_yes;
    
    transform(input.begin(), input.end(), input.begin(), ::tolower);
    if (LanguageManager::currentLanguage == "tr") {
        return (input == "e" || input == "y");
    } else {
        return (input == "y");
    }
}

// Bootloader işlemleri
void unlockBootloader() {
    cout << LanguageManager::get("unlocking") << endl;
    executeCommand("fastboot flashing unlock", false);
    executeCommand("fastboot flashing unlock_critical", false);
    executeCommand("fastboot reboot bootloader", false);
    sleep(5);
}

void flashBootImage() {
    string path;
    cout << LanguageManager::get("ask_boot_img");
    getline(cin, path);
    
    if (!path.empty()) {
        cout << LanguageManager::get("flashing") << endl;
        if (executeCommand("fastboot flash boot " + path, false) == 0) {
            cout << LanguageManager::get("success") << endl;
            executeCommand("fastboot reboot", false);
        } else {
            cout << LanguageManager::get("error") << endl;
        }
    }
}

// Ana fonksiyon
int main() {
    try {
        // Dil yükleme
        const char* lang_env = getenv("LANG");
        string lang = "en";
        if (lang_env) {
            string lang_str(lang_env);
            if (lang_str.find("tr") != string::npos) {
                lang = "tr";
            }
        }
        LanguageManager::loadLanguage(lang);

        // Cihaz bağlantı kontrolü
        if (!isDeviceConnected()) {
            cout << LanguageManager::get("no_device") << endl;
            return EXIT_FAILURE;
        }

        // Üretici kontrolleri
        if (isHuaweiDevice()) {
            string model = getDeviceModel();
            string hardware = executeCommandWithOutput("adb shell getprop ro.hardware");
            
            cout << LanguageManager::get("huawei_header") << endl;
            cout << LanguageManager::get("device_model") << model << endl;
            cout << LanguageManager::get("device_hardware") << hardware << endl;
            cout << LanguageManager::get("huawei_not_supported") << endl;
            cout << LanguageManager::get("huawei_reason") << endl;
            cout << LanguageManager::get("footer") << endl;
            return EXIT_FAILURE;
        }

        if (isXiaomiDevice()) {
            string brand = executeCommandWithOutput("adb shell getprop ro.product.brand");
            string model = getDeviceModel();
            transform(brand.begin(), brand.end(), brand.begin(), ::tolower);
            
            if (brand == "poco") {
                cout << LanguageManager::get("poco_header") << endl;
                cout << LanguageManager::get("poco_note") << endl;
            } 
            else if (brand == "redmi") {
                cout << LanguageManager::get("redmi_header") << endl;
                cout << LanguageManager::get("redmi_note") << endl;
            }
            else {
                cout << LanguageManager::get("xiaomi_header") << endl;
                cout << LanguageManager::get("xiaomi_note") << endl;
            }
            
            cout << LanguageManager::get("device_model") << model << endl;
            cout << LanguageManager::get("footer") << endl;
            
            if (!confirm(LanguageManager::get("continue_anyway"))) {
                return EXIT_SUCCESS;
            }
        }

        // Cihaz bilgilerini göster
        cout << LanguageManager::get("device_info") << getDeviceModel() << endl;
        cout << LanguageManager::get("codename_info") << getCodename() << endl;

        // Root kontrolü
        if (isRooted()) {
            cout << LanguageManager::get("root_detected") << endl;
            return EXIT_SUCCESS;
        }
        cout << LanguageManager::get("no_root") << endl;

        // Bootloader işlemleri
        if (confirm(LanguageManager::get("ask_bootloader"))) {
            executeCommand("adb reboot bootloader");
            sleep(5);

            if (isBootloaderUnlocked()) {
                cout << LanguageManager::get("unlocked") << endl;
                flashBootImage();
            } else if (confirm(LanguageManager::get("ask_unlock"))) {
                unlockBootloader();
                flashBootImage();
            } else {
                cout << LanguageManager::get("canceled") << endl;
            }
        } else {
            cout << LanguageManager::get("canceled") << endl;
        }

    } catch (const exception& e) {
        cerr << LanguageManager::get("error_prefix") << e.what() << endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
