#include <iostream>
#include <iomanip> // Для std::hex и std::setw
#include <sstream> // Для std::ostringstream
#include <memory>
#include <string>
#include "EncryptionAlgorithm.h"
#include "CaesarCipher.h"
#include "XORCipher.h"
#include "VernamCipher.h"
#include "TranspositionCipher.h"
#include "PlayfairCipher.h"
#include "AffineCipher.h"
#include "VigenereCipher.h"
#include "ColumnarTranspositionCipher.h"
#include "AtbashCipher.h"  // Не забывайте подключить заголовочный файл для Атбаш
#include "SubstitutionCipher.h"
#include "../Utils.h"


class CipherFactory {
public:
    static std::unique_ptr<EncryptionAlgorithm> createCipher(int choice, const std::string& key, bool& useHexOutput) {
        switch (choice) {
            case 1:  // Caesar Cipher (сдвиг должен быть числом)
                try {
                    int shift = std::stoi(key);
                    return std::make_unique<CaesarCipher>(shift);
                } catch (const std::invalid_argument&) {
                    throw std::invalid_argument("Ошибка: ключ для шифра Цезаря должен быть числом.");
                }

            case 2:  // XOR шифр (один символ)
            useHexOutput = true;
                if (key.size() == 1) {
                    return std::make_unique<XORCipher>(key[0]);
                } else {
                    throw std::invalid_argument("Ошибка: ключ для XOR шифра должен быть одним символом.");
                }

            case 3:  // Шифр Вернама (текстовый ключ той же длины, что и текст)
            useHexOutput = true;
                return std::make_unique<VernamCipher>(key);

            case 4:  // Шифр перестановки (без ключа)
                return std::make_unique<TranspositionCipher>();

            case 5:  // Шифр Плейфера (текстовый ключ)
                return std::make_unique<PlayfairCipher>(key);

            case 6:  // Аффинный шифр (два числовых параметра, формат a,b)
                try {
                    size_t commaPos = key.find(',');
                    if (commaPos == std::string::npos) {
                        throw std::invalid_argument("Ошибка: ключ для аффинного шифра должен содержать два числа, разделенных запятой.");
                    }
                    int a = std::stoi(key.substr(0, commaPos));
                    int b = std::stoi(key.substr(commaPos + 1));
                    return std::make_unique<AffineCipher>(a, b);
                } catch (const std::invalid_argument&) {
                    throw std::invalid_argument("Ошибка: ключ для аффинного шифра должен быть в формате 'a,b'.");
                }

            case 7:  // Шифр Виженера (текстовый ключ)
                return std::make_unique<VigenereCipher>(key);

            case 8:  // Шифр столбцовой транспозиции (текстовый ключ)
                return std::make_unique<ColumnarTranspositionCipher>(key);

            case 9:  // Шифр Атбаш (без ключа)
                return std::make_unique<AtbashCipher>();

            case 10:  // Шифр подстановки (алфавитный ключ из 26 символов)
                if (key.length() == 26) {
                    return std::make_unique<SubstitutionCipher>(key);
                } else {
                    throw std::invalid_argument("Ошибка: ключ для шифра подстановки должен содержать ровно 26 символов.");
                }

            default:
                throw std::invalid_argument("Неверный выбор шифра");
        }
    }
};
