#include <stdio.h>

int main() {

    int V, P, A;
    scanf("%d %d %d", &V, &P, &A);

    int Fileira = (V - A) / P;

    if (Fileira < 1) {
        printf("Na mesa do professor!\n");
    }
    else {
        printf("%d\n", Fileira);
    }

    return 0;
}
