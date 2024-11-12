#ifndef VERNAM_CIPHER_H
#define VERNAM_CIPHER_H

#include "EncryptionAlgorithm.h"
#include <string>
#include <stdexcept>

// Определение класса VernamCipher, который наследует абстрактный класс EncryptionAlgorithm
class VernamCipher : public EncryptionAlgorithm {
private:
    std::string key; // Закрытая переменная для хранения ключа шифрования
public:
    // Конструктор VernamCipher, принимающий ключ и инициализирующий его
    explicit VernamCipher(const std::string& key) : key(key) {}

    // Переопределение метода encrypt для шифрования текста
    std::string encrypt(const std::string& text) override {
        if (text.size() != key.size()) { // Проверка, что длина ключа совпадает с длиной текста
            throw std::invalid_argument("Ошибка: Длина ключа должна совпадать с длиной текста."); // Исключение при несовпадении
        }
        std::string encryptedText; // Строка для хранения зашифрованного текста
        for (size_t i = 0; i < text.size(); ++i) { // Цикл по каждому символу текста
            encryptedText += text[i] ^ key[i]; // Применение побитовой операции XOR с символом ключа и добавление к encryptedText
        }
        return encryptedText; // Возвращаем зашифрованный текст
    }
    // Переопределение метода decrypt для расшифрования текста
    std::string decrypt(const std::string& encryptedText) override {
        if (encryptedText.size() != key.size()) { // Проверка, что длина ключа совпадает с длиной зашифрованного текста
            throw std::invalid_argument("Ошибка: Длина ключа должна совпадать с длиной зашифрованного текста."); // Исключение при несовпадении
        }
        std::string decryptedText; // Строка для хранения расшифрованного текста
        for (size_t i = 0; i < encryptedText.size(); ++i) { // Цикл по каждому символу зашифрованного текста
            decryptedText += encryptedText[i] ^ key[i]; // Применение побитовой операции XOR с символом ключа и добавление к decryptedText
        }
        return decryptedText; // Возвращаем расшифрованный текст
    }
};



#endif // VERNAM_CIPHER_H
