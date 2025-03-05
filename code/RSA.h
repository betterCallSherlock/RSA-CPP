#ifndef RSA_H
#define RSA_H
#include <iostream>
#include <math.h>
#include <numeric>
#include <valarray>

// 使用幂模算法来计算 a^b mod c
long long modPow(long long a, long long b, long long c) {
    long long result = 1;
    while (b > 0) {
        if (b % 2 == 1) {  // 如果 b 是奇数
            result = (result * a) % c;
        }
        b = b / 2;  // b 减半
        a = (a * a) % c;
    }
    return result;
}
// RSA 加密
long long encrypt(long long message, long long e, long long n) {
    return modPow(message, e, n);
}
// RSA 解密
long long decrypt(long long cipher, long long d, long long n) {
    return modPow(cipher, d, n);
}

// Miller-Rabin素性测试
bool millerRabinTest(long long n, int k) {
    if (n < 2) return false;
    if (n == 2 || n == 3) return true;
    if (n % 2 == 0) return false;
    // 将 n - 1 写成 d * 2^r 的形式
    long long d = n - 1;
    int r = 0;
    while (d % 2 == 0) {
        d /= 2;
        r++;
    }
    // 重复 k 次测试
    for (int i = 0; i < k; i++) {
        long long a = 2 + rand() % (n - 4); // 随机选择 a, 2 <= a <= n-2
        long long x = modPow(a, d, n);      // 计算 x = a^d % n
        if (x == 1 || x == n - 1) continue;
        bool composite = true;
        for (int j = 0; j < r - 1; j++) {
            x = modPow(x, 2, n);
            if (x == n - 1) {
                composite = false;
                break;
            }
        }
        if (composite) return false;  // n 不是素数
    }
    return true;  // 通过 k 次测试，n 可能是素数
}


// 生成随机奇数
long long generateRandomOddNumber(int bitLength) {
    // srand(time(nullptr));
    long long num = rand() % (1LL << (bitLength - 1));  // 随机生成 bitLength 位的数
    num |= (1LL << (bitLength - 1));  // 设置最高位，确保是 bitLength 位的数
    num |= 1;  // 设置最低位，确保是奇数
    return num;
}
// 生成大素数
long long generateLargePrime(int bitLength, int accuracy) {
    long long prime;
    do {
        prime = generateRandomOddNumber(bitLength);  // 生成随机奇数
    } while (!millerRabinTest(prime, accuracy));     // 使用Miller-Rabin素性测试检查是否为素数
    return prime;
}
// 欧拉函数
long long EulerFunction(long long a, long long b) {
    return (a-1) * (b-1);
}
// 欧几里得算法计算模逆
long long modInverse(long long e, long long phi) {
    long long t = 0, newT = 1;
    long long r = phi, newR = e;
    while (newR != 0) {
        long long quotient = r / newR;
        std::swap(t, newT);
        newT -= quotient * t;
        std::swap(r, newR);
        newR -= quotient * r;
    }
    if (r > 1) {
        std::cerr << "e 不可逆！" << std::endl;
        return -1;
    }
    if (t < 0) t += phi;
    return t;
}
// 生成RSA公钥e私钥d
void generateRSAKeys(long long p, long long q, long long &n, long long &e, long long &d) {
    n = p * q;
    long long phi = (p - 1) * (q - 1);

    // 选择公钥指数 e
    e = 3;
    while (std::gcd(e, phi) != 1) {
        e += 2;
    }

    // 计算私钥 d
    d = modInverse(e, phi);
    if (d == -1) {
        std::cout<<"RSA Keys Generation Failed! Try Angin!"<<std::endl;
        std::cerr << "私钥生成失败！" << std::endl;
        return;
    }
    std::cout <<"PR(e):"<<e<<" PU(d):"<<d<<" n:"<<n<< std::endl;

}
#endif //RSA_H
