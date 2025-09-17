#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int *fib_seq;
int n;

void *generate_fib(void *arg)
{
    fib_seq[0] = 0;
    if (n > 1)
        fib_seq[1] = 1;
    for (int i = 2; i < n; i++)
        fib_seq[i] = fib_seq[i - 1] + fib_seq[i - 2];
    pthread_exit(0);
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s <count>\n", argv[0]);
        return 1;
    }
    n = atoi(argv[1]);
    fib_seq = malloc(n * sizeof(int));

    pthread_t tid;
    pthread_create(&tid, NULL, generate_fib, NULL);
    pthread_join(tid, NULL);

    for (int i = 0; i < n; i++)
        printf("%d ", fib_seq[i]);
    printf("\n");

    free(fib_seq);
    return 0;
}
