#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
	char *p;
	p = (char *)malloc(10 * sizeof(char));
	if (p == NULL)
	return -1;
	strcpy(p, "123456789");
	p[10] = 'a'; //此句越界 (1)
	p[14] = 'A'; //此句越界
	p[15] = 'B'; //此句越界
//	p[10] = '\xfd'; //此句越界 (2)
	printf("addr:%p\n", p);
	for (int i = -4; i < 16; i++) //注意，只有 0-9 是合理范围，其余都是越界读
	printf("%p:%02x\n", (p+i), p[i]);
	free(p);//(3)
	return 0;
}