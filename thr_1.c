#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int string_length(char *pointer) {
	int i = 0;
	while(*(pointer+i) != '\0')
		i++;
	return i;
}

void *
reverse_hello(void *v) {
	char *hello = (char *)v;
	int length, i;
	char *begin, *end, temp;

	length = string_length(hello);
	begin = hello;
	end = hello;

	for(i = 0; i < length-1; i++)
		end++;

	for(i = 0; i < length/2; i++) {
		temp = *end;
		*end = *begin;
		*begin = temp;

		begin++;
		end--;
	}
	printf("%s\n", hello);	
}

int main() {
	char s[100];

	scanf("%s", s);

	pthread_t thr;
	if(pthread_create(&thr, NULL, reverse_hello, s)) {
		perror(NULL);
		return errno;
	}
	void *result;
	if(pthread_join(thr, &result)) {
		perror(NULL);
		return errno;
	}
	
	return 0;
}
