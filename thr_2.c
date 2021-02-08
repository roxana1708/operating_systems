#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int m1[4][4], m2[4][4], result[4][4];

typedef struct arg {
	int x;
	int y;
}args;

void *calcElem(void *arg){
	
	args* p = arg;

	for(int i = 0; i < 4; i++) {
		result[p->x][p->y] += m1[p->x][i] * m2[i][p->y];
	}
}

int main() {

	pthread_t thread[16];
	int thr_index = 0;
	args p[4*4];

	for(int i = 0; i < 4; i++) {
                for(int j = 0; j < 4; j++) {
                        m1[i][j] = 1;
			m2[i][j] = 2;
                }
        }

	for(int i = 0; i < 4; i++) {
		for(int j = 0; j < 4; j++) {
			p[thr_index].x = i;
			p[thr_index].y = j;

			if(pthread_create(&thread[thr_index], NULL, calcElem, (void *) &p[thr_index])) {
				perror(NULL);
				return errno;
			}

			thr_index++;
		}
	}

	for(int i = 0; i < 16; i++)
		pthread_join(thread[i], NULL);

	for(int i = 0; i < 4; i++) {
		for(int j = 0; j < 4; j++) {
			printf("%d", result[i][j]);
		}
		printf("\n");
	}
	return 0;
}
