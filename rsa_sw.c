#include <stdio.h>

unsigned long long int gcd(unsigned long long int, unsigned long long int);
unsigned long long int lcm(unsigned long long int, unsigned long long int);
unsigned long long power(unsigned long long, unsigned long long, unsigned long long);

int main(){
    // Two random prime numbers
    unsigned long long int p = 5;
    unsigned long long int q = 7;
    // First part of public key
    unsigned long long int n = p*q;
    // Finding other part of public key
    unsigned int long long e = 2;
    // unsigned long long int z = lcm(p-1,q-1);
    unsigned long long int z = (p-1)*(q-1);

    // point1

    while (e < z) {
        // e must be co-prime to z and smaller than z
        if (gcd(e, z)==1)
            break;
        else
            e++;
    }

    //point 2

    unsigned long long int d = 2;
    while (d < z) {
        if ((d*e)%z == 1)
            break;
        else
            d++;
    }
    printf("e=%lld d=%lld z=%lld\n", e, d, z);
    // point 3

    // Message to be encrypted
    unsigned long long msg = (long long int)'!';
    printf("Message data = %lld\n", msg);

    // point 4

    // Encryption c = (msg ^ e) % n
    unsigned long long c  = power(msg, e, n);
    // c %= n;
    printf("Encrypted data = %lld\n", c);

    // point 5

    // Decryption m = (c ^ d) % n
    unsigned long long m = power(c, d, n);
    // m %= n;
    printf("Original Message Sent = %lld\n", m);

    return 0;
}

unsigned long long int gcd(unsigned long long int a, unsigned long long int h){
    unsigned long long int a_f = a;
    unsigned long long int h_f = h;
    unsigned int temp;
    while (1) {
        temp = a%h;
        if (temp == 0) {
            printf("[debug] gcd(%lld, %lld) = %lld\n", a_f, h_f, h);
            return h;
            }
        a = h;
        h = temp;
    }
}

unsigned long long int lcm(unsigned long long int a, unsigned long long int h){
    return (a*h)/gcd(a, h);
}

unsigned long long power(unsigned long long a, unsigned long long n, unsigned long long m){
    unsigned long long pow = a;
    for (int i=1; i<n; i++){
        pow = (pow*a)%m;
    }
    printf("[debug] pow(%lld, %lld, %lld) = %lld\n", a, n, m, pow);
    return pow;
}
