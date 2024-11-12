#ifndef ATBASH_CIPHER_H
#define ATBASH_CIPHER_H

#include "EncryptionAlgorithm.h"

class AtbashCipher : public EncryptionAlgorithm {
public:
    std::string encrypt(const std::string& plainText) override {
        std::string cipherText;
        
        for (char c : plainText) {
            if (isalpha(c)) {
                char base = islower(c) ? 'a' : 'A';
                cipherText += base + ('Z' - std::toupper(c));
            } else {
                cipherText += c;  // Сохраняем пробелы и другие символы без изменений
            }
        }
        return cipherText;
    }

    std::string decrypt(const std::string& cipherText) override {
        return encrypt(cipherText);  // Шифр Атбаш симметричен
    }
};

#endif // ATBASH_CIPHER_H
