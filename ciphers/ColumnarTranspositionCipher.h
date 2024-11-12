#ifndef COLUMNAR_TRANSPOSITION_CIPHER_H
#define COLUMNAR_TRANSPOSITION_CIPHER_H

#include "EncryptionAlgorithm.h"
#include <vector>
#include <algorithm>

class ColumnarTranspositionCipher : public EncryptionAlgorithm {
private:
    std::string key;

    std::vector<int> getKeyOrder() {
    std::vector<std::pair<char, int>> keyOrder;
    for (size_t i = 0; i < key.length(); ++i) {
        keyOrder.emplace_back(key[i], i);
    }
    std::sort(keyOrder.begin(), keyOrder.end());

    std::vector<int> order;
    for (const auto& pair : keyOrder) {
        order.push_back(pair.second);
    }
    return order;
}


public:
    ColumnarTranspositionCipher(const std::string& key) : key(key) {}

    std::string encrypt(const std::string& plainText) override {
    int numCols = key.length();
    int numRows = (plainText.length() + numCols - 1) / numCols; // Округление вверх
    std::vector<std::string> grid(numRows, std::string(numCols, ' '));

    // Заполняем таблицу построчно
    for (size_t i = 0; i < plainText.length(); ++i) {
        grid[i / numCols][i % numCols] = plainText[i];
    }

    // Чтение символов по столбцам в порядке, определённом ключом
    std::string result;
    std::vector<int> keyOrder = getKeyOrder();
    for (int col : keyOrder) {
        for (int row = 0; row < numRows; ++row) {
            if (grid[row][col] != ' ') { // Пропуск пустых символов
                result += grid[row][col];
            }
        }
    }
    return result;
}

    std::string decrypt(const std::string& cipherText) override {
    int numCols = key.length();
    int numRows = (cipherText.length() + numCols - 1) / numCols;
    std::vector<std::string> grid(numRows, std::string(numCols, ' '));

    // Получение порядка ключа
    std::vector<int> keyOrder = getKeyOrder();
    size_t index = 0;

    // Заполнение таблицы по столбцам в порядке ключа
    for (int colIdx = 0; colIdx < numCols; ++colIdx) {
        int col = keyOrder[colIdx]; // Получаем индекс столбца по порядку ключа
        for (int row = 0; row < numRows; ++row) {
            if (index < cipherText.length()) {
                grid[row][col] = cipherText[index++];
            }
        }
    }

    // Чтение текста построчно
    std::string result;
    for (int row = 0; row < numRows; ++row) {
        for (int col = 0; col < numCols; ++col) {
            if (grid[row][col] != ' ') { // Пропуск пустых символов
                result += grid[row][col];
            }
        }
    }
    return result;
}



};

#endif // COLUMNAR_TRANSPOSITION_CIPHER_H
