/**
 * Amazing John的P30拍照贼棒
 * in_4
*/

#define MXN (10000020)

#define OO ("08.in")

#define N (1000000)
#define A (1000000)

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <map>

int c;

signed main() {
    freopen(OO, "w", stdout);

    srand(time(NULL));

    printf("%d\n", N);

    printf("%d %d\n", c = (rand() % (N - 1)) + 2, 0);
    for (int i = 2, v; i <= N; ++i) {
        do
            v = (rand() % (i - 1)) + 1;
        while (c == i && v == 1);
        printf("%d %d\n", v, rand() % A);
    }
}