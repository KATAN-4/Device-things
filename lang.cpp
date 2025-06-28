#include "lang.h"
#include <algorithm> 


std::map<std::string, std::map<std::string, std::string>> LanguageManager::translations;
std::string LanguageManager::currentLanguage = "en";


std::string LanguageManager::trim(const std::string& str) {
    size_t first = str.find_first_not_of(" \t");
    if (std::string::npos == first) return "";
    size_t last = str.find_last_not_of(" \t");
    return str.substr(first, (last - first + 1));
}

void LanguageManager::loadLanguage(const std::string& langCode) {
    std::string filename = "lang_" + langCode + ".txt";
    std::ifstream file(filename);
    
    if (!file.is_open()) {
        throw std::runtime_error("Language file not found: " + filename);
    }

    translations[langCode].clear();
    std::string line;
    
    while (std::getline(file, line)) {
        line = trim(line);
        if (line.empty() || line[0] == '#') continue; 
        
        size_t delimiter_pos = line.find('=');
        if (delimiter_pos != std::string::npos) {
            std::string key = trim(line.substr(0, delimiter_pos));
            std::string value = trim(line.substr(delimiter_pos + 1));
            if (!key.empty()) {
                translations[langCode][key] = value;
            }
        }
    }
    
    currentLanguage = langCode;
}

std::string LanguageManager::get(const std::string& key) {
    auto lang_iter = translations.find(currentLanguage);
    if (lang_iter != translations.end()) {
        auto key_iter = lang_iter->second.find(key);
        if (key_iter != lang_iter->second.end()) {
            return key_iter->second;
        }
    }
    return "[" + key + "]";
}
