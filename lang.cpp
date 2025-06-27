#include "lang.h"
#include <fstream>

std::string LanguageManager::currentLanguage = "en";
std::map<std::string, std::map<std::string, std::string>> LanguageManager::translations;

void LanguageManager::loadLanguage(const std::string& langCode) {
    translations.clear();
    currentLanguage = langCode;
    
    std::string filename = "lang_" + langCode + ".txt";
    std::ifstream file(filename);
    
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            size_t delim = line.find('=');
            if (delim != std::string::npos) {
                std::string key = line.substr(0, delim);
                std::string value = line.substr(delim + 1);
                translations[key][langCode] = value;
            }
        }
    }
}

std::string LanguageManager::get(const std::string& key) {
    auto it_key = translations.find(key);
    if (it_key != translations.end()) {
        auto it_lang = it_key->second.find(currentLanguage);
        if (it_lang != it_key->second.end()) {
            return it_lang->second;
        }
    }
    return key;
}
