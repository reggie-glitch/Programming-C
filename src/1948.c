#include <stdio.h>

int delitsya(int a, int b);
int prostoe(int n);
int max_prostoe(int n);

int main() {
    int a;
    int result = 0;  // для хранения результата
    int res = scanf("%d", &a);

    if (res != 1) {
        printf("n/a\n");
        result = 1;
    } else if (a == 0) {
        printf("n/a\n");
        result = 0;
    } else if (a == 1 || a == -1) {
        printf("1\n");
        result = 0;
    } else {
        int otvet = max_prostoe(a);
        printf("%d\n", otvet);
        result = 0;
    }

    return result;
}

int delitsya(int a, int b) {
    int result = 0;

    if (a < 0) {
        a = -a;
    }
    if (b < 0) {
        b = -b;
    }

    if (b == 0) {
        printf("n/a");
        // result уже 0
    } else {
        int ost = a;
        while (ost >= b) {
            ost = ost - b;
        }
        if (ost == 0) {
            result = 1;
        }
    }

    return result;
}

int prostoe(int n) {
    int result = 1;

    if (n <= 1) {
        result = 0;
    } else if (n == 2) {
        result = 1;
    } else {
        for (int i = 2; i < n; i++) {
            if (delitsya(n, i)) {
                result = 0;
                break;
            }
        }
    }

    return result;
}

int max_prostoe(int n) {
    int res = 1;

    if (n < 0) {
        n = -n;
    }

    for (int i = 2; i <= n; i++) {
        if (delitsya(n, i) == 1 && prostoe(i) == 1) {
            res = i;
        }
    }

    return res;
}