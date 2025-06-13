#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("用法: %s <源文件> <目标文件>\n", argv[0]);
        return 1;
    }

    FILE *src = fopen(argv[1], "rb");
    if (!src) {
        perror("打开源文件失败");
        return 1;
    }

    FILE *dst = fopen(argv[2], "wb");
    if (!dst) {
        perror("打开目标文件失败");
        fclose(src);
        return 1;
    }

    int ch;
    while ((ch = getc(src)) != EOF) {
        if (putc(ch, dst) == EOF) {
            perror("写入目标文件失败");
            fclose(src);
            fclose(dst);
            return 1;
        }
    }

    fclose(src);
    fclose(dst);
    printf("文件复制完成。\n");
    return 0;
}