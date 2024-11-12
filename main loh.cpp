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
#include "ciphers/CipherFactory.cpp"






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

    std::cin.ignore();

std::string key;
std::cout << "Введите ключ для шифра: ";
std::getline(std::cin, key);

bool useHexOutput = false;
std::unique_ptr<EncryptionAlgorithm> cipher;

try {
    cipher = CipherFactory::createCipher(choice, key, useHexOutput);

    std::string text;
    std::cout << "Введите текст для шифрования: ";
    std::getline(std::cin, text);

    std::string encryptedText = cipher->encrypt(text);

    if (useHexOutput) {
        std::string encryptedHex = Utils::toHex(encryptedText);
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
