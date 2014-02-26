#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

double my_rand() {
    return 1.0 * rand() / RAND_MAX;
}

int main() {
    srand(time(NULL));
    double l0 = 0.3, H = 1, q = 0.6, position = 0;
    int neutron_max = 30000000, passed = 0, neutron;
    for (neutron = 0; neutron < neutron_max; neutron++) {
        position = 0;
        while (position < H) {
            position += -l0*log(1-my_rand());
            if (position < H && my_rand() < 1 - q)
                break;
            if (position > H)
                passed++;
        }
    }
    double ans = 1.0 * passed / neutron_max;
    printf("I = %lf", ans);
    return 0;
}
