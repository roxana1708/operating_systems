#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>
 
//#define MAX_SEQ_SIZE 1000

void error_exit(const char *msg) {
    if (errno)
        perror(msg);
    else
        fprintf(stderr, "%s\n", msg);
    exit(EXIT_FAILURE);
}

int *calcCollatz(int n, void* ptr_c) {
    //int *collatzSeq = malloc(1024 * sizeof *collatzSeq);
    //int j = 0;
    while (n != 1) {
        if (n % 2 == 0)
            n /= 2;
        else
            n = (3 * n) + 1;
        if (j == 1024)
            error_exit("MAX_SEQ_SIZE reached");
        collatzSeq[j++] = n;
    }
    return collatzSeq;
}
 
int main(int argc, char *argv[]) {
    const int SIZE = 4096; //size in bytes of Shared Memory Object
    const char *name = "myshm"; //name of the Shared memory Object

    //if (argc != 2) error_exit("Usage: shmcollatz N\n");

    int shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
    ftruncate(shm_fd, SIZE); //configure the size of the shm

    char *ptr= mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (ptr == MAP_FAILED) error_exit("map failed");
    char *pshm = ptr;

    pshm += sprintf(pshm, "%s", argv[1]);

    int size = 0;
    int *a = calcCollatz(atoi(argv[1]), &size);
    memcpy(pshm, a, size * sizeof *a);
    pshm += size * sizeof *a;

    printf("%s", pshm);
    
    return 0;
}
