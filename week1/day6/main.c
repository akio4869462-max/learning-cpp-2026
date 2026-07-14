#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "parse.h"
#include "collect.h"

int main(int argc, char *argv[]){
    if(argc>=2){
        if(!strcmp(argv[1], "filter")){
            if(argc!=4){
                fprintf(stderr, "引数の数が間違っています。\n");
                return 1;
            }
        }else{
            if(argc!=3){
                fprintf(stderr, "引数の数が間違っています。\n");
                return 1;
            }
        }
    }else{
        fprintf(stderr, "引数の数が間違っています。\n");
        return 1;
    }
    FILE *fp = fopen(argv[2], "r");   // "r" = 読み込みモード
    if (fp == NULL) {
        // 開けなかった(ファイルが無い等)。mallocのNULLチェックと同じ発想
        return 1;
    }

    SensorLog *sl = slog_create(3);

    char line[256];                      // 1行分のバッファ
    while (fgets(line, sizeof(line), fp) != NULL) {
        // line に1行分の文字列が入る(末尾に改行'\n'付き)
        int ts, id, value;
        int n = sscanf(line, "%d,%d,%d", &ts, &id, &value);
        if(n!=3){
            fprintf(stderr, "データが3つではありません\n");
        }else{
            slog_push(sl, ts, id, value);
        }
    }
    if(!strcmp(argv[1],"stats")){
        collect_stats(sl);
    }else if(!strcmp(argv[1],"filter"))
        {collect_filter(sl, (size_t)atoi(argv[3]));
    }else if(!strcmp(argv[1],"worst")){
        collect_worst(sl);
    }else{
        fprintf(stderr, "コマンドが間違っています。\n");
        return 1;
    }
    slog_destroy(sl);
    fclose(fp);                          // 開けたら必ず閉じる(free と同じ発想)

    return 0;
}