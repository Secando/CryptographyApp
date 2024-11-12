#ifndef CAESAR_CIPHER_H
#define CAESAR_CIPHER_H

#include "EncryptionAlgorithm.h"

// Определение класса CaesarCipher, который наследует абстрактный класс EncryptionAlgorithm
class CaesarCipher : public EncryptionAlgorithm {
private:
    int shift; 
    // Закрытая переменная для хранения величины сдвига
public:
    // Конструктор CaesarCipher, инициализирующий величину сдвига
    CaesarCipher(int shift) : shift(shift) {}
    // Переопределение метода encrypt для шифрования текста
    std::string encrypt(const std::string& plainText) override {
        std::string cipherText; 
        // Строка для хранения зашифрованного текста
        for (char c : plainText) { 
            // Цикл по каждому символу строки plainText
            if (isalpha(c)) { 
                // Проверка, является ли символ буквой
                char base = islower(c) ? 'a' : 'A'; 
                // Определение базового символа ('a' или 'A') в зависимости от регистра
                cipherText += (c - base + shift) % 26 + base; 
                // Шифрование символа с учетом сдвига и добавление его в cipherText
            } else {
                cipherText += c; 
                // Добавление символа без изменений, если это не буква
            }
        }
        return cipherText; 
        // Возвращаем зашифрованный текст
    }

    // Переопределение метода decrypt для расшифрования текста
    std::string decrypt(const std::string& cipherText) override {
        std::string plainText; 
        // Строка для хранения расшифрованного текста
        for (char c : cipherText) { 
            // Цикл по каждому символу строки cipherText
            if (isalpha(c)) { 
                // Проверка, является ли символ буквой
                char base = islower(c) ? 'a' : 'A'; 
                // Определение базового символа ('a' или 'A') в зависимости от регистра
                plainText += (c - base - shift + 26) % 26 + base; 
                // Дешифрование символа и добавление его в plainText
            } else {
                plainText += c; 
                // Добавление символа без изменений, если это не буква
            }
        }
        return plainText; 
        // Возвращаем расшифрованный текст
    }
};


#endif // CAESAR_CIPHER_H
