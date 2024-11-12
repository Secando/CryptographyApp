#ifndef CIPHER_TEST_H
#define CIPHER_TEST_H

#include <iostream>
#include <string>
#include <memory>
#include "../ciphers/EncryptionAlgorithm.h"

class CipherTest {
public:
    void runAllTests();  // Метод для запуска всех тестов
    
    void testCaesarCipher();
    void testXORCipher();
    void testVernamCipher();
    void testTranspositionCipher();
    void testPlayfairCipher();
    void testAffineCipher();
    void testVigenereCipher();
    void testColumnarTranspositionCipher();
    void testAtbashCipher();
    void testSubstitutionCipher();

private:
    bool assertEqual(const std::string& result, const std::string& expected, const std::string& testName);
};

#endif // CIPHER_TEST_H
