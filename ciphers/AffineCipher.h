#ifndef AFFINE_CIPHER_H
#define AFFINE_CIPHER_H

#include "EncryptionAlgorithm.h"
#include <stdexcept>

class AffineCipher : public EncryptionAlgorithm {
private:
    int a, b;
    const int m = 26;

    int modInverse(int a, int m) {
        for (int x = 1; x < m; ++x) {
            if ((a * x) % m == 1) {
                return x;
            }
        }
        throw std::invalid_argument("Мультипликативная инверсия не существует");
    }

    // Реализация собственного алгоритма Евклида для нахождения НОД
    int gcd(int a, int b) {
        while (b != 0) {
            int temp = b;
            b = a % b;
            a = temp;
        }
        return a;
    }

public:
    // Конструктор шифра с параметрами 'a' и 'b'
    AffineCipher(int a, int b) : a(a), b(b) {
        // Проверяем, что 'a' взаимно просто с модулем 'm' (обычно 26 для алфавита)
        if (gcd(a, m) != 1) { // Используем собственную функцию для НОД
            throw std::invalid_argument("Число 'a' должно быть взаимно простым с 26");
        }
    }

    // Метод для шифрования текста
    std::string encrypt(const std::string& plainText) override {
        std::string cipherText; // Результирующая строка зашифрованного текста
        for (char c : plainText) {
            if (c >= 'A' && c <= 'Z') { 
                // Шифрование заглавных букв
                cipherText += (char)(((a * (c - 'A') + b) % m) + 'A');
            } else if (c >= 'a' && c <= 'z') { 
                // Шифрование строчных букв
                cipherText += (char)(((a * (c - 'a') + b) % m) + 'a');
            } else {
                cipherText += c; // Если символ не буква, добавляем его без изменений
            }
        }
        return cipherText; // Возвращаем зашифрованный текст
    }

    // Метод для расшифрования текста
    std::string decrypt(const std::string& cipherText) override {
        int a_inv = modInverse(a, m); // Находим обратный элемент для 'a' по модулю 'm'
        std::string plainText; // Результирующая строка расшифрованного текста
        for (char c : cipherText) {
            if (c >= 'A' && c <= 'Z') {
                // Расшифрование заглавных букв
                plainText += (char)((a_inv * ((c - 'A' - b + m) % m)) % m + 'A');
            } else if (c >= 'a' && c <= 'z') {
                // Расшифрование строчных букв
                plainText += (char)((a_inv * ((c - 'a' - b + m) % m)) % m + 'a');
            } else {
                plainText += c; // Если символ не буква, добавляем его без изменений
            }
        }
        return plainText; // Возвращаем расшифрованный текст
    }
};

#endif // AFFINE_CIPHER_H
