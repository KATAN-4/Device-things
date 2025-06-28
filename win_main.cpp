#include "lang.h"
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <cctype>
#include <cstring>
#include <fstream>
#include <stdexcept>

#ifdef _WIN32
#include <windows.h>
#define sleep(x) Sleep((x) * 1000)
#define GREP_COMMAND "findstr"
#else
#include <unistd.h>
#define GREP_COMMAND "grep"
#endif

using namespace std;

// Sistem komutları
int executeCommand(const string& cmd, bool silent = true) {
    string full_cmd = silent ? cmd + " >nul 2>&1" : cmd;
    return system(full_cmd.c_str());
}

string executeCommandWithOutput(const string& cmd) {
    string result;
    char buffer[256];
#ifdef _WIN32
    FILE* pipe = _popen(cmd.c_str(), "r");
#else
    FILE* pipe = popen(cmd.c_str(), "r");
#endif
    if (!pipe) return "";

    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        result += buffer;
    }

#ifdef _WIN32
    _pclose(pipe);
#else
    pclose(pipe);
#endif

    if (!result.empty() && result.back() == '\n') {
        result.pop_back();
    }
    return result;
}

// Cihaz kontrol fonksiyonları
bool isDeviceConnected() {
    return executeCommand("adb devices | " GREP_COMMAND " -w device") == 0;
}

bool isHuaweiDevice() {
    string hw = executeCommandWithOutput("adb shell getprop ro.hardware");
    string plat = executeCommandWithOutput("adb shell getprop ro.board.platform");
    transform(hw.begin(), hw.end(), hw.begin(), ::tolower);
    transform(plat.begin(), plat.end(), plat.begin(), ::tolower);
    return (hw.find("hi") == 0 || hw.find("kirin") == 0 || plat.find("hi") == 0 || plat.find("kirin") == 0);
}

bool isXiaomiDevice() {
    string brand = executeCommandWithOutput("adb shell getprop ro.product.brand");
    string manu = executeCommandWithOutput("adb shell getprop ro.product.manufacturer");
    string hw = executeCommandWithOutput("adb shell getprop ro.hardware");

    transform(brand.begin(), brand.end(), brand.begin(), ::tolower);
    transform(manu.begin(), manu.end(), manu.begin(), ::tolower);
    transform(hw.begin(), hw.end(), hw.begin(), ::tolower);

    return (brand == "xiaomi" || brand == "redmi" || brand == "poco" || manu == "xiaomi" ||
            hw.find("qcom") != string::npos || hw.find("mt") == 0);
}

// Cihaz bilgileri
string getDeviceModel() {
    string brand = executeCommandWithOutput("adb shell getprop ro.product.brand");
    string model = executeCommandWithOutput("adb shell getprop ro.product.model");
    string market = executeCommandWithOutput("adb shell getprop ro.product.marketname");
    if (!brand.empty()) brand[0] = toupper(brand[0]);
    if (market.empty()) {
        market = executeCommandWithOutput("adb shell getprop ro.product.vendor.device");
    }
    return market.empty() ? brand + " " + model : market;
}

string getCodename() {
    string code = executeCommandWithOutput("adb shell getprop ro.product.device");
    if (code.empty()) code = executeCommandWithOutput("adb shell getprop ro.product.vendor.device");
    return code.empty() ? "unknown" : code;
}

// Root ve bootloader
bool isRooted() {
    return executeCommand("adb shell \"su -c id | " GREP_COMMAND " uid=0\"") == 0 ||
           executeCommand("adb shell \"if exist /system/bin/su (exit 0) else (exit 1)\"") == 0;
}

bool isBootloaderUnlocked() {
    string result = executeCommandWithOutput("fastboot getvar unlocked 2>&1");
    return result.find("unlocked: yes") != string::npos;
}

bool confirm(const string& prompt, bool default_yes = true) {
    cout << prompt;
    string input;
    getline(cin, input);
    if (input.empty()) return default_yes;
    transform(input.begin(), input.end(), input.begin(), ::tolower);
    return (input == "y" || input == "e");
}

// Bootloader
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

// Main
int main() {
    try {
        string lang = "en";
        const char* lang_env = getenv("LANG");
        if (lang_env && string(lang_env).find("tr") != string::npos)
            lang = "tr";
        LanguageManager::loadLanguage(lang);

        if (!isDeviceConnected()) {
            cout << LanguageManager::get("no_device") << endl;
            return EXIT_FAILURE;
        }

        if (isHuaweiDevice()) {
            cout << LanguageManager::get("huawei_header") << endl;
            cout << LanguageManager::get("device_model") << getDeviceModel() << endl;
            cout << LanguageManager::get("device_hardware") << executeCommandWithOutput("adb shell getprop ro.hardware") << endl;
            cout << LanguageManager::get("huawei_not_supported") << endl;
            cout << LanguageManager::get("huawei_reason") << endl;
            cout << LanguageManager::get("footer") << endl;
            return EXIT_FAILURE;
        }

        if (isXiaomiDevice()) {
            string brand = executeCommandWithOutput("adb shell getprop ro.product.brand");
            transform(brand.begin(), brand.end(), brand.begin(), ::tolower);
            cout << (brand == "poco" ? LanguageManager::get("poco_header") :
                     brand == "redmi" ? LanguageManager::get("redmi_header") :
                     LanguageManager::get("xiaomi_header")) << endl;
            cout << (brand == "poco" ? LanguageManager::get("poco_note") :
                     brand == "redmi" ? LanguageManager::get("redmi_note") :
                     LanguageManager::get("xiaomi_note")) << endl;
            cout << LanguageManager::get("device_model") << getDeviceModel() << endl;
            cout << LanguageManager::get("footer") << endl;

            if (!confirm(LanguageManager::get("continue_anyway"))) {
                return EXIT_SUCCESS;
            }
        }

        cout << LanguageManager::get("device_info") << getDeviceModel() << endl;
        cout << LanguageManager::get("codename_info") << getCodename() << endl;

        if (isRooted()) {
            cout << LanguageManager::get("root_detected") << endl;
            return EXIT_SUCCESS;
        }

        cout << LanguageManager::get("no_root") << endl;

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

