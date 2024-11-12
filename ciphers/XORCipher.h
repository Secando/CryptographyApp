#ifndef XOR_CIPHER_H
#define XOR_CIPHER_H

#include "EncryptionAlgorithm.h"

// Определение класса XORCipher, который наследует абстрактный класс EncryptionAlgorithm
class XORCipher : public EncryptionAlgorithm {
private:
    char key; 
    // Закрытая переменная для хранения ключа шифрования
public:
    XORCipher(char key) : key(key) {}
    // Конструктор XORCipher, инициализирующий ключ, переданный как параметр
    std::string encrypt(const std::string& plainText) override {
    // Переопределение метода encrypt для шифрования текста
        std::string cipherText = plainText; 
        // Создание копии plainText для хранения зашифрованного текста
        for (char& c : cipherText) { 
            // Цикл по каждому символу строки cipherText
            c ^= key; 
            // Применение побитовой операции XOR к каждому символу с ключом
        }
        return cipherText; 
        // Возвращаем зашифрованный текст
    }
    std::string decrypt(const std::string& cipherText) override {
        // Переопределение метода decrypt для расшифрования текста
        // Для XOR шифра дешифрование идентично шифрованию, так как операция XOR является обратимой
        return encrypt(cipherText); // Повторное применение метода encrypt для дешифрования
    }
};


#endif // XOR_CIPHER_H


