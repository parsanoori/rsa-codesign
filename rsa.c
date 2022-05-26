#include <stdio.h>

// gcd memory map
volatile unsigned long long int *gcd_in_a = (unsigned long long int *) 0x80000000;
volatile unsigned long long int *gcd_in_b = (unsigned long long int *) 0x80000008;
volatile unsigned long long int *gcd_out = (unsigned long long int *) 0x80000010;
volatile unsigned  int *gcd_load = (unsigned int *) 0x80000018;
volatile unsigned  int *gcd_done = (unsigned int *) 0x8000001c;

// power memory map
volatile unsigned long long int *pow_in_b = (unsigned long long int *) 0x80000020;
volatile unsigned long long int *pow_in_e = (unsigned long long int *) 0x80000028;
volatile unsigned long long int *pow_in_m = (unsigned long long int *) 0x80000030;
volatile unsigned long long int *pow_out = (unsigned long long int *) 0x80000038;
volatile unsigned  int *pow_load = (unsigned int *) 0x80000040;
volatile unsigned  int *pow_done = (unsigned int *) 0x80000044;

// prototypes
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
    unsigned long long int z = lcm(p-1,q-1); // results in smaller d than just multiplying them

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
    // printf("[debug] e=%lld d=%lld z=%lld\n", e, d, z);
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

unsigned long long int gcd(unsigned long long int a, unsigned long long int b){
    *gcd_in_a = a;
    *gcd_in_b = b;
    *gcd_load = 1;
    while (*gcd_done !=1 );
    long long int result = *gcd_out;
    *gcd_load = 0;
    // printf("[debug] gcd(%lld, %lld) = %lld\n", a, b, result);
    return result;
}

unsigned long long int lcm(unsigned long long int a, unsigned long long int h){
    return (a*h)/gcd(a, h);
}

unsigned long long power(unsigned long long b, unsigned long long e, unsigned long long m){
    *pow_in_b = b;
    *pow_in_e = e;
    *pow_in_m = m;
    *pow_load = 1;
    while (*pow_done !=1 );
    long long int result = *pow_out;
    *pow_load = 0;
    // printf("[debug] pow(%lld, %lld, %lld) = %lld\n", b, e, m, result);
    return result;
}
