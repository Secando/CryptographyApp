#ifndef VIGENERE_CIPHER_H
#define VIGENERE_CIPHER_H

#include "EncryptionAlgorithm.h"
#include <cctype>
#include <string>
#include <stdexcept>

class VigenereCipher : public EncryptionAlgorithm {
private:
    std::string key;

    char shiftChar(char c, int shift) {
        if (std::isalpha(c)) {
            char base = std::isupper(c) ? 'A' : 'a';
            return static_cast<char>((c - base + shift) % 26 + base);
        }
        return c;
    }

public:
    // Конструктор для инициализации шифра Виженера с ключом
    explicit VigenereCipher(const std::string& key) : key(key) {
        // Проверка на пустой ключ, так как ключ обязателен для шифра Виженера
        if (key.empty()) {
            throw std::invalid_argument("Ключ для шифра Виженера не может быть пустым.");
        }
    }
    // Метод шифрования текста
    std::string encrypt(const std::string& text) override {
        std::string encryptedText; // Результирующая строка для зашифрованного текста
        int keyIndex = 0; // Индекс для отслеживания символов ключа

        for (char c : text) {
            if (std::isalpha(c)) { // Проверка, является ли символ буквой
                // Вычисляем смещение для текущего символа ключа
                int shift = std::toupper(key[keyIndex % key.length()]) - 'A';
                encryptedText += shiftChar(c, shift); // Шифруем символ с использованием смещения
                keyIndex++; // Переходим к следующему символу ключа
            } else {
                encryptedText += c; // Сохраняем небуквенные символы без изменений
            }
        }
        return encryptedText; // Возвращаем зашифрованный текст
    }
    // Метод для расшифрования текста
    std::string decrypt(const std::string& encryptedText) override {
        std::string decryptedText; // Результирующая строка для расшифрованного текста
        int keyIndex = 0; // Индекс для отслеживания символов ключа

        for (char c : encryptedText) {
            if (std::isalpha(c)) { // Проверка, является ли символ буквой
                // Вычисляем смещение для текущего символа ключа, но в обратную сторону
                int shift = std::toupper(key[keyIndex % key.length()]) - 'A';
                decryptedText += shiftChar(c, -shift); // Расшифровываем символ с использованием смещения
                keyIndex++; // Переходим к следующему символу ключа
            } else {
                decryptedText += c; // Сохраняем небуквенные символы без изменений
            }
        }
        return decryptedText; // Возвращаем расшифрованный текст
    }
};


#endif // VIGENERE_CIPHER_H
