#include <bits/stdc++.h>
#include "rsa.h"

// 简单的哈希函数，用于生成消息的哈希值
long long simpleHash(const std::string &message) {
    long long hashValue = 0;
    for (char ch : message) {
        hashValue = (hashValue * 31 + ch) % 1000000007;  // 使用一个素数来限制哈希值大小
    }
    return hashValue;
}

// 数字签名生成
long long signMessage(const std::string &message, long long d, long long n) {
    // 生成消息的哈希值
    long long hashValue = simpleHash(message);
    // 使用私钥对哈希值加密生成签名
    long long signature = encrypt(hashValue, d, n);
    return signature;
}

// 验证签名
bool verifySignature(const std::string &message, long long signature, long long e, long long n) {
    // 解密签名，得到哈希值
    long long decryptedHash = decrypt(signature, e, n);
    // 生成消息的哈希值
    long long originalHashValue = simpleHash(message);
    // 比较解密后的哈希值与原始消息的哈希值是否相同
    return decryptedHash == originalHashValue;
}

int main() {
    //生成RSA公钥和私钥
    long long p = generateLargePrime(16, 5);  // 生成16位素数
    long long q = generateLargePrime(16, 5);
    long long n, e, d;
    generateRSAKeys(p, q, n, e, d);

    std::string message = "This is a test message for digital signature.";
    // 签名消息
    long long signature = signMessage(message, d, n);
    std::cout << "Signature: " << signature << std::endl;
    // 验证签名 -- 正确
    bool isValid = verifySignature(message, signature, e, n);
    std::cout << "Verification-1: ";
    if (isValid) std::cout << "Signature Verified Successful" << std::endl;
    else std::cout << "Signature Verified Failed" << std::endl;
    // 验证签名 -- 错误
    std::cout << "Verification-2: ";
    std::string errorMessage = message + "2022150057周楚皓";
    isValid = verifySignature(errorMessage, signature, e, n);
    if (isValid) std::cout << "Signature Verified Successful" << std::endl;
    else std::cout << "Signature Verified Failed" << std::endl;

    return 0;
}
