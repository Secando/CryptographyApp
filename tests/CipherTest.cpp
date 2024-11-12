#include "CipherTest.h"
#include "../ciphers/CaesarCipher.h"
#include "../ciphers/XORCipher.h"
#include "../ciphers/VernamCipher.h"
#include "../ciphers/TranspositionCipher.h"
#include "../ciphers/PlayfairCipher.h"
#include "../ciphers/AffineCipher.h"
#include "../ciphers/VigenereCipher.h"
#include "../ciphers/ColumnarTranspositionCipher.h"
#include "../ciphers/AtbashCipher.h"
#include "../ciphers/SubstitutionCipher.h"

void CipherTest::runAllTests() {
    testCaesarCipher();
    testXORCipher();
    testVernamCipher();
    testTranspositionCipher();
    testPlayfairCipher();
    testAffineCipher();
    testVigenereCipher();
    testColumnarTranspositionCipher();
    testAtbashCipher();
    testSubstitutionCipher();
}

bool CipherTest::assertEqual(const std::string& result, const std::string& expected, const std::string& testName) {
    if (result == expected) {
        std::cout << testName << " passed.\n";
        return true;
    } else {
        std::cout << testName << " failed. Expected: " << expected << ", but got: " << result << '\n';
        return false;
    }
}

void CipherTest::testCaesarCipher() {
    std::unique_ptr<EncryptionAlgorithm> cipher = std::make_unique<CaesarCipher>(3);
    std::string plainText = "HELLO";
    std::string encrypted = cipher->encrypt(plainText);
    std::string decrypted = cipher->decrypt(encrypted);

    assertEqual(encrypted, "KHOOR", "Caesar Cipher Encryption");
    assertEqual(decrypted, plainText, "Caesar Cipher Decryption");
}

void CipherTest::testXORCipher() {
    std::unique_ptr<EncryptionAlgorithm> cipher = std::make_unique<XORCipher>('K');
    std::string plainText = "HELLO";
    std::string encrypted = cipher->encrypt(plainText);
    std::string decrypted = cipher->decrypt(encrypted);

    assertEqual(decrypted, plainText, "XOR Cipher Decryption");
}

void CipherTest::testVernamCipher() {
    std::string key = "XMCKL";
    std::unique_ptr<EncryptionAlgorithm> cipher = std::make_unique<VernamCipher>(key);
    std::string plainText = "HELLO";
    std::string encrypted = cipher->encrypt(plainText);
    std::string decrypted = cipher->decrypt(encrypted);

    assertEqual(decrypted, plainText, "Vernam Cipher Decryption");
}

void CipherTest::testTranspositionCipher() {
    std::unique_ptr<EncryptionAlgorithm> cipher = std::make_unique<TranspositionCipher>();
    std::string plainText = "HELLO";
    std::string encrypted = cipher->encrypt(plainText);
    std::string decrypted = cipher->decrypt(encrypted);

    assertEqual(decrypted, plainText, "Transposition Cipher Decryption");
}

void CipherTest::testPlayfairCipher() {
    std::unique_ptr<EncryptionAlgorithm> cipher = std::make_unique<PlayfairCipher>("KEYWORD");
    std::string plainText = "HELLO";
    std::string encrypted = cipher->encrypt(plainText);
    std::string decrypted = cipher->decrypt(encrypted);

    assertEqual(decrypted, plainText, "Playfair Cipher Decryption");
}

void CipherTest::testAffineCipher() {
    std::unique_ptr<EncryptionAlgorithm> cipher = std::make_unique<AffineCipher>(5, 8);
    std::string plainText = "HELLO";
    std::string encrypted = cipher->encrypt(plainText);
    std::string decrypted = cipher->decrypt(encrypted);

    assertEqual(decrypted, plainText, "Affine Cipher Decryption");
}

void CipherTest::testVigenereCipher() {
    std::unique_ptr<EncryptionAlgorithm> cipher = std::make_unique<VigenereCipher>("K");
    std::string plainText = "PASSWORD";
    std::string encrypted = cipher->encrypt(plainText);
    std::string decrypted = cipher->decrypt(encrypted);

    assertEqual(decrypted, plainText, "Vigenere Cipher Decryption");
}

void CipherTest::testColumnarTranspositionCipher() {
    std::unique_ptr<EncryptionAlgorithm> cipher = std::make_unique<ColumnarTranspositionCipher>("KEY");
    std::string plainText = "HELLO";
    std::string encrypted = cipher->encrypt(plainText);
    std::string decrypted = cipher->decrypt(encrypted);

    assertEqual(decrypted, plainText, "Columnar Transposition Cipher Decryption");
}

void CipherTest::testAtbashCipher() {
    std::unique_ptr<EncryptionAlgorithm> cipher = std::make_unique<AtbashCipher>();
    std::string plainText = "HELLO";
    std::string encrypted = cipher->encrypt(plainText);
    std::string decrypted = cipher->decrypt(encrypted);

    assertEqual(decrypted, plainText, "Atbash Cipher Decryption");
}

void CipherTest::testSubstitutionCipher() {
    std::string key = "QWERTYUIOPASDFGHJKLZXCVBNM";
    std::unique_ptr<EncryptionAlgorithm> cipher = std::make_unique<SubstitutionCipher>(key);
    std::string plainText = "HELLO";
    std::string encrypted = cipher->encrypt(plainText);
    std::string decrypted = cipher->decrypt(encrypted);

    assertEqual(decrypted, plainText, "Substitution Cipher Decryption");
}
