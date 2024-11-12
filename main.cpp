#include <iostream>
#include <iomanip> // Для std::hex и std::setw
#include <sstream> // Для std::ostringstream
#include <memory>
#include <string>
#include "ciphers/CaesarCipher.h"
#include "ciphers/XORCipher.h"
#include "ciphers/VernamCipher.h"
#include "ciphers/TranspositionCipher.h"
#include "ciphers/PlayfairCipher.h"
#include "ciphers/AffineCipher.h"
#include "ciphers/VigenereCipher.h"
#include "ciphers/ColumnarTranspositionCipher.h"
#include "ciphers/AtbashCipher.h"  // Не забывайте подключить заголовочный файл для Атбаш
#include "ciphers/SubstitutionCipher.h"

// Функция для преобразования строки в шестнадцатеричное представление
std::string toHex(const std::string& str) {
    std::ostringstream hexStream;
    for (unsigned char c : str) {
        hexStream << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(c);
    }
    return hexStream.str();
}

int main() {
    int choice;
    std::cout << "Выберите алгоритм шифрования:\n";
    std::cout << "1. Шифр Цезаря\n";
    std::cout << "2. XOR шифр\n";
    std::cout << "3. Шифр Вернама\n";
    std::cout << "4. Шифр перестановки\n";
    std::cout << "5. Шифр Плейфера\n";
    std::cout << "6. Аффинный шифр\n";
    std::cout << "7. Шифр Виженера\n";
    std::cout << "8. Шифр столбцовой транспозиции\n";
    std::cout << "9. Шифр Атбаш\n";  // Добавим шифр Атбаш в список
    std::cout << "10. Шифр Шифр подстановки\n";  // Добавим шифр Атбаш в список
    std::cout << "Введите номер алгоритма: ";
    std::cin >> choice;

    std::unique_ptr<EncryptionAlgorithm> cipher;
    bool useHexOutput = false;

    std::cin.ignore();  // Очистим буфер перед получением строки

    if (choice == 1) {
        int shift;
        std::cout << "Введите сдвиг для шифра Цезаря: ";
        std::cin >> shift;
        std::cin.ignore(); 
        cipher = std::make_unique<CaesarCipher>(shift);
    } else if (choice == 2) {
        
        char key;
        std::cout << "Введите ключ для XOR шифра: ";
        std::cin >> key;
        std::cin.ignore();
        cipher = std::make_unique<XORCipher>(key);
        useHexOutput = true;
    } else if (choice == 3) {
        std::cin.ignore();
        std::string key;
        std::cout << "Введите ключ для шифра Вернама (той же длины, что и текст): ";
        std::getline(std::cin, key);
        cipher = std::make_unique<VernamCipher>(key);
        useHexOutput = true;
    } else if (choice == 4) {
        cipher = std::make_unique<TranspositionCipher>();
    } else if (choice == 5) {
        std::cin.ignore();
        std::string key;
        std::cout << "Введите ключ для шифра Плейфера: ";
        std::getline(std::cin, key);
        cipher = std::make_unique<PlayfairCipher>(key);
    } else if (choice == 6) {
        int a, b;
        std::cout << "Введите значения a и b для аффинного шифра: ";
        std::cin >> a >> b;
        try {
            cipher = std::make_unique<AffineCipher>(a, b);
        } catch (const std::exception& e) {
            std::cerr << "Ошибка: " << e.what() << '\n';
            return 1;
        }
    } else if (choice == 7) {
        std::cin.ignore();
        std::string key;
        std::cout << "Введите ключ для шифра Виженера: ";
        std::getline(std::cin, key);
        cipher = std::make_unique<VigenereCipher>(key);
    } else if (choice == 8) {
        std::cin.ignore();
        std::string key;
        std::cout << "Введите ключ для шифра столбцовой транспозиции: ";
        std::getline(std::cin, key);
        cipher = std::make_unique<ColumnarTranspositionCipher>(key);
    } else if (choice == 9) {
        std::cout << "Вы выбрали шифр Атбаш." << std::endl;
        cipher = std::make_unique<AtbashCipher>();  // Шифр Атбаш
    } else if (choice == 10) {
        std::string key;
        std::cout << "Введите ключ для шифра подстановки (26 символов, без пробелов): ";
        std::getline(std::cin, key);
            if (key.length() != 26) {
            std::cerr << "Ошибка: Ключ должен содержать 26 символов.\n";
            return 1;
            }
        cipher = std::make_unique<SubstitutionCipher>(key);  // Шифр подстановки 
    }   else {
        std::cerr << "Неверный выбор!\n";
        return 1;
    }

    std::string text;
    std::cout << "Введите текст для шифрования: ";
    std::getline(std::cin, text);  // Получаем текст для шифрования

    try {
        std::string encryptedText = cipher->encrypt(text);

        if (useHexOutput) {
            std::string encryptedHex = toHex(encryptedText);
            std::cout << "Зашифрованный текст (в шестнадцатеричном формате): " << encryptedHex << '\n';
        } else {
            std::cout << "Зашифрованный текст: " << encryptedText << '\n';
        }

        std::string decryptedText = cipher->decrypt(encryptedText);
        std::cout << "Расшифрованный текст: " << decryptedText << '\n';
    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << '\n';
    }

    return 0;
}
