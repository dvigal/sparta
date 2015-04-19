#include <stdio.h>

struct page {
	int a: 1;
	int b: 31;
};

typedef struct page page_t;

char *int2bin(int a, char *buffer, int buf_size) {
	buffer += (buf_size - 1);
	for (int i = 31; i >= 0; i--) {
		*buffer-- = (a & 1) + '0';
		a >>= 1;
	}
	return buffer;
}

void strreverse(char *begin, char *end) {
	char aux;
	while (end > begin) {
		aux = *end;
		*end-- = *begin;
		*begin++ = aux;
	}
}

void itoa(int value, char *str, int base) {
	static char num[] = "0123456789abcdefghijklmnopqrstuvwxyz";
	char *wstr = str;
	int sign;
	if (base < 2 || base > 35) {
		*wstr='\0';
		return;
	}
	if ((sign=value) < 0) {
		value = - value;
	}
	do {
		*wstr++=num[value%base];
	} while (value/=base);
	if (sign < 0) *wstr++='-';
	*wstr='\0';
	strreverse(str, wstr-1);
}


int main() {
	page_t p;
	p.a = 1;
	p.b = 10;
	char buffer[33];
 	buffer[32] = '\0';
	//int2bin(p.a, buffer, 32);
	itoa((1 << 4) | (0XFF & 1),buffer,2);
	printf("Size of page is %s\n", buffer);
	return 0;
}

