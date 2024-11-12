#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <sstream>
#include <iomanip>

class Utils {
public:
    // Метод для преобразования строки в шестнадцатеричное представление
    static std::string toHex(const std::string& str) {
        std::ostringstream hexStream;
        for (unsigned char c : str) {
            hexStream << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(c);
        }
        return hexStream.str();
    }
};

#endif // UTILS_H
