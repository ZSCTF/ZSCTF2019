#include <stdio.h>
#include <math.h>

void swap(long long *a, long long *b)
{
    *a ^= *b;
    *b ^= *a;
    *a ^= *b;
}

unsigned long long calculate(long long a, long long b, long long c, long long d, long long p, long long m)
{
    if (a > b)
        swap(&a, &b);
    if (c > d)
        swap(&c, &d);
    if (b - a + 1 < d - c + 1)
    {
        swap(&a, &c);
        swap(&b, &d);
    }

    unsigned long long left = 0;
    long long kl1 = ceil(1.0 * (a + c - m) / p),
              kl2 = floor(1.0 * (a + d - m) / p);
    if (kl1 <= kl2)
    {
        long long sl = (kl1 * p + m - a) - c + 1,
                  nl = kl2 - kl1 + 1;
        left = (sl + (sl + p * (nl - 1))) * nl / 2;
    }

    unsigned long long right = 0;
    long long kr1 = ceil(1.0 * (b + c - m) / p),
              kr2 = floor(1.0 * (b + d - m) / p);
    if (kr1 <= kr2)
    {
        long long sr = d - (kr2 * p + m - b) + 1,
                  nr = kr2 - kr1 + 1;
        right = (sr + (sr + p * (nr - 1))) * nr / 2;
    }

    unsigned long long middle = 0;
    if (d - c + 1 != b - a + 1)
    {
        long long km1 = ceil(1.0 * ((a + 1) + d - m) / p),
                  km2 = floor(1.0 * ((b - 1) + c - m) / p);
        if (km1 <= km2)
        {
            long long nm = km2 - km1 + 1;
            middle = nm * (d - c + 1);
        }
    }

    if ((a + d) % p == m && d - c + 1 == b - a + 1)
    {
        left -= d - c + 1;
    }

    unsigned long long ans = left + middle + right;
    return ans;
}

unsigned long long calculate_slow(long long a, long long b, long long c, long long d, long long p, long long m)
{
    unsigned long long ans = 0;
    for (long long i = (a < b ? a : b); i <= (a < b ? b : a); i++)
    {
        for (long long j = (c < d ? c : d); j <= (c < d ? d : c); j++)
        {
            long long t = (i & j) + (i | j);
            while (t >= p)
                t -= p;
            ans += (t == m);
        }
    }
    return ans;
}

unsigned int f(const char *str)
{
    return ((str[3] << 8 | str[2]) << 8 | str[1]) << 8 | str[0];
}

int main()
{
    if (calculate(3, 19, 6, 22, 3, 1) != 97 ||
        calculate(15, 16, 21, 22, 10, 6) != 1 ||
        calculate(15, 76, 13, 13, 3, 0) != 20 ||
        calculate(174, 174, 219, 219, 131, 0) != 1)
    {
        puts("sorry");
        return 0;
    }

    unsigned long long F, L, A, G;
    F = calculate(2, 30, 1, 11, 3, 1) *
        calculate(1, 0x20191109, 1, 0x19260817, 0xcc, 0x3f);
    L = calculate(0x00010203, 0x04050607, 0x08090a0b, 0x0c0d0e0f, 123456, 78910) *
        calculate(1, 1, 1, 1, 1, 0);
    A = calculate(f("welcome"), f("to  "), f("zsctf"), f("2019"), 3, 2) *
        calculate(f("have"), f("fun"), f("solving"), f("problems"), 7, 5);
    G = calculate(f("zhakul"), f("melody"), f("techial"), f("docupa"), f("tql"), f("nb")) *
        calculate(f("when"), f("will"), f("zhakul"), f("update"), f("  his"), f("  blog?"));

    F = (F & 0xf1a9f1a9f1a9f1a9) ^ (L | 0x123456789abcdef);
    L = (L >> (A & 0b1010)) ^ (L << (G & 0b0101));
    A = F ^ L;
    G = (F & L) ^ (A | G);

    char flag[20] = {0};
    for (int i = 0; i < 16; i += 2)
    {
        flag[i] = (((F * L + A * G) ^ 0xa9235d97c0ffa702) >> (56 - (i << 2))) & 0xff;
        flag[i | 1] = (((F - L * A - G) ^ 0x36e8e2750a5548e5) >> (56 - (i << 2))) & 0xff;
    }
    printf("flag is zsctf{%s}", flag);
    return 0;
}