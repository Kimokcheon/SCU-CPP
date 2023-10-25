#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
using namespace std;
int main(){
    char *p;
    p = new(nothrow) char[10];
    if (p == NULL)
        return -1;
    strcpy(p, "123456789");
    p[10] = 'a'; //此句越界 (1)
    p[14] = 'A'; //此句越界
    p[15] = 'B'; //此句越界
    p[10] = '\xfd'; //此句越界 (2)
    cout << "addr:" << hex << (void *)(p) << endl;
    for (int i = -4; i < 16; i++) //注意，只有 0-9 是合理范围，其余都是越界读
    cout << hex << (void *)(p + i) << ":" << int(p[i]) << endl;
    delete[]p;//(3)
    return 0;
}