#ifndef SUBSTITUTION_CIPHER_H
#define SUBSTITUTION_CIPHER_H

#include "EncryptionAlgorithm.h"
#include <unordered_map>
#include <string>

#include <iostream>
#include <string>
#include <unordered_map>

class SubstitutionCipher : public EncryptionAlgorithm {
public:
    explicit SubstitutionCipher(const std::string& key) {
        if (key.size() != 26) {
            throw std::invalid_argument("Ключ должен содержать 26 уникальных символов.");
        }

        // Создаем таблицы для шифрования и расшифрования
        for (size_t i = 0; i < 26; ++i) {
            char plainChar = 'A' + i;
            char cipherChar = key[i];
            encryptionMap[plainChar] = cipherChar;
            decryptionMap[cipherChar] = plainChar;
        }
    }

    std::string encrypt(const std::string& text) override {
        std::string encryptedText;
        for (char c : text) {
            if (isalpha(c)) {
                c = std::toupper(c);
                encryptedText.push_back(encryptionMap[c]);
            } else {
                encryptedText.push_back(c);  // Если не буква, оставляем символ как есть
            }
        }
        return encryptedText;
    }

    std::string decrypt(const std::string& text) override {
        std::string decryptedText;
        for (char c : text) {
            if (isalpha(c)) {
                c = std::toupper(c);
                decryptedText.push_back(decryptionMap[c]);
            } else {
                decryptedText.push_back(c);  // Если не буква, оставляем символ как есть
            }
        }
        return decryptedText;
    }

private:
    std::unordered_map<char, char> encryptionMap;
    std::unordered_map<char, char> decryptionMap;
};


#endif // SUBSTITUTION_CIPHER_H
