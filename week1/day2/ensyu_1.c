#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

size_t my_strlen(const char *s);
void my_strcpy(char *dst, size_t dst_size, const char *src);
int my_strcmp(const char *s1, const char *s2);

int main(){
    char s1[] = "abc";            // {'a','b','c','\0'} の4バイト
    char s2[] = "adc";            // {'a','b','c','\0'} の4バイト
    const char *msg = "hello";   // 文字列リテラルは書き換え禁止 → const必須

    
    printf("n: %d\n", (int)my_strlen(s1));
    printf("n: %d\n", (int)my_strlen(msg));
    
    char copy[16];
    my_strcpy(copy, sizeof(copy), msg);

    printf("cmp: %d\n", (int)my_strcmp(s1, s2));
    
    printf("copy: %s\n", copy);
    
    return 0;
}

size_t my_strlen(const char *s) {
    size_t n = 0;
    while (s[n] != '\0') n++;
    return n;
}

void my_strcpy(char *dst, size_t dst_size, const char *src) {
    size_t i=0;
    if (dst_size == 0) return;

    while(src[i] != '\0' && i < dst_size-1){
        dst[i] = src[i];
        i++;
    }
    dst[i] = '\0'; 
}

int my_strcmp(const char *s1, const char *s2) {
    size_t n = 0;
    while (s1[n] == s2[n])
    {
        if(s1[n] == '\0')
            return 0;
        n++;
    }
    return (s1[n] - s2[n]);
}