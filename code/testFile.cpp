#include <bits/stdc++.h>
#include "rsa.h"
using namespace std;
// 加密文件
void encryptFile(const std::string &inputFileName, const std::string &outputFileName, long long e, long long n) {
    std::ifstream inputFile(inputFileName, std::ios::binary);
    std::ofstream outputFile(outputFileName, std::ios::binary);

    if (!inputFile || !outputFile) {
        std::cerr << "无法打开文件！" << std::endl;
        return;
    }

    char byte;// 字节分组
    while (inputFile.get(byte)) {
        long long message = static_cast<unsigned char>(byte);  // 转换为无符号类型来处理字符
        long long encryptedMessage = encrypt(message, e, n);
        outputFile.write(reinterpret_cast<const char *>(&encryptedMessage), sizeof(encryptedMessage));
    }

    inputFile.close();
    outputFile.close();
    std::cout << "File Encrypted:"<<outputFileName << std::endl;
}

// 解密加密的文件
void decryptFile(const std::string &inputFileName, const std::string &outputFileName, long long d, long long n) {
    std::ifstream inputFile(inputFileName, std::ios::binary);
    std::ofstream outputFile(outputFileName, std::ios::binary);

    if (!inputFile || !outputFile) {
        std::cerr << "无法打开文件！" << std::endl;
        return;
    }

    long long encryptedMessage;
    while (inputFile.read(reinterpret_cast<char *>(&encryptedMessage), sizeof(encryptedMessage))) {
        long long decryptedMessage = decrypt(encryptedMessage, d, n);
        char byte = static_cast<char>(decryptedMessage);
        outputFile.put(byte);
    }

    inputFile.close();
    outputFile.close();
    std::cout << "File Decrypted:"<< outputFileName << std::endl;
}

int main() {
    long long p = generateLargePrime(16, 5);  // 生成16位素数
    long long q = generateLargePrime(16, 5);
    long long n, e, d;
    generateRSAKeys(p, q, n, e, d);

    std::string inputFileName = "2022150057.txt";   // 待加密的文件
    std::string encryptedFileName = "encrypted_2022150057.txt";  // 加密后的文件
    std::string decryptedFileName = "decrypted_2022150057.txt";  // 解密后的文件

    // 加密文件
    encryptFile(inputFileName, encryptedFileName, e, n);

    // 解密文件
    decryptFile(encryptedFileName, decryptedFileName, d, n);

    return 0;
}
