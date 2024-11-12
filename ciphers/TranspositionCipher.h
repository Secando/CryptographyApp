#ifndef TRANSPOSITION_CIPHER_H
#define TRANSPOSITION_CIPHER_H

#include "EncryptionAlgorithm.h"
#include <algorithm>

// Определение класса TranspositionCipher, который наследует абстрактный класс EncryptionAlgorithm
class TranspositionCipher : public EncryptionAlgorithm {
public:
    // Переопределение метода encrypt для шифрования текста
    std::string encrypt(const std::string& plainText) override {
        std::string cipherText = plainText; // Создание копии plainText для хранения зашифрованного текста
        std::reverse(cipherText.begin(), cipherText.end()); // Обратный порядок символов в строке cipherText
        return cipherText; // Возвращаем зашифрованный текст
    }

    // Переопределение метода decrypt для расшифрования текста
    std::string decrypt(const std::string& cipherText) override {
        // Для TranspositionCipher дешифрование идентично шифрованию, так как порядок символов просто переворачивается
        return encrypt(cipherText); // Повторное применение метода encrypt для дешифрования
    }
};


#endif // TRANSPOSITION_CIPHER_H
