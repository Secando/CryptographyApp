#ifndef PLAYFAIR_CIPHER_H
#define PLAYFAIR_CIPHER_H
#include <unordered_set>

#include "EncryptionAlgorithm.h"
#include <vector>
#include <unordered_map>
#include <algorithm>

// Определение класса PlayfairCipher, который наследует абстрактный класс EncryptionAlgorithm
class PlayfairCipher : public EncryptionAlgorithm {
private:
    char matrix[5][5]; // Матрица 5x5 для хранения шифровальной таблицы
    std::unordered_map<char, std::pair<int, int>> charPositions; // Позиции символов в матрице
    // Метод для построения матрицы на основе ключа
    void buildMatrix(const std::string& key) {
        std::string filteredKey; // Строка для хранения уникальных символов ключа
        std::unordered_set<char> used; // Множество для отслеживания использованных символов
        // Заполнение матрицы уникальными символами ключа, исключая 'J'
        for (char c : key) {
            c = std::toupper(c); // Преобразуем символ к верхнему регистру
            if (c >= 'A' && c <= 'Z' && c != 'J' && used.find(c) == used.end()) {
                filteredKey += c;
                used.insert(c);
            }
        }
        // Добавление оставшихся букв алфавита, исключая 'J'
        for (char c = 'A'; c <= 'Z'; ++c) {
            if (c != 'J' && used.find(c) == used.end()) {
                filteredKey += c;
                used.insert(c);
            }
        }

        // Заполнение матрицы символами из filteredKey
        int index = 0;
        for (int i = 0; i < 5; ++i) {
            for (int j = 0; j < 5; ++j) {
                matrix[i][j] = filteredKey[index]; // Присваиваем элемент матрице
                charPositions[filteredKey[index]] = {i, j}; // Сохраняем позицию символа в матрице
                ++index;
            }
        }
    }
    // Метод для шифрования пары символов
    std::pair<char, char> encodePair(char a, char b) {
        auto [rowA, colA] = charPositions[a]; // Позиция первого символа
        auto [rowB, colB] = charPositions[b]; // Позиция второго символа

        if (rowA == rowB) {
            // Символы в одной строке
            return {matrix[rowA][(colA + 1) % 5], matrix[rowB][(colB + 1) % 5]};
        } else if (colA == colB) {
            // Символы в одном столбце
            return {matrix[(rowA + 1) % 5][colA], matrix[(rowB + 1) % 5][colB]};
        } else {
            // Прямоугольная перестановка
            return {matrix[rowA][colB], matrix[rowB][colA]};
        }
    }
    // Метод для дешифрования пары символов
    std::pair<char, char> decodePair(char a, char b) {
        auto [rowA, colA] = charPositions[a]; // Позиция первого символа
        auto [rowB, colB] = charPositions[b]; // Позиция второго символа

        if (rowA == rowB) {
            // Символы в одной строке
            return {matrix[rowA][(colA + 4) % 5], matrix[rowB][(colB + 4) % 5]};
        } else if (colA == colB) {
            // Символы в одном столбце
            return {matrix[(rowA + 4) % 5][colA], matrix[(rowB + 4) % 5][colB]};
        } else {
            // Прямоугольная перестановка
            return {matrix[rowA][colB], matrix[rowB][colA]};
        }
    }

public:
    // Конструктор, инициализирующий матрицу с использованием ключа
    PlayfairCipher(const std::string& key) {
        buildMatrix(key); // Построение матрицы с учетом ключа
    }

    // Метод шифрования текста
    std::string encrypt(const std::string& plainText) override {
        std::string cleanedText;
        for (char c : plainText) {
            if (c >= 'A' && c <= 'Z') {
                cleanedText += c; // Добавление букв верхнего регистра
            } else if (c >= 'a' && c <= 'z') {
                cleanedText += std::toupper(c); // Преобразование к верхнему регистру
            }
        }

        // Обработка повторяющихся букв и добавление 'X' для парности
        for (size_t i = 0; i < cleanedText.length(); i += 2) {
            if (i + 1 < cleanedText.length() && cleanedText[i] == cleanedText[i + 1]) {
                cleanedText.insert(i + 1, 1, 'X');  // Вставка 'X' между одинаковыми буквами
            }
        }
        if (cleanedText.length() % 2 != 0) {
            cleanedText += 'X';  // Добавляем 'X' для парности
        }

        std::string cipherText;
        for (size_t i = 0; i < cleanedText.length(); i += 2) {
            auto [first, second] = encodePair(cleanedText[i], cleanedText[i + 1]); // Шифрование пары символов
            cipherText += first;
            cipherText += second;
        }

        return cipherText; // Возвращаем зашифрованный текст
    }

    // Метод дешифрования текста
    std::string decrypt(const std::string& cipherText) override {
        std::string plainText;
        for (size_t i = 0; i < cipherText.length(); i += 2) {
            auto [first, second] = decodePair(cipherText[i], cipherText[i + 1]); // Дешифрование пары символов
            plainText += first;
            plainText += second;
        }

        // Удаление символов 'X', добавленных для разделения пар
        for (size_t i = 1; i < plainText.length(); ++i) {
            if (plainText[i] == 'X' && plainText[i - 1] == plainText[i + 1]) {
                plainText.erase(i, 1);
            }
        }

        // Удаление последнего символа 'X', если он был добавлен для парности
        if (!plainText.empty() && plainText.back() == 'X') {
            plainText.pop_back();
        }

        return plainText; // Возвращаем расшифрованный текст
    }
};


#endif // PLAYFAIR_CIPHER_H
