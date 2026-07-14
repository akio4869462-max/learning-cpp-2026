#include <stdlib.h>
#include <stdio.h>

size_t my_strlen(const char *s);

int main(){
    char s[] = "abc";            // {'a','b','c','\0'} の4バイト
    const char *msg = "hello";   // 文字列リテラルは書き換え禁止 → const必須

    printf("n: %d\n", (int)my_strlen(s));
    printf("n: %d\n", (int)my_strlen(msg));

    return 0;
}

size_t my_strlen(const char *s) {
    size_t n = 0;
    while (s[n] != '\0') n++;
    return n;
}