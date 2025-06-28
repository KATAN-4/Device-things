#ifndef LANG_H
#define LANG_H

#include <string>
#include <map>
#include <fstream>  
#include <stdexcept> 

class LanguageManager {
public:
    static void loadLanguage(const std::string& langCode);
    static std::string get(const std::string& key);
    static std::string currentLanguage;

private:
    static std::map<std::string, std::map<std::string, std::string>> translations;
    static std::string trim(const std::string& str); // Yardımcı fonksiyon
};

#endif
